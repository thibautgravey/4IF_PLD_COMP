/*******************************************************************************
                           ASTGenerator  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <ASTGenerator> (fichier ASTGenerator.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
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
        instr = (Instr *)visit(ctx->var_decl());
    } else if (ctx->expr()) {
        Expr * expr = visit(ctx->expr());
        if (expr == nullptr) {
            return (Instr *)nullptr;
        }
        instr = new ExprInstr(ctx->start->getLine(), visit(ctx->expr()));
    } else if (ctx->ifblock()) {
        instr = (Instr *)visit(ctx->ifblock());

    } else if (ctx->whileblock()) {
        instr = (Instr *)visit(ctx->whileblock());
    }

    return instr;
} //----- Fin de visitLine

antlrcpp::Any ASTGenerator::visitVar_decl(ifccParser::Var_declContext * ctx) {
    Instr * tmpRet = nullptr;
    Instr * ret = nullptr;

    lastDeclaredType = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());

    if (program->GetSymbolTable().DefineVariable(currentFunction, ctx->ID()->getText(), lastDeclaredType, ctx->start->getLine())) {

        if (ctx->expr()) {
            Expr * expr = (Expr *)visit(ctx->expr());
            if (!checkExpr(expr)) {
                return (Instr *)nullptr;
            }

            tmpRet = new VarAffInstr(ctx->start->getLine(), ctx->ID()->getText(), lastDeclaredType, expr);
            ret = tmpRet;
        }

        for (int i = 0; i < ctx->inline_var_decl().size(); i++) {
            Instr * instr = (Instr *)visit(ctx->inline_var_decl(i));
            if (instr != nullptr) {
                if (tmpRet == nullptr) {
                    tmpRet = instr;
                    ret = tmpRet;
                } else {
                    ((VarAffInstr *)tmpRet)->SetVarAffInstrNext(instr);
                    tmpRet = instr;
                }
            }
        }
    } else {
        program->SetErrorFlag(true);
    }

    return ret;
}

antlrcpp::Any ASTGenerator::visitInline_var_decl(ifccParser::Inline_var_declContext * ctx) {
    Instr * ret = nullptr;

    if (lastDeclaredType != ERROR && program->GetSymbolTable().DefineVariable(currentFunction, ctx->ID()->getText(), lastDeclaredType, ctx->start->getLine())) {
        if (ctx->expr()) {
            Expr * expr = (Expr *)visit(ctx->expr());
            if (!checkExpr(expr)) {
                return (Instr *)nullptr;
            }

            ret = (Instr *)new VarAffInstr(ctx->start->getLine(), ctx->ID()->getText(), lastDeclaredType, expr);
        }
    } else {
        program->SetErrorFlag(true);
    }

    return ret;
}

antlrcpp::Any ASTGenerator::visitVar_aff(ifccParser::Var_affContext * ctx) {
    // TODO: voir pour la règle var_aff (operande de gauche)

    //TODO: considérer l'affectation comme une opération binaire (EQ)

    /*
    Expr * expr = (Expr *)visit(ctx->expr());

    return (Instr *)new VarAffInstr(ctx->start->getLine(), ctx->ID()->getText(), lastDeclaredType, expr);
    */

    Expr * affExpr = (Expr *)visit(ctx->expr());
    if (!checkExpr(affExpr)) {
        return (Expr *)nullptr;
    }
    Expr * var = new Var(ctx->start->getLine(), ctx->ID()->getText());
    return (Expr *)new OpBin(ctx->start->getLine(), var, affExpr, EQ);

} //----- Fin de visitVar_aff

antlrcpp::Any ASTGenerator::visitReturn_stmt(ifccParser::Return_stmtContext * ctx) {

    program->GetSymbolTable().SetHasReturnFunction(currentFunction);

    Expr * expr = visit(ctx->expr());
    if (!checkExpr(expr)) {
        return (Instr *)nullptr;
    }
    return (Instr *)new ReturnInstr(ctx->start->getLine(), expr);
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

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperator);
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

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperator);
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

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorOr);
} //----- Fin de visitOr

antlrcpp::Any ASTGenerator::visitAnd(ifccParser::AndContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperatorAnd = AND;

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorAnd);
} //----- Fin de visitAnd

antlrcpp::Any ASTGenerator::visitXor(ifccParser::XorContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperatorXor = XOR;

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorXor);
} //----- Fin de visitXor

antlrcpp::Any ASTGenerator::visitConst(ifccParser::ConstContext * ctx) {
    return (Expr *)new ConstLiteral(ctx->start->getLine(), stoi(ctx->getText()));
} //----- Fin de visitConst

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

    return (Expr *)new OpUn(ctx->start->getLine(), op, unitOperator);
} //----- Fin de visitOpp_or_not

antlrcpp::Any ASTGenerator::visitVar(ifccParser::VarContext * ctx) {
    Expr * ret = nullptr;
    if (program->GetSymbolTable().LookUpVariable(currentFunction, ctx->ID()->getText())) {
        ret = new Var(ctx->start->getLine(), ctx->ID()->getText());
        program->GetSymbolTable().SetUsedVariable(currentFunction, ctx->ID()->getText());
    } else {
        program->SetErrorFlag(true);
        cerr << "variable " + ctx->ID()->getText() + " does not exist in contextVariableTable from " + currentFunction << endl;
    }

    return ret;
} //----- Fin de visitVar

