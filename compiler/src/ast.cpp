#include "ast.h"

//------- Réalisation de la classe <Node> ---
int Node::GetLine() const {
    return this->line;
}

//------- Réalisation de la classe <Expr> ---

//------- Réalisation de la classe <Var> ---
string Var::GetName() {
    return this->name;
}

//------- Réalisation de la classe <ConstLiteral> ---
int ConstLiteral::GetValue() const {
    return this->value;
}

//------- Réalisation de la classe <OpBin> ---
Expr * OpBin::GetOperand1() {
    return this->operand1;
}

Expr * OpBin::GetOperand2() {
    return this->operand2;
}

BinaryOperator OpBin::GetOp() {
    return this->op;
}

//------- Réalisation de la classe <Instr> ---

//------- Réalisation de la classe <ReturnInstr> ---
Expr * ReturnInstr::GetReturnExpr() {
    return this->returnExpr;
}

string ReturnInstr::GenerateAsm(SymbolTable & symbolTable) {
    string instrAssembly;
    if (dynamic_cast<ConstLiteral *>(returnExpr)) {
        ConstLiteral * constLiteral = dynamic_cast<ConstLiteral *>(returnExpr);
        instrAssembly = "   movl $" + to_string(constLiteral->GetValue()) + ", %eax\n";
    } else if (dynamic_cast<Var *>(returnExpr)) {
        Var * var = dynamic_cast<Var *>(returnExpr);
        instrAssembly = "   movl " + to_string(symbolTable.GetVariableOffset("main", var->GetName())) + "(%rbp), %eax\n";
    } else if (dynamic_cast<OpBin *>(returnExpr)) {
        OpBin * opBin = dynamic_cast<OpBin *>(returnExpr);
    }
    return instrAssembly;
}

//------- Réalisation de la classe <VarAffInstr> ---
string VarAffInstr::GetName() {
    return this->name;
}

Expr * VarAffInstr::GetRightExpr() {
    return this->rightExpr;
}

string VarAffInstr::GenerateAsm(SymbolTable & symbolTable) {
    string instrAssembly;
    if (dynamic_cast<ConstLiteral *>(rightExpr)) {
        ConstLiteral * constLiteral = dynamic_cast<ConstLiteral *>(rightExpr);
        instrAssembly = "   movl $" +
                        to_string(constLiteral->GetValue()) +
                        ", " +
                        to_string(symbolTable.GetVariableOffset("main", name)) +
                        "(%rbp)\n";
    } else if (dynamic_cast<Var *>(rightExpr)) {
        Var * var = dynamic_cast<Var *>(rightExpr);
        instrAssembly = "   movl " +
                        to_string(symbolTable.GetVariableOffset("main", var->GetName())) +
                        "(%rbp), %eax\n";
        instrAssembly += "   movl %eax, " +
                         to_string(symbolTable.GetVariableOffset("main", name)) +
                         "(%rbp)\n";
    } else if (dynamic_cast<OpBin *>(rightExpr)) {
        OpBin * opBin = dynamic_cast<OpBin *>(rightExpr);
    }

    return instrAssembly;
}

//------- Réalisation de la classe <Program> ---
vector<Instr *> Program::GetListInstr() {
    return this->listInstr;
}

SymbolTable & Program::GetSymbolTable() {
    return this->symbolTable;
}

void Program::AddInstr(Instr * instr) {
    this->listInstr.push_back(instr);
}

string Program::GenerateAsm() {
    string assembly = "   .globl main\n"
                      "\n"
                      "main: \n"
                      "   # prologue\n"
                      "   pushq %rbp\n"
                      "   movq %rsp, %rbp\n"
                      "\n"
                      "   # body\n";

    // AST walk
    vector<Instr *>::iterator it;
    for (it = this->listInstr.begin(); it != this->listInstr.end(); it++) {
        assembly += (*it)->GenerateAsm(this->symbolTable);
    }

    assembly += "\n"
                "   # epilogue\n"
                "   popq %rbp\n"
                "   ret\n";

    return assembly;
}

void Program::SetErrorFlag(bool flag) {
    this->errorFlag = flag;
}

bool Program::GetErrorFlag() {
    return this->errorFlag;
}