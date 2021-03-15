#ifndef IR_H
#define IR_H

#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

// Declarations from the parser -- replace with your own
#include "SymbolTable.h"
#include "ast.h"

class BasicBlock;
class CFG;
class DefFonction;

//! The class for one 3-address instruction
class IRInstr {

  public:
    /** The instructions themselves -- feel free to subclass instead */
    typedef enum {
        ldconst,
        copy,
        add,
        sub,
        mul,
        rmem,
        wmem,
        call,
        cmp_eq,
        cmp_lt,
        cmp_le
    } Operation;

    /**  constructor */
    IRInstr(BasicBlock * bb_, Operation op, Type t, vector<string> params);

    /** Actual code generation */
    void gen_asm(ostream & o); /**< x86 assembly code generation for this IR instruction */

  private:
    BasicBlock * bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
    Operation op;
    Type t;
    vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
                           // if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design.
};

/**  The class for a basic block */

/* A few important comments.
	 IRInstr has no jump instructions.
	 cmp_* instructions behaves as an arithmetic two-operand instruction (add or mult),
	  returning a boolean value (as an int)

	 Assembly jumps are generated as follows:
	 BasicBlock::gen_asm() first calls IRInstr::gen_asm() on all its instructions, and then
		    if  exit_true  is a  nullptr,
            the epilogue is generated
        else if exit_false is a nullptr,
          an unconditional jmp to the exit_true branch is generated
				else (we have two successors, hence a branch)
          an instruction comparing the value of test_var_name to true is generated,
					followed by a conditional branch to the exit_false branch,
					followed by an unconditional branch to the exit_true branch
	 The attribute test_var_name itself is defined when converting
  the if, while, etc of the AST  to IR.

Possible optimization:
     a cmp_* comparison instructions, if it is the last instruction of its block,
       generates an actual assembly comparison
       followed by a conditional jump to the exit_false branch
*/

class BasicBlock {
  public:
    BasicBlock(CFG * cfg, string entry_label);
    void gen_asm(ostream & o); /**< x86 assembly code generation for this basic block (very simple) */

    void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);

    // No encapsulation whatsoever here. Feel free to do better.
    BasicBlock * exit_true;   /**< pointer to the next basic block, true branch. If nullptr, return from procedure */
    BasicBlock * exit_false;  /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
    string label;             /**< label of the BB, also will be the label in the generated code */
    CFG * cfg;                /** < the CFG where this block belongs */
    vector<IRInstr *> instrs; /** < the instructions themselves. */
    string test_var_name;     /** < when generating IR code for an if(expr) or while(expr) etc,
													 store here the name of the variable that holds the value of expr */
  protected:
};

/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	 The entry block is the one with the same label as the AST function name.
	   (it could be the first of bbs, or it could be defined by an attribute value)
	 The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG {
  public:
    CFG(DefFonction * ast);

    DefFonction * ast; /**< The AST this CFG comes from */

    void add_bb(BasicBlock * bb);

    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
    void gen_asm(ostream & o);
    string IR_reg_to_asm(string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
    void gen_asm_prologue(ostream & o);
    void gen_asm_epilogue(ostream & o);

    // basic block management
    string new_BB_name();
    BasicBlock * current_bb;

  protected:
    int nextBBnumber; /**< just for naming */

    vector<BasicBlock *> bbs; /**< all the basic blocks of this CFG*/
};

class IR {
  public:
    void BuildIR(Program * ast);
    string GenerateAsmX86();

    IR() = default;
    virtual ~IR() = default;

  protected:
    vector<CFG *> allCFG;
};

#endif
