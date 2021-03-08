#ifndef AST_H
#define AST_H

#include "SymbolTable.h"

#include <vector>
using namespace std;

enum BinaryOperator
{
    PLUS,
    MINUS,
    MULT
};

//---------- Interface de la classe <Node> ----------------
class Node
{
public:
    //----------------------------------------------------- Méthodes publiques
    int GetLine();
    //-------------------------------------------- Constructeurs - destructeur
    Node(int line) : line(line){};
    ~Node() {}

protected:
    int line;
};

//---------- Interface de la classe <Expr> ----------------
class Expr : public Node
{
public:
    //-------------------------------------------- Constructeurs - destructeur
    Expr(int line) : Node(line){};
    ~Expr() {}
};

//---------- Interface de la classe <Var> ----------------
class Var : public Expr
{
public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    //-------------------------------------------- Constructeurs - destructeur
    Var(int line, string name) : Expr(line), name(name){};
    ~Var() {}

protected:
    string name;
};

//---------- Interface de la classe <ConstLiteral> ----------------
class ConstLiteral : public Expr
{
public:
    //----------------------------------------------------- Méthodes publiques
    int GetValue();
    //-------------------------------------------- Constructeurs - destructeur
    ConstLiteral(int line, int value) : Expr(line), value(value){};
    ~ConstLiteral() {}

protected:
    int value;
};

//---------- Interface de la classe <OpBin> ----------------
class OpBin : public Expr
{
public:
    //----------------------------------------------------- Méthodes publiques
    Expr *GetOperand1();
    Expr *GetOperand2();
    BinaryOperator GetOp();

    //-------------------------------------------- Constructeurs - destructeur
    OpBin(int line, Expr *operand1, Expr *operand2, BinaryOperator op) : Expr(line), operand1(operand1), operand2(operand2), op(op){};
    ~OpBin() {}

protected:
    Expr *operand1;
    Expr *operand2;
    BinaryOperator op;
};

//---------- Interface de la classe <Instr> ----------------
class Instr : public Node
{
public:
    //-------------------------------------------- Constructeurs - destructeur
    Instr(int line) : Node(line){};
    ~Instr() {}
};

//---------- Interface de la classe <ReturnInstr> ----------------
class ReturnInstr : public Instr
{
public:
    //----------------------------------------------------- Méthodes publiques
    Expr *GetReturnExpr();
    //-------------------------------------------- Constructeurs - destructeur
    ReturnInstr(int line, Expr *expr) : Instr(line), returnExpr(expr){};
    ~ReturnInstr() {}

protected:
    Expr *returnExpr;
};

//---------- Interface de la classe <VarAffInstr> ----------------
class VarAffInstr : public Instr
{
public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    Expr *GetRightExpr();
    //-------------------------------------------- Constructeurs - destructeur
    VarAffInstr(int line, string name, Expr *rightExprp) : Instr(line), name(name), rightExpr(rightExpr){};
    ~VarAffInstr() {}

protected:
    string name;
    Expr *rightExpr;
};

//---------- Interface de la classe <Program> ----------------
class Program : public Node
{
public:
    //----------------------------------------------------- Méthodes publiques
    vector<Instr *> GetListInstr();
    SymbolTable GetSymbolTable();
    void AddInstr(Instr *instr);
    string GenerateAsm();
    //-------------------------------------------- Constructeurs - destructeur
    Program(int l) : Node(l) {}
    ~Program() {}

protected:
    vector<Instr *> listInstr;
    SymbolTable symbolTable;
};

#endif