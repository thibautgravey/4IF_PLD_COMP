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
    INT //, BITE, LONG, DOUBLE, CHAR, STRING
};

struct ContextVariable {
    Type type;
    int offset = 0;
    bool used = false;
};

struct ContextTable {
    map<string, ContextVariable*> contextVariableTable;
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
    bool DefineFunction(string name, Type type);

    bool DefineVariable(string function, string name, Type type, string scope = "");

    bool LookUp(string function, string name, string scope = "") const;

    struct ContextVariable* GetVariable(string function, string name, string scope = "") const;

    //-------------------------------------------- Constructeurs - destructeur
    SymbolTable() {}
    // Mode d'emploi :
    //
    // Contrat :
    //

    ~SymbolTable();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes privées
    void printError(string error);


    //----------------------------------------------------- Attributs protégés

    map<string, ContextTable*> globalFunctionTable;

};
//-------------------------------- Autres définitions dépendantes de <SymbolTable>

#endif // SYMBOL_H