/*******************************************************************************
                           SymbolTable  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <SymbolTable> (fichier SymbolTable.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

using namespace std;

//------------------------------------------------------ Include personnel
#include "SymbolTable.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool SymbolTable::DefineFunction(string name, Type type) {
    globalFunctionTable::iterator iterator = globalFunctionTable.find(name);
    if(iterator != globalFunctionTable.end()) {
        printError("function "+name+" already exist in globalFunctionTable");
        return false;
    }

    ContextTable* contextTable = new ContextTable;
    contextTable->returnType = type;
    globalFunctionTable.insert(name, contextTable);

    return true;

} //----- Fin de DefineFunction

bool SymbolTable::DefineVariable(string function, string name, Type type, string scope) {

} //----- Fin de DefineVariable

bool SymbolTable::LookUp(string function, string name, string scope) const {

} //----- Fin de LookUp

struct ContextVariable SymbolTable::GetVariable(string function, string name, string scope) const {

} //----- Fin de GetVariable

//-------------------------------------------- Constructeurs - destructeur
SymbolTable::~SymbolTable(){
#ifdef MAP
    cout << "Appel au destructeur de <SymbolTable>" << endl;
#endif

} //----- Fin de ~SymbolTable

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées

void SymbolTable::printError(string error) {
    cerr << error << endl;
}