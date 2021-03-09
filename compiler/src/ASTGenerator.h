
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "ifccBaseVisitor.h"
#include "antlr4-runtime.h"
#include <map>

#include "ast.h"

using namespace std;

typedef struct {
    string type;
    int * val;
    int * offset;
} varInfo;

typedef struct {
    bool isConst;
    void * value;
    string varExprName;
} exprInfo;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the
 * available methods.
 */
class ASTGenerator : public ifccBaseVisitor {
  public:
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext * ctx) override {
        return visit(ctx->prog());
    }

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext * ctx) override {
        Program * program = new Program(ctx->start->getLine());

        for (int i = 0; i < ctx->line().size(); i++) {
            Instr * instr = (Instr *)visit(ctx->line(i));
            if (instr != nullptr) {
                program->AddInstr(instr);
            }
        }

        /*
        // add prologue
        assembly = ".globl	main\n"
                   " main: \n"
                   "  # prologue\n"
                   "  pushq %rbp\n"
                   "  movq %rsp, %rbp\n"
                   "\n"
                   "  # body\n";

        visitor.visit(tree);visitChildren(ctx);

        // calculate space needed for variables
        int spaceNeeded = 0;
        map<string, varInfo>::iterator it;
        for (it = variables.begin(); it != variables.end(); it++) {
            if (it->second.offset != nullptr) {
                // if offset is not null, it means the variable need space
                spaceNeeded += 4; // 4 for INT
            } else {
                cout << "[Warning] La variable '" << it->first << "' a été
        déclarée mais n'est pas utilisée." << endl;
            }
        }

        // round space to the nearest multiple of 16
        if (spaceNeeded % 16) {
            spaceNeeded = ((spaceNeeded / 16) + 1) * 16;
        }

        assembly += "  subq $" + to_string(spaceNeeded) + ", %rsp\n";

        assembly += assemblyTmpBuf;

        exprInfo retExprInfo = visit(ctx->expr());

        if (retExprInfo.isConst) {
            assembly += "  movl $" + to_string(*((int *)retExprInfo.value)) + ",
        %eax\n"; } else { map<string, varInfo>::iterator it =
        variables.find(retExprInfo.varExprName); if (it != variables.end()) { if
        (it->second.offset == nullptr) {
                    //cout << "[visitProg] Erreur la variable '" <<
        retExprInfo.varExprName << "' n'a pas de valeur !" << endl;
        variablesOffset
        -= 4; // 4 pour INT it->second.offset = new int;
                    *(it->second.offset) = variablesOffset;
                }
                assembly += "  movl " + to_string(*((int *)it->second.offset)) +
        "(%rbp), %eax\n"; } else { hasError = true; cout << "[visitProg] Erreur
        la variable '" << retExprInfo.varExprName << "' n'a pas été déclarée !"
        << endl; assembly += "  movl $-1, %eax\n";
            }
        }

        // add epilogue
        assembly += "\n"
                    "  # epilogue\n"
                    "  addq $" +
                    to_string(spaceNeeded) + ", %rsp\n"
                                             "  popq %rbp\n"
                                             "  ret\n";

        // write the assembly if there is no error
        if (!hasError)
            cout << assembly;

        return hasError;
        */
        return program;
    }

    virtual antlrcpp::Any visitLine(ifccParser::LineContext * ctx) override {
        Instr * instr;
        if (ctx->var_aff()) {
            instr = (Instr *)visit(ctx->var_aff());
            //instr = new VarAffInstr(0, ctx->VAR_NAME()->getText(), visit(ctx->expr()));
        } else if (ctx->return_stmt()) {
            instr = (Instr *)visit(ctx->return_stmt());
            //instr = new ReturnInstr(0, visit(ctx->expr()));
        } else if (ctx->var_decl()) {
            instr = (Instr *)visit(ctx->var_decl());
        }

        return instr; // si déclaration aller dans la table des symboles etc...
    }

    virtual antlrcpp::Any visitVar_decl(ifccParser::Var_declContext * ctx) override {
        // TO DO : Ajouter à la table des symboles

        Expr * expr;
        if (ctx->expr()) {
            expr = (Expr *)visit(ctx->expr());
            Instr * ret = new VarAffInstr(ctx->start->getLine(), ctx->VAR_NAME()->getText(), expr);
            return ret;
        }
        return nullptr;
        /*
        string type = ctx->TYPE()->getText();
        string name = ctx->VAR_NAME()->getText();

        map<string, varInfo>::iterator it = variables.find(name);

        if (it != variables.end()) {
            hasError = true;
            cout << "[visitVar_decl] Erreur la variable '" << name << "' a déjà été déclarée !" << endl;
            return 0;
        }

        int *val = nullptr;
        int *offset = nullptr;

        if (ctx->expr()) {
            exprInfo retExprInfo = visit(ctx->expr());

            if (retExprInfo.isConst) {
                val = new int;
                *val = *((int *)retExprInfo.value);
                variablesOffset -= 4; // 4 pour INT
                offset = new int;
                *offset = variablesOffset;
                assemblyTmpBuf += "  movl $" + to_string((*val)) + ", " + to_string(*offset) + "(%rbp)\n";
            } else {
                map<string, varInfo>::iterator it = variables.find(retExprInfo.varExprName);
                if (it != variables.end()) {
                    if (it->second.val != nullptr) {
                        val = new int;
                        *val = *(it->second.val);
                    }
                    variablesOffset -= 4;
                    offset = new int;
                    *offset = variablesOffset;
                    assemblyTmpBuf += "  movl " + to_string(*(it->second.offset)) + "(%rbp), %eax\n";
                    assemblyTmpBuf += "  movl %eax, " + to_string(*offset) + "(%rbp)\n";
                } else {
                    hasError = true;
                    cout << "[visitVar_decl] Erreur affectation de la variable '" << retExprInfo.varExprName << "' qui n'a pas été déclarée !" << endl;
                }
            }
        }

        varInfo info = {type, val, offset};

        variables.insert(make_pair(name, info));
        return 0;
        */
    }

    virtual antlrcpp::Any visitVar_aff(ifccParser::Var_affContext * ctx) override {
        Expr * expr = (Expr *)visit(ctx->expr());
        return new VarAffInstr(ctx->start->getLine(), ctx->VAR_NAME()->getText(), expr);
        /*
        string name = ctx->VAR_NAME()->getText();

        map<string, varInfo>::iterator it = variables.find(name);

        if (it != variables.end()) {
            exprInfo retExprInfo = visit(ctx->expr());

            if (retExprInfo.isConst) {
                it->second.val = new int;
                *(it->second.val) = *((int *)retExprInfo.value);
                variablesOffset -= 4; // 4 pour INT
                it->second.offset = new int;
                *(it->second.offset) = variablesOffset;
                assemblyTmpBuf += "  movl $" + to_string(*(it->second.val)) + ", " + to_string(*(it->second.offset)) + "(%rbp)\n";
            } else {
                map<string, varInfo>::iterator it2 = variables.find(retExprInfo.varExprName);
                if (it2 != variables.end()) {
                    if (it2->second.val != nullptr) {
                        it->second.val = new int;
                        *(it->second.val) = *(it2->second.val);
                    }
                    variablesOffset -= 4; // 4 pour INT
                    it->second.offset = new int;
                    *(it->second.offset) = variablesOffset;
                    assemblyTmpBuf += "  movl " + to_string(*(it2->second.offset)) + "(%rbp), %eax\n";
                    assemblyTmpBuf += "  movl %eax, " + to_string(*(it->second.offset)) + "(%rbp)\n";
                } else {
                    hasError = true;
                    cout << "[visitVar_aff] Erreur affectation de la variable '" << retExprInfo.varExprName << "' qui n'a pas été déclarée !" << endl;
                }
            }
            return *(it->second.val);
        } else {
            hasError = true;
            cout << "[visitVar_aff] Erreur la variable '" << name << "' n'a pas été déclarée !" << endl;
        }
        return 0;
        */
    }

    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext * ctx) override {
        Expr * expr = (Expr *)visit(ctx->expr());
        Instr * ret = new ReturnInstr(ctx->start->getLine(), expr);
        return ret;
    }

    virtual antlrcpp::Any visitPar(ifccParser::ParContext * ctx) override {
        return (int)visit(ctx->expr());
    }

    virtual antlrcpp::Any visitAdd(ifccParser::AddContext * ctx) override {
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));
        BinaryOperator binaryOperatorPlus = PLUS;

        Expr * ret = new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorPlus);

        return ret;
    }

    virtual antlrcpp::Any visitLess(ifccParser::LessContext * ctx) override {
        //return (int)visit(ctx->expr(0)) - (int)visit(ctx->expr(1));
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));

        BinaryOperator binaryOperatorMinus = MINUS;

        Expr * ret = new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorMinus);

        return ret;
    }

    virtual antlrcpp::Any visitDiv(ifccParser::DivContext * ctx) override {
        //return (int)visit(ctx->expr(0)) / (int)visit(ctx->expr(1));
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));

        BinaryOperator binaryOperatorDiv = DIV;

        Expr * ret = new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorDiv);

        return ret;
    }

    virtual antlrcpp::Any visitMult(ifccParser::MultContext * ctx) override {
        Expr * op1 = (Expr *)visit(ctx->expr(0));
        Expr * op2 = (Expr *)visit(ctx->expr(1));

        BinaryOperator binaryOperatorMult = MULT;

        Expr * ret = new OpBin(ctx->start->getLine(), op1, op2, binaryOperatorMult);

        return ret;
        /*
        exprInfo ret0 = visit(ctx->expr(0));
        exprInfo ret1 = visit(ctx->expr(1));

        exprInfo ret;
        exprInfo retCopie;

        ret.isConst = true;
        ret.value = new int;
        *((int *)ret.value) = (*((int *)ret0.value)) * (*((int *)ret1.value));

        map<string, varInfo>::iterator it;

        if ((ret0.isConst && !ret1.isConst) || (!ret0.isConst && ret1.isConst)) {
            int constValue;
            if (ret0.isConst && !ret1.isConst) {
                it = variables.find(ret1.varExprName);
                retCopie = ret1;
                constValue = (*((int *)ret0.value));
            }

            else {
                it = variables.find(ret0.varExprName);
                retCopie = ret0;
                constValue = (*((int *)ret1.value));
            }

            if (it != variables.end()) {

                //à quoi sert cette vérif ?
                assemblyTmpBuf += "  movl " + to_string(*(it->second.offset)) + "(%rbp), %eax\n";
                assemblyTmpBuf += "  imul $" + to_string(constValue) + ", %eax\n";
            } else {
                hasError = true;
                cout << "[visitMult] Erreur multiplication de la variable '" << retCopie.varExprName << "' qui n'a pas été déclarée !" << endl;
            }
        }
        */

        /*
    if (!ret0.isConst && !ret1.isConst)
    {

      it = variables.find(ret0.varExprName);
      map<string, varInfo>::iterator it2 = variables.find(ret1.varExprName);

      if (it != variables.end() && it2 != variables.end())
      {
        if (it->second.val != nullptr && it2->second.val != nullptr)
        {
          //à quoi sert cette vérif ?
          assemblyTmpBuf += "  movl " + to_string(*(it->second.offset)) +
    "(%rbp), %eax\n"; assemblyTmpBuf += "  imul $" + to_string(ret0.value) + ",
    %eax\n";
        }
      }

      else
      {
        hasError = true;
        if (it == variables.end())
        {
          cout << "[visitMult] Erreur multiplication de la variable '" <<
    retExprInfo.varExprName << "' qui n'a pas été déclarée !" << endl;
        }

        //2 variables
      }
    }
    */
        //return ret;
    }

    virtual antlrcpp::Any visitConst(ifccParser::ConstContext * ctx) override {

        Expr * test = new ConstLiteral(ctx->start->getLine(), stoi(ctx->getText()));

        return test;

        /*exprInfo ret;

        ret.isConst = true;
        ret.value = new int;
        *((int *)ret.value) = stoi(ctx->CONST()->getText());
        return ret;
        */
    }

    virtual antlrcpp::Any visitVar(ifccParser::VarContext * ctx) override {
        Expr * ret = new Var(ctx->start->getLine(), ctx->getText());
        return ret;
        /*exprInfo ret;
        ret.isConst = false;
        string varName = ctx->VAR_NAME()->getText();
        ret.varExprName = varName;
        ret.value = nullptr;
        map<string, varInfo>::iterator it = variables.find(varName);
        if (it != variables.end()) {
            if (it->second.val != nullptr) {
                ret.value = new int;
                *((int *)ret.value) = *(it->second.val);
            }
            if (it->second.offset == nullptr) {
                variablesOffset -= 4; // 4 pour INT
                it->second.offset = new int;
                *(it->second.offset) = variablesOffset;
            }
        } else {
            hasError = true;
            cout << "[visitVar] Erreur la variable '" << varName
                 << "' n'a pas été déclarée !" << endl;
        }
        return ret;
        */
    }

  protected:
    map<string, varInfo> variables; // key = name
    int variablesOffset = 0;
    string assembly;
    string assemblyTmpBuf;
    bool hasError = false;
};
