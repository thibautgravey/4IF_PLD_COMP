
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "ifccBaseVisitor.h"
#include <map>

#include "ast.h"

using namespace std;

class ASTGenerator : public ifccBaseVisitor {
  public:
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext * ctx) override {
        return visit(ctx->prog());
    }

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext * ctx) override {
        program = new Program(ctx->start->getLine());
        program->GetSymbolTable().DefineFunction("main", INT, ctx->start->getLine());

        for (int i = 0; i < ctx->line().size(); i++) {
            Instr * instr = (Instr *)visit(ctx->line(i));
            if (instr != nullptr) {
                program->AddInstr(instr);
            }
        }

        return program;
    }

    virtual antlrcpp::Any visitLine(ifccParser::LineContext * ctx) override {
        Instr * instr;
        if (ctx->var_aff()) {
            instr = (Instr *)visit(ctx->var_aff());
        } else if (ctx->return_stmt()) {
            instr = (Instr *)visit(ctx->return_stmt());
        } else if (ctx->var_decl()) {
            instr = (Instr *)visit(ctx->var_decl());
        }

        return instr;
    }

    virtual antlrcpp::Any visitVar_decl(ifccParser::Var_declContext * ctx) override {
        Instr * ret = nullptr;
        if (program->GetSymbolTable().DefineVariable("main", ctx->VAR_NAME()->getText(), INT, ctx->start->getLine())) {
            if (ctx->expr()) {
                Expr * expr = (Expr *)visit(ctx->expr());
                ret = new VarAffInstr(ctx->start->getLine(), ctx->VAR_NAME()->getText(), expr);
            }
        } else {
            program->SetErrorFlag(true);
        }

        return ret;
    }

    virtual antlrcpp::Any visitVar_aff(ifccParser::Var_affContext * ctx) override {
        Expr * expr = (Expr *)visit(ctx->expr());
        return (Instr *)new VarAffInstr(ctx->start->getLine(), ctx->VAR_NAME()->getText(), expr);
    }

    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext * ctx) override {
        Expr * expr = (Expr *)visit(ctx->expr());
        return (Instr *)new ReturnInstr(ctx->start->getLine(), expr);
    }

    virtual antlrcpp::Any visitPar(ifccParser::ParContext * ctx) override {
        return visit(ctx->expr());
    }

    virtual antlrcpp::Any visitAdd(ifccParser::AddContext * ctx) override {
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));
        BinaryOperator binaryOperatorPlus = PLUS;

        return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorPlus);
    }

    virtual antlrcpp::Any visitLess(ifccParser::LessContext * ctx) override {
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));
        BinaryOperator binaryOperatorMinus = MINUS;

        return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorMinus);
    }

    virtual antlrcpp::Any visitDiv(ifccParser::DivContext * ctx) override {
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));
        BinaryOperator binaryOperatorDiv = DIV;

        return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorDiv);
    }

    virtual antlrcpp::Any visitMult(ifccParser::MultContext * ctx) override {
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));
        BinaryOperator binaryOperatorMult = MULT;

        return (Expr *)new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorMult);
    }

    virtual antlrcpp::Any visitConst(ifccParser::ConstContext * ctx) override {
        return (Expr *)new ConstLiteral(ctx->start->getLine(), stoi(ctx->getText()));
    }

    virtual antlrcpp::Any visitVar(ifccParser::VarContext * ctx) override {
        Expr * ret = nullptr;
        if (program->GetSymbolTable().LookUp("main", ctx->VAR_NAME()->getText())) {
            ret = new Var(ctx->start->getLine(), ctx->VAR_NAME()->getText());
            program->GetSymbolTable().SetUsedVariable("main", ctx->VAR_NAME()->getText());
        } else {
            program->SetErrorFlag(true);
            cerr << "variable " + ctx->VAR_NAME()->getText() + " does not exist in contextVariableTable from " + "main";
        }

        return ret;
    }

  protected:
    Program * program;
};
