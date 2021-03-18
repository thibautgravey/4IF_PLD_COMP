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
    
    string p1,p2,p3;
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
        case copy :
            o << "        mov     " << p1 << ", " << p2 << endl;
            break;
        case add :
            o << "        add     " << p1 << " " << p2 << endl;
            break;
        case sub :
            o << "        sub     " << p1 << " " << p2 << endl;
            break;
        case mul :
            o << "        imul    " << p1 << " " << p2 << endl;
            break;
        case orB :
            break;
        case andB :
            break;
        case xorB :
            break;
        case rmem :
            o << "        mov     " << p1 << ", " << p2 << endl;
            break;
        case wmem :
            o << "        mov     " << p1 << ", " << p2 << endl;
            break;
        case call :
            o << "        call    " << p1 << endl;
            break;
        case cmp_eq :
            break;
        case cmp_lt :
            break;
        case cmp_le :
            break;
        case ret :
            o << "        ret" << endl; //? Never used
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
    for ( BasicBlock* bb : this->bbs ) {
        o << bb->label << endl;
        for ( IRInstr * instr : bb->instrs ) {
            instr->gen_asm(o);
        }
        if ( bb->exit_false == nullptr ) {
            o << "jmp" << bb->exit_true->label << endl;
        } else {
            o << "je" << bb->exit_true->label << endl;
            o << "jmp" << bb->exit_false->label << endl;
        }
    }

    gen_asm_epilogue(o, lastbb);
} //fin de gen_asm(CFG)

string CFG::IR_reg_to_asm(string reg) {

    string ret;

    if ( reg == "reg1" ) {
        ret = "eax";
    } else if ( reg == "reg2" ) {
        ret = "ebx";
    } else {
        int offset = this->symbolTable->GetVariableOffset("main", reg);
        ret = "DWORD PTR -" + to_string(offset) +  "[ebp]"; //? '-'
    }

    return ret;
} //fin de IR_reg_to_asm

void CFG::gen_asm_prologue(ostream & o, BasicBlock * bb) {
    o << "main:" << endl;
    o << "." << bb->label << ":" << endl;
    o << "        push    ebp" << endl;
    o << "        mov     ebp, esp" << endl;
    o << "        sub     ebp, " << to_string(this->symbolTable->CalculateSpaceForFunction("main")) << endl;
} //fin de gen_asm_prologue

void CFG::gen_asm_epilogue(ostream & o, BasicBlock * bb) {
    o << "." << bb->label << ":" << endl;
    o << "        leave" << endl;
    o << "        ret" << endl;
} //fin de gen_asm_epilogue

string CFG::new_BB_name() {
    string functionName = "main"; //TODO : change this when implementing function
    if (this->nextBBnumber == 0) {
        this->nextBBnumber++;
        return functionName;
    } else {
        return functionName + "BB" + to_string(this->nextBBnumber++);
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

    for ( CFG* cfg : this->allCFG ) {
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
    o << "        .globl main" << endl << endl; 
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
