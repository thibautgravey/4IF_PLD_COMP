/*******************************************************************************
                           IR  -  description
                             -------------------
    copyright            : (C) 2021 par l'HexaOne
*******************************************************************************/

//------- Réalisation de la classe <IR> (fichier IR.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <stdint.h>

using namespace std;

//------------------------------------------------------ Include personnel
#include "IR.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void IRInstr::gen_asm_X86(ostream & o) {

    string p1, p2, p3;
    Type t;

    if (this->op == call) {
        p1 = this->params[0];
        p2 = this->bb->cfg->IR_reg_to_asm_X86(this->params[1], this->bb->scope, this->t);
    } else if (this->op == jmp) {
        p1 = this->params[0];
    } else {
        switch (this->params.size()) {
            case 3:
                p3 = this->bb->cfg->IR_reg_to_asm_X86(this->params[2], this->bb->scope, this->t);
            case 2:
                p2 = this->bb->cfg->IR_reg_to_asm_X86(this->params[1], this->bb->scope, this->t);
            case 1:
                p1 = this->bb->cfg->IR_reg_to_asm_X86(this->params[0], this->bb->scope, this->t);
            default:
                break;
        }
    }

    switch (this->op) {
        case ldconst:
            if (this->t == INT64_T) {
                o << "        movabsq    " << p2 << ", %rax" << endl;
                o << "        movq       %rax, " << p1 << endl;
            } else {
                o << "        " << getMovInstr() << "       " << p2 << ", " << p1 << endl;
            }
            break;
        case copy:
            t = this->t;
            if (p2.at(0) == '%') {
                t = findRegType(p2);
            }
            o << "        " << getMovInstr(t) << "       " << p2 << ", " << getReg1(t) << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case add:
            if (p2 == "%rbp") {
                o << "        movq       " << p2 << ", %rax" << endl;
            } else {
                o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            }
            o << "        " << getAddInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case sub:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getSubInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case mul:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << p3 << ", " << getTmpReg() << endl;
            o << "        " << getMullInstr() << "      " << getTmpReg() << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case div:
            if (p3[0] == '$') {
                o << "        " << getMovInstr() << "       " << p3 << ", " << getTmpReg() << endl;
                p3 = getTmpReg();
            }
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        cltd" << endl;
            o << "        " << getDivInstr() << "       " << p3 << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case orB:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getOrInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case andB:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getAndInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case xorB:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getXorInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case neg:
            o << "        " << getCmpInstr() << "       $0, " << p2 << endl;
            o << "        sete       %al" << endl;
            o << "        movzbl    %al, %eax" << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case opp:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getNegInstr() << "       " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << getReg1() << ", " << p1 << endl;
            break;
        case rmem:
            o << "        movq     " << p2 << ", %rax" << endl;
            o << "        movq     (%rax), %r10" << endl;
            o << "        movq     %r10, " << p1 << endl;
            break;
        case wmem:
            o << "        " << getMovInstr() << "       " << p1 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "       " << p2 << ", " << getTmpReg() << endl;
            o << "        " << getMovInstr() << "       " << getTmpReg() << ", (" << getReg1() << ")" << endl;
            break;
        case call: {
            for (int i = 2; i < params.size(); i++) {
                p3 = this->bb->cfg->IR_reg_to_asm_X86(this->params[i], this->bb->scope, this->t);
                Type paramType;
                if (this->bb->cfg->GetSymbolTable()->LookUpFunction(p1)) {
                    // fonction interne --> Type des paramètres de la fonction appelé
                    paramType = this->bb->cfg->GetSymbolTable()->GetFunctionParams(p1)[i - 2]->type;
                } else {
                    // fonction externe --> Type des paramètres dans l'appelant
                    if (this->bb->cfg->GetSymbolTable()->LookUpVariable(this->bb->cfg->GetName(), this->params[i], this->bb->scope)) {
                        // passage de paramètre via une variable
                        paramType = this->bb->cfg->GetSymbolTable()->GetVariableType(this->bb->cfg->GetName(), this->params[i], this->bb->scope);
                    } else {
                        // passage direct de valeur
                        int64_t value;
                        istringstream tmpSS(this->params[i]);
                        tmpSS >> value;
                        if (value > INT32_MAX) {
                            paramType = INT64_T;
                        } else {
                            paramType = INT32_T;
                        }
                    }
                }

                if (paramType == CHAR) {
                    paramType = INT32_T;
                }

                string dest;
                switch (i - 2) {
                    case 0:
                        if (paramType == INT64_T)
                            dest = "%rdi";
                        else
                            dest = "%edi";
                        break;
                    case 1:
                        if (paramType == INT64_T)
                            dest = "%rsi";
                        else
                            dest = "%esi";
                        break;
                    case 2:
                        if (paramType == INT64_T)
                            dest = "%rdx";
                        else
                            dest = "%edx";
                        break;
                    case 3:
                        if (paramType == INT64_T)
                            dest = "%rcx";
                        else
                            dest = "%ecx";
                        break;
                    case 4:
                        if (paramType == INT64_T)
                            dest = "%r8";
                        else
                            dest = "%r8d";
                        break;
                    case 5:
                        if (paramType == INT64_T)
                            dest = "%r9";
                        else
                            dest = "%r9d";
                        break;
                }
                o << "        " << getMovInstr(paramType) << "       " << p3 << ", " << dest << endl;
            }
            o << "        call       " << p1 << endl;
            break;
        }
        case cmp_eq:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        sete       %al" << endl;
            o << "        movzbq    %al, %rax" << endl;
            o << "        movq       %rax, " << p1 << endl;
            break;
        case cmp_neq:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        setne      %al" << endl;
            o << "        movzbq     %al, %rax" << endl;
            o << "        movq       %rax, " << p1 << endl;
            break;
        case cmp_g:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        setg       %al" << endl;
            o << "        movzbq     %al, %rax" << endl;
            o << "        movq       %rax, " << p1 << endl;
            break;
        case cmp_ge:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        setge      %al" << endl;
            o << "        movzbq     %al, %rax" << endl;
            o << "        movq       %rax, " << p1 << endl;
            break;
        case cmp_l:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        setl       %al" << endl;
            o << "        movzbq     %al, %rax" << endl;
            o << "        movq       %rax, " << p1 << endl;
            break;
        case cmp_le:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "       " << p3 << ", " << getReg1() << endl;
            o << "        setle      %al" << endl;
            o << "        movzbq     %al, %rax" << endl;
            o << "        movq       %rax, " << p1 << endl;
            break;

        case cdtAnd:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        and        " << p3 << ", " << getReg1() << endl;
            o << "        movl       %eax, " << p1 << endl;
            break;
        case cdtOr:
            o << "        " << getMovInstr() << "       " << p2 << ", " << getReg1() << endl;
            o << "        or         " << p3 << ", " << getReg1() << endl;
            o << "        movl       %eax, " << p1 << endl;
            break;
        case ret:
            o << "        " << getMovInstr() << "       " << p1 << ", " << getReg1() << endl;
            o << "        jmp        " << bb->cfg->bb_epilogue->label << endl;
            break;
        case jmp:
            o << "        jmp        " << p1 << endl;

        default:
            break;
    }
} //fin de gen_asm_X86(Ir_Instr)
bool IRInstr::param_is_number(string p) {
    for (int i = 0; i < p.size(); i++) {
        if (!(isdigit(p[i]) || p[i] == '-'))
            return false;
    }
    return true;
}

