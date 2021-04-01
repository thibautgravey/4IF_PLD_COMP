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

void IRInstr::gen_asm(ostream & o) {

    string p1, p2, p3;
    // TODO : voir si on peut améliorer

    if (this->op != call) {
        switch (this->params.size()) {
            case 3:
                p3 = this->bb->cfg->IR_reg_to_asm(this->params[2]);
            case 2:
                p2 = this->bb->cfg->IR_reg_to_asm(this->params[1]);
            case 1:
                p1 = this->bb->cfg->IR_reg_to_asm(this->params[0]);
            default:
                break;
        }
    } else {
        p1 = this->bb->cfg->IR_reg_to_asm(this->params[0]);
        p2 = this->bb->cfg->IR_reg_to_asm(this->params[1]);
    }

    switch (this->op) {
        case ldconst:
            o << "        movl    $" << p2 << ", " << p1 << endl;
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
                p3 = this->bb->cfg->IR_reg_to_asm(this->params[i]);
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
            o << "        cmpl     " << p3  << ", %eax" << endl;
            o << "        sete     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_neq:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3  << ", %eax" << endl;
            o << "        setne    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_g:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3  << ", %eax" << endl;
            o << "        setg     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_ge:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3  << ", %eax" << endl;
            o << "        setge    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_l:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3  << ", %eax" << endl;
            o << "        setl     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_le:
            o << "        movl     " << p2 << ", %eax" << endl;
            o << "        cmpl     " << p3  << ", %eax" << endl;
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
} //fin de gen_asm(Ir_Instr)

void BasicBlock::gen_asm(ostream & o) {
} //fin de gen_asm(Basic_Block)

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
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

void CFG::gen_asm(ostream & o) {
    gen_asm_prologue(o, this->bbs[0]);

    vector<BasicBlock *>::iterator it;
    for (it = this->bbs.begin() + 1; it != (this->bbs.end() - 1); it++) {
        o << (*it)->label << ":" << endl;
        for (IRInstr * instr : (*it)->instrs) {
            instr->gen_asm(o);
        }
        if ((*it)->exit_false == nullptr) {
            o << "        jmp      " << (*it)->exit_true->label << endl;
        } else {
            o << "        cmpl     $1, " << (*it)->cfg->IR_reg_to_asm((*it)->test_var_name) << endl;
            o << "        jne      " << (*it)->exit_false->label << endl;
            o << "        jmp      " << (*it)->exit_true->label << endl;
        }
    }

    gen_asm_epilogue(o, this->bbs[this->bbs.size() - 1]);
} //fin de gen_asm(CFG)

string CFG::IR_reg_to_asm(string reg) {

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
        if (this->symbolTable->LookUpVariable(cfgName, reg)) {
            int offset = this->symbolTable->GetVariableOffset(cfgName, reg);
            ret = to_string(offset) + "(%rbp)";
        } else {
            ret = reg;
        }
    }

    return ret;
} //fin de IR_reg_to_asm

void CFG::gen_asm_prologue(ostream & o, BasicBlock * bb) {
    o << "        .globl " << cfgName << endl
      << endl;
    o << cfgName << ":" << endl;
    o << bb->label << ":" << endl;
    o << "        pushq    %rbp" << endl;
    o << "        movq     %rsp, %rbp" << endl;

    int spaceNeeded = this->symbolTable->CalculateSpaceForFunction(cfgName);

    // Round space to the nearest multiple of 16
    if (spaceNeeded % 16) {
        spaceNeeded = ((spaceNeeded / 16) + 1) * 16;
    }

    o << "        subq     $" << to_string(spaceNeeded) << ", %rsp" << endl;
    o << "        jmp " << bb->exit_true->label << endl;
} //fin de gen_asm_prologue

void CFG::gen_asm_epilogue(ostream & o, BasicBlock * bb) {
    o << bb->label << ":" << endl;
    o << "        leave" << endl;
    o << "        ret" << endl;
} //fin de gen_asm_epilogue

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
    //gen_asm_prologue_global(o);

    for (CFG * cfg : this->allCFG) {
        cfg->gen_asm(o);
        o << endl;
    }
    //TODO? ajouter épilogue bdsm
} //----- Fin de GenerateAsmX86

void IR::GenerateAsmARM(ostream & o) {
    gen_asm_prologue_global(o);

    for (CFG * cfg : this->allCFG) {
        cfg->gen_asm(o);
        o << endl;
    }
    //TODO? ajouter épilogue bdsm
} //----- Fin de GenerateAsmARM

void IR::AddCFG(CFG * newCFG) {
    this->allCFG.push_back(newCFG);
}

void IR::gen_asm_prologue_global(ostream & o) {
    o << "        .globl main" << endl
      << endl;
} //----- Fin de gen_asm_prologue_global

IR::~IR() {
    for (CFG * cfg : allCFG) {
        delete (cfg);
    }
}

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
