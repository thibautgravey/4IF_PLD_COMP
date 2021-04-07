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
    // TODO : voir si on peut améliorer

    if (this->op != call) {
        switch (this->params.size()) {
            case 3:
                p3 = this->bb->cfg->IR_reg_to_asm_X86(this->params[2], this->bb->scope);
            case 2:
                p2 = this->bb->cfg->IR_reg_to_asm_X86(this->params[1], this->bb->scope);
            case 1:
                p1 = this->bb->cfg->IR_reg_to_asm_X86(this->params[0], this->bb->scope);
            default:
                break;
        }
    } else {
        p1 = this->params[0];
        p2 = this->bb->cfg->IR_reg_to_asm_X86(this->params[1], this->bb->scope);
    }

    switch (this->op) {
        case ldconst:
            o << "        movl    " << p2 << ", " << p1 << endl;
            break;
        case copy:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        movl    %eax, " << p1 << endl;
            break;
        case add:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        addl     " << p3 << ", %eax" << endl;
            o << "        movl    %eax, " << p1 << endl;
            break;
        case sub:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        subl     " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case mul:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        imull    " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case div:
            if (p3[0] == '$') {
                o << "        movl     " << p3 << ", %ecx" << endl;
                p3 = "%ecx";
            }
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cltd     " << endl;
            o << "        idivl    " << p3 << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case orB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        orl      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case andB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        andl     " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case xorB:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        xorl     " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case neg:
            o << "        cmpl     $0, " << p2 << endl;
            o << "        sete     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case opp:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        negl     %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case rmem:
            o << "        movl     " << p2 << ", " << p1 << endl;
            break;
        case wmem:
            o << "        movl     " << p2 << ", " << p1 << endl;
            break;
        case call: {
            // TODO : voir pour les registres de passages de paramètre : 32 ou 64 bits
            for (int i = 2; i < params.size(); i++) {
                p3 = this->bb->cfg->IR_reg_to_asm_X86(this->params[i], this->bb->scope);
                string dest;
                switch (i - 2) {
                    case 0:
                        dest = "%edi";
                        break;
                    case 1:
                        dest = "%esi";
                        break;
                    case 2:
                        dest = "%edx";
                        break;
                    case 3:
                        dest = "%ecx";
                        break;
                    case 4:
                        dest = "%r8d";
                        break;
                    case 5:
                        dest = "%r9d";
                        break;
                }
                o << "        movl    " << p3 << ", " << dest << endl;
            }
            o << "        call    " << p1 << endl;
            break;
        }
        case cmp_eq:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3 << ", %eax" << endl;
            o << "        sete     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_neq:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3 << ", %eax" << endl;
            o << "        setne    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_g:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3 << ", %eax" << endl;
            o << "        setg     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_ge:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3 << ", %eax" << endl;
            o << "        setge    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_l:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3 << ", %eax" << endl;
            o << "        setl     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_le:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3 << ", %eax" << endl;
            o << "        setle    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;

        case cdtAnd:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        and      " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cdtOr:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        or       " << p3 << ", %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case ret:
            o << "        movl     " << p1 << ", %eax" << endl;
            o << "        jmp      " << bb->cfg->bb_epilogue->label << endl;
            break;

        default:
            break;
    }
} //fin de gen_asm_X86(Ir_Instr)