string IRInstr::fake_gen_asm_X86() {
    if (this->op == jmp) {
        return this->params[0];
    }
    return "";
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
            o << "        movs    r3, #" << p2 << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case copy:
            if (param_is_number(p2)) {
                o << "        movs    r3, #" << p2 << endl;
                o << "        str     r3, " << p1 << endl;
            } else {
                o << "        ldr     r3, " << p2 << endl;
                o << "        str     r3, " << p1 << endl;
            }
            break;
        case add:
            if (p2 == "base_pointer") {
                if (param_is_number(p3)) {
                    o << "        movs    r3, #" << p3 << endl;
                } else {
                    o << "        ldr     r3, " << p3 << endl;
                    //Invert sign bc of x86 negativ offset
                    o << "        neg     r3, r3" << endl;
                }
                o << "        add     r3, r7, r3" << endl;
                o << "        str     r3, " << p1 << endl;

            } else {
                if (param_is_number(p2)) {
                    o << "        movs    r2, #" << p2 << endl;
                } else {
                    o << "        ldr     r2, " << p2 << endl;
                }
                if (param_is_number(p3)) {
                    o << "        movs    r3, #" << p3 << endl;
                } else {
                    o << "        ldr     r3, " << p3 << endl;
                }
                o << "        add     r3, r2, r3" << endl;
                o << "        str     r3, " << p1 << endl;
            }
            break;
        case sub:
            if (param_is_number(p2)) {
                o << "        movs    r2, #" << p2 << endl;
            } else {
                o << "        ldr     r2, " << p2 << endl;
            }
            if (param_is_number(p3)) {
                o << "        movs    r3, #" << p3 << endl;
            } else {
                o << "        ldr     r3, " << p3 << endl;
            }
            o << "        subs    r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case mul:
            if (param_is_number(p2)) {
                o << "        movs    r2, #" << p2 << endl;
            } else {
                o << "        ldr     r2, " << p2 << endl;
            }
            if (param_is_number(p3)) {
                o << "        movs    r3, #" << p3 << endl;
            } else {
                o << "        ldr     r3, " << p3 << endl;
            }
            o << "        mul     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case div:
            if (param_is_number(p2)) {
                o << "        movs    r0, #" << p2 << endl;
            } else {
                o << "        ldr     r0, " << p2 << endl;
            }
            if (param_is_number(p3)) {
                o << "        movs    r1, #" << p3 << endl;
            } else {
                o << "        ldr     r1, " << p3 << endl;
            }
            o << "        bl      __aeabi_idiv(PLT)" << endl;
            o << "        mov     r3, r0" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case orB:
            if (param_is_number(p2)) {
                o << "        movs    r2, #" << p2 << endl;
            } else {
                o << "        ldr     r2, " << p2 << endl;
            }
            if (param_is_number(p3)) {
                o << "        movs    r3, #" << p3 << endl;
            } else {
                o << "        ldr     r3, " << p3 << endl;
            }
            o << "        orrs    r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case andB:
            if (param_is_number(p2)) {
                o << "        movs    r2, #" << p2 << endl;
            } else {
                o << "        ldr     r2, " << p2 << endl;
            }
            if (param_is_number(p3)) {
                o << "        movs    r3, #" << p3 << endl;
            } else {
                o << "        ldr     r3, " << p3 << endl;
            }
            o << "        ands     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case xorB:
            if (param_is_number(p2)) {
                o << "        movs    r2, #" << p2 << endl;
            } else {
                o << "        ldr     r2, " << p2 << endl;
            }
            if (param_is_number(p3)) {
                o << "        movs    r3, #" << p3 << endl;
            } else {
                o << "        ldr     r3, " << p3 << endl;
            }
            o << "        eors     r3, r2, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case neg:
            if (param_is_number(p2)) {
                o << "        movs    r3, #" << p2 << endl;
            } else {
                o << "        ldr     r3, " << p2 << endl;
            }
            o << "        cmp     r3, #0" << endl;
            o << "        ite     eq" << endl;
            o << "        moveq   r3, #1" << endl;
            o << "        movne   r3, #0" << endl;
            o << "        uxtb    r3, r3" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case opp:
            if (param_is_number(p2)) {
                o << "        movs    r3, #" << p2 << endl;
            } else {
                o << "        ldr     r3, " << p2 << endl;
            }
            o << "        rsbs     r3, r3, #0" << endl;
            o << "        str     r3, " << p1 << endl;
            break;
        case rmem:
            o << "        rmem" << endl;
            break;
        case wmem:
            if (param_is_number(p2)) {
                o << "        movs     r3, #" << p2 << endl;
                o << "        ldr     r2, " << p1 << endl;
                o << "        str     r3, [r2]" << endl;
            } else {
                o << "        ldr     r3, " << p2 << endl;
                o << "        ldr     r2, " << p1 << endl;
                o << "        str     r3, [r2]" << endl;
            }
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
                if (param_is_number(p3)) {
                    o << "        movs    " << dest << ", #" << p3 << endl;
                } else {
                    o << "        ldr     " << dest << ", " << p3 << endl;
                }
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
            if (param_is_number(p1)) {
                o << "        movs    r3, #" << p1 << endl;
            } else {
                o << "        ldr     r3, " << p1 << endl;
            }
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
    /*
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
                o << "        jmp        " << (*it)->exit_true->label << endl;

            } else {
                delete_jump = true;
            }

        } else {
            Type type = (*it)->cfg->GetSymbolTable()->GetVariableType((*it)->cfg->GetName(), (*it)->test_var_name, (*it)->scope);
            o << "        cmpq       $0, " << (*it)->cfg->IR_reg_to_asm_X86((*it)->test_var_name, (*it)->scope, type) << endl;
            o << "        jne        " << (*it)->exit_true->label << endl;

            if ((*(it + 1))->label != (*it)->exit_false->label || use_block_label) {
                o << "        jmp        " << (*it)->exit_false->label << endl;
            } else {
                delete_jump = true;
            }
        }
    }
    */

    unordered_set<string> labelsToKeep;
    for (it = this->bbs.begin() + 1; it != (this->bbs.end() - 1); it++) {
        for (IRInstr * instr : (*it)->instrs) {
            string label = instr->fake_gen_asm_X86();
            if (label != "") {
                labelsToKeep.insert(label);
            }
        }
    }

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

        if (labelsToKeep.find((*it)->exit_true->label) != labelsToKeep.end()) {
            use_block_label = true;
        } else {
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
        }

        if ((*it)->exit_false == nullptr) {

            if ((*(it + 1))->label != (*it)->exit_true->label || use_block_label) {
                o << "        jmp        " << (*it)->exit_true->label << endl;

            } else {
                delete_jump = true;
            }

        } else {
            Type type = (*it)->cfg->GetSymbolTable()->GetVariableType((*it)->cfg->GetName(), (*it)->test_var_name, (*it)->scope);
            string cmpInstr;
            switch (type) {
                case CHAR:
                    cmpInstr = "cmpb";
                    break;
                case INT32_T:
                    cmpInstr = "cmpl";
                    break;
                case INT64_T:
                    cmpInstr = "cmpq";
                    break;
                default:
                    cmpInstr = "UndefinedTypeCmp";
                    break;
            }
            o << "        " << cmpInstr << "       $0, " << (*it)->cfg->IR_reg_to_asm_X86((*it)->test_var_name, (*it)->scope, type) << endl;
            o << "        jne        " << (*it)->exit_true->label << endl;

            if ((*(it + 1))->label != (*it)->exit_false->label || use_block_label) {
                o << "        jmp        " << (*it)->exit_false->label << endl;
            } else {
                delete_jump = true;
            }
        }
    }

    gen_asm_epilogue_X86(o, this->bbs[this->bbs.size() - 1]);
} //fin de gen_asm_x86(CFG)

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

