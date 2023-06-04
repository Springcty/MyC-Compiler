#include <string>
#include <vector>
#include "CodeGen.h"
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/ADT/Twine.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

llvm::LLVMContext myContext; //定义全局context
llvm::IRBuilder<> myBuilder(myContext); //定义全局IRbuilder

CodeGenContext::CodeGenContext(){
    this->myModule = new llvm::Module("main",myContext);
    this->printf = getPrintf();
    this->scanf = getScanf();
    this->gets = getGets();
    this->hasReturn = false;
    this->isArgs = false;
}



map<string, llvm::Value*>& CodeGenContext::getTop() {  // 得到栈顶对应的当前域的符号表
    return symbolTable_stack.back()-> local_var; 
    }
map<string, llvm::Type*>& CodeGenContext::getTopType(){
    return symbolTable_stack.back()->local_var_type;
}

void CodeGenContext::pushBlock(){
    symbolTable_stack.push_back(new symbolTable());//最近的作用域放在末尾
}

void CodeGenContext::popBlock(){
    symbolTable *tmp = symbolTable_stack.back();
    symbolTable_stack.pop_back();
    delete tmp;
}

llvm::Value* CodeGenContext::findVariable(string variableName) {
    
    // 首先按照作用域由近到远查找局部变量
    vector<symbolTable*>::reverse_iterator riter = symbolTable_stack.rbegin();
    for (; riter != symbolTable_stack.rend(); ++riter)
    {
        symbolTable* curTable = *riter;
        if(curTable->local_var.find(variableName) != curTable->local_var.end())
            return curTable->local_var[variableName];
    }

    // 若没有局部变量, 则查找全局变量
    // 若没有返回 nullptr
    return this->myModule->getGlobalVariable(variableName, true);
}

// 

void CodeGenContext::Run(NBlock* Root){
    Root->CodeGen(*this);
    llvm::verifyModule(*this->myModule, &llvm::outs());
    this->myModule->print(llvm::outs(), nullptr);
}



llvm::Function* CodeGenContext::getPrintf(){
//     vector<llvm::Type*> printf_arg_types; //printf内参数的类型
//     printf_arg_types.push_back(myBuilder.getInt8PtrTy()); //8位代表void*

//     llvm::FunctionType* printf_type = 
//     llvm::FunctionType::get(myBuilder.getInt32Ty(),printf_arg_types,true);
//     llvm::Function* printf_func = 
//     llvm::Function::Create(printf_type,llvm::Function::ExternalLinkage,llvm::Twine("printf"),this->myModule);

//     printf_func->setCallingConv(llvm::CallingConv::C);
//     return printf_func;
// }

// llvm::Function* CodeGenContext::getScanf(){
//     llvm::FunctionType* scanf_type = 
//     llvm::FunctionType::get(myBuilder.getInt32Ty(),true);
//     llvm::Function* scanf_func = 
//     llvm::Function::Create(scanf_type,llvm::Function::ExternalLinkage,llvm::Twine("scanf"),this->myModule);

//     scanf_func->setCallingConv(llvm::CallingConv::C);
//     return scanf_func;
// }

// llvm::Function* CodeGenContext::getGets(){
//     llvm::FunctionType* gets_type = 
//     llvm::FunctionType::get(myBuilder.getInt32Ty(),true);
//     llvm::Function* gets_func = 
//     llvm::Function::Create(gets_type,llvm::Function::ExternalLinkage,llvm::Twine("gets"),this->myModule);

//     gets_func->setCallingConv(llvm::CallingConv::C);
//     return gets_func;
// }