void IRInstr::gen_asm_ARM(ostream & o) {

    string p1, p2, p3;
    if (this->op != call) {
        switch (this->params.size()) {
            case 3:
                p3 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[2], this->bb->scope);
            case 2:
                p2 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[1], this->bb->scope);
            case 1:
                p1 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[0], this->bb->scope);
            default:
                break;
        }
    } else {
        p1 = this->params[0];
        p2 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[1], this->bb->scope);
    }

    switch (this->op) {
        case ldconst:
            if (p1 != "r3") {
                o << "        movs    r3, #" << p2 << endl;
                o << "        str     r3, " << p1 << endl;
            }
            break;
        case copy:
            o << "       @COPY     " << p3 << ", " << p2 << ", " << p1 << endl;
            if (p2 == "r0" || p2 == "r1" || p2 == "r2" || p2 == "r3") {
                o << "        str     " << p2 << ", " << p1 << endl;
            } else {
                o << "        ldr     r3, " << p2 << endl;
                o << "        str     r3, " << p1 << endl;
            }
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
            o << "        ldr     r0, " << p2 << endl;
            o << "        ldr     r1, " << p3 << endl;
            o << "        bl      __aeabi_idiv(PLT)" << endl;
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
            o << "  NOT IMPLEMENDTED" << endl;
            break;
        case wmem:
            o << " wmem NOT IMPLEMENDTED" << endl;
            break;
        // begin to change
        case call: {
            // TODO : voir pour les registres de passages de paramètre : 32 ou 64 bits
            for (int i = 2; i < params.size(); i++) {
                p3 = this->bb->cfg->IR_reg_to_asm_ARM(this->params[i], this->bb->scope);
                string dest;
                switch (i - 2) {
                    case 0:
                        dest = "r0";
                        break;
                    case 1:
                        dest = "r1";
                        break;
                    case 2:
                        dest = "r2";
                        break;
                    case 3:
                        dest = "r3";
                        break;
                }
                o << "        ldr    " << dest << ", " << p3 << endl;
            }
            o << "        bl    " << p1 << endl;
            o << "        mov     r3, r0" << endl;
            o << "        str     r3, " << p2 << endl;
            break;
        }
        case cmp_eq:
            o << "  cmp_eq NOT IMPLEMENDTED" << endl;
            break;
        case cmp_neq:
            o << "  cmp_neq NOT IMPLEMENDTED" << endl;
            break;
        case cmp_g:
            o << "  cmp_g NOT IMPLEMENDTED" << endl;
            break;
        case cmp_ge:
            o << "  cmp_ge NOT IMPLEMENDTED" << endl;
            break;
        case cmp_l:
            o << "  cmp_l NOT IMPLEMENDTED" << endl;
            break;
        case cmp_le:
            o << "  cmp_le NOT IMPLEMENDTED" << endl;
            break;
        case cdtAnd:
            o << " cdtAnd  NOT IMPLEMENDTED" << endl;
            break;
        case cdtOr:
            o << "  cdtOr NOT IMPLEMENDTED" << endl;
            break;
            //end to change
        case ret:
            o << "        ldr     r3, " << p1 << endl;
            break;
        default:
            break;
    }
} //fin de gen_asm_ARM(Ir_Instr)

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params, string scope) {
    if (this->instrs.empty()) {
        this->scope = scope;
    }
    this->instrs.push_back(new IRInstr(this, op, t, params));
} //fin de add_IRInst

BasicBlock::~BasicBlock() {
    for (IRInstr * instr : this->instrs) {
        delete (instr);
    }
}

void CFG::add_bb(BasicBlock * bb) {
    this->bbs.push_back(bb);
    this->current_bb = bb;
} //fin de add_bb

void CFG::gen_asm_X86(ostream & o) {
    bool delete_jump = gen_asm_prologue_X86(o, this->bbs[0]);

    vector<BasicBlock *>::iterator it;
    vector<BasicBlock *>::iterator it2;

    bool use_block_label = false;
    for (it = this->bbs.begin() + 1; it != (this->bbs.end() - 1); it++) {
        if (delete_jump == false) {
            o << (*it)->label << ":" << endl;
        } else {
            delete_jump = false;
        }

        for (IRInstr * instr : (*it)->instrs) {
            instr->gen_asm_X86(o);
        }

        use_block_label = false;

        for (it2 = this->bbs.begin() + 1; it2 != (it); it2++) {
            if ((*it2)->exit_true == (*it)->exit_true || (*it2)->exit_false == (*it)->exit_true) {
                use_block_label = true;
                break;
            }
        }

        for (it2 = it + 1; it2 != (this->bbs.end() - 1); it2++) {
            if ((*it2)->exit_true == (*it)->exit_true || (*it2)->exit_false == (*it)->exit_true) {
                use_block_label = true;
                break;
            }
        }
        if ((*it)->exit_false == nullptr) {
            if ((*(it + 1))->label != (*it)->exit_true->label || use_block_label) {
                o << "        jmp      " << (*it)->exit_true->label << endl;

            } else {
                delete_jump = true;
            }

        } else {
            o << "        cmpl     $1, " << (*it)->cfg->IR_reg_to_asm_X86((*it)->test_var_name, (*it)->scope) << endl;
            o << "        jne      " << (*it)->exit_false->label << endl;

            if ((*(it + 1))->label != (*it)->exit_true->label || use_block_label) {
                o << "        jmp      " << (*it)->exit_true->label << endl;
            } else {
                delete_jump = true;
            }
        }
    }

    gen_asm_epilogue_X86(o, this->bbs[this->bbs.size() - 1]);
} //fin de gen_asm_x86(CFG)

