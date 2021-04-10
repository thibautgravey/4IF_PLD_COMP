/*******************************************************************************
                           SymbolTable  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//-------- Interface de la classe <SymbolTable> (fichier SymbolTable.h) ---------
#if !defined(SYMBOLTABLE_H)
#define SYMBOLTABLE_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

enum Type {
    CHAR,
    INT32_T,
    INT64_T,
    VOID,
    ERROR
    // CHAR, LONG, DOUBLE, STRING
};

typedef struct fp {
    Type type;
    string name;
    fp(Type t, string n)
        : type(t), name(n){};
} FunctionParam;

static unordered_map<string, Type> const TYPE_TABLE = {{"int32_t", INT32_T}, {"int64_t", INT64_T}, {"char", CHAR}, {"void", VOID}};

struct ContextVariable {
    Type type;
    int declaredLine;
    int offset = 0;
    bool used = false;
    uint size = 1; // 1 : variable, >=0 : array
};

struct ContextTable {
    map<string, ContextVariable *> contextVariableTable;
    int declaredLine;
    int offsetContext = 0;
    Type returnType;
    bool used = false;
    bool hasReturned = false;
    vector<FunctionParam *> params;
};

//------------------------------------------------------------------------
// Rôle de la classe <SymbolTable>
// Classe modélisant un SymbolTable défini par une table de fonctions
// ainsi qu'une table de variables
// C'est une interface permettant de gérer les différents contextes
// ainsi que les différentes variables globales
//------------------------------------------------------------------------
class SymbolTable {
    //----------------------------------------------------------------- PUBLIC

  public:
    //----------------------------------------------------- Méthodes publiques
    bool DefineFunction(const string & name, Type type, vector<FunctionParam *> params, int declaredLine);

    bool DefineVariable(const string & function, const string & name, Type type, int declaredLine, const string & scope, int size = 1);

    bool LookUpVariable(const string & function, const string & name, const string & scope) const;

    bool LookUpFunction(const string & function) const;

    string CreateTempVar(const string & function, Type type, const string & scope);

    Type GetVariableType(const string & function, const string & name, const string & scope) const;

    int GetVariableOffset(const string & function, const string & name, const string & scope) const;

    string GetVariableScope(const string & function, const string & name, const string & scope) const;

    bool IsUsedVariable(const string & function, const string & name, const string & scope) const;
    int GetArrayElementOffset(const string & function, const string & name, int index, const string) const;

    void UnusedVariableAnalysis() const;

    void UnusedFunctionAnalysis() const;

    void FunctionReturnAnalysis() const;

    void SetUsedVariable(const string & function, const string & name, const string & scope);

    void SetUsedFunction(const string & function);

    void SetHasReturnFunction(const string & function);

    bool FunctionHasReturn(const string & function);

    int CalculateSpaceForFunction(const string & function);

    Type StringToType(const string & name);

    vector<FunctionParam *> GetFunctionParams(const string & function);

    Type GetFunctionType(const string & function);

    //-------------------------------------------- Constructeurs - destructeur
    SymbolTable() = default;
    // Mode d'emploi :
    //
    // Contrat :
    //

    ~SymbolTable();

    //------------------------------------------------------------------ PRIVE

  protected:
    //----------------------------------------------------- Méthodes privées
    struct ContextVariable * getVariable(const string & function, const string & name, const string & scope) const;

    struct ContextTable * getFunction(const string & function) const;

    void decreaseContextOffset(const string & function, const Type & type, uint size = 1);

    int computeScopeSize(const string & name) const;

    static void printError(const string & error);

    //----------------------------------------------------- Attributs protégés

    map<string, ContextTable *> globalFunctionTable;
};
//-------------------------------- Autres définitions dépendantes de <SymbolTable>

#endif // SYMBOL_H