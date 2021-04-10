/*************************************************************************
                           tree  -  Header file
                             -------------------
    début                : 23/02/2021
    copyright            : (C) 2021 par Killian OECHSLIN et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <tree> (fichier tree.h) ----------------

//--------------------------------------------------- Interfaces utilisées
#pragma once
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <tree>
//
//
//------------------------------------------------------------------------
using namespace std;

typedef struct
{
   string type;
   int *val;
   int *offset;
} varInfo;

typedef struct
{
   bool isConst;
   void *value;
   string varExprName;
} exprInfo;

typedef struct
{
   string type;
   int val;
   int offset;
} varTempInfo;

class Tree
{
   //----------------------------------------------------------------- PUBLIC
public:
   //----------------------------------------------------- Méthodes publiques

   //------------------------------------------------- Surcharge d'opérateurs

   //-------------------------------------------- Constructeurs - destructeur
   Tree(Tree *n1, Tree *n2, exprInfo v, varTempInfo v2, bool terminal, string s) : n1(n1), n2(n2), termInfo(v), nonTermInfo(v2), isTerminal(terminal), symbole(s){};
   virtual ~Tree(){};
   void Afficher(int depth);

   //------------------------------------------------------------------ PRIVE
protected:
   //----------------------------------------------------- Méthodes protégées

   //----------------------------------------------------- Attributs protégés
   Tree *n1;
   Tree *n2;
   exprInfo termInfo;
   varTempInfo nonTermInfo;
   bool isTerminal;
   string symbole;
};
