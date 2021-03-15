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
} //fin de add_IRInst

void CFG::add_bb(BasicBlock * bb) {
} //fin de add_bb

void CFG::gen_asm(ostream & o) {
} //fin de grn_asm

string CFG::IR_reg_to_asm(string reg) {
} //fin de IR_reg_to_asm

void CFG::gen_asm_prologue(ostream & o) {
} //fin de gen_asm_prologue

void CFG::gen_asm_epilogue(ostream & o) {
} //fin de gen_asm_epilogue

string CFG::new_BB_name() {
} //fin de new_BB_name

void IR::BuildIR(Program * ast) {

} //----- Fin de BuildIR

string IR::GenerateAsmX86() {

} //----- Fin de GenerateAsmX86

//-------------------------------------------- Constructeurs - destructeur

IRInstr::IRInstr(BasicBlock * bb_, Operation op, Type t, vector<string> params) {

} //fin de constructeur de IRInst

BasicBlock::BasicBlock(CFG * cfg, string entry_label) {
} //fin de constructeur de BasicBlock

CFG::CFG(DefFonction * ast) {

} //fin de constructeur de CFG

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
