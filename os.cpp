#include "Assembler.h"
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
    Assembler as;
    
    if (argc == 1){
        cout << "Must Suppy An Input File Name. \n";
        exit(1);
    }
    
    string inputFile = argv[1];
    int pos = inputFile.find(".");
    if (pos > inputFile.length() || inputFile[pos + 1] != 's') {
        cout << "No .s Suffix. \n";
        exit(2);
    }
    
    string name = inputFile.substr(0, pos);
    string outputFile = name + ".o";
    fstream assembly, objectCode;
    assembly.open(inputFile.c_str(), ios::in);
    objectCode.open(outputFile.c_str(), ios::out);
    
    if (as.assemble(assembly, objectCode)){
        cout << "Assembler Error \n";
        assembly.close();
        objectCode.close();
        exit(3);
    }
    
    assembly.close();
    objectCode.close();
    
    return 0;
}
