/*************************************************************************
                           Tree  -  Implementation
                             -------------------
    début                : 23/02/2021
    copyright            : (C) 2021 par Killian OECHSLIN et Thomas MIGNOT
*************************************************************************/

//---------- Réalisation de la classe <Tree> (fichier tree.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "tree.h"
#include <iostream>
using namespace std;
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Tree::Afficher(int depth, string assembleur)
{
    cout << "depth= " << depth << "; Symbole : " << symbole << endl;

    if (!isTerminal)
    {
        if (!n1->isTerminal)
        {
            n1->Afficher(depth + 1);
        }

        if (!n2->isTerminal)
        {
            n2->Afficher(depth + 1);
        }

        if (n1->isTerminal && n2->isTerminal)
        {
        }

        n2->Afficher(depth + 1);
    }

    else
    {
        if (termInfo.isConst)
        {
        }
        else
        {
        }
    }

    if (symbole.size() == 1)
    {
        cout << symbole << endl;
        n1->Afficher(depth + 1);
        n2->Afficher(depth + 1);
    }
    else
    {
        cout << "Noeud terminal" << endl;
    }
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées