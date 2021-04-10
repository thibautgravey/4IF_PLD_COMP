#include "ast.h"

//------- Réalisation de la classe <Node> ---
int Node::GetLine() const {
    return this->line;
}

//------- Réalisation de la classe <Expr> ---
string Expr::GetScope() const {
    return this->scope;
}

//------- Réalisation de la classe <Var> ---
string ExprVarRvalue::GetName() {
    return this->name;
}

string ExprVarRvalue::GenerateIR(CFG * cfg) {
    return this->scope + this->name;
}

//------- Réalisation de la classe <Var> ---
string ExprVarLvalue::GetName() {
    return this->name;
}

string ExprVarLvalue::GenerateIR(CFG * cfg) {
    int offset = cfg->GetSymbolTable()->GetVariableOffset(cfg->GetName(), this->name, this->scope);
    string tempVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), Type::INT64_T, this->scope);
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::ldconst, Type::INT64_T, {tempVar, to_string(offset)}, this->scope);
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::add, Type::INT64_T, {tempVar, "base_pointer", tempVar}, this->scope);
    return tempVar;
}

//------- Réalisation de la classe <ConstLiteral> ---
int64_t ConstLiteral::GetValue() const {
    return this->value;
}

string ConstLiteral::GenerateIR(CFG * cfg) {
    return to_string(this->GetValue());
}

//------- Réalisation de la classe <CharLiteral> ---

char CharLiteral::GetValue() const {
    return this->value;
}

string CharLiteral::GenerateIR(CFG * cfg) {
    return to_string((char)this->GetValue());
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
    Type t;

    Type t1 = cfg->GetSymbolTable()->GetVariableType(cfg->GetName(), tmpVar1, this->GetScope());
    Type t2 = cfg->GetSymbolTable()->GetVariableType(cfg->GetName(), tmpVar2, this->GetScope());
    if (t1 != ERROR && t2 != ERROR) {
        if (t1 > t2) {
            t = t1;
        } else {
            t = t2;
        }
    } else {
        if (t1 == ERROR) {
            t = t2;
        } else {
            t = t1;
        }
    }
    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), t, this->GetScope());

    Type typeRes;
    switch (this->op) {
        case BinaryOperator::PLUS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::add, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::MINUS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::sub, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::MULT:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::mul, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::DIV:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::div, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::OR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::orB, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::AND:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::andB, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::XOR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::xorB, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::EQUAL:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_eq, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::NEQUAL:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_neq, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::GREATER:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_g, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::GREATERE:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_ge, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::LESS:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_l, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::LESSE:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cmp_le, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::CDTAND:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cdtAnd, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
            break;
        case BinaryOperator::CDTOR:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::cdtOr, t, {tmpResVar, tmpVar1, tmpVar2}, this->scope);
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
    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), Type::INT32_T, this->GetScope());
    switch (this->op) {
        case UnitOperator::NOT:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::neg, Type::INT32_T, {tmpResVar, tmpVar1}, this->scope);
            break;
        case UnitOperator::OPP:
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::opp, Type::INT32_T, {tmpResVar, tmpVar1}, this->scope);
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
    vector<string> paramsIRInstr = {this->name, "reg1"};
    for (Expr * param : this->params) {
        paramsIRInstr.push_back(param->GenerateIR(cfg));
    }

    if (cfg->GetSymbolTable()->GetFunctionParams(this->name).size() == 0) {
        // si la fonction n'attend pas d'args
        cfg->GetCurrentBB()->add_IRInstr(IRInstr::ldconst, Type::INT32_T, {"reg1", "0"}, this->scope);
    }

    cfg->GetCurrentBB()->add_IRInstr(IRInstr::call, Type::ERROR, paramsIRInstr, this->scope);

    string tmpResVar = cfg->GetSymbolTable()->CreateTempVar(cfg->GetName(), Type::INT32_T, this->GetScope());
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, Type::INT32_T, {tmpResVar, "reg1"}, this->scope);

    return tmpResVar;
}

Function::~Function() {
    for (Expr * param : params) {
        delete (param);
    }
}

//------- Réalisation de la classe <Instr> ---
string Instr::GetScope() const {
    return scope;
}

//------- Réalisation de la classe <ReturnInstr> ---
Expr * ReturnInstr::GetReturnExpr() {
    return this->returnExpr;
}

