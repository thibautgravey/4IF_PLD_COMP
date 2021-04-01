/*******************************************************************************
                           IR  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <IR> (fichier IR.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

using namespace std;

//------------------------------------------------------ Include personnel
#include "IR.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void IRInstr::gen_asm_X86(ostream & o) {

    string p1, p2, p3;
    switch (this->params.size()) {
        case 3:
            p3 = this->bb->cfg->IR_reg_to_asm_X86(this->params[2]);
        case 2:
            p2 = this->bb->cfg->IR_reg_to_asm_X86(this->params[1]);
        case 1:
            p1 = this->bb->cfg->IR_reg_to_asm_X86(this->params[0]);
        default:
            break;
    }

    switch (this->op) {
        case ldconst:
            o << "        movl    $" << p2 << ", " << p1 << endl;
            break;
        case copy:
            o << "        movl    " << p2 << ", %eax" << endl;
            o << "        movl    %eax, " << p1 << endl;
            break;
        case add:
            o << "        movl    " << p2 << ", %eax" << endl;
            o << "        addl    " << p3 << ", %eax" << endl;
            o << "        movl    %eax, " << p1 << endl;
            break;
        case sub:
            o << "        movl    " << p2 << ", %eax" << endl;
            o << "        subl    " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case mul:
            o << "        movl    " << p2 << ", %eax" << endl;
            o << "        imull    " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case div:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cltd   " << endl;
            o << "        idivl  " << p3 << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case orB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        orl      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case andB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        andl      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case xorB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        xorl      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case neg:
            o << "        cmpl     $0, " << p2 << endl;
            o << "        sete     %al" << endl;
            o << "        movzbl     %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case opp:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        negl     %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case rmem:
            o << "        movl    " << p2 << ", " << p1 << endl;
            break;
        case wmem:
            o << "        movl    " << p2 << ", " << p1 << endl;
            break;
        case call:
            o << "        call    " << p1 << endl;
            break;
        case cmp_eq:
            o << "cmp_eq NOT IMPLEMENDTED" << endl;
            break;
        case cmp_lt:
            o << "cmp_lt NOT IMPLEMENDTED" << endl;
            break;
        case cmp_le:
            o << "cmp_eq NOT IMPLEMENDTED" << endl;
            break;
        case ret:
            o << "        movl    " << p1 << ", %eax" << endl;
            break;
        default:
            break;
    }
} //fin de gen_asm_X86(Ir_Instr)

void IRInstr::gen_asm_ARM(ostream & o) {

    string p1, p2, p3;
    switch (this->params.size()) {
        case 3:
            p3 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[2]);
        case 2:
            p2 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[1]);
        case 1:
            p1 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[0]);
        default:
            break;
    }

    switch (this->op) {
        case ldconst:
            o << "        movs    r3, #" << p2 << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case copy:
            o << "        ldr     r3, " << p1 << endl;
            o << "        str     r3, " << p2 << endl;
            break;
        case add:
            o << "        ldr     r2, " << p2 << endl;
            o << "        ldr     r3, " << p3 << endl;
            o << "        add     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case sub:
            o << "        ldr     r2, " << p2 << endl;
            o << "        ldr     r3, " << p3 << endl;
            o << "        subs     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case mul:
            o << "        ldr     r2, " << p2 << endl;
            o << "        ldr     r3, " << p3 << endl;
            o << "        mul     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case div:
            o << "        ldr     r2, " << p2 << endl;
            o << "        ldr     r3, " << p3 << endl;
            o << "        bl      __aeabi_idiv" << endl;
            o << "        mov     r3, r0" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case orB:
            o << "        ldr     r2, " << p2 << endl;
            o << "        ldr     r3, " << p3 << endl;
            o << "        orrs     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case andB:
            o << "        ldr     r2, " << p2 << endl;
            o << "        ldr     r3, " << p3 << endl;
            o << "        ands     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case xorB:
            o << "        ldr     r2, " << p2 << endl;
            o << "        ldr     r3, " << p3 << endl;
            o << "        eors     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case neg:
            o << "        ldr     r3, " << p2 << endl;
            o << "        cmp     r3, #0" << endl;
            o << "        ite     eq" << endl;
            o << "        moveq   r3, #1" << endl;
            o << "        movne   r3, #0" << endl;
            o << "        uxtb    r3, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case opp:
            o << "        ldr     r3, " << p2 << endl;
            o << "        rsbs     r3, r3, #0" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case rmem:
            o << " rmem NOT IMPLEMENDTED" << endl;
            break;
        case wmem:
            o << " wmem NOT IMPLEMENDTED" << endl;
            break;
        case call:
            o << "        bl    " << p1 << endl;
            break;
        case cmp_eq:
            o << "cmp_eq NOT IMPLEMENDTED" << endl;
            break;
        case cmp_lt:
            o << "cmp_lt NOT IMPLEMENDTED" << endl;
            break;
        case cmp_le:
            o << "cmp_eq NOT IMPLEMENDTED" << endl;
            break;
        case ret:
            o << "        ldr     r3, " << p1 << endl;
            break;
        default:
            break;
    }
} //fin de gen_asm_ARM(Ir_Instr)

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
    this->instrs.push_back(new IRInstr(this, op, t, params));
} //fin de add_IRInst

void CFG::add_bb(BasicBlock * bb) {
    this->bbs.push_back(bb);
    this->current_bb = bb;
} //fin de add_bb

void CFG::gen_asm_X86(ostream & o) {
    BasicBlock * lastbb = this->bbs.back();
    this->bbs.pop_back();
    gen_asm_prologue_X86(o, this->bbs[0]);
    this->bbs.erase(this->bbs.begin());
    for (BasicBlock * bb : this->bbs) {
        o << bb->label << ":" << endl;
        for (IRInstr * instr : bb->instrs) {
            instr->gen_asm_X86(o);
        }
        if (bb->exit_false == nullptr) {
            o << "        jmp " << bb->exit_true->label << endl;
        } else {
            o << "        je " << bb->exit_true->label << endl;
            o << "        jmp " << bb->exit_false->label << endl;
        }
    }

    gen_asm_epilogue_X86(o, lastbb);
} //fin de gen_asm_x86(CFG)

//TODO
void CFG::gen_asm_ARM(ostream & o) {
    BasicBlock * lastbb = this->bbs.back();
    this->bbs.pop_back();
    gen_asm_prologue_ARM(o, this->bbs[0]);
    this->bbs.erase(this->bbs.begin());
    for (BasicBlock * bb : this->bbs) {
        o << bb->label << ":" << endl;
        for (IRInstr * instr : bb->instrs) {
            instr->gen_asm_ARM(o);
        }
        if (bb->exit_false == nullptr) {
            o << "        b " << bb->exit_true->label << endl;
        } else {
            o << "        beq " << bb->exit_true->label << endl;
            o << "        b " << bb->exit_false->label << endl;
        }
    }

    gen_asm_epilogue_ARM(o, lastbb);
} //fin de gen_asm_ARM(CFG)

string CFG::IR_reg_to_asm_X86(string reg) {

    string ret;

    if (reg == "reg1") {
        ret = "%eax";
    } else if (reg == "reg2") {
        ret = "%ebx";
    } else {
        if (this->symbolTable->LookUp("main", reg)) {
            int offset = this->symbolTable->GetVariableOffset("main", reg);
            ret = to_string(offset) + "(%rbp)";
        } else {
            ret = reg;
        }
    }

    return ret;
} //fin de IR_reg_to_asm_X86

string CFG::IR_reg_to_asm_ARM(string reg) {

    string ret;

    if (reg == "reg1") {
        ret = "r3";
    } else if (reg == "reg2") {
        ret = "r0";
    } else {
        if (this->symbolTable->LookUp("main", reg)) {
            int offset = -(this->symbolTable->GetVariableOffset("main", reg));
            ret = "[r7, #" + to_string(offset) + "]";
        } else {
            ret = reg;
        }
    }

    return ret;
} //fin de IR_reg_to_asm_ARM

void CFG::gen_asm_prologue_X86(ostream & o, BasicBlock * bb) {
    o << "main:" << endl;
    o << bb->label << ":" << endl;
    o << "        pushq    %rbp" << endl;
    o << "        movq     %rsp, %rbp" << endl;

    int spaceNeeded = this->symbolTable->CalculateSpaceForFunction("main");

    // Round space to the nearest multiple of 16
    if (spaceNeeded % 16) {
        spaceNeeded = ((spaceNeeded / 16) + 1) * 16;
    }

    o << "        subq     $" << to_string(spaceNeeded) << ", %rsp" << endl;
    o << "        jmp " << bb->exit_true->label << endl;
} //fin de gen_asm_prologue_X86

//TODO
void CFG::gen_asm_prologue_ARM(ostream & o, BasicBlock * bb) {
    o << bb->label << ":" << endl;
    o << "        push    {r7}" << endl; //si main : push    {r7, lr}

    int spaceNeeded = this->symbolTable->CalculateSpaceForFunction("main");

    // Round space to the nearest multiple of 4
    if (spaceNeeded % 8) {
        spaceNeeded = ((spaceNeeded / 8) + 1) * 8 + 4;
    }

    o << "        sub     sp, sp, #" << spaceNeeded << endl;
    o << "        add     r7, sp, #0" << endl;
    // o << "        subq     $" << to_string(spaceNeeded) << ", %rsp" << endl;
    // o << "        jmp " << bb->exit_true->label << endl;
} //fin de gen_asm_prologue_ARM

void CFG::gen_asm_epilogue_X86(ostream & o, BasicBlock * bb) {
    o << bb->label << ":" << endl;
    o << "        leave" << endl;
    o << "        ret" << endl;
} //fin de gen_asm_epilogue_X86

//TODO
void CFG::gen_asm_epilogue_ARM(ostream & o, BasicBlock * bb) {

    int spaceNeeded = this->symbolTable->CalculateSpaceForFunction("main");

    // Round space to the nearest multiple of 4
    if (spaceNeeded % 8) {
        spaceNeeded = ((spaceNeeded / 8) + 1) * 8 + 4;
    }

    o << bb->label << ":" << endl;
    o << "        mov     r0, r3" << endl;
    o << "        adds    r7, r7, #" << spaceNeeded << endl;
    o << "        mov     sp, r7" << endl;
    o << "        ldr     r7, [sp], #4" << endl;
    o << "        bx      lr" << endl;
} //fin de gen_asm_epilogue_ARM

string CFG::new_BB_name(const string & prefix) {
    string functionName = "main"; //TODO : change this when implementing function
    if (prefix.empty()) {
        return "." + functionName + "BB" + to_string(this->nextBBnumber++);
    } else {
        return "." + prefix + "_" + functionName;
    }
} //fin de new_BB_name

BasicBlock * CFG::GetCurrentBB() {
    return this->current_bb;
} //----- Fin de GetCurrentBB

SymbolTable * CFG::GetSymbolTable() {
    return this->symbolTable;
} //----- Fin de GetSymbolTable

void IR::GenerateAsmX86(ostream & o) {
    gen_asm_prologue_global_X86(o);

    for (CFG * cfg : this->allCFG) {
        cfg->gen_asm_X86(o);
        o << endl;
    }
    //TODO? ajouter épilogue bdsm
} //----- Fin de GenerateAsmX86

void IR::GenerateAsmARM(ostream & o) {
    gen_asm_prologue_global_ARM(o);

    for (CFG * cfg : this->allCFG) {
        cfg->gen_asm_ARM(o);
        o << endl;
    }
    //TODO? ajouter épilogue bdsm
} //----- Fin de GenerateAsmARM

void IR::AddCFG(CFG * newCFG) {
    this->allCFG.push_back(newCFG);
}

void IR::gen_asm_prologue_global_X86(ostream & o) {
    o << "        .globl main" << endl
      << endl;
} //----- Fin de gen_asm_prologue_global_X86

void IR::gen_asm_prologue_global_ARM(ostream & o) {
    o << ".globl _start" << endl;
    o << ".arm" << endl;
} //----- Fin de gen_asm_prologue_global_ARM

//-------------------------------------------- Constructeurs - destructeur

IRInstr::IRInstr(BasicBlock * bb_, Operation op, Type t, vector<string> params)
    : bb(bb_), op(op), t(t), params(params) {

} //fin de constructeur de IRInst

BasicBlock::BasicBlock(CFG * cfg, string entry_label) {
    this->cfg = cfg;
    this->label = entry_label;
    this->exit_true = nullptr;
    this->exit_false = nullptr;
} //fin de constructeur de BasicBlock

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
