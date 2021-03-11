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
bool SymbolTable::DefineFunction(const string & name, Type type) {
    auto iterator = globalFunctionTable.find(name);
    if (iterator != globalFunctionTable.end()) {
        printError("function " + name + " already exist in globalFunctionTable");
        return false;
    }

    ContextTable * contextTable = new ContextTable;
    contextTable->returnType = type;
    globalFunctionTable.insert(make_pair(name, contextTable));

    return true;

} //----- Fin de DefineFunction

bool SymbolTable::DefineVariable(const string & function, const string & name, Type type, const string & scope) {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function " + function + " does not exist in globalFunctionTable");
        return false;
    }

    string completeName = scope + name;
    ContextTable * contextTable = globalFunctionTableIterator->second;
    auto it = contextTable->contextVariableTable.find(completeName);
    if (it != contextTable->contextVariableTable.end()) {
        printError("variable " + completeName + " already exist in contextVariableTable from " + function);
        return false;
    }

    decreaseContextOffset(function);

    ContextVariable * contextVariable = new ContextVariable;
    contextVariable->type = type;
    contextVariable->offset = globalFunctionTableIterator->second->offsetContext;
    contextTable->contextVariableTable.insert(make_pair(completeName, contextVariable));

    return true;
} //----- Fin de DefineVariable

bool SymbolTable::LookUp(const string & function, const string & name, const string & scope) const {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        return false;
    }

    string completeName = scope + name;
    ContextTable * contextTable = globalFunctionTableIterator->second;
    auto it = contextTable->contextVariableTable.find(completeName);
    if (it == contextTable->contextVariableTable.end()) {
        return false;
    }

    return true;
} //----- Fin de LookUp

Type SymbolTable::GetVariableType(const string & function, const string & name, const string & scope) const {
    ContextVariable * variable = getVariable(function, name, scope);
    if (variable == nullptr) {
        return ERROR;
    }

    return variable->type;
} //----- Fin de GetVariableType

int SymbolTable::GetVariableOffset(const string & function, const string & name, const string & scope) const {
    ContextVariable * variable = getVariable(function, name, scope);
    if (variable == nullptr) {
        return -1;
    }

    return variable->offset;
} //----- Fin de GetVariableOffset

bool SymbolTable::IsUsedVariable(const string & function, const string & name, const string & scope) const {
    ContextVariable * variable = getVariable(function, name, scope);
    if (variable == nullptr) {
        return false;
    }

    return variable->used;
} //----- Fin de IsUsedVariable

string SymbolTable::CreateTempVar(const string & function, Type type) {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function " + function + " does not exist in globalFunctionTable");
        return "";
    }

    decreaseContextOffset(function);

    string completeName = "tmp" + to_string(abs(globalFunctionTableIterator->second->offsetContext));

    ContextTable * contextTable = globalFunctionTableIterator->second;

    ContextVariable * contextVariable = new ContextVariable;
    contextVariable->type = type;
    contextVariable->offset = globalFunctionTableIterator->second->offsetContext;
    contextTable->contextVariableTable.insert(make_pair(completeName, contextVariable));

    return completeName;
} //----- Fin de CreateTempVar

//-------------------------------------------- Constructeurs - destructeur
SymbolTable::~SymbolTable() {
#ifdef MAP
    cout << "Appel au destructeur de <SymbolTable>" << endl;
#endif

    for (auto & it : globalFunctionTable) {

        ContextTable * contextTable = it.second;

        for (auto & it2 : contextTable->contextVariableTable) {
            delete (it2.second);
        }

        delete (contextTable);
    }

} //----- Fin de ~SymbolTable

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées

struct ContextVariable * SymbolTable::getVariable(const string & function, const string & name, const string & scope) const {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function " + function + " does not exist in globalFunctionTable");
        return nullptr;
    }

    string completeName = scope + name;
    ContextTable * contextTable = globalFunctionTableIterator->second;
    auto it = contextTable->contextVariableTable.find(completeName);
    if (it == contextTable->contextVariableTable.end()) {
        printError("variable " + completeName + " does not exist in contextVariableTable from " + function);
        return nullptr;
    }

    return it->second;
} //----- Fin de getVariable

void SymbolTable::decreaseContextOffset(const string & function) {
    // In this function, we've already check the existence of the function
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    globalFunctionTableIterator->second->offsetContext -= 4;
} //----- Fin de decreaseContextOffset

void SymbolTable::printError(const string & error) {
    cerr << error << endl;
} //----- Fin de printError