ReturnInstr::~ReturnInstr() {
    delete (returnExpr);
}

void ReturnInstr::GenerateIR(CFG * cfg) {
    string tmpRetVar = this->returnExpr->GenerateIR(cfg);
    Type type = cfg->GetSymbolTable()->GetFunctionType(cfg->GetName());
    if (type == Type::VOID) {
        type = Type::INT32_T;
    }
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::ret, type, {tmpRetVar}, this->scope);
}

//------- Réalisation de la classe <ExprAffectation> ---

Expr * ExprAffectation::GetLValue() {
    return this->lValue;
}

Expr * ExprAffectation::GetRValue() {
    return rValue;
}

ExprAffectation::~ExprAffectation() {
    delete (rValue);
    delete (lValue);
}

string ExprAffectation::GenerateIR(CFG * cfg) {

    string rightVarName = rValue->GenerateIR(cfg);

    string leftVarName = lValue->GenerateIR(cfg);
    //vector<string> params = { right, left };

    Type t = cfg->GetSymbolTable()->GetVariableType(cfg->GetName(), leftVarName, this->GetScope());

    cfg->GetCurrentBB()->add_IRInstr(IRInstr::wmem, t, {leftVarName, rightVarName}, this->scope);

    /*
    if (cfg->GetSymbolTable()->IsUsedVariable(cfg->GetName(), leftVarName, this->scope)) {
        if (dynamic_cast<ConstLiteral *>(rValue)) {
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::ldconst, Type::INT32_T, {leftVarName, rightVarName}, this->scope);
        } else
            cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, Type::INT32_T, {leftVarName, rightVarName}, this->scope);
        }
    }
    */

    return rightVarName;
}

//------- Réalisation de la classe <ExprInstr> ---
void ExprInstr::GenerateIR(CFG * cfg) {
    this->expr->GenerateIR(cfg);
}

ExprInstr::~ExprInstr() {
    delete (expr);
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

    // EMPTY BB FOR EPILOGUE
    BasicBlock * output = new BasicBlock(cfg, cfg->new_BB_name("epilogue"));

    BasicBlock * body = new BasicBlock(cfg, cfg->new_BB_name());

    cfg->add_bb(entry);

    entry->exit_true = body;
    cfg->add_bb(body);
    cfg->bb_epilogue = output;

    // TODO: recuperer les variables passees en arguments pour plus que 6
    vector<FunctionParam *> functionParams = cfg->GetSymbolTable()->GetFunctionParams(cfg->GetName());
    for (int i = 0; i < functionParams.size(); i++) {
        string reg = "paramReg" + to_string(i + 1);
        cfg->GetCurrentBB()->add_IRInstr(IRInstr::copy, functionParams[i]->type, {functionParams[i]->name, reg}, this->scope);
    }

    for (Instr * instr : this->GetListInstr()) {
        instr->GenerateIR(cfg);
    }

    cfg->GetCurrentBB()->exit_true = output;
    cfg->add_bb(output);
}

