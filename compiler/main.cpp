#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "antlr4-generated/ifccBaseVisitor.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-runtime.h"
#include "visitor.h"

#include "ast.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv) {
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
    tree::ParseTree *tree = parser.axiom();

    //TODO : Create a real ASTVisitor/ASTGenerator and generate an AST

    Visitor visitor;

    Program *program = visitor.visit(tree);

    // TO DO : detect if there are errors
    bool visitorError = false;

    int lexerErrors = lexer.getNumberOfSyntaxErrors();
    int parserErrors = parser.getNumberOfSyntaxErrors();

    if (lexerErrors || parserErrors || visitorError)
        return 1;

    //TODO : Create an IR and generate ASM

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
