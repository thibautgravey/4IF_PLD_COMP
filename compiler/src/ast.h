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
    AND,
    CDTAND,
    CDTOR,
    EQUAL,
    NEQUAL,
    GREATER,
    GREATERE,
    LESS,
    LESSE

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

    string GetScope() const;
    //-------------------------------------------- Constructeurs - destructeur
    Expr(int line, string scope)
        : Node(line), scope(scope){};

    virtual ~Expr() = default;

  protected:
    string scope;
};

//---------- Interface de la classe <Var> ----------------
class ExprVarRvalue : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    virtual string GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    ExprVarRvalue(int line, string name, string scope)
        : Expr(line, scope), name(name){};

    virtual ~ExprVarRvalue() = default;

  protected:
    string name;
};

//---------- Interface de la classe <ExprVarLvalue> ----------------
class ExprVarLvalue : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    string GetName();
    virtual string GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    ExprVarLvalue(int line, string name, string scope)
        : Expr(line, scope), name(name){};

    virtual ~ExprVarLvalue() = default;

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
    ConstLiteral(int line, int32_t value, string scope)
        : Expr(line, scope), value(value){};

    virtual ~ConstLiteral() = default;

  protected:
    int32_t value;
};

//---------- Interface de la classe <ConstLiteral> ----------------
class CharLiteral : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    char GetValue() const;
    virtual string GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    CharLiteral(int line, char value, string scope)
        : Expr(line, scope), value(value){};

    virtual ~CharLiteral() = default;

  protected:
    char value;
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
    OpBin(int line, Expr * operand1, Expr * operand2, BinaryOperator op, string scope)
        : Expr(line, scope), operand1(operand1), operand2(operand2), op(op){};

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
    OpUn(int line, Expr * operand, UnitOperator op, string scope)
        : Expr(line, scope), operand(operand), op(op){};

    virtual ~OpUn();

  protected:
    Expr * operand;
    UnitOperator op;
};

//---------- Interface de la classe <Function> ----------------
class Function : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    vector<Expr *> GetParams();
    string GetName();
    void SetParams(vector<Expr *> params);
    virtual string GenerateIR(CFG * cfg);

    //-------------------------------------------- Constructeurs - destructeur
    Function(int line, string name, string scope)
        : Expr(line, scope), name(name){};

    virtual ~Function();

  protected:
    vector<Expr *> params;
    string name;
};

//---------- Interface de la classe <Instr> ----------------
class Instr : public Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    virtual void GenerateIR(CFG * cfg) = 0;

    string GetScope() const;
    //-------------------------------------------- Constructeurs - destructeur
    Instr(int line, string scope)
        : Node(line), scope(scope){};

    virtual ~Instr() = default;

  protected:
    string scope;
};

//---------- Interface de la classe <ReturnInstr> ----------------
class ReturnInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetReturnExpr();
    virtual void GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    ReturnInstr(int line, Expr * expr, string scope)
        : Instr(line, scope), returnExpr(expr){};

    virtual ~ReturnInstr();

  protected:
    Expr * returnExpr;
};

//---------- Interface de la classe <VarAffInstr> ----------------
class ExprAffectation : public Expr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetLValue();
    Expr * GetRValue();
    virtual string GenerateIR(CFG * cfg);

    //-------------------------------------------- Constructeurs - destructeur
    ExprAffectation(Expr * lValue, Expr * rValue, int line, string scope)
        : Expr(line, scope), lValue(lValue), rValue(rValue) {};

    virtual ~ExprAffectation();

  protected:
    Expr * lValue;
    Expr * rValue;
};

//---------- Interface de la classe <ExprInstr> ----------------
class ExprInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    virtual void GenerateIR(CFG * cfg);

    //-------------------------------------------- Constructeurs - destructeur
    ExprInstr(int line, Expr * expr, string scope)
        : Instr(line, scope), expr(expr){};
    virtual ~ExprInstr();

  protected:
    Expr * expr;
};

//---------- Interface de la classe <DefFuncInstr> ----------------
class DefFuncInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    void AddInstr(Instr * instr);
    Type GetType();
    string GetName();
    vector<Instr *> GetListInstr();
    virtual void GenerateIR(CFG * cfg);

    //-------------------------------------------- Constructeurs - destructeur
    DefFuncInstr(int line, string name, Type type, string scope)
        : Instr(line, scope), name(name), type(type) {}

    virtual ~DefFuncInstr();

  protected:
    Type type;
    string name;
    vector<Instr *> listInstr;
};

class BlockInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    vector<Instr *> GetListInstr();
    virtual void GenerateIR(CFG * cfg);
    void AddInstr(Instr * instr);
    //-------------------------------------------- Constructeurs - destructeur
    BlockInstr(int line, string scope)
        : Instr(line, scope){};

    virtual ~BlockInstr();

  protected:
    vector<Instr *> listInstr;
};

class IfElseInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetIfExpr();
    BlockInstr * GetIfBlock();
    BlockInstr * GetElseBlock();
    virtual void GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    IfElseInstr(int line, Expr * expr, BlockInstr * ifBlock, BlockInstr * elseBlock, string scope)
        : Instr(line, scope), ifExpr(expr), ifBlock(ifBlock), elseBlock(elseBlock){};

    virtual ~IfElseInstr();

  protected:
    Expr * ifExpr;
    BlockInstr * ifBlock;
    BlockInstr * elseBlock;
};

class WhileInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    Expr * GetWhileExpr();
    BlockInstr * GetWhileBlock();
    virtual void GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    WhileInstr(int line, Expr * expr, BlockInstr * whileBlock, string scope)
        : Instr(line, scope), whileExpr(expr), whileBlock(whileBlock){};

    virtual ~WhileInstr();

  protected:
    Expr * whileExpr;
    BlockInstr * whileBlock;
};

class ForInstr : public Instr {
  public:
    //----------------------------------------------------- Méthodes publiques
    vector<Expr *> GetInitExprs();
    Expr * GetConditionnalExpr();
    vector<Expr *> GetUpdateExprs();
    BlockInstr * GetForBlock();
    virtual void GenerateIR(CFG * cfg);
    //-------------------------------------------- Constructeurs - destructeur
    ForInstr(int line, vector<Expr *> init, Expr * cond, vector<Expr *> update, BlockInstr * block, string scope)
        : Instr(line, scope), initExprs(init), conditionnalExpr(cond), updateExprs(update), forBlock(block){};

    virtual ~ForInstr();

  protected:
    vector<Expr *> initExprs;
    Expr * conditionnalExpr;
    vector<Expr *> updateExprs;
    BlockInstr * forBlock;
};

//---------- Interface de la classe <Program> ----------------
class Program : public Node {
  public:
    //----------------------------------------------------- Méthodes publiques
    vector<Instr *> GetListInstr();
    SymbolTable & GetSymbolTable();
    void AddInstr(Instr * instr);
    void UnusedVariableAnalysis() const;
    void UnusedFunctionAnalysis() const;
    void FunctionReturnAnalysis() const;
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