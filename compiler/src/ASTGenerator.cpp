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
        program->AddInstr(instr);
    }
} //----- Fin de visitProg

antlrcpp::Any ASTGenerator::visitLine(ifccParser::LineContext * ctx) {
    Instr * instr;
    if (ctx->var_aff()) {
        instr = (Instr *)visit(ctx->var_aff());
    } else if (ctx->return_stmt()) {
        instr = (Instr *)visit(ctx->return_stmt());
    } else if (ctx->var_decl()) {
        instr = (Instr *)visit(ctx->var_decl());
    } else if (ctx->expr()) {
        instr = (Instr *)visit(ctx->expr());
    }

    return instr;
} //----- Fin de visitLine

antlrcpp::Any ASTGenerator::visitVar_decl(ifccParser::Var_declContext * ctx) {
    Instr * tmpRet = nullptr;
    Instr * ret = nullptr;

    lastDeclaredType = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());

    if (program->GetSymbolTable().DefineVariable("main", ctx->ID()->getText(), lastDeclaredType, ctx->start->getLine())) {

        if (ctx->expr()) {
            Expr * expr = (Expr *)visit(ctx->expr());
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

    if (lastDeclaredType != ERROR && program->GetSymbolTable().DefineVariable("main", ctx->ID()->getText(), lastDeclaredType, ctx->start->getLine())) {
        if (ctx->expr()) {
            Expr * expr = (Expr *)visit(ctx->expr());
            ret = (Instr *)new VarAffInstr(ctx->start->getLine(), ctx->ID()->getText(), lastDeclaredType, expr);
        }
    } else {
        program->SetErrorFlag(true);
    }

    return ret;
}

antlrcpp::Any ASTGenerator::visitVar_aff(ifccParser::Var_affContext * ctx) {
    Expr * expr = (Expr *)visit(ctx->expr());
    return (Instr *)new VarAffInstr(ctx->start->getLine(), ctx->ID()->getText(), lastDeclaredType, expr);
} //----- Fin de visitVar_aff

antlrcpp::Any ASTGenerator::visitReturn_stmt(ifccParser::Return_stmtContext * ctx) {
    this->mainHasReturn = true;
    Expr * expr = (Expr *)visit(ctx->expr());
    return (Instr *)new ReturnInstr(ctx->start->getLine(), expr);
} //----- Fin de visitReturn_stmt

antlrcpp::Any ASTGenerator::visitPar(ifccParser::ParContext * ctx) {
    return visit(ctx->expr());
} //----- Fin de visitPar

antlrcpp::Any ASTGenerator::visitLess_or_add(ifccParser::Less_or_addContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperator;

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
    BinaryOperator binaryOperatorOr = OR;

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorOr);
} //----- Fin de visitOr

antlrcpp::Any ASTGenerator::visitAnd(ifccParser::AndContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorAnd = AND;

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorAnd);
} //----- Fin de visitAnd

antlrcpp::Any ASTGenerator::visitXor(ifccParser::XorContext * ctx) {
    Expr * op1 = (Expr *)visit(ctx->expr(0));
    Expr * op2 = (Expr *)visit(ctx->expr(1));
    BinaryOperator binaryOperatorXor = XOR;

    return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorXor);
} //----- Fin de visitXor

antlrcpp::Any ASTGenerator::visitConst(ifccParser::ConstContext * ctx) {
    return (Expr *)new ConstLiteral(ctx->start->getLine(), stoi(ctx->getText()));
} //----- Fin de visitConst

antlrcpp::Any ASTGenerator::visitOpp_or_not(ifccParser::Opp_or_notContext * ctx) {
    Expr * op = (Expr *)visit(ctx->expr());
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
    if (program->GetSymbolTable().LookUpVariable("main", ctx->ID()->getText())) {
        ret = new Var(ctx->start->getLine(), ctx->ID()->getText());
        program->GetSymbolTable().SetUsedVariable("main", ctx->ID()->getText());
    } else {
        program->SetErrorFlag(true);
        cerr << "variable " + ctx->ID()->getText() + " does not exist in contextVariableTable from " + "main";
    }

    return ret;
} //----- Fin de visitVar

antlrcpp::Any ASTGenerator::visitFunction(ifccParser::FunctionContext * ctx) {
    Expr * ret = nullptr;
    if (program->GetSymbolTable().LookUpFunction(ctx->ID()->getText())) {
        Function * function = new Function(ctx->start->getLine(), ctx->ID()->getText());
        if (ctx->expr_list()) {
            function->SetParams(visit(ctx->expr_list()));
        }
        ret = function;
    } else {
        program->SetErrorFlag(true);
        cerr << "function " + ctx->ID()->getText() + " does not exist in globalFunctionTable";
    }

    return ret;
} //----- Fin de visitFunction

antlrcpp::Any ASTGenerator::visitDef_func(ifccParser::Def_funcContext * ctx) {
    //string func_name = ctx->FUNC_NAME()->getText();
    string func_name("main");
    Type func_type = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());
    DefFuncInstr * def_func = nullptr;

    if (program->GetSymbolTable().DefineFunction(func_name, func_type, ctx->start->getLine())) {
        this->currentFunction = func_name;

        def_func = new DefFuncInstr(ctx->start->getLine(), func_name, func_type);

        if (ctx->param_list()) {
            def_func->SetParam(visit(ctx->param_list()));
        }

        for (int i = 0; i < ctx->line().size(); i++) {
            Instr * instr = (Instr *)visit(ctx->line(i));

            if (instr != nullptr) {
                def_func->AddInstr(instr);
            }
        }

        if (!this->mainHasReturn && func_name.compare("main")) {
            Expr * retExpr = new ConstLiteral(ctx->start->getLine(), 0);
            Instr * retInstr = new ReturnInstr(ctx->start->getLine(), retExpr);
            def_func->AddInstr(retInstr);
        }

    } else {
        program->SetErrorFlag(true);
    }

    return def_func;

} //----- Fin de visitDef_func

antlrcpp::Any ASTGenerator::visitParam_list(ifccParser::Param_listContext * ctx) {
    vector<Param *> params;

    for (int i = 0; i < ctx->param().size(); i++) {
        params.push_back(visit(ctx->param(i)));
    }

    return params;
} //----- Fin de visitParam_list

antlrcpp::Any ASTGenerator::visitParam(ifccParser::ParamContext * ctx) {
    Type type = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());
    Param * ret = new Param(ctx->start->getLine(), ctx->ID()->getText(), type);
} //----- Fin de visitParam

antlrcpp::Any ASTGenerator::visitExpr_list(ifccParser::Expr_listContext * ctx) {
    vector<Expr *> params;

    for (int i = 0; i < ctx->expr().size(); i++) {
        params.push_back(visit(ctx->expr(i)));
    }

    return params;
} //----- Fin de visitExpr_list

//-------------------------------------------- Constructeurs - destructeur

ASTGenerator::~ASTGenerator() {
    delete (program);
} //----- Fin de ~ASTGenerator

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
