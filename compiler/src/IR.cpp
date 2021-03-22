/*******************************************************************************
                           IR  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <IR> (fichier IR.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

using namespace std;

//------------------------------------------------------ Include personnel
#include "IR.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void IRInstr::gen_asm(ostream & o) {

    string p1, p2, p3;
    switch (this->params.size()) {
        case 3:
            p3 = this->bb->cfg->IR_reg_to_asm(this->params[2]);
        case 2:
            p2 = this->bb->cfg->IR_reg_to_asm(this->params[1]);
        case 1:
            p1 = this->bb->cfg->IR_reg_to_asm(this->params[0]);
        default:
            break;
    }

    switch (this->op) {
        case ldconst:
            o << "        movl    $" << p2 << ", " << p1 << endl;
            break;
        case copy:
            o << "        movl    " << p2 << ", %eax" << endl;
            o << "        movl    %eax, " << p1 << endl;
            break;
        case add:
            o << "        movl    " << p2 << ", %eax" << endl;
            o << "        addl    " << p3 << ", %eax" << endl;
            o << "        movl    %eax, " << p1 << endl;
            break;
        case sub:
            o << "        subl     " << p2 << ", " << p1 << endl;
            break;
        case mul:
            o << "        imull    " << p2 << ", " << p1 << endl;
            break;
        case div:
            o << "        cltd   " << endl;
            o << "        idivl  " << p1 << endl;
            break;
        case orB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        orl      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case andB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        andl      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case xorB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        xorl      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case neg:
            o << "        cmpl     $0, " << p2 << endl;
            o << "        sete     %al" << endl;
            o << "        movzbl     %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case opp:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        negl     %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case rmem:
            o << "        movl    " << p2 << ", " << p1 << endl;
            break;
        case wmem:
            o << "        movl    " << p2 << ", " << p1 << endl;
            break;
        case call:
            o << "        call    " << p1 << endl;
            break;
        case cmp_eq:
            o << "cmp_eq NOT IMPLEMENDTED" << endl;
            break;
        case cmp_lt:
            o << "cmp_lt NOT IMPLEMENDTED" << endl;
            break;
        case cmp_le:
            o << "cmp_eq NOT IMPLEMENDTED" << endl;
            break;
        case ret:
            o << "        movl    " << p1 << ", %eax" << endl;
            break;
        default:
            break;
    }
} //fin de gen_asm(Ir_Instr)

void BasicBlock::gen_asm(ostream & o) {
} //fin de gen_asm(Basic_Block)

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
    this->instrs.push_back(new IRInstr(this, op, t, params));
} //fin de add_IRInst

void CFG::add_bb(BasicBlock * bb) {
    this->bbs.push_back(bb);
    this->current_bb = bb;
} //fin de add_bb

void CFG::gen_asm(ostream & o) {
    BasicBlock * lastbb = this->bbs.back();
    this->bbs.pop_back();
    gen_asm_prologue(o, this->bbs[0]);
    this->bbs.erase(this->bbs.begin());
    for (BasicBlock * bb : this->bbs) {
        o << bb->label << ":" << endl;
        for (IRInstr * instr : bb->instrs) {
            instr->gen_asm(o);
        }
        if (bb->exit_false == nullptr) {
            o << "        jmp " << bb->exit_true->label << endl;
        } else {
            o << "        je " << bb->exit_true->label << endl;
            o << "        jmp " << bb->exit_false->label << endl;
        }
    }

    gen_asm_epilogue(o, lastbb);
} //fin de gen_asm(CFG)

string CFG::IR_reg_to_asm(string reg) {

    string ret;

    if (reg == "reg1") {
        ret = "%eax";
    } else if (reg == "reg2") {
        ret = "%ebx";
    } else {
        if (this->symbolTable->LookUp("main", reg)) {
            int offset = this->symbolTable->GetVariableOffset("main", reg);
            ret = to_string(offset) + "(%rbp)";
        } else {
            ret = reg;
        }
    }

    return ret;
} //fin de IR_reg_to_asm

void CFG::gen_asm_prologue(ostream & o, BasicBlock * bb) {
    o << "main:" << endl;
    o << bb->label << ":" << endl;
    o << "        pushq    %rbp" << endl;
    o << "        movq     %rsp, %rbp" << endl;
    o << "        subq     $" << to_string(this->symbolTable->CalculateSpaceForFunction("main")) << ", %rbp" << endl;
    o << "        jmp " << bb->exit_true->label << endl;
} //fin de gen_asm_prologue

void CFG::gen_asm_epilogue(ostream & o, BasicBlock * bb) {
    o << bb->label << ":" << endl;
    o << "        leave" << endl;
    o << "        ret" << endl;
} //fin de gen_asm_epilogue

string CFG::new_BB_name(string prefix) {
    string functionName = "main"; //TODO : change this when implementing function
    if (prefix.empty()) {
        return "." + functionName + "BB" + to_string(this->nextBBnumber++);
    } else {
        return "." + prefix + "_" + functionName;
    }
} //fin de new_BB_name

BasicBlock * CFG::GetCurrentBB() {
    return this->current_bb;
} //----- Fin de GetCurrentBB

SymbolTable * CFG::GetSymbolTable() {
    return this->symbolTable;
} //----- Fin de GetSymbolTable

string IR::GenerateAsmX86() {
    ostream & o = cout;
    gen_asm_prologue_global(o);

    for (CFG * cfg : this->allCFG) {
        cfg->gen_asm(o);
        o << endl;
    }
    //TODO? ajouter épilogue bdsm
    return "";
} //----- Fin de GenerateAsmX86

void IR::AddCFG(CFG * newCFG) {
    this->allCFG.push_back(newCFG);
}

void IR::gen_asm_prologue_global(ostream & o) {
    o << "        .globl main" << endl
      << endl;
} //----- Fin de gen_asm_prologue_global

//-------------------------------------------- Constructeurs - destructeur

IRInstr::IRInstr(BasicBlock * bb_, Operation op, Type t, vector<string> params)
    : bb(bb_), op(op), t(t), params(params) {

} //fin de constructeur de IRInst

BasicBlock::BasicBlock(CFG * cfg, string entry_label) {
    this->cfg = cfg;
    this->label = entry_label;
} //fin de constructeur de BasicBlock

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
