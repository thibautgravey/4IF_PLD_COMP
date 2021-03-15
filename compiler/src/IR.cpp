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
} //fin de grn_asm

string CFG::IR_reg_to_asm(string reg) {
    return "";
} //fin de IR_reg_to_asm

void CFG::gen_asm_prologue(ostream & o) {
} //fin de gen_asm_prologue

void CFG::gen_asm_epilogue(ostream & o) {
} //fin de gen_asm_epilogue

string CFG::new_BB_name() {
    string functionName = "main"; // TO DO : change this when implementing function
    if (this->nextBBnumber++ == 0) {
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
    return "";
} //----- Fin de GenerateAsmX86

void IR::AddCFG(CFG * newCFG) {
    this->allCFG.push_back(newCFG);
}

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
