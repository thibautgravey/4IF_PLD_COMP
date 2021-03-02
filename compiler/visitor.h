
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include <map>

using namespace std;

typedef struct {
  string type;
  int * val;
} varInfo;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Visitor : public ifccVisitor {
public:

  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {

    //int retval = stoi(ctx->CONST()->getText());
    visitChildren(ctx);

    cout<<".globl	main\n"
              " main: \n"
              "  # prologue\n"
              "  pushq %rbp\n"
              "  movq %rsp, %rbp\n"
              "\n"
              "  # body\n"
              " 	movl	$"<<42<<", %eax\n"
              "\n"
              "  # epilogue\n"
              "  popq %rbp\n"
              " 	ret\n";

    map<string, varInfo>::iterator it;
    for (it = variables.begin(); it!=variables.end(); it++) {
      cout << "Nom : " << it->first << " | Type : " << it->second.type << " | Valeur : ";
      if(it->second.val != nullptr) {
        cout << *(it->second.val);
      } else {
        cout << "[Pas de valeur]";
      }
      cout << endl;
    }

    return 0;
  }

  virtual antlrcpp::Any visitLine(ifccParser::LineContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecl(ifccParser::DeclContext *ctx) override {
    string type = ctx->TYPE()->getText();
    string name = ctx->VAR_NAME()->getText();

    varInfo info = {type, nullptr};

    variables.insert(make_pair(name, info));
    return 0;
  }

  virtual antlrcpp::Any visitDef(ifccParser::DefContext *ctx) override {

    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAff(ifccParser::AffContext *ctx) override {
    string name = ctx->VAR_NAME()->getText();

    map<string, varInfo>::iterator it = variables.find(name);

    if(it != variables.end()) {
      if(it->second.val == nullptr) {
        it->second.val = new int;
      }
      *(it->second.val) = (int) visit(ctx->expr());
    } else {
      cout << "[visitAff] Erreur la variable " << name << " n'a pas été déclarée !" << endl;
    }
    return 0;
  }

  virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override {
    int val;
    if(ctx->CONST()) {
      val = stoi(ctx->CONST()->getText());
    } else if(ctx->VAR_NAME()) {
      string varName = ctx->VAR_NAME()->getText();
      map<string, varInfo>::iterator it = variables.find(varName);
      if(it != variables.end()) {
        int * ptrVal = it->second.val;
        if(ptrVal != nullptr) {
          val = *(it->second.val);
        } else {
          cout << "[visitExpr] Erreur la variable " << varName << " n'a pas de valeur !" << endl;
        }
      } else {
        cout << "[visitExpr] Erreur la variable " << varName << " n'a pas été déclarée !" << endl;
      }
    }
    return val;
  }

protected:
  map<string, varInfo> variables; // key = name

};

