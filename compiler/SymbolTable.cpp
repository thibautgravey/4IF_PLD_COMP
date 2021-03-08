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
    globalFunctionTable::iterator globalFunctionTableIterator = globalFunctionTable.find(function);
    if(globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function "+name+" does not exist in globalFunctionTable");
        return false;
    }

    name = scope+name;
    ContextTable* contextTable = globalFunctionTableIterator->second;
    contextTable->contextVariableTable::iterator it = contextTable->contextVariableTable.find(name);
    if(it != contextTable->contextVariableTable.end()) {
        printError("variable "+name+" already exist in contextVariableTable from "+function);
        return false;
    }

    ContextVariable* contextVariable = new ContextVariable;
    contextVariable->type = type;
    contextTable->contextVariableTable.insert(contextVariable);

} //----- Fin de DefineVariable

bool SymbolTable::LookUp(string function, string name, string scope) const {
    globalFunctionTable::iterator globalFunctionTableIterator = globalFunctionTable.find(function);
    if(globalFunctionTableIterator == globalFunctionTable.end()) {
        return false;
    }

    name = scope+name;
    ContextTable* contextTable = globalFunctionTableIterator->second;
    contextTable->contextVariableTable::iterator it = contextTable->contextVariableTable.find(name);
    if(it == contextTable->contextVariableTable.end()) {
        return false;
    }

    return true;
} //----- Fin de LookUp

struct ContextVariable* SymbolTable::GetVariable(string function, string name, string scope) const {
    globalFunctionTable::iterator globalFunctionTableIterator = globalFunctionTable.find(function);
    if(globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function "+name+" does not exist in globalFunctionTable");
        return nullptr;
    }

    name = scope+name;
    ContextTable* contextTable = globalFunctionTableIterator->second;
    contextTable->contextVariableTable::iterator it = contextTable->contextVariableTable.find(name);
    if(it == contextTable->contextVariableTable.end()) {
        printError("variable "+name+" does not exist in contextVariableTable from "+function);
        return nullptr;
    }

    return it->second;
} //----- Fin de GetVariable

//-------------------------------------------- Constructeurs - destructeur
SymbolTable::~SymbolTable(){
#ifdef MAP
    cout << "Appel au destructeur de <SymbolTable>" << endl;
#endif

    for(globalFunctionTable::iterator it = globalFunctionTable.begin(); it != globalFunctionTable.end(); ++it) {

        ContextTable* contextTable = it->second;

        for(contextTable->contextVariableTable::iterator it2 = contextTable->contextVariableTable ; it2 != contextTable->contextVariableTable.end(); ++it2){
            delete(it2->second);
        }

        delete(contextTable);
    }

} //----- Fin de ~SymbolTable

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées

void SymbolTable::printError(string error) {
    cerr << error << endl;
}