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

    //TODO : Create a real ASTVisitor/ASTGenerator and generate an AST with first static analysis

    ASTGenerator astGenerator;

    Program * program = astGenerator.visit(tree);

    //TODO : Other static analysis

    program->UnusedVariableAnalysis();

    //TODO : Check error

    int lexerErrors = lexer.getNumberOfSyntaxErrors();
    int parserErrors = parser.getNumberOfSyntaxErrors();

    if (lexerErrors || parserErrors || program->GetErrorFlag())
        return 1;

    //TODO : Create an IR and generate ASM
    string generatedAsm = program->GenerateAsm();
    cout << generatedAsm << endl;

    //Create the output path
    string outPath(argv[1]);
    if (argn == 3) {
        outPath = string(argv[2]);
    }

    size_t dotPosition = outPath.find('.');
    if (dotPosition != string::npos) {
        outPath.erase(outPath.find('.'));
    }
    outPath.append(".s");

    ofstream out(outPath);
    if (out.bad()) {
        cerr << "An error occured when writing Generated ASM to " + outPath << endl;
    } else {
        out << generatedAsm;
    }

    out.close();

    //TODO : Generate an exec file with a an "as file.s -o file.o" and then link using gcc

    return 0;
}
