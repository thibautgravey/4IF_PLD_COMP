/*******************************************************************************
                           ASTGenerator  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <ASTGenerator> (fichier ASTGenerator.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

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

    Type declaredType = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());

    if (program->GetSymbolTable().DefineFunction("main", declaredType, ctx->start->getLine())) {

        for (int i = 0; i < ctx->line().size(); i++) {
            Instr * instr = (Instr *)visit(ctx->line(i));

            if (instr != nullptr) {
                program->AddInstr(instr);
            }
        }

    } else {
        program->SetErrorFlag(true);
    }

    return program;
} //----- Fin de visitProg

antlrcpp::Any ASTGenerator::visitLine(ifccParser::LineContext * ctx) {
    Instr * instr;
    if (ctx->var_aff()) {
        instr = (Instr *)visit(ctx->var_aff());
    } else if (ctx->return_stmt()) {
        instr = (Instr *)visit(ctx->return_stmt());
    } else if (ctx->var_decl()) {
        instr = (Instr *)visit(ctx->var_decl());
    }

    return instr;
} //----- Fin de visitLine

antlrcpp::Any ASTGenerator::visitVar_decl(ifccParser::Var_declContext * ctx) {
    Instr * tmpRet = nullptr;
    Instr * ret = nullptr;

    lastDeclaredType = program->GetSymbolTable().StringToType(ctx->TYPE()->getText());

    if (program->GetSymbolTable().DefineVariable("main", ctx->VAR_NAME()->getText(), lastDeclaredType, ctx->start->getLine())) {

        if (ctx->expr()) {
            Expr * expr = (Expr *)visit(ctx->expr());
            tmpRet = new VarAffInstr(ctx->start->getLine(), ctx->VAR_NAME()->getText(), expr);
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

    if (lastDeclaredType != ERROR && program->GetSymbolTable().DefineVariable("main", ctx->VAR_NAME()->getText(), lastDeclaredType, ctx->start->getLine())) {
        if (ctx->expr()) {
            Expr * expr = (Expr *)visit(ctx->expr());
            ret = (Instr *)new VarAffInstr(ctx->start->getLine(), ctx->VAR_NAME()->getText(), expr);
        }
    } else {
        program->SetErrorFlag(true);
    }

    return ret;
}

antlrcpp::Any ASTGenerator::visitVar_aff(ifccParser::Var_affContext * ctx) {
    Expr * expr = (Expr *)visit(ctx->expr());
    return (Instr *)new VarAffInstr(ctx->start->getLine(), ctx->VAR_NAME()->getText(), expr);
} //----- Fin de visitVar_aff

antlrcpp::Any ASTGenerator::visitReturn_stmt(ifccParser::Return_stmtContext * ctx) {
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

antlrcpp::Any ASTGenerator::visitNot(ifccParser::NotContext * ctx) {
    Expr * op = (Expr *)visit(ctx->expr());
    UnitOperator unitOperatorNot = NOT;
    return (Expr *)new OpUn(ctx->start->getLine(), op, unitOperatorNot);
} //----- Fin de visitNot

antlrcpp::Any ASTGenerator::visitOpp(ifccParser::OppContext * ctx) {
    Expr * op = (Expr *)visit(ctx->expr());
    UnitOperator unitOperatorOpp = OPP;
    return (Expr *)new OpUn(ctx->start->getLine(), op, unitOperatorOpp);
} //----- Fin de visitOpp

antlrcpp::Any ASTGenerator::visitVar(ifccParser::VarContext * ctx) {
    Expr * ret = nullptr;
    if (program->GetSymbolTable().LookUp("main", ctx->VAR_NAME()->getText())) {
        ret = new Var(ctx->start->getLine(), ctx->VAR_NAME()->getText());
        program->GetSymbolTable().SetUsedVariable("main", ctx->VAR_NAME()->getText());
    } else {
        program->SetErrorFlag(true);
        cerr << "variable " + ctx->VAR_NAME()->getText() + " does not exist in contextVariableTable from " + "main";
    }

    return ret;
} //----- Fin de visitVar

//-------------------------------------------- Constructeurs - destructeur

ASTGenerator::~ASTGenerator() {
    delete (program);
} //----- Fin de ~ASTGenerator

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
