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

void IRInstr::gen_asm(ostream & o) {

    string p1, p2, p3;
    // TODO : voir si on peut améliorer

    if (this->op != call) {
        switch (this->params.size()) {
            case 3:
                p3 = this->bb->cfg->IR_reg_to_asm(this->params[2], this->bb->scope, this->t);
            case 2:
                p2 = this->bb->cfg->IR_reg_to_asm(this->params[1], this->bb->scope, this->t);
            case 1:
                p1 = this->bb->cfg->IR_reg_to_asm(this->params[0], this->bb->scope, this->t);
            default:
                break;
        }
    } else {
        p1 = this->params[0];
        p2 = this->bb->cfg->IR_reg_to_asm(this->params[1], this->bb->scope, this->t);
    }

    switch (this->op) {
        case ldconst:
            if (this->t == INT64_T) {
                o << "        movabsq     " << p2 << ", %rax" << endl;
                o << "        movq     %rax, " << p1 << endl;
            } else {
                o << "        " << getMovInstr() << "     " << p2 << ", " << p1 << endl;
            }
            break;
        case copy:
            if ((p2.at(0) == '%' && p1.at(0) != '%') || (p2.at(0) != '%' && p1.at(0) == '%')) {
                o << "        " << getMovInstr() << "     " << p2 << ", " << p1 << endl;
            } else {
                o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
                o << "        " << getMovInstr() << "    " << getReg1() << ", " << p1 << endl;
            }
            break;
        case add:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getAddInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "    " << getReg1() << ", " << p1 << endl;
            break;
        case sub:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getSubInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case mul:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getMullInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case div:
            if (p3[0] == '$') {
                o << "        " << getMovInstr() << "     " << p3 << ", " << getTmpReg() << endl;
                p3 = getTmpReg();
            }
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        cltd     " << endl;
            o << "        " << getDivInstr() << "    " << p3 << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case orB:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getOrInstr() << "      " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case andB:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getAndInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case xorB:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getXorInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case neg:
            o << "        " << getCmpInstr() << "     $0, " << p2 << endl;
            o << "        sete     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case opp:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getNegInstr() << "     " << getReg1() << endl;
            o << "        " << getMovInstr() << "     " << getReg1() << ", " << p1 << endl;
            break;
        case rmem:
            o << "        " << getMovInstr() << "     " << p2 << ", " << p1 << endl;
            break;
        case wmem:
            o << "        " << getMovInstr() << "     " << p2 << ", " << p1 << endl;
            break;
        case call: {
            for (int i = 2; i < params.size(); i++) {
                p3 = this->bb->cfg->IR_reg_to_asm(this->params[i], this->bb->scope, this->t);
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
                o << "        " << getMovInstr(paramType) << "    " << p3 << ", " << dest << endl;
            }
            o << "        call    " << p1 << endl;
            break;
        }
        case cmp_eq:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        sete     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_neq:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        setne    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_g:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        setg     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_ge:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        setge    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_l:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        setl     %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cmp_le:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        " << getCmpInstr() << "     " << p3 << ", " << getReg1() << endl;
            o << "        setle    %al" << endl;
            o << "        movzbl   %al, %eax" << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;

        case cdtAnd:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        and      " << p3 << ", " << getReg1() << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case cdtOr:
            o << "        " << getMovInstr() << "     " << p2 << ", " << getReg1() << endl;
            o << "        or       " << p3 << ", " << getReg1() << endl;
            o << "        movl     %eax, " << p1 << endl;
            break;
        case ret:
            o << "        " << getMovInstr() << "     " << p1 << ", " << getReg1() << endl;
            o << "        jmp      " << bb->cfg->bb_epilogue->label << endl;
            break;

        default:
            break;
    }
} //fin de gen_asm(Ir_Instr)

void BasicBlock::gen_asm(ostream & o) {
} //fin de gen_asm(Basic_Block)

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

void CFG::gen_asm(ostream & o) {
    bool delete_jump = gen_asm_prologue(o, this->bbs[0]);

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
            instr->gen_asm(o);
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
            Type type = (*it)->cfg->GetSymbolTable()->GetVariableType((*it)->cfg->GetName(), (*it)->test_var_name, (*it)->scope);
            o << "        cmpl     $1, " << (*it)->cfg->IR_reg_to_asm((*it)->test_var_name, (*it)->scope, type) << endl;
            o << "        jne      " << (*it)->exit_false->label << endl;

            if ((*(it + 1))->label != (*it)->exit_true->label || use_block_label) {
                o << "        jmp      " << (*it)->exit_true->label << endl;
            } else {
                delete_jump = true;
            }
        }
    }

    gen_asm_epilogue(o, this->bbs[this->bbs.size() - 1]);
} //fin de gen_asm(CFG)

string CFG::IR_reg_to_asm(string reg, string scope, Type type) {

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
    } else {
        if (this->symbolTable->LookUpVariable(cfgName, reg, scope)) {
            int offset = this->symbolTable->GetVariableOffset(cfgName, reg, scope);
            ret = to_string(offset) + "(%rbp)";
        } else {
            ret = "$" + reg;
        }
    }

    return ret;
} //fin de IR_reg_to_asm

bool CFG::gen_asm_prologue(ostream & o, BasicBlock * bb) {
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

string IRInstr::getTmpReg() {
    string reg;
    switch (this->t) {
        case Type::INT32_T:
            reg = "%ecx";
            break;
        case Type::INT64_T:
            reg = "%rcx";
            break;
        case Type::CHAR:
            reg = "%cl";
            break;
        default:
            reg = "UndefinedTypeForTmpReg";
            break;
    }
    return reg;
} //--------- Fin de getTmpReg