antlrcpp::Any ASTGenerator::visitFunction(ifccParser::FunctionContext * ctx) {
    Function * ret = new Function(ctx->start->getLine(), ctx->ID()->getText());

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
    string func_name = ctx->ID()->getText();
    Type func_type = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());
    DefFuncInstr * def_func = nullptr;
    vector<FunctionParam *> paramList;

    if (ctx->param_list()) {
        paramList = visit(ctx->param_list()).as<vector<FunctionParam *>>();
    }

    if (program->GetSymbolTable().DefineFunction(func_name, func_type, paramList, ctx->start->getLine())) {
        this->currentFunction = func_name;

        def_func = new DefFuncInstr(ctx->start->getLine(), func_name, func_type);

        // TEMP (?)
        for (FunctionParam * param : paramList) {
            program->GetSymbolTable().DefineVariable(func_name, param->name, param->type, ctx->start->getLine());
        }

        for (int i = 0; i < ctx->line().size(); i++) {
            Instr * instr = visit(ctx->line(i));

            if (instr != nullptr) {
                def_func->AddInstr(instr);
            }
        }

        if (func_name.compare("main") == 0 && !program->GetSymbolTable().FunctionHasReturn("main")) {
            Expr * retExpr = new ConstLiteral(ctx->start->getLine(), 0);
            Instr * retInstr = new ReturnInstr(ctx->start->getLine(), retExpr);
            def_func->AddInstr(retInstr);
        }

    } else {
        program->SetErrorFlag(true);
    }

    return (Instr *)def_func;

} //----- Fin de visitDef_func

antlrcpp::Any ASTGenerator::visitParam_list(ifccParser::Param_listContext * ctx) {
    vector<FunctionParam *> params;
    //vector<Param *> params;

    for (int i = 0; i < ctx->param().size(); i++) {
        params.push_back(visit(ctx->param(i)));
    }

    return params;
} //----- Fin de visitParam_list

antlrcpp::Any ASTGenerator::visitParam(ifccParser::ParamContext * ctx) {
    Type type = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());
    return new FunctionParam(type, ctx->ID()->getText());
    //return new Param(ctx->start->getLine(), ctx->ID()->getText(), type);
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
    //ifElseInstr * ifelseblock = new ifElseInstr(ctx->start->getLine(), exprIf);

    // Récupération des intructions du IF
    BlockInstr * ifblock;
    if (ctx->line()) {
        ifblock = new BlockInstr(ctx->start->getLine());
        ifblock->AddInstr((Instr *)visit(ctx->line()));
    } else { //
        ifblock = (BlockInstr *)visit(ctx->block());
    }

    // Récupération des intructions du else
    BlockInstr * elseblock = nullptr;
    if (ctx->elseblock()) {
        elseblock = (BlockInstr *)visit(ctx->elseblock());
    }

    // Création du ifElseInstr
    Instr * ifelse = new IfElseInstr(ctx->start->getLine(), exprIf, ifblock, elseblock);

    return ifelse;
}

antlrcpp::Any ASTGenerator::visitElseblock(ifccParser::ElseblockContext * ctx) {
    BlockInstr * elseblock;

    if (ctx->line()) {
        elseblock = new BlockInstr(ctx->start->getLine());
        elseblock->AddInstr((Instr *)visit(ctx->line()));
    } else if (ctx->block()) { //
        elseblock = (BlockInstr *)visit(ctx->block());
    } else {
        elseblock = new BlockInstr(ctx->start->getLine());
        elseblock->AddInstr((Instr *)visit(ctx->ifblock()));
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
        //TO DO : ajouter vérification instruction non nulle
        whileblock = new BlockInstr(ctx->start->getLine());
        whileblock->AddInstr((Instr *)visit(ctx->line()));
    } else { //
        whileblock = (BlockInstr *)visit(ctx->block());
    }

    // Création du whileInstr
    Instr * whileInstr = new WhileInstr(ctx->start->getLine(), exprWhile, whileblock);

    return whileInstr;
}

antlrcpp::Any ASTGenerator::visitBlock(ifccParser::BlockContext * ctx) {
    BlockInstr * blockInstr = new BlockInstr(ctx->start->getLine());

    for (int i = 0; i < ctx->line().size(); i++) {
        Instr * instr = (Instr *)visit(ctx->line(i));

        if (instr != nullptr) {
            blockInstr->AddInstr(instr);
        }
    }

    return blockInstr;
}

antlrcpp::Any ASTGenerator::visitCdtand(ifccParser::CdtandContext * ctx) {
    Expr * op1 = visit(ctx->expr(0));
    Expr * op2 = visit(ctx->expr(1));
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    BinaryOperator binaryOperatorCdtAnd = CDTAND;

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorCdtAnd);
}

antlrcpp::Any ASTGenerator::visitCdtor(ifccParser::CdtorContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorCdtOr = CDTOR;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorCdtOr);
}

antlrcpp::Any ASTGenerator::visitEqual(ifccParser::EqualContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorEqual = EQUAL;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorEqual);
}

antlrcpp::Any ASTGenerator::visitNotequal(ifccParser::NotequalContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorNotEqual = NEQUAL;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorNotEqual);
}

antlrcpp::Any ASTGenerator::visitGreaterequal(ifccParser::GreaterequalContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorGreaterEqual = GREATERE;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorGreaterEqual);
}

antlrcpp::Any ASTGenerator::visitGreater(ifccParser::GreaterContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorGreater = GREATER;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorGreater);
}

antlrcpp::Any ASTGenerator::visitLessequal(ifccParser::LessequalContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorLessEqual = LESSE;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorLessEqual);
}

antlrcpp::Any ASTGenerator::visitLess(ifccParser::LessContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorLess = LESS;
    if (!checkExpr(op1) || !checkExpr(op2)) {
        return (Expr *)nullptr;
    }

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorLess);
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
            // TODO : continuer vérification de type ?
            res = true;
        }
    }
    if (!res) {
        this->program->SetErrorFlag(true);
    }
    return res;
}