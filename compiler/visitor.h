
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include <map>

using namespace std;

typedef struct
{
  string type;
  int *val;
  int *offset;
} varInfo;

typedef struct
{
  bool isConst;
  void *value;
  string varExprName;
} exprInfo;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class Visitor : public ifccVisitor
{
public:
  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override
  {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override
  {

    //int retval = stoi(ctx->CONST()->getText());
    assembly = ".globl	main\n"
               " main: \n"
               "  # prologue\n"
               "  pushq %rbp\n"
               "  movq %rsp, %rbp\n"
               "\n"
               "  # body\n";

    visitChildren(ctx);

    exprInfo retExprInfo = visit(ctx->expr());

    if(retExprInfo.isConst) {
      assembly += "  movl $" + to_string(*((int *) retExprInfo.value)) + ", %eax\n";
    } else {
      map<string, varInfo>::iterator it = variables.find(retExprInfo.varExprName);
      if(it != variables.end()) {
        if(it->second.val == nullptr) {
          cout << "[visitProg] Erreur la variable '" << retExprInfo.varExprName << "' n'a pas de valeur !" << endl;
          assembly += "  movl $0, %eax\n";
        } else {
          assembly += "  movl " + to_string(*((int *) it->second.offset)) + "(%rbp), %eax\n";
        }
      } else {
        cout << "[visitProg] Erreur la variable '" << retExprInfo.varExprName << "' n'a pas été déclarée !" << endl;
        assembly += "  movl $0, %eax\n";
      }
    }

    assembly += "\n"
                "  # epilogue\n"
                "  popq %rbp\n"
                " 	ret\n";

    cout << assembly;

    /*
    map<string, varInfo>::iterator it;
    for (it = variables.begin(); it != variables.end(); it++)
    {
      cout << "Nom : " << it->first << " | Type : " << it->second.type << " | Valeur : ";
      if (it->second.val != nullptr)
      {
        cout << *(it->second.val);
      }
      else
      {
        cout << "[Pas de valeur]";
      }
      cout << endl;
    }
    */

    return 0;
  }

  virtual antlrcpp::Any visitLine(ifccParser::LineContext *ctx) override
  {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVar_decl(ifccParser::Var_declContext *ctx) override
  {
    string type = ctx->TYPE()->getText();
    string name = ctx->VAR_NAME()->getText();

    map<string, varInfo>::iterator it = variables.find(name);

    if (it != variables.end())
    {
      cout << "[visitVar_decl] Erreur la variable '" << name << "' a déjà été déclarée !" << endl;
      return 0;
    }

    int *val = nullptr;
    int *offset = nullptr;

    if (ctx->expr())
    {
      variablesOffset -= 4; // 4 pour INT
      offset = new int;
      *offset = variablesOffset;
      val = new int;
      exprInfo retExprInfo = visit(ctx->expr());

      if (retExprInfo.value == nullptr)
      {
        cout << "[visitVar_decl] Erreur lors du retour de l'expression !" << endl;
        val = nullptr;
      }
      else
      {
        *val = *((int *)retExprInfo.value);

        if (!retExprInfo.isConst)
        {
          int exprVarOffset = *(variables.find(retExprInfo.varExprName)->second.offset);
          assembly += "  movl " + to_string(exprVarOffset) + "(%rbp), %eax\n";
          assembly += "  movl %eax, " + to_string(*offset) + "(%rbp)\n";
        }
        else
        {
          assembly += "  movl $" + to_string((*val)) + ", " + to_string(*offset) + "(%rbp)\n";
        }
      }
    }

    varInfo info = {type, val, offset};

    variables.insert(make_pair(name, info));
    return 0;
  }

  virtual antlrcpp::Any visitVar_aff(ifccParser::Var_affContext *ctx) override
  {
    string name = ctx->VAR_NAME()->getText();

    map<string, varInfo>::iterator it = variables.find(name);

    if (it != variables.end())
    {
      if (it->second.val == nullptr)
      {
        it->second.val = new int;
      }
      exprInfo retExprInfo = visit(ctx->expr());

      if (retExprInfo.value == nullptr)
      {
        cout << "[visitVar_aff] Erreur lors du retour de l'expression !" << endl;
        return 0;
      }
      *(it->second.val) = *((int *)retExprInfo.value);

      if (it->second.offset == nullptr)
      {
        variablesOffset -= 4; // 4 pour INT
        it->second.offset = new int;
        *(it->second.offset) = variablesOffset;
      }

      if (!retExprInfo.isConst)
      {
        int exprVarOffset = *(variables.find(retExprInfo.varExprName)->second.offset);
        assembly += "  movl " + to_string(exprVarOffset) + "(%rbp), %eax\n";
        assembly += "  movl %eax, " + to_string(*(it->second.offset)) + "(%rbp)\n";
      }
      else
      {
        assembly += "  movl $" + to_string(*(it->second.val)) + ", " + to_string(*(it->second.offset)) + "(%rbp)\n";
      }

      return *(it->second.val);
    }
    else
    {
      cout << "[visitVar_aff] Erreur la variable '" << name << "' n'a pas été déclarée !" << endl;
    }
    return 0;
  }

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override
  {
    return (int)visit(ctx->expr());
  }

  virtual antlrcpp::Any visitAdd(ifccParser::AddContext *ctx) override
  {
    return (int)visit(ctx->expr(0)) + (int)visit(ctx->expr(1));
  }

  virtual antlrcpp::Any visitLess(ifccParser::LessContext *ctx) override
  {
    return (int)visit(ctx->expr(0)) - (int)visit(ctx->expr(1));
  }

  virtual antlrcpp::Any visitDiv(ifccParser::DivContext *ctx) override
  {
    return (int)visit(ctx->expr(0)) / (int)visit(ctx->expr(1));
  }

  virtual antlrcpp::Any visitMult(ifccParser::MultContext *ctx) override
  {
    return (int)visit(ctx->expr(0)) * (int)visit(ctx->expr(1));
  }

  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override
  {
    exprInfo ret;

    ret.isConst = true;
    ret.value = new int;
    *((int *)ret.value) = stoi(ctx->CONST()->getText());
    return ret;
  }

  virtual antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override
  {
    exprInfo ret;
    ret.isConst = false;
    string varName = ctx->VAR_NAME()->getText();
    ret.varExprName = varName;
    map<string, varInfo>::iterator it = variables.find(varName);
    if (it != variables.end())
    {
      int *ptrVal = it->second.val;
      if (ptrVal != nullptr)
      {
        ret.value = new int;
        *((int *)ret.value) = *(it->second.val);
      }
      else
      {
        cout << "[visitExpr] Erreur la variable '" << varName << "' n'a pas de valeur !" << endl;
      }
    }
    else
    {
      cout << "[visitExpr] Erreur la variable '" << varName << "' n'a pas été déclarée !" << endl;
    }
    return ret;
  }

protected:
  map<string, varInfo> variables; // key = name
  int variablesOffset = 0;
  string assembly;
};
