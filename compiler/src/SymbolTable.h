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

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

enum Type {
    INT,
    ERROR //, BITE, LONG, DOUBLE, CHAR, STRING
};

struct ContextVariable {
    Type type;
    int offset = 0;
    bool used = false;
};

struct ContextTable {
    map<string, ContextVariable *> contextVariableTable;
    int offsetContext = 0;
    Type returnType;
};

// struct function {} ?

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
    bool DefineFunction(const string& name, Type type);

    bool DefineVariable(const string& function, const string& name, Type type, const string& scope = "");

    bool LookUp(const string& function, const string& name, const string& scope = "") const;

    string CreateTempVar(Type type);

    Type GetVariableType(const string& function, const string& name, const string& scope = "") const;

    int GetVariableOffset(const string& function, const string& name, const string& scope = "") const;

    bool IsUsedVariable(const string& function, const string& name, const string& scope = "") const;

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
    struct ContextVariable * getVariable(const string& function, const string& name, const string& scope = "") const;

    static void printError(const string& error) ;

    //----------------------------------------------------- Attributs protégés

    map<string, ContextTable *> globalFunctionTable;
};
//-------------------------------- Autres définitions dépendantes de <SymbolTable>

#endif // SYMBOL_H