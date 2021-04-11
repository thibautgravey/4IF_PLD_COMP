# PLD Comp : C compiler written in C++ and using Antlr4, by HexaOne (H4211)

This is a long duration project made in 4th year at INSA Lyon.
The objective of this project is the design of a compiler for a subset of the C language.

Link to our github repository : https://github.com/thibautgravey/4IF_PLD_COMP

## Folders

`compiler/` : contains the Antlr4 grammar (ifcc.g4), the Makefile, the wrapper to use docker and the various compilation scripts.<br>
`compiler/src` : contains the source code (.h and .cpp files).<br>
`tests/` : contains all the files and scripts related to tests.<br>

## Prerequisites

You have to override the antlr directories in the Makefile with you local installation :

`ANTLR4_BINDIR=/usr/bin`
`ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime `
`ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib`

The above example should work in the IF machines of rooms 208 and 219.

_Note : You can use the wrapper (`compiler/wrapper.sh`) to execute our compiler through docker if you don't have a local installation of antlr._

## Usage

First, you have to go in the `compiler/` folder.

You can compile the project by running `make`.

You can execute the compiler with `./ifcc INPUT_FILE [OUTPUT_FILE] [--as=ASSEMBLY_TYPE]`

INPUT_FILE : a path to .c file with the code you want to compile<br>
OUTPUT_FILE : a path to .s file, where the assembly code is going to be written (default: same name than INPUT_FILE, with .s extension)<br>
ASSEMBLY_TYPE : the assembly language you want to compile in. Supported : x86, arm. (default: x86)<br>

## Tests

You can run all the tests with `make test`.

Then, you can have detailed results in the folder `tests/pld-test-output/` (one folder per test)
