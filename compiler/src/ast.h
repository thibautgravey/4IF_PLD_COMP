#ifndef AST_H
#define AST_H

#include "IR.h"
#include "SymbolTable.h"

#include <string>
#include <vector>
using namespace std;

enum BinaryOperator {
    PLUS,
    MINUS,
    MULT,
    DIV,
    OR,
    XOR,
    AND
};

enum UnitOperator {
    NOT,
    OPP
};

//---------- Interface de la classe <Node> ----------------
class Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    int GetLine() const;
    //-------------------------------------------- Constructeurs - destructeur
    Node(int line)
        : line(line){};

    virtual ~Node() = default;

  protected:
    int line;
};

//---------- Interface de la classe <Expr> ----------------
class Expr : public Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    virtual string GenerateIR(CFG * cfg) = 0;
    //-------------------------------------------- Constructeurs - destructeur
    Expr(int line)
        : Node(line){};

    virtual ~Expr() = default;
};

//---------- Interface de la classe <Var> ----------------
class Var : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    virtual string GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    Var(int line, string name)
        : Expr(line), name(name){};

    virtual ~Var() = default;

  protected:
    string name;
};

//---------- Interface de la classe <ConstLiteral> ----------------
class ConstLiteral : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    int GetValue() const;
    virtual string GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    ConstLiteral(int line, int32_t value)
        : Expr(line), value(value){};

    virtual ~ConstLiteral() = default;

  protected:
    int32_t value;
};

//---------- Interface de la classe <OpBin> ----------------
class OpBin : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetOperand1();
    Expr * GetOperand2();
    BinaryOperator GetOp();
    virtual string GenerateIR(CFG * cfg);

    //-------------------------------------------- Constructeurs - destructeur
    OpBin(int line, Expr * operand1, Expr * operand2, BinaryOperator op)
        : Expr(line), operand1(operand1), operand2(operand2), op(op){};

    virtual ~OpBin();

  protected:
    Expr * operand1;
    Expr * operand2;
    BinaryOperator op;
};

//---------- Interface de la classe <OpUn> ----------------
class OpUn : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetOperand();
    UnitOperator GetOp();
    virtual string GenerateIR(CFG * cfg);

    //-------------------------------------------- Constructeurs - destructeur
    OpUn(int line, Expr * operand, UnitOperator op)
        : Expr(line), operand(operand), op(op){};

    virtual ~OpUn();

  protected:
    Expr * operand;
    UnitOperator op;
};

//---------- Interface de la classe <Instr> ----------------
class Instr : public Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    virtual void GenerateIR(CFG * cfg) = 0;
    //-------------------------------------------- Constructeurs - destructeur
    Instr(int line)
        : Node(line){};

    virtual ~Instr() = default;
};

//---------- Interface de la classe <ReturnInstr> ----------------
class ReturnInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetReturnExpr();
    virtual void GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    ReturnInstr(int line, Expr * expr)
        : Instr(line), returnExpr(expr){};

    virtual ~ReturnInstr();

  protected:
    Expr * returnExpr;
};

//---------- Interface de la classe <VarAffInstr> ----------------
class VarAffInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    Expr * GetRightExpr();
    void SetVarAffInstrNext(Instr * next);
    Instr * GetvarAffInstrNext();
    virtual void GenerateIR(CFG * cfg);

    //-------------------------------------------- Constructeurs - destructeur
    VarAffInstr(int line, string name, Expr * rightExpr, Instr * next = nullptr)
        : Instr(line), name(name), rightExpr(rightExpr), varAffInstrNext(next){};

    virtual ~VarAffInstr();

  protected:
    string name;
    Expr * rightExpr;
    Instr * varAffInstrNext;
};

class IfElseInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetIfExpr();
    BlockInstr * GetIfBlock();
    BlockInstr * GetElseBlock();
    virtual void GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    IfElseInstr(int line, Expr * expr, BlockInstr* ifBlock,BlockInstr* elseBlock)
        : Instr(line), ifExpr(expr), ifBlock(ifBlock), elseBlock(elseBlock){};

    virtual ~IfElseInstr();

  protected:
    Expr * ifExpr;
    BlockInstr *  ifBlock;
    BlockInstr * elseBlock;
};

class BlockInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    vector<Instr *> GetListInstr();
    virtual void GenerateIR(CFG * cfg);
    void AddInstr(Instr * instr);
    //-------------------------------------------- Constructeurs - destructeur
    BlockInstr(int line)
        : Instr(line){};

    virtual ~BlockInstr();

  protected:
    vector<Instr *>  listInstr;
};


//---------- Interface de la classe <Program> ----------------
class Program : public Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    vector<Instr *> GetListInstr();
    SymbolTable & GetSymbolTable();
    void AddInstr(Instr * instr);
    void UnusedVariableAnalysis() const;
    void SetErrorFlag(bool flag);
    bool GetErrorFlag();
    IR * GenerateIR();
    //-------------------------------------------- Constructeurs - destructeur
    Program(int l)
        : Node(l), errorFlag(false) {}

    virtual ~Program();

  protected:
    vector<Instr *> listInstr;
    SymbolTable symbolTable;
    bool errorFlag;
};

#endif