//TODO
void CFG::gen_asm_ARM(ostream & o) {
    bool delete_jump = gen_asm_prologue_ARM(o, this->bbs[0]);

    vector<BasicBlock *>::iterator it;
    vector<BasicBlock *>::iterator it2;

    bool use_block_label = false;
    for (it = this->bbs.begin() + 1; it != (this->bbs.end() - 1); it++) {
        if (delete_jump == false) {
            o << (*it)->label << ":" << endl;
        } else {
            delete_jump = false;
        }

        for (IRInstr * instr : (*it)->instrs) {
            instr->gen_asm_ARM(o);
        }

        use_block_label = false;

        for (it2 = this->bbs.begin() + 1; it2 != (it); it2++) {
            if ((*it2)->exit_true == (*it)->exit_true || (*it2)->exit_false == (*it)->exit_true) {
                use_block_label = true;
                break;
            }
        }

        for (it2 = it + 1; it2 != (this->bbs.end() - 1); it2++) {
            if ((*it2)->exit_true == (*it)->exit_true || (*it2)->exit_false == (*it)->exit_true) {
                use_block_label = true;
                break;
            }
        }
        if ((*it)->exit_false == nullptr) {
            if ((*(it + 1))->label != (*it)->exit_true->label || use_block_label) {
                o << "        bl      " << (*it)->exit_true->label << endl;

            } else {
                delete_jump = true;
            }

        } else {
            o << "        cmp     $1, " << (*it)->cfg->IR_reg_to_asm_ARM((*it)->test_var_name, (*it)->scope) << endl;
            o << "        bne      " << (*it)->exit_false->label << endl;

            if ((*(it + 1))->label != (*it)->exit_true->label || use_block_label) {
                o << "        bl      " << (*it)->exit_true->label << endl;
            } else {
                delete_jump = true;
            }
        }
    }

    // BasicBlock * lastbb = this->bbs.back();
    // this->bbs.pop_back();
    // gen_asm_prologue_ARM(o, this->bbs[0]);
    // this->bbs.erase(this->bbs.begin());
    // for (BasicBlock * bb : this->bbs) {
    //     o << bb->label << ":" << endl;
    //     for (IRInstr * instr : bb->instrs) {
    //         instr->gen_asm_ARM(o);
    //     }
    //     if (bb->exit_false == nullptr) {
    //         o << "        b " << bb->exit_true->label << endl;
    //     } else {
    //         o << "        beq " << bb->exit_true->label << endl;
    //         o << "        b " << bb->exit_false->label << endl;
    //     }
    // }

    gen_asm_epilogue_ARM(o, this->bbs[this->bbs.size() - 1]);
} //fin de gen_asm_ARM(CFG)

string CFG::IR_reg_to_asm_X86(string reg, string scope) {

    string ret;

    if (reg == "reg1") {
        ret = "%eax";
    } else if (reg == "reg2") {
        ret = "%ebx";
    } else if (reg == "paramReg1") {
        ret = "%edi";
    } else if (reg == "paramReg2") {
        ret = "%esi";
    } else if (reg == "paramReg3") {
        ret = "%edx";
    } else if (reg == "paramReg4") {
        ret = "%ecx";
    } else if (reg == "paramReg5") {
        ret = "%r8d";
    } else if (reg == "paramReg6") {
        ret = "%r9d";
    } else {
        if (this->symbolTable->LookUpVariable(cfgName, reg, scope)) {
            int offset = this->symbolTable->GetVariableOffset(cfgName, reg, scope);
            ret = to_string(offset) + "(%rbp)";
        } else {
            ret = "$" + reg;
        }
    }

    return ret;
} //fin de IR_reg_to_asm_X86

string CFG::IR_reg_to_asm_ARM(string reg, string scope) {

    string ret;

    if (reg == "reg1") {
        ret = 'r3';
    } else if (reg == "reg2") {
        ret = 'r0';
    } else if (reg == "paramReg1") {
        ret = "r0";
    } else if (reg == "paramReg2") {
        ret = "r1";
    } else if (reg == "paramReg3") {
        ret = "r2";
    } else if (reg == "paramReg4") {
        ret = "r3";
    } else {
        if (this->symbolTable->LookUpVariable(cfgName, reg, scope)) {
            int offset = -(this->symbolTable->GetVariableOffset(cfgName, reg, scope));
            ret = "[r7, #" + to_string(offset) + "]";
        } else {
            ret = reg;
        }
    }

    return ret;
} //fin de IR_reg_to_asm_ARM

