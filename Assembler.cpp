#include "Assembler.h"


Assembler::Assembler(){
    order["load"] = &Assembler::load;
    order["loadi"] = &Assembler::loadi;
    order["store"] = &Assembler::store;
    order["add"] = &Assembler::add;
    order["addi"] = &Assembler::addi;
    order["addc"] = &Assembler::addc;
    order["addci"] = &Assembler::addci;
    order["sub"] = &Assembler::sub;
    order["subi"] = &Assembler::subi;
    order["subc"] = &Assembler::subc;
    order["subci"] = &Assembler::subci;
    order["_and"] = &Assembler::_and;
    order["_andi"] = &Assembler::_andi;
    order["_xor"] = &Assembler::_xor;
    order["_xori"] = &Assembler::_xori;
    order["_compl"] = &Assembler::_compl;
    order["shl"] = &Assembler::shl;
    order["shla"] = &Assembler::shla;
    order["shr"] = &Assembler::shr;
    order["shra"] = &Assembler::shra;
    order["compr"] = &Assembler::compr;
    order["compri"] = &Assembler::compri;
    order["getstat"] = &Assembler::getstat;
    order["putstat"] = &Assembler::putstat;
    order["jump"] = &Assembler::jump;
    order["jumpl"] = &Assembler::jumpl;
    order["jumpe"] = &Assembler::jumpe;
    order["jumpg"] = &Assembler::jumpg;
    order["call"] = &Assembler::call;
    order["_return"] = &Assembler::_return;
    order["read"] = &Assembler::read;
    order["write"] = &Assembler::write;
    order["halt"] = &Assembler::halt;
    order["noop"] = &Assembler::noop;
}

int Assembler::assemble(fstream& in, fstream& out){
	string line;
	string opcode;
	const int success = false;
	const int error = true;

	int instruction;

	getline(in, line);
	while(!in.eof()){
		istringstream str(line.c_str());
		str >> opcode;
		if (opcode[0] == '!'){
			getline(in, line);
			continue;
		}

		try {
			if (!order[opcode]){
				throw NullPointerException();
			}
			else{
				instruction = (this->*order[opcode])(str);
			}
		} catch (NullPointerException e){
			cerr << e.what() << endl;
			return error;
		}

		if (instruction == -1){
			return error;
		}

		out << instruction << endl;
        getline(in, line);
	}
	return success;
}

//instructions
int Assembler::load(istringstream & str){
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
int Assembler::loadi(istringstream & str){
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

int Assembler::store(istringstream & str){
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

int Assembler::add(istringstream & str){
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

int Assembler::addi(istringstream & str){
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

int Assembler::addc(istringstream & str){
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
int Assembler::addci(istringstream & str){
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
int Assembler::sub(istringstream & str){
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
int Assembler::subi(istringstream & str){
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

int Assembler::subc(istringstream & str){
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
int Assembler::subci(istringstream & str){
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

int Assembler::_and(istringstream & str){
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

int Assembler::_andi(istringstream & str){
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

int Assembler::_xor(istringstream & str){
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

int Assembler::_xori(istringstream & str){
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
    return inst;
}

int Assembler::_compl(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 8;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shl(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 9;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shla(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 10;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shr(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 11;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shra(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 12;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::compr(istringstream & str){
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

int Assembler::compri(istringstream & str){
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

int Assembler::getstat(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 14;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::putstat(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 15;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::jump(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 16;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::jumpl(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 17;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}
int Assembler::jumpe(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 18;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}
int Assembler::jumpg(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 19;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::call(istringstream & str){
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255){
        return -1;
    }
    int inst = 20;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::_return(istringstream & str){
    int inst = 21;
    inst = inst << 11;
    return inst;
}

int Assembler::read(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 22;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::write(istringstream & str){
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3){
        return -1;
    }
    int inst = 23;
    inst = inst << 11 | rd << 9;
    return inst;
}
int Assembler::halt(istringstream & str){
    int inst = 24;
    inst = inst << 11;
    return inst;
}

int Assembler::noop(istringstream & str){
    int inst = 25;
    inst = inst << 11;
    return inst;
}
