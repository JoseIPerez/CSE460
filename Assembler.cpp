//
//  Assembler.cpp
//  CSE460Project
//
//  Created by Familia on 10/2/18.
//

#include "Assembler.hpp"
Assembler::Assembler(){
    order["load"] = &Assembler::load;
    order["loadi"] = &Assembler::loadi;
    order["store"] = &Assembler::store;
    order["add"] = &Assembler::add;
    ....
}
//assembles .s file into .o file
int assemble(fstream& in, fstream& out){
    string buffer;
    string opcode;
    
    const int success = false;
    const int error = true;
    
    int instruction;
    
    getline(in, buffer);
    while(!in.eof()){
        istringstream str(buffer.c_str());
        str >> opcode;
        if (opcode[0] == '!'){
            getline(in, buffer);
            continue;
        }
        
        try{
            if (!order[opcode]){
                throw NullPointerException();
            }
            else{
                instruction = (this->*order[opcode])(str);
            }
        }
        
        catch (NullpointerException n){
            //cerr: standard output for errors
            //.what(): returns a null terminated character sequence
            cerr << n.what() << endl;
            return error;
        }
        
        if (instruction == -1){
            return error;
        }
        
        cout << instruction << endl;
        getline(in, buffer);
    }
    return success;
}

//instructions
int load(istringstream & str){
    int rd, addr;
    str >> rd >> addr;
    
    //only 4 registers
    if (rd < 0 || rd > 3){
        return -1;
    }
    //only 256 memory
    if (addr < 0 || addr > 255){
        return -1;
    }
    
    int inst = 0;
    inst = inst << 11 | rd << 9 | addr;
    return inst;
}
int loadi(istringstream & str){
    int rd, constant;
    str >> rd >> constant;
    
    //only 4 registers
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 0;
    //1 << 8 stands for i
    //0x000000ff = 0000 0000 0000 0000 0000 0000 1111 1111
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int store(istringstream & str){
    int addr, rd;
    str >> addr >> rd;
    if (addr < 0 || addr > 255){
        return -1;
    }
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 1;
    inst = inst << 11 | rd << 9 | addr;
    return inst;
}

int add(istringstream & str){
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (rs < 0 || rs > 3){
        return -1;
    }
    int inst = 2;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int addi(istringstream & str){
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 2;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int addc(istringstream & str){
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (rs < 0 || rs > 3){
        return -1;
    }
    int inst = 3;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int addci(istringstream & str){
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    
    int inst = 3;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int sub(istringstream & str){
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 0){
        return -1;
    }
    if (rs < 0 || rs > 3){
        return -1;
    }
    int inst = 4;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int subi(istringstream & str){
    int rd , constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 4;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int subc(istringstream & str){
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (rs < 0 || rs > 3){
        return -1;
    }
    int inst = 5;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int subci(istringstream & str){
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 5;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int _and(istringstream & str){
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (rs < 0 || rs > 3){
        return -1;
    }
    int inst = 6;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int _andi(istringstream & str){
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 6;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int _xor(istringstream & str){
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (rs < 0 || rs > 3){
        return -1;
    }
    int inst = 7;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int _xori(istringstream & str){
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 7;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return -1;
}

int _compl(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 8;
    inst = inst << 11 | rd << 9;
    return inst;
}

int shl(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 9;
    inst = inst << 11 | rd << 9;
    return inst;
}

int shla(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 10;
    inst = inst << 11 | rd << 9;
    return inst;
}

int shr(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 11;
    inst = inst << 11 | rd << 9;
    return inst;
}

int shra(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 12;
    inst = inst << 11 | rd << 9;
    return inst;
}

int compr(istringstream & str){
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (rs < 0 || rs > 3){
        return -1;
    }
    int inst = 13;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int compri(istringstream & str){
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 13;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int getstat(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 14;
    inst = inst << 11 | rd << 9;
    return inst;
}

int putstat(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 15;
    inst = inst << 11 | rd << 9;
    return inst;
}

int jump(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 16;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int jumpl(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 17;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}
int jumpe(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 18;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}
int jumpg(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 19;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int call(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 20;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int _return(istringstream & str){
    int inst = 21;
    inst = inst << 11;
    return inst;
}

int read(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 22;
    inst = inst << 11 | rd << 9;
    return inst;
}

int write(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 23;
    inst = inst << 11 | rd << 9;
    return inst;
}
int halt(istringstream & str){
    int inst = 24;
    inst = inst << 11;
    return inst;
}

int noop(istringstream & str){
    int inst = 25;
    inst = inst << 11;
    return inst;
}
