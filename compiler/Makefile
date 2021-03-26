OUTPUT=output
GENERATED=antlr4-generated
SOURCES=src
GRAMMAR=ifcc.g4

#override with your local installation
#ANTLR4_BINDIR=/usr/bin
#ANTLR4_INCDIR=/usr/local/include/antlr4-runtime
#ANTLR4_LIBDIR=/usr/local/lib
ANTLR4_BINDIR=/usr/bin
ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib
TEST_DIR=../tests

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

compile: ifcc

ifcc: dirs antlr $(SOURCES)/main.cpp $(SOURCES)/ASTGenerator.cpp $(SOURCES)/ASTGenerator.h $(SOURCES)/SymbolTable.cpp $(SOURCES)/SymbolTable.h $(SOURCES)/IR.cpp $(SOURCES)/IR.h
	$(CC) $(CCARGS) $(SOURCES)/main.cpp  -o $(OUTPUT)/main.o
	$(CC) $(CCARGS) $(GENERATED)/ifccBaseVisitor.cpp -o $(OUTPUT)/ifccBaseVisitor.o
	$(CC) $(CCARGS) $(GENERATED)/ifccLexer.cpp -o $(OUTPUT)/ifccLexer.o
	$(CC) $(CCARGS) $(GENERATED)/ifccVisitor.cpp -o $(OUTPUT)/ifccVisitor.o
	$(CC) $(CCARGS) $(GENERATED)/ifccParser.cpp -o $(OUTPUT)/ifccParser.o
	$(CC) $(CCARGS) $(SOURCES)/ASTGenerator.cpp -o $(OUTPUT)/ASTGenerator.o
	$(CC) $(CCARGS) $(SOURCES)/ast.cpp -o $(OUTPUT)/ast.o
	$(CC) $(CCARGS) $(SOURCES)/SymbolTable.cpp -o $(OUTPUT)/SymbolTable.o
	$(CC) $(CCARGS) $(SOURCES)/IR.cpp -o $(OUTPUT)/IR.o
	$(CC) $(LDARGS) $(OUTPUT)/main.o $(OUTPUT)/ifccBaseVisitor.o $(OUTPUT)/ifccLexer.o $(OUTPUT)/ifccVisitor.o $(OUTPUT)/ifccParser.o $(OUTPUT)/ASTGenerator.o $(OUTPUT)/ast.o $(OUTPUT)/SymbolTable.o $(OUTPUT)/IR.o $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o ifcc

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT)
	mkdir -p $(GENERATED)

test:
	cd $(TEST_DIR) && sh test_if.sh

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)
