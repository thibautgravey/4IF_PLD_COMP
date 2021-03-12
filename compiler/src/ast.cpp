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

string OpBin::GenerateAsmOpBin(SymbolTable & symbolTable, string & assembly) {
    string tmpVar1;
    string tmpVar2;

    if (dynamic_cast<OpBin *>(operand1)) {
        OpBin * opBin = dynamic_cast<OpBin *>(operand1);
        tmpVar1 = opBin->GenerateAsmOpBin(symbolTable, assembly);

    } else if (dynamic_cast<ConstLiteral *>(operand1)) {
        ConstLiteral * constLiteral = dynamic_cast<ConstLiteral *>(operand1);
        tmpVar1 = symbolTable.CreateTempVar("main", INT);
        assembly += "   movl $" + to_string(constLiteral->GetValue()) + ", " + to_string(symbolTable.GetVariableOffset("main", tmpVar1)) + "(%rbp)\n";

    } else if (dynamic_cast<Var *>(operand1)) {
        Var * var = dynamic_cast<Var *>(operand1);
        tmpVar1 = var->GetName();
    }

    if (dynamic_cast<OpBin *>(operand2)) {
        OpBin * opBin = dynamic_cast<OpBin *>(operand2);
        tmpVar2 = opBin->GenerateAsmOpBin(symbolTable, assembly);

    } else if (dynamic_cast<ConstLiteral *>(operand2)) {
        ConstLiteral * constLiteral = dynamic_cast<ConstLiteral *>(operand2);
        tmpVar2 = symbolTable.CreateTempVar("main", INT);
        assembly += "   movl $" + to_string(constLiteral->GetValue()) + ", " + to_string(symbolTable.GetVariableOffset("main", tmpVar2)) + "(%rbp)\n";

    } else if (dynamic_cast<Var *>(operand2)) {
        Var * var = dynamic_cast<Var *>(operand2);
        tmpVar2 = var->GetName();
    }

    string tmpVarRes = symbolTable.CreateTempVar("main", INT);
    assembly += "   movl " + to_string(symbolTable.GetVariableOffset("main", tmpVar1)) + "(%rbp), %eax\n";

    switch (op) {
        case PLUS:
            assembly += "   addl " + to_string(symbolTable.GetVariableOffset("main", tmpVar2)) + "(%rbp), %eax\n";
            break;
        case MULT:
            assembly += "   imull " + to_string(symbolTable.GetVariableOffset("main", tmpVar2)) + "(%rbp), %eax\n";
            break;
        case MINUS:
            assembly += "   subl " + to_string(symbolTable.GetVariableOffset("main", tmpVar2)) + "(%rbp), %eax\n";
            break;
        case DIV:
            //TODO : Div op
            break;
    }

    assembly += "   movl %eax, " + to_string(symbolTable.GetVariableOffset("main", tmpVarRes)) + "(%rbp)\n";

    return tmpVarRes;
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
        string tmpVarRes = opBin->GenerateAsmOpBin(symbolTable, instrAssembly);
        instrAssembly += "   movl " +
                         to_string(symbolTable.GetVariableOffset("main", tmpVarRes)) +
                         "(%rbp), %eax\n";
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
        string tmpVarRes = opBin->GenerateAsmOpBin(symbolTable, instrAssembly);
        instrAssembly += "   movl " +
                         to_string(symbolTable.GetVariableOffset("main", tmpVarRes)) +
                         "(%rbp), %eax\n";
        instrAssembly += "   movl %eax, " +
                         to_string(symbolTable.GetVariableOffset("main", name)) +
                         "(%rbp)\n";
    }

    return instrAssembly;
}

//------- Réalisation de la classe <Program> ---
vector<Instr *> Program::GetListInstr() {
    return this->listInstr;
}

SymbolTable & Program::GetSymbolTable() {
    return this->symbolTable;
} //----- Fin de GetSymbolTable

void Program::AddInstr(Instr * instr) {
    this->listInstr.push_back(instr);
} //----- Fin de AddInstr

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
} //----- Fin de GenerateAsm

void Program::UnusedVariableAnalysis() const {
    this->symbolTable.UnusedVariableAnalysis();
} //----- Fin de UnusedVariableAnalysis

void Program::SetErrorFlag(bool flag) {
    this->errorFlag = flag;
} //----- Fin de SetErrorFlag

bool Program::GetErrorFlag() {
    return this->errorFlag;
} //----- Fin de GetErrorFlag