DefFuncInstr::~DefFuncInstr() {
    for (Instr * instr : listInstr) {
        delete (instr);
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

//---------------//
//  WhileInstr  //
//---------------//

Expr * WhileInstr::GetWhileExpr() {
    return whileExpr;
}

BlockInstr * WhileInstr::GetWhileBlock() {
    return whileBlock;
}

void WhileInstr::GenerateIR(CFG * cfg) {
    BasicBlock *testBB, *whileBB, *endwhile;

    //Création des BB
    testBB = new BasicBlock(cfg, cfg->new_BB_name());
    whileBB = new BasicBlock(cfg, cfg->new_BB_name());
    endwhile = new BasicBlock(cfg, cfg->new_BB_name());

    cfg->AddCurrentLoopEntryLabel(testBB->label);
    cfg->AddCurrentLoopEndLabel(endwhile->label);

    cfg->GetCurrentBB()->exit_true = testBB;

    // Ajout des instructions test
    cfg->add_bb(testBB);
    cfg->GetCurrentBB()->test_var_name = whileExpr->GenerateIR(cfg);
    cfg->GetCurrentBB()->exit_true = whileBB;
    cfg->GetCurrentBB()->exit_false = endwhile;

    // Ajout des instructions whileBB
    cfg->add_bb(whileBB);
    whileBlock->GenerateIR(cfg);
    cfg->GetCurrentBB()->exit_true = testBB;

    cfg->add_bb(endwhile);

    cfg->RemoveLastCurrentLoopEntryLabel();
    cfg->RemoveLastCurrentLoopEndLabel();
}

WhileInstr::~WhileInstr() {
    delete (whileExpr);
    delete (whileBlock);

} //----- Fin de ~WhileInstr

//---------------//
//   ForInstr    //
//---------------//

vector<Expr *> ForInstr::GetInitExprs() {
    return initExprs;
}

Expr * ForInstr::GetConditionnalExpr() {
    return conditionnalExpr;
}

vector<Expr *> ForInstr::GetUpdateExprs() {
    return updateExprs;
}

BlockInstr * ForInstr::GetForBlock() {
    return forBlock;
}

void ForInstr::GenerateIR(CFG * cfg) {
    BasicBlock *enterForBB, *testBB, *forBB, *endFor, *updateBB;

    //Création des BB
    enterForBB = new BasicBlock(cfg, cfg->new_BB_name());
    forBB = new BasicBlock(cfg, cfg->new_BB_name());
    testBB = new BasicBlock(cfg, cfg->new_BB_name());
    endFor = new BasicBlock(cfg, cfg->new_BB_name());
    updateBB = new BasicBlock(cfg, cfg->new_BB_name());

    cfg->AddCurrentLoopEntryLabel(updateBB->label);
    cfg->AddCurrentLoopEndLabel(endFor->label);

    cfg->GetCurrentBB()->exit_true = enterForBB;

    // Génération IR init for
    cfg->add_bb(enterForBB);
    for (Expr * e : initExprs) {
        e->GenerateIR(cfg);
    }
    cfg->GetCurrentBB()->exit_true = testBB;

    // Génération IR expression conditionnelle
    cfg->add_bb(testBB);
    cfg->GetCurrentBB()->test_var_name = conditionnalExpr->GenerateIR(cfg);
    cfg->GetCurrentBB()->exit_true = forBB;
    cfg->GetCurrentBB()->exit_false = endFor;

    // Ajout des instructions forBB
    cfg->add_bb(forBB);
    forBlock->GenerateIR(cfg);
    cfg->GetCurrentBB()->exit_true = updateBB;

    cfg->add_bb(updateBB);
    for (Expr * e : updateExprs) {
        e->GenerateIR(cfg);
    }
    cfg->GetCurrentBB()->exit_true = testBB;

    // Ajout du bb de sortie
    cfg->add_bb(endFor);

    cfg->RemoveLastCurrentLoopEntryLabel();
    cfg->RemoveLastCurrentLoopEndLabel();
}

ForInstr::~ForInstr() {
    for (Expr * e : initExprs) {
        delete (e);
    }

    delete (conditionnalExpr);

    for (Expr * e : updateExprs) {
        delete (e);
    }

    delete (forBlock);
}

void BreakInstr::GenerateIR(CFG * cfg) {
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::jmp, VOID, {cfg->GetCurrentLoopEndLabel()}, this->scope);
}

void ContinueInstr::GenerateIR(CFG * cfg) {
    cfg->GetCurrentBB()->add_IRInstr(IRInstr::jmp, VOID, {cfg->GetCurrentLoopEntryLabel()}, this->scope);
}

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
    for (Instr * instr : listInstr) {
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

void Program::UnusedFunctionAnalysis() const {
    this->symbolTable.UnusedFunctionAnalysis();
}

void Program::FunctionReturnAnalysis() const {
    this->symbolTable.FunctionReturnAnalysis();
}

void Program::SetErrorFlag(bool flag) {
    this->errorFlag = flag;
} //----- Fin de SetErrorFlag

bool Program::GetErrorFlag() {
    return this->errorFlag;
} //----- Fin de GetErrorFlag

Program::~Program() {
    for (Instr * instr : listInstr) {
        delete (instr);
    }
} //----- Fin de ~Program

IR * Program::GenerateIR() {
    IR * ir = new IR();

    for (Instr * instr : this->listInstr) {
        // Normally all instructions in listInstr are def function instruction
        DefFuncInstr * defFuncInstr = dynamic_cast<DefFuncInstr *>(instr);

        CFG * tmpCFG = new CFG(&(this->symbolTable), defFuncInstr->GetName());

        defFuncInstr->GenerateIR(tmpCFG);

        ir->AddCFG(tmpCFG);
    }

    return ir;
}