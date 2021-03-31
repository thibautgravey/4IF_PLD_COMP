#include <iostream>

#include "ASTGenerator.h"
#include "antlr4-runtime.h"
#include "ifccLexer.h"
#include "ifccParser.h"

#include "IR.h"
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

    ifccParser parser(&tokens);
    tree::ParseTree * tree = parser.axiom();

    //TODO : Check error from the parser

    int lexerErrors = lexer.getNumberOfSyntaxErrors();
    int parserErrors = parser.getNumberOfSyntaxErrors();

    if (lexerErrors || parserErrors)
        return EXIT_FAILURE;

    //TODO : Create a real ASTVisitor/ASTGenerator and generate an AST with first static analysis

    ASTGenerator astGenerator;

    Program * program = astGenerator.visit(tree);

    if (program->GetErrorFlag())
        return EXIT_FAILURE;

    //TODO : Other static analysis

    program->UnusedVariableAnalysis();
    program->UnusedFunctionAnalysis();

    //TODO : Create an IR and generate ASM
    IR * ir = program->GenerateIR();

    //Create the output path
    string outPath(argv[1]);
    if (argn == 3) {
        outPath = string(argv[2]);

        size_t dotPosition = outPath.find('.');
        if (dotPosition != string::npos) {
            outPath.erase(outPath.find('.'));
        }
        outPath.append(".s");

        ofstream out(outPath);
        if (out.bad()) {
            cerr << "An error occured when writing Generated ASM to " + outPath << endl;
        } else {
            ir->GenerateAsmX86(out);
            out.close();
        }
    } else {
        ir->GenerateAsmX86(cout);
    }

    //TODO : Generate an exec file with a an "as file.s -o file.o" and then link using gcc

    return EXIT_SUCCESS;
}
