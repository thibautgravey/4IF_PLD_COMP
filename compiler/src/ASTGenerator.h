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

    virtual antlrcpp::Any visitConst(ifccParser::ConstContext * ctx) override;

    virtual antlrcpp::Any visitOpp_or_not(ifccParser::Opp_or_notContext * ctx) override;

    virtual antlrcpp::Any visitVar(ifccParser::VarContext * ctx) override;

    virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext * ctx) override;

    virtual antlrcpp::Any visitInline_var_decl(ifccParser::Inline_var_declContext * ctx) override;

    virtual antlrcpp::Any visitDef_func(ifccParser::Def_funcContext * ctx) override;

    virtual antlrcpp::Any visitParam_list(ifccParser::Param_listContext * ctx) override;

    virtual antlrcpp::Any visitParam(ifccParser::ParamContext * ctx) override;

    virtual antlrcpp::Any visitExpr_list(ifccParser::Expr_listContext * ctx) override;
    
    virtual antlrcpp::Any visitIfblock(ifccParser::IfblockContext * ctx) override;

    virtual antlrcpp::Any visitElseblock(ifccParser::ElseblockContext * ctx) override;

    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext * ctx) override;

    virtual antlrcpp::Any visitCdtand(ifccParser::CdtandContext * context) override;

    virtual antlrcpp::Any visitCdtor(ifccParser::CdtorContext * context) override;

    virtual antlrcpp::Any visitEqual(ifccParser::EqualContext * context) override;

    virtual antlrcpp::Any visitNotequal(ifccParser::NotequalContext * context) override;

    virtual antlrcpp::Any visitGreaterequal(ifccParser::GreaterequalContext * context) override;

    virtual antlrcpp::Any visitGreater(ifccParser::GreaterContext * context) override;

    virtual antlrcpp::Any visitLessequal(ifccParser::LessequalContext * context) override;

    virtual antlrcpp::Any visitLess(ifccParser::LessContext * context) override;

    //-------------------------------------------- Constructeurs - destructeur
    ASTGenerator()
        : program(nullptr), lastDeclaredType(ERROR) {}
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~ASTGenerator() override;

    //------------------------------------------------------------------ PRIVE

  protected:
    bool checkExpr(Expr * expr);
    //----------------------------------------------------- Attributs protégés

    Program * program;
    Type lastDeclaredType;
    string currentFunction;
};
//-------------------------------- Autres définitions dépendantes de <ASTGenerator>

#endif // ASTGENERATOR_H