string CFG::IR_reg_to_asm_X86(string reg, string scope, Type type) {

    string ret;

    if (reg == "reg1") {
        if (type == Type::INT64_T)
            ret = "%rax";
        else
            ret = "%eax";
    } else if (reg == "reg2") {
        if (type == Type::INT64_T)
            ret = "%rbx";
        else
            ret = "%ebx";
    } else if (reg == "paramReg1") {
        if (type == Type::INT64_T)
            ret = "%rdi";
        else
            ret = "%edi";
    } else if (reg == "paramReg2") {
        if (type == Type::INT64_T)
            ret = "%rsi";
        else
            ret = "%esi";
    } else if (reg == "paramReg3") {
        if (type == Type::INT64_T)
            ret = "%rdx";
        else
            ret = "%edx";
    } else if (reg == "paramReg4") {
        if (type == Type::INT64_T)
            ret = "%rcx";
        else
            ret = "%ecx";
    } else if (reg == "paramReg5") {
        if (type == Type::INT64_T)
            ret = "%r8";
        else
            ret = "%r8d";
    } else if (reg == "paramReg6") {
        if (type == Type::INT64_T)
            ret = "%r9";
        else
            ret = "%r9d";
    } else if (reg == "base_pointer") {
        ret = "%rbp";
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
        ret = "r3";
    } else if (reg == "reg2") {
        ret = "r0";
    } else if (reg == "paramReg1") {
        ret = "r0";
    } else if (reg == "paramReg2") {
        ret = "r1";
    } else if (reg == "paramReg3") {
        ret = "r2";
    } else if (reg == "paramReg4") {
        ret = "r3";
    } else if (reg == "base_pointer") {
        ret = "base_pointer";
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

    o << "        pushq      %rbp" << endl;
    o << "        movq       %rsp, %rbp" << endl;

    int spaceNeeded = this->symbolTable->CalculateSpaceForFunction(cfgName);

    // Round space to the nearest multiple of 16
    if (spaceNeeded % 16) {
        spaceNeeded = ((spaceNeeded / 16) + 1) * 16;
    }

    o << "        subq       $" << to_string(spaceNeeded) << ", %rsp" << endl;

    if (jump == false) {
        o << "        jmp        " << bb->exit_true->label << endl;
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

string CFG::GetCurrentLoopEntryLabel() {
    return this->currentLoopEntryLabels.back();
} //----- Fin de GetCurrentLoopEntryLabel

void CFG::AddCurrentLoopEntryLabel(string label) {
    this->currentLoopEntryLabels.push_back(label);
} //----- Fin de AddCurrentLoopEntryLabel

void CFG::RemoveLastCurrentLoopEntryLabel() {
    this->currentLoopEntryLabels.pop_back();
} //----- Fin de RemoveLastCurrentLoopEntryLabel

string CFG::GetCurrentLoopEndLabel() {
    return this->currentLoopEndLabels.back();
} //----- Fin de GetCurrentLoopEndLabel

void CFG::AddCurrentLoopEndLabel(string label) {
    this->currentLoopEndLabels.push_back(label);
} //----- Fin de AddCurrentLoopEndLabel

void CFG::RemoveLastCurrentLoopEndLabel() {
    this->currentLoopEndLabels.pop_back();
} //----- Fin de RemoveLastCurrentLoopEndLabel

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
    // o << ".global	main" << endl;
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
string IRInstr::getMovInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "movl";
            break;
        case Type::INT64_T:
            instr = "movq";
            break;
        case Type::CHAR:
            instr = "movb";
            break;
        default:
            instr = "UndefinedTypeForInstrMov";
            break;
    }
    return instr;
} //--------- Fin de getMovInstr

string IRInstr::getMovInstr(Type requestType) {
    string instr;
    switch (requestType) {
        case Type::INT32_T:
            instr = "movl";
            break;
        case Type::INT64_T:
            instr = "movq";
            break;
        case Type::CHAR:
            instr = "movb";
            break;
        default:
            instr = "UndefinedTypeForInstrMov";
            break;
    }
    return instr;
} //--------- Fin de getMovInstr

string IRInstr::getAddInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "addl";
            break;
        case Type::INT64_T:
            instr = "addq";
            break;
        case Type::CHAR:
            instr = "addb";
            break;
        default:
            instr = "UndefinedTypeForInstrAdd";
            break;
    }
    return instr;
} //--------- Fin de getAddInstr

