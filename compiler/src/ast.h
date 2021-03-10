#ifndef AST_H
#define AST_H

#include "SymbolTable.h"

#include <string>
#include <vector>
using namespace std;

enum BinaryOperator {
    PLUS,
    MINUS,
    MULT,
    DIV
};

//---------- Interface de la classe <Node> ----------------
class Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    int GetLine() const;
    //-------------------------------------------- Constructeurs - destructeur
    Node(int line)
        : line(line){};
    virtual ~Node() {}

  protected:
    int line;
};

//---------- Interface de la classe <Expr> ----------------
class Expr : public Node {
  public:
    //-------------------------------------------- Constructeurs - destructeur
    Expr(int line)
        : Node(line){};
    virtual ~Expr() {}
};

//---------- Interface de la classe <Var> ----------------
class Var : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    //-------------------------------------------- Constructeurs - destructeur
    Var(int line, string name)
        : Expr(line), name(name){};
    virtual ~Var() {}

  protected:
    string name;
};

//---------- Interface de la classe <ConstLiteral> ----------------
class ConstLiteral : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    int GetValue() const;
    //-------------------------------------------- Constructeurs - destructeur
    ConstLiteral(int line, int value)
        : Expr(line), value(value){};
    virtual ~ConstLiteral() {}

  protected:
    int value;
};

//---------- Interface de la classe <OpBin> ----------------
class OpBin : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetOperand1();
    Expr * GetOperand2();
    BinaryOperator GetOp();
    string GenerateAsmOpBin(SymbolTable & symbolTable, string & assembly);

    //-------------------------------------------- Constructeurs - destructeur
    OpBin(int line, Expr * operand1, Expr * operand2, BinaryOperator op)
        : Expr(line), operand1(operand1), operand2(operand2), op(op){};
    virtual ~OpBin() {}

  protected:
    Expr * operand1;
    Expr * operand2;
    BinaryOperator op;
};

//---------- Interface de la classe <Instr> ----------------
class Instr : public Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    virtual string GenerateAsm(SymbolTable & symbolTable) = 0;
    //-------------------------------------------- Constructeurs - destructeur
    Instr(int line)
        : Node(line){};
    virtual ~Instr() {}
};

//---------- Interface de la classe <ReturnInstr> ----------------
class ReturnInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetReturnExpr();
    virtual string GenerateAsm(SymbolTable & symbolTable);
    //-------------------------------------------- Constructeurs - destructeur
    ReturnInstr(int line, Expr * expr)
        : Instr(line), returnExpr(expr){};
    virtual ~ReturnInstr() {}

  protected:
    Expr * returnExpr;
};

//---------- Interface de la classe <VarAffInstr> ----------------
class VarAffInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    Expr * GetRightExpr();
    virtual string GenerateAsm(SymbolTable & symbolTable);
    //-------------------------------------------- Constructeurs - destructeur
    VarAffInstr(int line, string name, Expr * rightExpr)
        : Instr(line), name(name), rightExpr(rightExpr){};
    virtual ~VarAffInstr() {}

  protected:
    string name;
    Expr * rightExpr;
};

//---------- Interface de la classe <Program> ----------------
class Program : public Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    vector<Instr *> GetListInstr();
    SymbolTable & GetSymbolTable();
    void AddInstr(Instr * instr);
    string GenerateAsm();
    void SetErrorFlag(bool flag);
    bool GetErrorFlag();
    //-------------------------------------------- Constructeurs - destructeur
    Program(int l)
        : Node(l) {}
    virtual ~Program() {}

  protected:
    vector<Instr *> listInstr;
    SymbolTable symbolTable;
    bool errorFlag;
};

#endif