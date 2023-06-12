#include "fstream"
#include "CodeGen.h"
#include "node.h"
#include <llvm/Support/TargetSelect.h>

extern int yyparse(void);
extern NBlock* programBlock;

int main(){
    yyparse();
    NBlock* Root;
    CodeGenContext* generator = new CodeGenContext();

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();

    cout<<"program begin"<<endl;

    // jsonize AST
    string jsonString("");
    programBlock->generateJson(jsonString);
    // std::cout << jsonString << std::endl;
    ofstream fout;
    fout.open("../visualization/AST.json");
    fout << jsonString;
    fout.close();

    generator->Run(programBlock);

    return 0;
}