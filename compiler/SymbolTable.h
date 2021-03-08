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
    int64_t offset;
    bool used;
};

struct ContextTable {
    map<string, ContextVariable> contextVariable;
    int64_t offsetContext;
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
    bool DefineVariable(string function, string scope, string name, string type);

    bool LookUp(string function, string name, string scope = "") const;

    struct variable Get(fstream &) const;

    //-------------------------------------------- Constructeurs - destructeur
    SymbolTable();
    // Mode d'emploi :
    //   startPoint correspond au point de départ du SymbolTable
    //   endPoint correspond au point d'arrivé du SymbolTable
    // Contrat :
    //   les chaines pointées par startPoint et endPoint doivent être allouées

    virtual ~SymbolTable();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Attributs protégés

    map<string, ContextTable> globalTable;

};
//-------------------------------- Autres définitions dépendantes de <SymbolTable>

#endif // SYMBOL_H