string IRInstr::getSubInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "subl";
            break;
        case Type::INT64_T:
            instr = "subq";
            break;
        case Type::CHAR:
            instr = "subb";
            break;
        default:
            instr = "UndefinedTypeForInstrSub";
            break;
    }
    return instr;
} //--------- Fin de getSubInstr

string IRInstr::getCmpInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "cmpl";
            break;
        case Type::INT64_T:
            instr = "cmpq";
            break;
        case Type::CHAR:
            instr = "cmpb";
            break;
        default:
            instr = "UndefinedTypeForInstrCmp";
            break;
    }
    return instr;
} //--------- Fin de getCmpInstr

string IRInstr::getMullInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "imull";
            break;
        case Type::INT64_T:
            instr = "imulq";
            break;
        case Type::CHAR:
            instr = "imulb";
            break;
        default:
            instr = "UndefinedTypeForInstrMull";
            break;
    }
    return instr;
} //--------- Fin de getMullInstr

string IRInstr::getDivInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "idivl";
            break;
        case Type::INT64_T:
            instr = "idivq";
            break;
        case Type::CHAR:
            instr = "idivb";
            break;
        default:
            instr = "UndefinedTypeForInstrDiv";
            break;
    }
    return instr;
} //--------- Fin de getDivInstr

