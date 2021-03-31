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
int32_t ConstLiteral::GetValue() const {
    return this->value;
}

string ConstLiteral::GenerateIR(CFG * cfg) {
    string tmpVar = cfg->GetSymbolTable()->CreateTempVar("main", Type::INT32_T);
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::ldconst, Type::INT32_T, {tmpVar, to_string(this->GetValue())});
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
    string tmpVar1 = this->operand1->GenerateIR(cfg);
    string tmpVar2 = this->operand2->GenerateIR(cfg);
    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar("main", Type::INT32_T);
    switch (this->op) {
        case BinaryOperator::PLUS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::add, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::MINUS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::sub, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::MULT:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::mul, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::DIV:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::div, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::OR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::orB, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::AND:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::andB, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::XOR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::xorB, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::EQUAL:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_eq, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::NEQUAL:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_neq, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::GREATER:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_g, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::GREATERE:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_ge, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::LESS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_l, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::LESSE:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_le, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::CDTAND:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cdtAnd, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
            break;
        case BinaryOperator::CDTOR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cdtOr, Type::INT32_T, {tmpResVar, tmpVar1, tmpVar2});
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
    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar("main", Type::INT32_T);
    switch (this->op) {
        case UnitOperator::NOT:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::neg, Type::INT32_T, {tmpResVar, tmpVar1});
            break;
        case UnitOperator::OPP:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::opp, Type::INT32_T, {tmpResVar, tmpVar1});
            break;
        default:
            break;
    }
    return tmpResVar;
}

OpUn::~OpUn() {
    delete (operand);
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

VarAffInstr::~VarAffInstr() {
    delete (rightExpr);
}

void VarAffInstr::GenerateIR(CFG * cfg) {
    VarAffInstr * tmpInstr = this;
    while (tmpInstr != nullptr) {
        string tmpVar = tmpInstr->rightExpr->GenerateIR(cfg);
        cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, cfg->GetSymbolTable()->GetVariableType("main", tmpInstr->name), {tmpInstr->name, tmpVar});
        tmpInstr = dynamic_cast<VarAffInstr *>(tmpInstr->varAffInstrNext);
    }
}

//---------------//
//  IfElseInstr  //
//---------------//

Expr * IfElseInstr::GetIfExpr() {
    return ifExpr;
}

BlockInstr * IfElseInstr::GetIfBlock() {
    return ifBlock;
}

BlockInstr * IfElseInstr::GetElseBlock() {
    return elseBlock;
}

void IfElseInstr::GenerateIR(CFG * cfg) {
    BasicBlock *ifBB, *elseBB, *endif;

    // Génération IR test if et enregistrement du résultat
    cfg->GetCurrentBB()->test_var_name = ifExpr->GenerateIR(cfg);

    // Création du BB de fin de if
    endif = new BasicBlock(cfg, cfg->new_BB_name());

    // Création du BB pour le ifblock
    ifBB = new BasicBlock(cfg, cfg->new_BB_name());
    cfg->GetCurrentBB()->exit_true = ifBB;

    // Création du BB pour le elseBlock si besoin
    if (elseBlock != nullptr) {
        elseBB = new BasicBlock(cfg, cfg->new_BB_name());
        cfg->GetCurrentBB()->exit_false = elseBB;
    } else {
        cfg->GetCurrentBB()->exit_false = endif;
    }

    // Ajout des instructions ifBB
    cfg->add_bb(ifBB);
    ifBlock->GenerateIR(cfg);
    cfg->GetCurrentBB()->exit_true = endif;

    // Ajout des instructins elseBB si besoin
    if (elseBlock != nullptr) {
        cfg->add_bb(elseBB);
        elseBlock->GenerateIR(cfg);
        cfg->GetCurrentBB()->exit_true = endif;
    }

    cfg->add_bb(endif);
}

IfElseInstr::~IfElseInstr() {
    delete (ifExpr);
    delete (ifBlock);
    delete (elseBlock);
} //----- Fin de ~IfElseInstr

//----------------//
//   BlockInstr   //
//----------------//

vector<Instr *> BlockInstr::GetListInstr() {
    return listInstr;
}

void BlockInstr::GenerateIR(CFG * cfg) {

    // TODO: change scope at the begining and the end of the block
    //cfg->enterblock();

    for (Instr * instr : listInstr) {
        instr->GenerateIR(cfg);
    }

    //cfg->leaveblock();
}

void BlockInstr::AddInstr(Instr * instr) {
    listInstr.push_back(instr);
}

BlockInstr::~BlockInstr() {
    for (const auto & instr : listInstr) {
        delete (instr);
    }
} //----- Fin de ~BlockInstr

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

    // TODO : foreach function definition
    CFG * tmpCFG = new CFG(&(this->symbolTable));

    // EMPTY BB FOR PROLOGUE
    BasicBlock * entry = new BasicBlock(tmpCFG, tmpCFG->new_BB_name("prologue"));

    // EMPTY BB FOR EPILOGUE
    BasicBlock * output = new BasicBlock(tmpCFG, tmpCFG->new_BB_name("epilogue"));

    BasicBlock * body = new BasicBlock(tmpCFG, tmpCFG->new_BB_name());

    tmpCFG->add_bb(entry);

    entry->exit_true = body;
    tmpCFG->add_bb(body);
    tmpCFG->bb_epilogue = output;

    // TODO : move this INT32_To GenerateIR of function definition
    for (Instr * instr : this->listInstr) {
        instr->GenerateIR(tmpCFG);
    }

    tmpCFG->GetCurrentBB()->exit_true = output;
    tmpCFG->add_bb(output);

    ir->AddCFG(tmpCFG);

    return ir;
}