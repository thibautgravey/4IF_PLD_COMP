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
    string tmpVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), Type::INT);
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

OpBin::~OpBin() {
    delete (operand1);
    delete (operand2);
}

string OpBin::GenerateIR(CFG * cfg) {
    // TODO: changer les types
    string tmpVar1 = this->operand1->GenerateIR(cfg);
    string tmpVar2 = this->operand2->GenerateIR(cfg);
    string tmpResVar;
    if (this->op != BinaryOperator::EQ) {
        tmpResVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), Type::INT);
    }

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
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::div, Type::INT, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::OR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::orB, Type::INT, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::AND:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::andB, Type::INT, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::XOR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::xorB, Type::INT, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::EQ:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, Type::INT, {tmpVar1, tmpVar2});
            tmpResVar = tmpVar1;
            break;
        default:
            break;
    }
    return tmpResVar;
}

//------- Réalisation de la classe <OpUn> ---
Expr * OpUn::GetOperand() {
    return this->operand;
}

UnitOperator OpUn::GetOp() {
    return this->op;
}

string OpUn::GenerateIR(CFG * cfg) {
    string tmpVar1 = this->operand->GenerateIR(cfg);
    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), Type::INT);
    switch (this->op) {
        case UnitOperator::NOT:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::neg, Type::INT, {tmpResVar, tmpVar1});
            break;
        case UnitOperator::OPP:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::opp, Type::INT, {tmpResVar, tmpVar1});
            break;
        default:
            break;
    }
    return tmpResVar;
}

OpUn::~OpUn() {
    delete (operand);
}

//------- Réalisation de la classe <Function> ---
vector<Expr *> Function::GetParams() {
    return params;
}

string Function::GetName() {
    return name;
}

void Function::SetParams(vector<Expr *> params) {
    this->params = params;
}

string Function::GenerateIR(CFG * cfg) {
    // TODO : a voir pour le type
    // TODO : a voir pour la destination (pour l'instant : reg1)
    vector<string> paramsIRInstr = {this->name, "reg1"};
    for (Expr * param : this->params) {
        paramsIRInstr.push_back(param->GenerateIR(cfg));
    }
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::call, Type::INT, paramsIRInstr);

    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), Type::INT);
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, Type::INT, {tmpResVar, "reg1"});

    // TODO: vérifier pour le registre
    return tmpResVar;
}

Function::~Function() {
    for (Expr * param : params) {
        delete (param);
    }
}

//------- Réalisation de la classe <Instr> ---

//------- Réalisation de la classe <ReturnInstr> ---
Expr * ReturnInstr::GetReturnExpr() {
    return this->returnExpr;
}

ReturnInstr::~ReturnInstr() {
    delete (returnExpr);
}

void ReturnInstr::GenerateIR(CFG * cfg) {
    string tmpRetVar = this->returnExpr->GenerateIR(cfg);
    // TODO : voir pour le type (ex : si c'est une fonction)
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::ret, cfg->GetSymbolTable()->GetVariableType(cfg->GetName(), tmpRetVar), {tmpRetVar});
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

VarAffInstr::~VarAffInstr() {
    delete (rightExpr);
}

void VarAffInstr::GenerateIR(CFG * cfg) {
    VarAffInstr * tmpInstr = this;
    while (tmpInstr != nullptr) {
        string tmpVar = tmpInstr->rightExpr->GenerateIR(cfg);
        cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, cfg->GetSymbolTable()->GetVariableType(cfg->GetName(), tmpInstr->name), {tmpInstr->name, tmpVar});
        tmpInstr = dynamic_cast<VarAffInstr *>(tmpInstr->varAffInstrNext);
    }
}

Type VarAffInstr::GetType() {
    return this->type;
}

//------- Réalisation de la classe <ExprInstr> ---
void ExprInstr::GenerateIR(CFG * cfg) {
    this->expr->GenerateIR(cfg);
}

//------- Réalisation de la classe <Param> ---
Param::~Param() {
}

//------- Réalisation de la classe <DefFuncInstr> ---
void DefFuncInstr::AddInstr(Instr * instr) {
    listInstr.push_back(instr);
}

Type DefFuncInstr::GetType() {
    return type;
}

string DefFuncInstr::GetName() {
    return name;
}

vector<Instr *> DefFuncInstr::GetListInstr() {
    return listInstr;
}

void DefFuncInstr::GenerateIR(CFG * cfg) {
    // EMPTY BB FOR PROLOGUE
    BasicBlock * entry = new BasicBlock(cfg, cfg->new_BB_name("prologue"));

    cfg->add_bb(entry);

    BasicBlock * body = new BasicBlock(cfg, cfg->new_BB_name());

    entry->exit_true = body;
    cfg->add_bb(body);

    // TODO: recuperer les variables passees en arguments
    vector<FunctionParam *> functionParams = cfg->GetSymbolTable()->GetFunctionParams(cfg->GetName());
    for (int i = 0; i < functionParams.size(); i++) {
        string reg = "paramReg" + to_string(i + 1);
        cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, functionParams[i]->type, {functionParams[i]->name, reg});
    }

    // TO DO : move this into GenerateIR of function definition
    for (Instr * instr : this->GetListInstr()) {
        instr->GenerateIR(cfg);
    }

    // EMPTY BB FOR EPILOGUE
    BasicBlock * output = new BasicBlock(cfg, cfg->new_BB_name("epilogue"));

    body->exit_true = output;
    cfg->add_bb(output);
}

DefFuncInstr::~DefFuncInstr() {
    for (Instr * instr : listInstr) {
        delete (instr);
    }
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

void Program::UnusedVariableAnalysis() const {
    this->symbolTable.UnusedVariableAnalysis();
} //----- Fin de UnusedVariableAnalysis

void Program::UnusedFunctionAnalysis() const {
    this->symbolTable.UnusedFunctionAnalysis();
}

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

    for (Instr * instr : this->listInstr) {
        // TODO: deplacer tout ce code dans GenerateIR de DefFuncInstr (besoin d'un CFG contenant tout les autres CFG ?)

        // Normally all instructions in listInstr are def function instruction
        DefFuncInstr * defFuncInstr = dynamic_cast<DefFuncInstr *>(instr);

        CFG * tmpCFG = new CFG(&(this->symbolTable), defFuncInstr->GetName());

        defFuncInstr->GenerateIR(tmpCFG);

        ir->AddCFG(tmpCFG);
    }

    return ir;
}