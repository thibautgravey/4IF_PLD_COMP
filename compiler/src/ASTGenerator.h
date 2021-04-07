/*******************************************************************************
                           ASTGenerator  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//-------- Interface de la classe <ASTGenerator> (fichier ASTGenerator.h) ---------
#ifndef ASTGENERATOR_H
#define ASTGENERATOR_H

//--------------------------------------------------- Interfaces utilisées
#include "antlr4-runtime.h"
#include "ifccBaseVisitor.h"
#include <map>

#include "ast.h"

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ASTGenerator>
//
//
//
//
//------------------------------------------------------------------------

class ASTGenerator : public ifccBaseVisitor {
    //----------------------------------------------------------------- PUBLIC

  public:
    //----------------------------------------------------- Méthodes publiques
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext * ctx) override;

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext * ctx) override;

    virtual antlrcpp::Any visitLine(ifccParser::LineContext * ctx) override;

    virtual antlrcpp::Any visitVar_decl(ifccParser::Var_declContext * ctx) override;

    virtual antlrcpp::Any visitVar_aff(ifccParser::Var_affContext * ctx) override;

    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext * ctx) override;

    virtual antlrcpp::Any visitPar(ifccParser::ParContext * ctx) override;

    virtual antlrcpp::Any visitLess_or_add(ifccParser::Less_or_addContext * ctx) override;

    virtual antlrcpp::Any visitDiv_or_mult(ifccParser::Div_or_multContext * ctx) override;

    virtual antlrcpp::Any visitOr(ifccParser::OrContext * ctx) override;

    virtual antlrcpp::Any visitAnd(ifccParser::AndContext * ctx) override;

    virtual antlrcpp::Any visitXor(ifccParser::XorContext * ctx) override;

    virtual antlrcpp::Any visitLiteral(ifccParser::LiteralContext * ctx) override;

    virtual antlrcpp::Any visitOpp_or_not(ifccParser::Opp_or_notContext * ctx) override;

    virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext * ctx) override;

    virtual antlrcpp::Any visitInline_var_decl(ifccParser::Inline_var_declContext * ctx) override;

    virtual antlrcpp::Any visitDef_func(ifccParser::Def_funcContext * ctx) override;

    virtual antlrcpp::Any visitParam_list(ifccParser::Param_listContext * ctx) override;

    virtual antlrcpp::Any visitParam(ifccParser::ParamContext * ctx) override;

    virtual antlrcpp::Any visitExpr_list(ifccParser::Expr_listContext * ctx) override;

    virtual antlrcpp::Any visitIfblock(ifccParser::IfblockContext * ctx) override;

    virtual antlrcpp::Any visitElseblock(ifccParser::ElseblockContext * ctx) override;

    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext * ctx) override;

    virtual antlrcpp::Any visitCdtand(ifccParser::CdtandContext * ctx) override;

    virtual antlrcpp::Any visitCdtor(ifccParser::CdtorContext * ctx) override;

    virtual antlrcpp::Any visitEqual(ifccParser::EqualContext * ctx) override;

    virtual antlrcpp::Any visitNotequal(ifccParser::NotequalContext * ctx) override;

    virtual antlrcpp::Any visitGreater_equal_lesser_equal(ifccParser::Greater_equal_lesser_equalContext * ctx) override;

    virtual antlrcpp::Any visitWhileblock(ifccParser::WhileblockContext * ctx) override;

    virtual antlrcpp::Any visitArray(ifccParser::ArrayContext * ctx) override;

    virtual antlrcpp::Any visitArray_decl(ifccParser::Array_declContext * ctx) override;

    virtual antlrcpp::Any visitArray_aff(ifccParser::Array_affContext * ctx) override;

    //-------------------------------------------- Constructeurs - destructeur
    ASTGenerator()
        : program(nullptr), lastDeclaredType(ERROR), currentScope("0") {}
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~ASTGenerator() override;

    //------------------------------------------------------------------ PRIVE

  protected:
    bool checkExpr(Expr * expr);
    void expandScope();
    void reduceScope();

    //----------------------------------------------------- Attributs protégés

    Program * program;
    Type lastDeclaredType;
    string currentFunction;
    string currentScope;
    vector<int> scopeIndexIncrement;
};
//-------------------------------- Autres définitions dépendantes de <ASTGenerator>

#endif // ASTGENERATOR_H