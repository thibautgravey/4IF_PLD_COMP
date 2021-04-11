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
    if (argn < 2) {
        cerr << "You have to specify an input file.\nUsage : ./ifcc INPUT_FILE [OUTPUT_FILE] [--as=ASSEMBLY_TYPE]" << endl;
        return EXIT_FAILURE;
    }

    if (argn >= 2) {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }

    string assemblyType = "x86";
    bool assemblyTypeSpecified = false;
    string outputPath = string(argv[1]);
    size_t dotPosition = outputPath.find('.');
    if (dotPosition != string::npos) {
        outputPath.erase(outputPath.find('.'));
    }
    outputPath.append(".s");

    if (argn >= 5) {
        cerr << "You have specified too many arguments.\nUsage : ./ifcc INPUT_FILE [OUTPUT_FILE] [--as=ASSEMBLY_TYPE]" << endl;
        return EXIT_FAILURE;
    } else {
        for (int i = 2; i < argn; i++) {
            if (string(argv[i]) == "--as=ARM" || string(argv[i]) == "--as=arm") {
                if (!assemblyTypeSpecified) {
                    assemblyType = "arm";
                    assemblyTypeSpecified = true;
                } else {
                    cerr << "You have specified 2 assembly types.\nUsage : ./ifcc INPUT_FILE [OUTPUT_FILE] [--as=ASSEMBLY_TYPE]" << endl;
                    return EXIT_FAILURE;
                }

            } else if (string(argv[i]) == "--as=X86" || string(argv[i]) == "--as=x86") {
                if (!assemblyTypeSpecified) {
                    assemblyType = "x86";
                    assemblyTypeSpecified = true;
                } else {
                    cerr << "You have specified 2 assembly types.\nUsage : ./ifcc INPUT_FILE [OUTPUT_FILE] [--as=ASSEMBLY_TYPE]" << endl;
                    return EXIT_FAILURE;
                }
            } else {
                outputPath = string(argv[i]);
                size_t dotPosition = outputPath.find('.');
                if (dotPosition != string::npos) {
                    outputPath.erase(outputPath.find('.'));
                }
                outputPath.append(".s");
            }
        }
    }

    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    ifccParser parser(&tokens);
    tree::ParseTree * tree = parser.axiom();

    //Check error from the parser

    int lexerErrors = lexer.getNumberOfSyntaxErrors();
    int parserErrors = parser.getNumberOfSyntaxErrors();

    if (lexerErrors || parserErrors)
        return EXIT_FAILURE;

    //Create a real ASTVisitor/ASTGenerator and generate an AST with first static analysis

    ASTGenerator astGenerator;

    Program * program = astGenerator.visit(tree);

    if (program->GetErrorFlag()) {
        return EXIT_FAILURE;
    }

    //Other static analysis

    program->UnusedVariableAnalysis();
    program->UnusedFunctionAnalysis();
    program->FunctionReturnAnalysis();

    //Create an IR and generate ASM
    IR * ir = program->GenerateIR();

    ofstream out(outputPath);
    if (out.bad()) {
        cerr << "An error occured when writing Generated ASM to " + outputPath << endl;
    } else {
        if (assemblyType == "x86") {
            ir->GenerateAsmX86(out);
        } else {
            ir->GenerateAsmARM(out);
        }
        out.close();
    }

    //Generate an exec file with a an "as file.s -o file.o" and then link using gcc

    delete (ir);

    return EXIT_SUCCESS;
}