bool CFG::gen_asm_prologue_X86(ostream & o, BasicBlock * bb) {
    bool jump = true;
    vector<BasicBlock *>::iterator it2;
    for (it2 = this->bbs.begin() + 1; it2 != (this->bbs.end() - 1); it2++) {
        if ((*it2)->exit_true == bb->exit_true || (*it2)->exit_false == bb->exit_true) {
            jump = false;
            break;
        }
    }
    o << "        .globl " << cfgName << endl
      << endl;
    o << cfgName << ":" << endl;
    if (jump == false) {
        o << bb->label << ":" << endl;
    }

    o << "        pushq    %rbp" << endl;
    o << "        movq     %rsp, %rbp" << endl;

    int spaceNeeded = this->symbolTable->CalculateSpaceForFunction(cfgName);

    // Round space to the nearest multiple of 16
    if (spaceNeeded % 16) {
        spaceNeeded = ((spaceNeeded / 16) + 1) * 16;
    }

    o << "        subq     $" << to_string(spaceNeeded) << ", %rsp" << endl;

    if (jump == false) {
        o << "        jmp " << bb->exit_true->label << endl;
    }
    return jump;
} //fin de gen_asm_prologue

//TODO
bool CFG::gen_asm_prologue_ARM(ostream & o, BasicBlock * bb) {
    bool jump = true;
    vector<BasicBlock *>::iterator it2;
    for (it2 = this->bbs.begin() + 1; it2 != (this->bbs.end() - 1); it2++) {
        if ((*it2)->exit_true == bb->exit_true || (*it2)->exit_false == bb->exit_true) {
            jump = false;
            break;
        }
    }

    o << "        .global " << cfgName << endl
      << endl;
    o << cfgName << ":" << endl;
    if (jump == false) {
        o << bb->label << ":" << endl;
    }
    o << "        push    {r7, lr}" << endl; //si main : push    {r7, lr}

    int spaceNeeded = this->symbolTable->CalculateSpaceForFunction(cfgName);

    // Round space to the nearest multiple of 4
    if (spaceNeeded % 4) {
        spaceNeeded = ((spaceNeeded / 4) + 1) * 4;
    }
    o << "        sub     sp, sp, #" << spaceNeeded << endl;
    o << "        add     r7, sp, #0" << endl;
    if (jump == false) {
        o << "        bl " << bb->exit_true->label << endl;
    }
    return jump;
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
    if (spaceNeeded % 4) {
        spaceNeeded = ((spaceNeeded / 4) + 1) * 4;
    }

    o << bb->label << ":" << endl;
    o << "        mov     r0, r3" << endl;
    o << "        adds    r7, r7, #" << spaceNeeded << endl;
    o << "        mov     sp, r7" << endl;
    o << "        pop	{r7, pc}" << endl;
} //fin de gen_asm_epilogue_ARM

string CFG::new_BB_name(const string & prefix) {
    if (prefix.empty()) {
        return "." + this->cfgName + "BB" + to_string(this->nextBBnumber++);
    } else {
        return "." + prefix + "_" + this->cfgName;
    }
} //fin de new_BB_name

BasicBlock * CFG::GetCurrentBB() {
    return this->current_bb;
} //----- Fin de GetCurrentBB

SymbolTable * CFG::GetSymbolTable() {
    return this->symbolTable;
} //----- Fin de GetSymbolTable

string CFG::GetName() {
    return this->cfgName;
}

CFG::~CFG() {
    for (BasicBlock * bb : bbs) {
        delete (bb);
    }
}

void IR::GenerateAsmX86(ostream & o) {
    //gen_asm_prologue_global_X86(o);

    for (CFG * cfg : this->allCFG) {
        cfg->gen_asm_X86(o);
        o << endl;
    }
    //TODO? ajouter épilogue asm
} //----- Fin de GenerateAsmX86

void IR::GenerateAsmARM(ostream & o) {
    gen_asm_prologue_global_ARM(o);

    for (CFG * cfg : this->allCFG) {
        cfg->gen_asm_ARM(o);
        o << endl;
    }
} //----- Fin de GenerateAsmARM

void IR::AddCFG(CFG * newCFG) {
    this->allCFG.push_back(newCFG);
}

void IR::gen_asm_prologue_global_X86(ostream & o) {
    o << "        .globl main" << endl
      << endl;
} //----- Fin de gen_asm_prologue_global_X86

void IR::gen_asm_prologue_global_ARM(ostream & o) {
    o << ".global	main" << endl;
    o << ".syntax unified" << endl;
} //----- Fin de gen_asm_prologue_global_ARM

IR::~IR() {
    for (CFG * cfg : allCFG) {
        delete (cfg);
    }
}

//-------------------------------------------- Constructeurs - destructeur

IRInstr::IRInstr(BasicBlock * bb_, Operation op, Type t, vector<string> params)
    : bb(bb_), op(op), t(t), params(params) {

} //fin de constructeur de IRInst

BasicBlock::BasicBlock(CFG * cfg, string entry_label, string scope) {
    this->cfg = cfg;
    this->label = entry_label;
    this->scope = scope;
    this->exit_true = nullptr;
    this->exit_false = nullptr;
} //fin de constructeur de BasicBlock

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
