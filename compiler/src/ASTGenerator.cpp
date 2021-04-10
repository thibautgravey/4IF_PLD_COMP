/*******************************************************************************
                           ASTGenerator  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <ASTGenerator> (fichier ASTGenerator.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>

using namespace std;

//------------------------------------------------------ Include personnel
#include "ASTGenerator.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

antlrcpp::Any ASTGenerator::visitAxiom(ifccParser::AxiomContext * ctx) {
    return visit(ctx->prog());
} //----- Fin de visitAxiom

antlrcpp::Any ASTGenerator::visitProg(ifccParser::ProgContext * ctx) {

    program = new Program(ctx->start->getLine());

    Instr * instr;

    for (int i = 0; i < ctx->def_func().size(); i++) {
        instr = (Instr *)visit(ctx->def_func(i));
        if (instr != nullptr) {
            program->AddInstr(instr);
        }
    }
    return program;
} //----- Fin de visitProg

antlrcpp::Any ASTGenerator::visitLine(ifccParser::LineContext * ctx) {
    Instr * instr;
    if (ctx->return_stmt()) {
        instr = (Instr *)visit(ctx->return_stmt());
    } else if (ctx->var_decl()) {
        vector<Instr *> retVecInstr;
        vector<Expr *> retVarDecl = visit(ctx->var_decl()).as<vector<Expr *>>();
        for (Expr * expr : retVarDecl) {
            if (checkExpr(expr)) {
                retVecInstr.push_back(new ExprInstr(ctx->start->getLine(), expr, currentScope));
            }
        }
        return retVecInstr;
    } else if (ctx->expr()) {
        Expr * expr = visit(ctx->expr());
        if (expr == nullptr) {
            return (Instr *)nullptr;
        }
        instr = (Instr *)new ExprInstr(ctx->start->getLine(), expr, currentScope);
    } else if (ctx->ifblock()) {
        instr = (Instr *)visit(ctx->ifblock());
    } else if (ctx->whileblock()) {
        //TO DO : breaks and continue (in while and for ) !
        instr = (Instr *)visit(ctx->whileblock());
    } else if (ctx->forblock()) {
        //TO DO : breaks and continue (in while and for ) !
        instr = (Instr *)visit(ctx->forblock());
    } else if (ctx->block()) {
        instr = (Instr *)visit(ctx->block()).as<BlockInstr *>();
    }

    return instr;
} //----- Fin de visitLine

antlrcpp::Any ASTGenerator::visitVar_decl(ifccParser::Var_declContext * ctx) {
    vector<Expr *> ret;
    lastDeclaredType = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());
    int line = ctx->start->getLine();

    if (program->GetSymbolTable().DefineVariable(currentFunction, ctx->ID()->getText(), lastDeclaredType, ctx->start->getLine(), currentScope)) {

        if (ctx->expr()) {
            Expr * rValue = (Expr *)visit(ctx->expr());
            if (!checkExpr(rValue)) {
                return (Expr *)nullptr;
            }

            ExprVarLvalue * lValue;
            string varname = ctx->ID()->getText();
            //string scope = program->GetSymbolTable().GetVariableScope(currentFunction, varname, currentScope);

            if (program->GetSymbolTable().LookUpVariable(currentFunction, varname, currentScope)) {
                lValue = new ExprVarLvalue(line, varname, currentScope);
            } else {
                program->SetErrorFlag(true);
                cerr << "variable " + varname + " does not exist in contextVariableTable from " + currentFunction << endl;
            }

            ret.push_back(((Expr *)new ExprAffectation(lValue, rValue, line, currentScope)));
        }

        for (int i = 0; i < ctx->inline_var_decl().size(); i++) {
            Expr * inlineExpr = (Expr *)visit(ctx->inline_var_decl(i));
            if (inlineExpr != nullptr) {
                ret.push_back(inlineExpr);
            }
        }
    } else {
        program->SetErrorFlag(true);
    }
    return ret;
}

antlrcpp::Any ASTGenerator::visitInline_var_decl(ifccParser::Inline_var_declContext * ctx) {
    int line = ctx->start->getLine();
    ExprVarLvalue * lValue;
    string varname = ctx->ID()->getText();
    //string scope = program->GetSymbolTable().GetVariableScope(currentFunction, varname, currentScope);

    if (lastDeclaredType != ERROR && program->GetSymbolTable().DefineVariable(currentFunction, varname, lastDeclaredType, line, currentScope)) {
        if (ctx->expr()) {
            Expr * rValue = (Expr *)visit(ctx->expr());
            if (!checkExpr(rValue)) {
                return (Expr *)nullptr;
            }

            if (program->GetSymbolTable().LookUpVariable(currentFunction, varname, currentScope)) {
                lValue = new ExprVarLvalue(line, varname, currentScope);
            } else {
                program->SetErrorFlag(true);
                cerr << "variable " + varname + " does not exist in contextVariableTable from " + currentFunction << endl;
            }

            return (Expr *)new ExprAffectation(lValue, rValue, line, currentScope);
        }
    } else {
        program->SetErrorFlag(true);
    }
    return (Expr *)nullptr;
}

antlrcpp::Any ASTGenerator::visitVar_aff(ifccParser::Var_affContext * ctx) {

    int line = ctx->start->getLine();

    // Right value
    Expr * rValue = (Expr *)visit(ctx->expr());
    if (!checkExpr(rValue)) {
        return (Expr *)nullptr;
    }

    // Left value
    ExprVarLvalue * lValue;
    string varname = ctx->ID()->getText();
    string scope = program->GetSymbolTable().GetVariableScope(currentFunction, varname, currentScope);

    if (program->GetSymbolTable().LookUpVariable(currentFunction, varname, currentScope)) {
        lValue = new ExprVarLvalue(line, varname, scope);
    } else {
        program->SetErrorFlag(true);
        cerr << "variable " + varname + " does not exist in contextVariableTable from " + currentFunction << endl;
    }

    return (Expr *)new ExprAffectation(lValue, rValue, line, currentScope);

} //----- Fin de visitVar_aff

antlrcpp::Any ASTGenerator::visitReturn_stmt(ifccParser::Return_stmtContext * ctx) {

    program->GetSymbolTable().SetHasReturnFunction(currentFunction);

    Expr * expr = visit(ctx->expr());
    if (!checkExpr(expr)) {
        return (Instr *)nullptr;
    }
    return (Instr *)new ReturnInstr(ctx->start->getLine(), expr, currentScope);
} //----- Fin de visitReturn_stmt

antlrcpp::Any ASTGenerator::visitPar(ifccParser::ParContext * ctx) {
    return visit(ctx->expr());
} //----- Fin de visitPar

antlrcpp::Any ASTGenerator::visitLess_or_add(ifccParser::Less_or_addContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperator;
    if (op1 == nullptr || op2 == nullptr) {
        return (Expr *)nullptr;
    }

    if (ctx->OP_LESS()) {
        binaryOperator = MINUS;
    } else if (ctx->OP_ADD()) {
        binaryOperator = PLUS;
    }

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (binaryOperator == PLUS) {
        if (op1Lit && val1 == 0) {
            delete (op1);
            return op2;
        } else {
            if (op2Lit && val2 == 0) {
                delete (op2);
                return op1;
            }
        }
    }

    if (binaryOperator == MINUS && (op2Lit && val2 == 0)) {
        delete (op2);
        return op1;
    }

    if (op1Lit && op2Lit) {

        if (binaryOperator == MINUS) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), val1 - val2, currentScope);
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), val1 + val2, currentScope);
        }
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperator, currentScope);
} //----- Fin de visitLess_or_add

antlrcpp::Any ASTGenerator::visitDiv_or_mult(ifccParser::Div_or_multContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperator;

    if (ctx->OP_DIV()) {
        binaryOperator = DIV;
    } else if (ctx->OP_MULT()) {
        binaryOperator = MULT;
    }

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (binaryOperator == MULT) {
        if (op1Lit && val1 == 1) {
            delete (op1);
            return op2;
        } else {
            if (op2Lit && val2 == 1) {
                delete (op2);
                return op1;
            }
        }
    }

    if (binaryOperator == DIV && (op2Lit && val2 == 1)) {
        delete (op2);
        return op1;
    }

    if (op1Lit && op2Lit) {
        if (binaryOperator == DIV) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), val1 / val2, currentScope);
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), val1 * val2, currentScope);
        }
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperator, currentScope);
} //----- Fin de visitDiv_or_mult

antlrcpp::Any ASTGenerator::visitOr(ifccParser::OrContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperatorOr = OR;
    if (op1 == nullptr || op2 == nullptr) {
        return (Expr *)nullptr;
    }

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        delete (op1);
        delete (op2);
        return (Expr *)new ConstLiteral(ctx->start->getLine(), val1 | val2, currentScope);
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorOr, currentScope);
} //----- Fin de visitOr

antlrcpp::Any ASTGenerator::visitAnd(ifccParser::AndContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperatorAnd = AND;

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        delete (op1);
        delete (op2);
        return (Expr *)new ConstLiteral(ctx->start->getLine(), val1 & val2, currentScope);
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorAnd, currentScope);
} //----- Fin de visitAnd

antlrcpp::Any ASTGenerator::visitXor(ifccParser::XorContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperatorXor = XOR;

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        delete (op1);
        delete (op2);
        return (Expr *)new ConstLiteral(ctx->start->getLine(), val1 ^ val2, currentScope);
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorXor, currentScope);
} //----- Fin de visitXor

antlrcpp::Any ASTGenerator::visitLiteral(ifccParser::LiteralContext * ctx) {
    Expr * ret = nullptr;
    if (ctx->CONST()) {
        int64_t value;
        istringstream tmpSS(ctx->getText());
        tmpSS >> value;
        ret = new ConstLiteral(ctx->start->getLine(), value, currentScope);
    } else if (ctx->CHAR()) {
        ret = new CharLiteral(ctx->start->getLine(), ctx->getText()[1], currentScope);
    } else if (ctx->ID()) {
        if (program->GetSymbolTable().LookUpVariable(currentFunction, ctx->ID()->getText(), currentScope)) {
            ret = new ExprVarRvalue(ctx->start->getLine(), ctx->ID()->getText(), program->GetSymbolTable().GetVariableScope(currentFunction, ctx->ID()->getText(), currentScope));
            program->GetSymbolTable().SetUsedVariable(currentFunction, ctx->ID()->getText(), program->GetSymbolTable().GetVariableScope(currentFunction, ctx->ID()->getText(), currentScope));
        } else {
            program->SetErrorFlag(true);
            cerr << "variable " + ctx->ID()->getText() + " does not exist in contextVariableTable from " + currentFunction << endl;
        }
    }

    return ret;
} //----- Fin de visitLiteral

antlrcpp::Any ASTGenerator::visitOpp_or_not(ifccParser::Opp_or_notContext * ctx) {
    Expr * op = (Expr *)visit(ctx->expr());
    if (!checkExpr(op)) {
        return (Expr *)nullptr;
    }

    UnitOperator unitOperator;

    if (ctx->OP_LESS()) {
        unitOperator = OPP;
    } else if (ctx->OP_UNAIRE_NOT()) {
        unitOperator = NOT;
    }

    int64_t val;
    bool opLit = isLiteral(op, val);

    if (unitOperator == OPP) {
        if (opLit) {
            delete (op);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), -val, currentScope);
        }
    } else if (unitOperator == NOT) {
        if (opLit) {
            if (val == 0) {
                delete (op);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
            } else {
                delete (op);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
            }
        }
    }

    return (Expr *)new OpUn(ctx->start->getLine(), op, unitOperator, currentScope);
} //----- Fin de visitOpp_or_not

antlrcpp::Any ASTGenerator::visitFunction(ifccParser::FunctionContext * ctx) {
    Function * ret = new Function(ctx->start->getLine(), ctx->ID()->getText(), currentScope);

    vector<Expr *> params;
    if (ctx->expr_list()) {
        params = visit(ctx->expr_list()).as<vector<Expr *>>();
    }

    ret->SetParams(params);

    if (program->GetSymbolTable().LookUpFunction(ctx->ID()->getText())) {
        // Internal Function

        // Check number of params
        int nbParamsNeeded = program->GetSymbolTable().GetFunctionParams(ctx->ID()->getText()).size();
        int nbParamsObtained = params.size();
        if (nbParamsNeeded != nbParamsObtained) {
            string errorType;
            if (nbParamsNeeded > nbParamsObtained) {
                errorType = "few";
            } else {
                errorType = "many";
            }
            cerr << "Too " << errorType << " arguments to function '" << ctx->ID()->getText() << "' (need : " << nbParamsNeeded << " ; obtained : " << nbParamsObtained << ")" << endl;
            program->SetErrorFlag(true);
            return (Expr *)nullptr;
        }

        // Check params types
        // TODO

        program->GetSymbolTable().SetUsedFunction(ctx->ID()->getText());
    }

    return (Expr *)ret;
} //----- Fin de visitFunction

antlrcpp::Any ASTGenerator::visitDef_func(ifccParser::Def_funcContext * ctx) {
    // TODO : modifier la grammaire pour accepter les déclarations de fonction avec juste "void" en arg
    string func_name = ctx->ID()->getText();
    Type func_type = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());
    DefFuncInstr * def_func = nullptr;
    vector<FunctionParam *> paramList;

    if (ctx->param_list()) {
        paramList = visit(ctx->param_list()).as<vector<FunctionParam *>>();
    }

    if (program->GetSymbolTable().DefineFunction(func_name, func_type, paramList, ctx->start->getLine())) {
        this->currentFunction = func_name;
        this->scopeIndexIncrement.clear();
        this->scopeIndexIncrement.push_back(0);
        this->currentScope = "0";

        def_func = new DefFuncInstr(ctx->start->getLine(), func_name, func_type, currentScope);

        // TEMP (?)
        for (FunctionParam * param : paramList) {
            program->GetSymbolTable().DefineVariable(func_name, param->name, param->type, ctx->start->getLine(), currentScope);
        }

        for (int i = 0; i < ctx->line().size(); i++) {
            antlrcpp::Any tmpVisitLine = visit(ctx->line(i));

            if (tmpVisitLine.is<Instr *>()) {
                Instr * instr = tmpVisitLine.as<Instr *>();
                if (instr != nullptr) {
                    def_func->AddInstr(instr);
                }
            } else if (tmpVisitLine.is<vector<Instr *>>()) {
                vector<Instr *> vectInstr = tmpVisitLine.as<vector<Instr *>>();
                for (Instr * instr : vectInstr) {
                    if (instr != nullptr) {
                        def_func->AddInstr(instr);
                    }
                }
            }
        }

        if (func_name.compare("main") == 0 && !program->GetSymbolTable().FunctionHasReturn("main")) {
            Expr * retExpr = new ConstLiteral(ctx->start->getLine(), 0, currentScope);
            Instr * retInstr = new ReturnInstr(ctx->start->getLine(), retExpr, currentScope);
            def_func->AddInstr(retInstr);
        }

    } else {
        program->SetErrorFlag(true);
    }

    return (Instr *)def_func;

} //----- Fin de visitDef_func

antlrcpp::Any ASTGenerator::visitParam_list(ifccParser::Param_listContext * ctx) {
    vector<FunctionParam *> params;

    for (int i = 0; i < ctx->param().size(); i++) {
        params.push_back(visit(ctx->param(i)));
    }

    return params;
} //----- Fin de visitParam_list

antlrcpp::Any ASTGenerator::visitParam(ifccParser::ParamContext * ctx) {
    Type type = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());
    return new FunctionParam(type, ctx->ID()->getText());
} //----- Fin de visitParam

antlrcpp::Any ASTGenerator::visitExpr_list(ifccParser::Expr_listContext * ctx) {
    vector<Expr *> params;

    for (int i = 0; i < ctx->expr().size(); i++) {
        Expr * tmpExpr = visit(ctx->expr(i));
        if (checkExpr(tmpExpr)) {
            params.push_back(tmpExpr);
        }
    }

    return params;
} //----- Fin de visitExpr_list

antlrcpp::Any ASTGenerator::visitIfblock(ifccParser::IfblockContext * ctx) {

    // Création de l'expression
    Expr * exprIf = (Expr *)visit(ctx->expr());
    if (!checkExpr(exprIf)) {
        return (Instr *)nullptr;
    }

    // Récupération des intructions du IF
    BlockInstr * ifblock;
    if (ctx->line()) {
        expandScope();
        Instr * instr = visit(ctx->line());
        if (instr != nullptr) {
            ifblock = new BlockInstr(ctx->start->getLine(), instr->GetScope());
            ifblock->AddInstr(instr);
        }
        reduceScope();
    } else {
        ifblock = (BlockInstr *)visit(ctx->block());
    }

    // Récupération des intructions du else
    BlockInstr * elseblock = nullptr;
    if (ctx->elseblock()) {
        elseblock = (BlockInstr *)visit(ctx->elseblock());
    }

    int64_t val;
    bool exprLit = isLiteral(exprIf, val);

    if (exprLit) {
        if (val == 0) {
            delete (ifblock);
            delete (exprIf);
            return (Instr *)elseblock;
        } else {
            delete (elseblock);
            delete (exprIf);
            return (Instr *)ifblock;
        }
    } else {
        // Création du ifElseInstr
        return (Instr *)new IfElseInstr(ctx->start->getLine(), exprIf, ifblock, elseblock, currentScope);
    }
}

antlrcpp::Any ASTGenerator::visitElseblock(ifccParser::ElseblockContext * ctx) {
    BlockInstr * elseblock;

    if (ctx->line()) {
        expandScope();
        Instr * instr = visit(ctx->line());
        if (instr != nullptr) {
            elseblock = new BlockInstr(ctx->start->getLine(), instr->GetScope());
            elseblock->AddInstr(instr);
        }
        reduceScope();
    } else if (ctx->block()) {
        elseblock = (BlockInstr *)visit(ctx->block());
    } else {
        Instr * instr = visit(ctx->ifblock());
        if (instr != nullptr) {
            elseblock = new BlockInstr(ctx->start->getLine(), instr->GetScope());
            elseblock->AddInstr(instr);
        }
    }

    return elseblock;
}

antlrcpp::Any ASTGenerator::visitWhileblock(ifccParser::WhileblockContext * ctx) {
    // Création de l'expression
    Expr * exprWhile = (Expr *)visit(ctx->expr());
    if (!checkExpr(exprWhile)) {
        return (Instr *)nullptr;
    }

    // Récupération des intructions du WHILE
    BlockInstr * whileblock;
    if (ctx->line()) {
        expandScope();
        Instr * instr = visit(ctx->line());
        if (instr != nullptr) {
            whileblock = new BlockInstr(ctx->start->getLine(), instr->GetScope());
            whileblock->AddInstr(instr);
        }
        reduceScope();
    } else {
        whileblock = (BlockInstr *)visit(ctx->block());
    }

    int64_t val;
    bool exprLit = isLiteral(exprWhile, val);
    if (exprLit) {
        if (val == 0) {
            delete (whileblock);
            delete (exprWhile);
            return (Instr *)nullptr;
        } else {
            // TODO : voir quoi faire en cas de boucle infinie
        }
    }

    // Création du whileInstr
    Instr * whileInstr = new WhileInstr(ctx->start->getLine(), exprWhile, whileblock, currentScope);

    return whileInstr;
}

antlrcpp::Any ASTGenerator::visitForblock(ifccParser::ForblockContext * ctx) {
    // On augmente le scope pour se placer dans le futur scope du for
    expandScope();

    // Création de la liste d'expression d'initialisation (1)
    vector<Expr *> initExprs;
    int currentExprList(0);
    if (ctx->var_decl()) {
        initExprs = visit(ctx->var_decl()).as<vector<Expr *>>();
    } else if (ctx->expr_list(currentExprList)) {
        initExprs = visit(ctx->expr_list(currentExprList)).as<vector<Expr *>>();
        currentExprList++;
    }

    //Création de l'expression de la condition (2)
    Expr * conditionalExpr;
    if (ctx->expr()) {
        conditionalExpr = (Expr *)visit(ctx->expr());
        if (!checkExpr(conditionalExpr)) {
            return (Instr *)nullptr;
        }
    } else {
        conditionalExpr = new ConstLiteral(ctx->start->getLine(), 1, currentScope);
    }

    //Création de la liste d'expression des mises à jour (3)
    vector<Expr *> updateExprs;
    if (ctx->expr_list(currentExprList)) {
        updateExprs = visit(ctx->expr_list(currentExprList)).as<vector<Expr *>>();
    }

    //On ajuste le scope afin que celui entrant du for sera la même et on réduit
    int currentSize = count(currentScope.begin(), currentScope.end(), '.');
    scopeIndexIncrement[currentSize]--;
    reduceScope();

    // Récupération des intructions du FOR
    BlockInstr * forBlock;
    if (ctx->line()) {
        expandScope();
        Instr * instr = visit(ctx->line());
        if (instr != nullptr) {
            forBlock = new BlockInstr(ctx->start->getLine(), instr->GetScope());
            forBlock->AddInstr(instr);
        }
        reduceScope();
    } else {
        forBlock = (BlockInstr *)visit(ctx->block());
    }

    ConstLiteral * constExpr = dynamic_cast<ConstLiteral *>(conditionalExpr);
    if (constExpr) {
        if (constExpr->GetValue() == 0) {
            delete (forBlock);
            delete (conditionalExpr);
            return (Instr *)nullptr;
        } else {
            // TODO : voir quoi faire en cas de boucle infinie
        }
    }

    // Création du forInstr
    Instr * forInstr = new ForInstr(ctx->start->getLine(), initExprs, conditionalExpr, updateExprs, forBlock, currentScope);

    return forInstr;
}

antlrcpp::Any ASTGenerator::visitBlock(ifccParser::BlockContext * ctx) {
    expandScope();
    BlockInstr * blockInstr = new BlockInstr(ctx->start->getLine(), currentScope);

    for (int i = 0; i < ctx->line().size(); i++) {

        antlrcpp::Any tmpVisitLine = visit(ctx->line(i));

        if (tmpVisitLine.is<Instr *>()) {
            Instr * instr = tmpVisitLine.as<Instr *>();
            if (instr != nullptr) {
                blockInstr->AddInstr(instr);
            }
        } else if (tmpVisitLine.is<vector<Instr *>>()) {
            vector<Instr *> vectInstr = tmpVisitLine.as<vector<Instr *>>();
            for (Instr * instr : vectInstr) {
                if (instr != nullptr) {
                    blockInstr->AddInstr(instr);
                }
            }
        }
    }
    reduceScope();
    return blockInstr;
}

antlrcpp::Any ASTGenerator::visitCdtand(ifccParser::CdtandContext * ctx) {
    Expr * op1 = visit(ctx->expr(0));
    Expr * op2 = visit(ctx->expr(1));

    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperatorCdtAnd = CDTAND;

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        if (val1 != 0 && val2 != 0) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
        }
    } else if (op1Lit && !op2Lit) {
        if (val1 != 0) {
            delete (op1);
            return op2;
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
        }
    } else if (op2Lit && !op1Lit) {
        if (val2 != 0) {
            delete (op2);
            return op1;
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
        }
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorCdtAnd, currentScope);
}

antlrcpp::Any ASTGenerator::visitCdtor(ifccParser::CdtorContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorCdtOr = CDTOR;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        if (val1 != 0 || val2 != 0) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
        }
    } else if (op1Lit && !op2Lit) {
        if (val1 != 0) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
        } else {
            delete (op1);
            return op2;
        }
    } else if (op2Lit && !op1Lit) {
        if (val2 != 0) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
        } else {
            delete (op2);
            return op1;
        }
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorCdtOr, currentScope);
}

antlrcpp::Any ASTGenerator::visitEqual(ifccParser::EqualContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorEqual = EQUAL;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        if (val1 == val2) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
        }
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorEqual, currentScope);
}

antlrcpp::Any ASTGenerator::visitNotequal(ifccParser::NotequalContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorNotEqual = NEQUAL;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        if (val1 != val2) {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
        } else {
            delete (op1);
            delete (op2);
            return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
        }
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorNotEqual, currentScope);
}

antlrcpp::Any ASTGenerator::visitGreater_equal_lesser_equal(ifccParser::Greater_equal_lesser_equalContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));

    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperator;

    if (ctx->OP_GREATER_EQUAL()) {
        binaryOperator = GREATERE;
    } else if (ctx->OP_GREATER()) {
        binaryOperator = GREATER;
    } else if (ctx->OP_LESSER_EQUAL()) {
        binaryOperator = LESSE;
    } else if (ctx->OP_LESSER()) {
        binaryOperator = LESS;
    }

    int64_t val1;
    bool op1Lit = isLiteral(op1, val1);
    int64_t val2;
    bool op2Lit = isLiteral(op2, val2);

    if (op1Lit && op2Lit) {
        if (binaryOperator == GREATERE) {
            if (val1 >= val2) {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
            } else {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
            }
        } else if (binaryOperator == GREATER) {
            if (val1 > val2) {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
            } else {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
            }
        } else if (binaryOperator == LESSE) {
            if (val1 <= val2) {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
            } else {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
            }
        } else if (binaryOperator == LESS) {
            if (val1 < val2) {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 1, currentScope);
            } else {
                delete (op1);
                delete (op2);
                return (Expr *)new ConstLiteral(ctx->start->getLine(), 0, currentScope);
            }
        }
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperator, currentScope);
}

//-------------------------------------------- Constructeurs - destructeur

ASTGenerator::~ASTGenerator() {
    delete (program);
} //----- Fin de ~ASTGenerator

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
bool ASTGenerator::checkExpr(Expr * expr) {
    bool res = false;
    if (expr) {
        Function * func = dynamic_cast<Function *>(expr);
        if (func && this->program->GetSymbolTable().GetFunctionType(func->GetName()) == VOID) {
            cerr << "Void value not ignored as it ought to be (function '" << func->GetName() << "')" << endl;
        } else {
            res = true;
        }
    }
    if (!res) {
        this->program->SetErrorFlag(true);
    }
    return res;
} //----- Fin de checkExpr

void ASTGenerator::expandScope() {
    int currentSize = count(currentScope.begin(), currentScope.end(), '.') + 1;
    if (currentSize >= scopeIndexIncrement.size()) {
        scopeIndexIncrement.push_back(0);
    }

    currentScope = currentScope + "." + to_string(scopeIndexIncrement[currentSize]++);
} //----- Fin de incrScope

void ASTGenerator::reduceScope() {
    size_t lastPos = currentScope.find_last_of('.');
    if (currentScope.size() > 0 && lastPos != string::npos) {
        currentScope = currentScope.substr(0, lastPos);
    }
} //----- Fin de decrScope

bool ASTGenerator::isLiteral(Expr * expr, int64_t & value) {
    if (expr == nullptr)
        return false;

    ConstLiteral * constLiteral = dynamic_cast<ConstLiteral *>(expr);
    CharLiteral * charLiteral = dynamic_cast<CharLiteral *>(expr);

    if (constLiteral) {
        value = constLiteral->GetValue();
        return true;
    } else if (charLiteral) {
        value = charLiteral->GetValue();
        return true;
    }

    return false;
} //----- Fin de isLiteral