string IRInstr::getOrInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "orl";
            break;
        case Type::INT64_T:
            instr = "orq";
            break;
        case Type::CHAR:
            instr = "orb";
            break;
        default:
            instr = "UndefinedTypeForInstrOr";
            break;
    }
    return instr;
} //--------- Fin de getOrInstr

string IRInstr::getAndInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "andl";
            break;
        case Type::INT64_T:
            instr = "andb";
            break;
        case Type::CHAR:
            instr = "andq";
            break;
        default:
            instr = "UndefinedTypeForInstrAnd";
            break;
    }
    return instr;
} //--------- Fin de getAndInstr

string IRInstr::getXorInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "xorl";
            break;
        case Type::INT64_T:
            instr = "xorq";
            break;
        case Type::CHAR:
            instr = "xorb";
            break;
        default:
            instr = "UndefinedTypeForInstrXor";
            break;
    }
    return instr;
} //--------- Fin de getXorInstr

string IRInstr::getNegInstr() {
    string instr;
    switch (this->t) {
        case Type::INT32_T:
            instr = "negl";
            break;
        case Type::INT64_T:
            instr = "negq";
            break;
        case Type::CHAR:
            instr = "negb";
            break;
        default:
            instr = "UndefinedTypeForInstrNeg";
            break;
    }
    return instr;
} //--------- Fin de getNegInstr

