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

void CFG::add_to_symbol_table(string name, Type t) {
} //fin de add_to_symbole_table

string CFG::create_new_tempvar(Type t) {
} //fin de create_new_tempvar

int CFG::get_var_index(string name) {
} //fin de get_var_index

Type CFG::get_var_type(string name) {
} //fin de get_var_type

string CFG::new_BB_name() {
} //fin de new_BB_name

//-------------------------------------------- Constructeurs - destructeur

IRInstr::IRInstr(BasicBlock * bb_, Operation op, Type t, vector<string> params) {

} //fin de constructeur de IRInst

BasicBlock::BasicBlock(CFG * cfg, string entry_label) {
} //fin de constructeur de BasicBlock

CFG::CFG(DefFonction * ast) {

} //fin de constructeur de CFG

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
