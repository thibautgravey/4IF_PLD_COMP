/*******************************************************************************
                           SymbolTable  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <SymbolTable> (fichier SymbolTable.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------ Include personnel
#include "SymbolTable.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool SymbolTable::DefineFunction(const string & name, Type type, vector<FunctionParam *> params, int declaredLine) {

    auto iterator = globalFunctionTable.find(name);
    if (iterator != globalFunctionTable.end()) {
        printError("function " + name + " already exist in globalFunctionTable");
        return false;
    }

    if (type == ERROR) {
        printError("function " + name + " has a bad return type");
        return false;
    }

    ContextTable * contextTable = new ContextTable;
    contextTable->returnType = type;
    contextTable->declaredLine = declaredLine;
    contextTable->params = params;
    globalFunctionTable.insert(make_pair(name, contextTable));

    return true;

} //----- Fin de DefineFunction

bool SymbolTable::DefineVariable(const string & function, const string & name, Type type, int declaredLine, const string & scope, int size) {

    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function " + function + " does not exist in globalFunctionTable");
        return false;
    }

    string completeName = scope + name;
    ContextTable * contextTable = globalFunctionTableIterator->second;

    if (type == ERROR) {
        printError("variable " + completeName + " has a bad type");
        return false;
    }

    auto it = contextTable->contextVariableTable.find(completeName);
    if (it != contextTable->contextVariableTable.end()) {
        printError("variable " + completeName + " already exist in contextVariableTable from " + function);
        return false;
    }

    decreaseContextOffset(function, type, size);

    ContextVariable * contextVariable = new ContextVariable;
    if (size != -1) {
        contextVariable->size = size;
    }
    contextVariable->type = type;
    contextVariable->declaredLine = declaredLine;
    contextVariable->offset = globalFunctionTableIterator->second->offsetContext;
    contextTable->contextVariableTable.insert(make_pair(completeName, contextVariable));

    return true;
} //----- Fin de DefineVariable

bool SymbolTable::LookUpVariable(const string & function, const string & name, const string & scope) const {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        return false;
    }

    //Generate scope :
    int scopeSize = computeScopeSize(name);
    string tmpScope = name.substr(0, scopeSize);
    string tmpName = name.substr(scopeSize, name.size());

    //If it's a variable without scope, use the current scope instead
    if (scopeSize == 0)
        tmpScope = scope;

    while (tmpScope.size() > 0) {
        ContextTable * contextTable = globalFunctionTableIterator->second;
        auto it = contextTable->contextVariableTable.find(tmpScope + tmpName);
        if (it != contextTable->contextVariableTable.end()) {
            return true;
        }

        //reduce the scope
        size_t lastPos = tmpScope.find_last_of('.');
        if (lastPos != string::npos) {
            tmpScope = tmpScope.substr(0, lastPos);
        } else {
            tmpScope = "";
        }
    }

    return false;
} //----- Fin de LookUpVariable

bool SymbolTable::LookUpFunction(const string & function) const {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        return false;
    }

    return true;
} //----- Fin de LookUpFunction

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

string SymbolTable::GetVariableScope(const string & function, const string & name, const string & scope) const {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        return "";
    }

    string tmpScope = scope;

    while (tmpScope.size() > 0) {

        ContextTable * contextTable = globalFunctionTableIterator->second;
        auto it = contextTable->contextVariableTable.find(tmpScope + name);
        if (it != contextTable->contextVariableTable.end()) {
            return tmpScope;
        }

        //reduce the scope
        size_t lastPos = tmpScope.find_last_of('.');
        if (lastPos != string::npos) {
            tmpScope = tmpScope.substr(0, lastPos);
        } else {
            tmpScope = "";
        }
    }

    return "";
} //----- Fin de GetVariableScope

//int SymbolTable::GetArrayElementOffset(const string & function, const string & name, int index, const string & scope) const {
//}

bool SymbolTable::IsUsedVariable(const string & function, const string & name, const string & scope) const {
    ContextVariable * variable = getVariable(function, name, scope);
    if (variable == nullptr) {
        return false;
    }

    return variable->used;
} //----- Fin de IsUsedVariable

string SymbolTable::CreateTempVar(const string & function, Type type, const string & scope) {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function " + function + " does not exist in globalFunctionTable");
        return "";
    }

    decreaseContextOffset(function, type, 1);
    string completeName = scope + "tmp" + to_string(abs(globalFunctionTableIterator->second->offsetContext));

    ContextTable * contextTable = globalFunctionTableIterator->second;

    ContextVariable * contextVariable = new ContextVariable;
    contextVariable->type = type;
    contextVariable->offset = globalFunctionTableIterator->second->offsetContext;
    contextTable->contextVariableTable.insert(make_pair(completeName, contextVariable));

    return completeName;
} //----- Fin de CreateTempVar

void SymbolTable::UnusedVariableAnalysis() const {

    for (const auto & function : globalFunctionTable) {

        map<string, ContextVariable *> contextVariables = function.second->contextVariableTable;

        for (auto & contextVariable : contextVariables) {

            if (!contextVariable.second->used) {
                printError("WARN : variable " + contextVariable.first + " is declared at line " + to_string(contextVariable.second->declaredLine) + " but never used in the program");
            }
        }
    }
} //----- Fin de UnusedVariableAnalysis

void SymbolTable::UnusedFunctionAnalysis() const {
    for (const auto & function : globalFunctionTable) {
        if (!function.second->used && !(function.first.compare("main") == 0)) {
            printError("WARN : function " + function.first + " is declared at line " + to_string(function.second->declaredLine) + " but never used in the program");
        }
    }
} //----- Fin de UnusedFunctionAnalysis

void SymbolTable::FunctionReturnAnalysis() const {
    for (const auto & function : globalFunctionTable) {
        if (function.second->returnType == Type::VOID && function.second->hasReturned) {
            printError("WARN : function " + function.first + " is a void function with a return statement");
        } else if (function.second->returnType != Type::VOID && !function.second->hasReturned) {
            printError("WARN : function " + function.first + " is a non-void function without a return statement");
        }
    }
} //----- Fin de FunctionReturnAnalysis

void SymbolTable::SetUsedVariable(const string & function, const string & name, const string & scope) {
    ContextVariable * variable = getVariable(function, name, scope);
    if (variable != nullptr) {
        variable->used = true;
    }
}

void SymbolTable::SetUsedFunction(const string & function) {
    ContextTable * functionPointer = getFunction(function);
    if (functionPointer != nullptr) {
        functionPointer->used = true;
    }
}

void SymbolTable::SetHasReturnFunction(const string & function) {
    ContextTable * functionPointer = getFunction(function);
    if (functionPointer != nullptr) {
        functionPointer->hasReturned = true;
    }
}

bool SymbolTable::FunctionHasReturn(const string & function) {
    ContextTable * functionPointer = getFunction(function);
    if (functionPointer == nullptr) {
        return false;
    }

    return functionPointer->hasReturned;
}

int SymbolTable::CalculateSpaceForFunction(const string & function) {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function " + function + " does not exist in globalFunctionTable");
        return -1;
    }

    ContextTable * contextTable = globalFunctionTableIterator->second;
    return -contextTable->offsetContext;
}

Type SymbolTable::StringToType(const string & name) {
    auto it = TYPE_TABLE.find(name);
    if (it != TYPE_TABLE.end()) {
        return it->second;
    } else {
        return ERROR;
    }
} //----- Fin de ~StringToType

vector<FunctionParam *> SymbolTable::GetFunctionParams(const string & function) {
    ContextTable * contextTable = getFunction(function);
    if (contextTable != nullptr) {
        return contextTable->params;
    }

    return {};
} //----- Fin de GetFunctionParams

Type SymbolTable::GetFunctionType(const string & function) {
    ContextTable * contextTable = getFunction(function);
    if (contextTable != nullptr) {
        return contextTable->returnType;
    }

    return ERROR;
}

//-------------------------------------------- Constructeurs - destructeur
SymbolTable::~SymbolTable() {
    for (auto & it : globalFunctionTable) {

        ContextTable * contextTable = it.second;

        for (auto & it2 : contextTable->contextVariableTable) {
            delete (it2.second);
        }

        for (FunctionParam * fp : contextTable->params) {
            delete (fp);
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

    //Generate scope :
    int scopeSize = computeScopeSize(name);
    string tmpScope = name.substr(0, scopeSize);
    string tmpName = name.substr(scopeSize, name.size());

    //If it's a variable without scope, use the current scope instead
    if (scopeSize == 0)
        tmpScope = scope;

    while (tmpScope.size() > 0) {
        ContextTable * contextTable = globalFunctionTableIterator->second;
        auto it = contextTable->contextVariableTable.find(tmpScope + tmpName);
        if (it != contextTable->contextVariableTable.end()) {
            return it->second;
        }

        //reduce the scope
        size_t lastPos = tmpScope.find_last_of('.');
        if (lastPos != string::npos) {
            tmpScope = tmpScope.substr(0, lastPos);
        } else {
            tmpScope = "";
        }
    }

    printError("variable " + name + " does not exist in contextVariableTable from " + function + " with scope " + scope);
    return nullptr;
} //----- Fin de getVariable

struct ContextTable * SymbolTable::getFunction(const string & function) const {
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    if (globalFunctionTableIterator == globalFunctionTable.end()) {
        printError("function " + function + " does not exist in globalFunctionTable");
        return nullptr;
    }

    return globalFunctionTableIterator->second;
} //----- Fin de getFunction

// TODO: Il faut plu
void SymbolTable::decreaseContextOffset(const string & function, const Type & type, uint size) {
    // In this function, we've already check the existence of the function
    auto globalFunctionTableIterator = globalFunctionTable.find(function);
    int bytes;
    switch (type) {
        case Type::CHAR:
            bytes = 1;
            break;
        case Type::INT32_T:
            bytes = 4;
            break;
        case Type::INT64_T:
        case Type::VOID:
        case default :
            bytes = 8;
            break;
    }
    int total = bytes * size; 
    if ( total % 8 > 0)
        total += 8 - total % 8;
    globalFunctionTableIterator->second->offsetContext -= bytes * size;

} //----- Fin de decreaseContextOffset

int SymbolTable::computeScopeSize(const string & name) const {
    int scopeSize(0);

    for (int i = 0; i < name.size(); i++) {
        if (isdigit(name[i]) || name[i] == '.')
            scopeSize++;
        else
            break;
    }

    return scopeSize;
} //----- Fin de computeScopeSize

void SymbolTable::printError(const string & error) {
    cerr << error << endl;
} //----- Fin de printError