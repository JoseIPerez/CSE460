//
//  Assembler.hpp
//  CSE460Project
//
//  Created by Jose on 10/2/18.
//

#ifndef Assembler_hpp
#define Assembler_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

class Assembler{
    typedef int(Assembler::*FP)(istringstream &);
    map<string, FP>order;
public:
    //constructor
    Assembler();
    
    //assembles .s file into .o file
    int assemble(fstream&, fstream&);
    
    //instructions
    int load(istringstream &);
    int loadi(istringstream &);
    int store(istringstream &);
    int add(istringstream &);
    int addi(istringstream &);
    int addc(istringstream &);
    int addci(istringstream &);
    int sub(istringstream &);
    int subi(istringstream &);
    int subc(istringstream &);
    int subci(istringstream &);
    int _and(istringstream &);
    int _andi(istringstream &);
    int _xor(istringstream &);
    int _xori(istringstream &);
    int _compl(istringstream &);
    int shl(istringstream &);
    int shla(istringstream &);
    int shr(istringstream &);
    int shra(istringstream &);
    int compr(istringstream &);
    int compri(istringstream &);
    int getstat(istringstream &);
    int putstat(istringstream &);
    int jump(istringstream &);
    int jumpl(istringstream &);
    int jumpe(istringstream &);
    int jumpg(istringstream &);
    int call(istringstream &);
    int _return(istringstream &);
    int read(istringstream &);
    int write(istringstream &);
    int halt(istringstream &);
    int noop(istringstream &);
    
};

class NullPointer:public runtime_error{
public:
    NullPointerException(): runtime_error("Null Function Pointer!"){}
};
}

#endif /* Assembler_hpp */