string IRInstr::getReg1() {
    string reg;
    switch (this->t) {
        case Type::INT32_T:
            reg = "%eax";
            break;
        case Type::INT64_T:
            reg = "%rax";
            break;
        case Type::CHAR:
            reg = "%al";
            break;
        default:
            reg = "UndefinedTypeForReg1";
            break;
    }
    return reg;
} //--------- Fin de getReg1

string IRInstr::getReg1(Type requestType) {
    string reg;
    switch (requestType) {
        case Type::INT32_T:
            reg = "%eax";
            break;
        case Type::INT64_T:
            reg = "%rax";
            break;
        case Type::CHAR:
            reg = "%al";
            break;
        default:
            reg = "UndefinedTypeForReg1";
            break;
    }
    return reg;
} //--------- Fin de getReg1

string IRInstr::getTmpReg() {
    string reg;
    switch (this->t) {
        case Type::INT32_T:
            reg = "%r10d";
            break;
        case Type::INT64_T:
            reg = "%r10";
            break;
        case Type::CHAR:
            reg = "%r10b";
            break;
        default:
            reg = "UndefinedTypeForTmpReg";
            break;
    }
    return reg;
} //--------- Fin de getTmpReg

Type IRInstr::findRegType(string reg) {
    if (reg.at(1) == 'r') {
        if (reg.at(2) == '8' || reg.at(2) == '9') {
            if (reg.size() == 3) {
                return INT64_T;
            } else {
                return INT32_T;
            }
        } else {
            return INT64_T;
        }
    } else if (reg.at(1) == 'e') {
        return INT32_T;
    } else {
        return CHAR;
    }
} //--------- Fin de findRegType