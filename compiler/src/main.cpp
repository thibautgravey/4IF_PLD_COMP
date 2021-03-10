#include <iostream>

#include "ASTGenerator.h"
#include "antlr4-runtime.h"
#include "ifccLexer.h"
#include "ifccParser.h"

#include "ast.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char ** argv) {
    stringstream in;
    if (argn >= 2) {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }
    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    //  for (auto token : tokens.getTokens()) {
    //    std::cout << token->toString() << std::endl;
    //  }

    ifccParser parser(&tokens);
    tree::ParseTree * tree = parser.axiom();

    //TODO : Create a real ASTVisitor/ASTGenerator and generate an AST

    ASTGenerator astGenerator;

    Program * program = astGenerator.visit(tree);

    int lexerErrors = lexer.getNumberOfSyntaxErrors();
    int parserErrors = parser.getNumberOfSyntaxErrors();

    if (lexerErrors || parserErrors || program->GetErrorFlag())
        return 1;

    //TODO : Create an IR and generate ASM
    cout << program->GenerateAsm();

    //Create the output path
    string outPath(argv[1]);
    if (argn == 3) {
        outPath = string(argv[2]);
    }
    outPath.erase(outPath.find("."));
    outPath.append(".s");

    //TODO : Generate an exec file with a an "as file.s -o file.o" and then link using gcc

    return 0;
}
