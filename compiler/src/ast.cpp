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

string Var::GenerateIR(CFG * cfg) {
    return this->name;
}

//------- Réalisation de la classe <ConstLiteral> ---
int ConstLiteral::GetValue() const {
    return this->value;
}

string ConstLiteral::GenerateIR(CFG * cfg) {
    string tmpVar = cfg->GetSymbolTable()->CreateTempVar("main", Type::INT);
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::ldconst, Type::INT, {tmpVar, to_string(this->GetValue())});
    return tmpVar;
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

OpBin::~OpBin() {
    delete (operand1);
    delete (operand2);
}

string OpBin::GenerateIR(CFG * cfg) {
    string tmpVar1 = this->operand1->GenerateIR(cfg);
    string tmpVar2 = this->operand2->GenerateIR(cfg);
    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar("main", Type::INT);
    switch (this->op) {
        case BinaryOperator::PLUS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::add, Type::INT, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::MINUS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::sub, Type::INT, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::MULT:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::mul, Type::INT, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::DIV:
            break;
        default:
            break;
    }
    return tmpResVar;
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

ReturnInstr::~ReturnInstr() {
    delete (returnExpr);
}

void ReturnInstr::GenerateIR(CFG * cfg) {
    string tmpRetVar = this->returnExpr->GenerateIR(cfg);
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::ret, cfg->GetSymbolTable()->GetVariableType("main", tmpRetVar), {tmpRetVar});
}

//------- Réalisation de la classe <VarAffInstr> ---
string VarAffInstr::GetName() {
    return this->name;
}

Expr * VarAffInstr::GetRightExpr() {
    return this->rightExpr;
}

void VarAffInstr::SetVarAffInstrNext(Instr * next) {
    this->varAffInstrNext = next;
}

Instr * VarAffInstr::GetvarAffInstrNext() {
    return this->varAffInstrNext;
}

string VarAffInstr::GenerateAsm(SymbolTable & symbolTable) {
    string instrAssembly = "";

    VarAffInstr * instr = this;
    Expr * rightExpression;
    string varAffName;

    while (instr != nullptr) {
        rightExpression = instr->GetRightExpr();
        varAffName = instr->GetName();

        if (dynamic_cast<ConstLiteral *>(rightExpression)) {
            ConstLiteral * constLiteral = dynamic_cast<ConstLiteral *>(rightExpression);
            instrAssembly += "   movl $" +
                             to_string(constLiteral->GetValue()) +
                             ", " +
                             to_string(symbolTable.GetVariableOffset("main", varAffName)) +
                             "(%rbp)\n";
        } else if (dynamic_cast<Var *>(rightExpression)) {
            Var * var = dynamic_cast<Var *>(rightExpression);
            instrAssembly += "   movl " +
                             to_string(symbolTable.GetVariableOffset("main", var->GetName())) +
                             "(%rbp), %eax\n";
            instrAssembly += "   movl %eax, " +
                             to_string(symbolTable.GetVariableOffset("main", varAffName)) +
                             "(%rbp)\n";
        } else if (dynamic_cast<OpBin *>(rightExpression)) {
            OpBin * opBin = dynamic_cast<OpBin *>(rightExpression);
            string tmpVarRes = opBin->GenerateAsmOpBin(symbolTable, instrAssembly);
            instrAssembly += "   movl " +
                             to_string(symbolTable.GetVariableOffset("main", tmpVarRes)) +
                             "(%rbp), %eax\n";
            instrAssembly += "   movl %eax, " +
                             to_string(symbolTable.GetVariableOffset("main", varAffName)) +
                             "(%rbp)\n";
        }
        instr = (VarAffInstr *)(instr->GetvarAffInstrNext());
    }

    return instrAssembly;
}

VarAffInstr::~VarAffInstr() {
    delete (rightExpr);
}

void VarAffInstr::GenerateIR(CFG * cfg) {
    string tmpVar = this->rightExpr->GenerateIR(cfg);
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, cfg->GetSymbolTable()->GetVariableType("main", this->name), {this->name, tmpVar});
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
                      "   movq %rsp, %rbp\n";

    // AST walk
    string tmpAssembly;
    vector<Instr *>::iterator it;
    for (it = this->listInstr.begin(); it != this->listInstr.end(); it++) {

        tmpAssembly += (*it)->GenerateAsm(this->symbolTable);
    }

    // Calculate space needed for variables (main function)
    int spaceNeeded = symbolTable.CalculateSpaceForFunction("main");

    // Round space to the nearest multiple of 16
    if (spaceNeeded % 16) {
        spaceNeeded = ((spaceNeeded / 16) + 1) * 16;
    }

    assembly += "   subq $" + to_string(spaceNeeded) + ", %rsp\n";

    assembly += "\n"
                "   # body\n";

    // Add temporary assembly
    assembly += tmpAssembly;

    assembly += "\n"
                "   # epilogue\n"
                "   addq $" +
                to_string(spaceNeeded) +
                ", %rsp\n"
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

Program::~Program() {
    for (const auto & instr : listInstr) {
        delete (instr);
    }
} //----- Fin de ~Program

IR * Program::GenerateIR() {
    IR * ir = new IR();

    // TO DO : foreach function definition
    CFG * tmpCFG = new CFG(&(this->symbolTable));

    BasicBlock * entry = new BasicBlock(tmpCFG, tmpCFG->new_BB_name());
    // TO DO : VOIR POUR LES INSTRUCTIONS DU PROLOGUE

    tmpCFG->add_bb(entry);

    BasicBlock * body = new BasicBlock(tmpCFG, tmpCFG->new_BB_name());

    tmpCFG->add_bb(body);

    // TO DO : move this into GenerateIR of function definition
    for (Instr * instr : this->listInstr) {
        instr->GenerateIR(tmpCFG);
    }

    BasicBlock * output = new BasicBlock(tmpCFG, tmpCFG->new_BB_name());
    // TO DO : VOIR POUR LES INSTRUCTIONS DE L'EPILOGUE

    tmpCFG->add_bb(output);

    ir->AddCFG(tmpCFG);

    return ir;
}