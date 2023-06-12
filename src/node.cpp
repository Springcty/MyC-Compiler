#include "node.h"
#include "parser.hpp"
#include "CodeGen.h"
#include <llvm/IR/BasicBlock.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

stack<llvm::BasicBlock *> GlobalAfterBB;

//辅助函数

llvm::Type* getLLvmType(string type){ //通过type，返回对应的LLVM的Type
    if(type == "int"){return llvm::Type::getInt32Ty(myContext);}
    else if(type == "float"){return llvm::Type::getFloatTy(myContext);}
    else if(type == "char"){return llvm::Type::getInt8Ty(myContext);}
    else if(type == "string"){return llvm::Type::getInt8PtrTy(myContext);}
    return llvm::Type::getVoidTy(myContext);
}

llvm::Type* getPtrLLvmType(string type){ //对于指针形式，返回对应的LLVM的Type
    if(type == "int"){return llvm::Type::getInt32PtrTy(myContext);}
    else if(type == "float"){return llvm::Type::getFloatPtrTy(myContext);}
    else if(type == "char"){return llvm::Type::getInt8PtrTy(myContext);}
    return llvm::Type::getVoidTy(myContext);
}

llvm::Type* getArrayLLvmType(string type,int size){ //对于数组形式，返回对应的LLVM的Type
    if(type == "int"){ //int数组
        return llvm::ArrayType::get(llvm::Type::getInt32Ty(myContext), size);
    }
    else if(type == "float"){
        return llvm::ArrayType::get(llvm::Type::getFloatTy(myContext), size);
    }
    else if(type == "char"){
        return llvm::ArrayType::get(llvm::Type::getInt8Ty(myContext), size);
    }
    else{return nullptr;}
}
//返回llvm数据类型转换的方法
llvm::Instruction::CastOps getCastInst(llvm::Type* src, llvm::Type* dst) {
    if (src == llvm::Type::getFloatTy(myContext) && dst == llvm::Type::getInt32Ty(myContext)) { //llvm下float到int
        return llvm::Instruction::FPToSI;  
    }
    else if (src == llvm::Type::getInt32Ty(myContext) && dst == llvm::Type::getFloatTy(myContext)) { //llvm下int到float
        return llvm::Instruction::SIToFP;
    }
    else if (src == llvm::Type::getInt8Ty(myContext) && dst == llvm::Type::getFloatTy(myContext)) {//float->char
        return llvm::Instruction::UIToFP;
    }
    else if (src == llvm::Type::getInt8Ty(myContext) && dst == llvm::Type::getInt32Ty(myContext)) {//cut
        return llvm::Instruction::ZExt;
    }
    else if (src == llvm::Type::getInt32Ty(myContext) && dst == llvm::Type::getInt8Ty(myContext)) {//extend
        return llvm::Instruction::Trunc;
    }
    else {
        throw logic_error("[ERROR] Wrong typecast");
    }
}

llvm::Value* typeCast(llvm::Value* src, llvm::Type* dst) {
    llvm::Instruction::CastOps op = getCastInst(src->getType(), dst);
    return myBuilder.CreateCast(op, src, dst, "tmptypecast");
}

vector<llvm::Value *> *getPrintfArgs(CodeGenContext &CodeGenContext,vector<NExpression*>args){
    vector<llvm::Value *> *printf_args = new vector<llvm::Value *>;
    for(auto it: args){
        llvm::Value* tmp = it->CodeGen(CodeGenContext);
        if (tmp->getType() == llvm::Type::getFloatTy(myContext))
            tmp = myBuilder.CreateFPExt(tmp, llvm::Type::getDoubleTy(myContext), "tmpdouble");
        printf_args->push_back(tmp);
    }
    return printf_args;
}

vector<llvm::Value *> *getScanfArgs(CodeGenContext &CodeGenContext,vector<NExpression*>args){
    vector<llvm::Value *> *scanf_args = new vector<llvm::Value *>;
    for(auto it: args){
        llvm::Value* tmp = it->CodeGen(CodeGenContext);
        scanf_args->push_back(tmp);
    }
    return scanf_args;
}

vector<llvm::Value *> *getGetsArgs(CodeGenContext &CodeGenContext,vector<NExpression*>args){
    vector<llvm::Value *> *gets_args = new vector<llvm::Value *>;
    for(auto it: args){
        llvm::Value* tmp = it->CodeGen(CodeGenContext);
        gets_args->push_back(tmp);
    }
    return gets_args;
}

vector<llvm::Value *> *getScanfArgsAddr(CodeGenContext &CodeGenContext,vector<NExpression*>args){
    vector<llvm::Value *> *scanf_args = new vector<llvm::Value *>;
    for(auto it: args){
        llvm::Value* tmp = it->GetAddr(CodeGenContext);
        scanf_args->push_back(tmp);
    }
    return scanf_args;

}

llvm:: Value* emitPrintf(CodeGenContext &CodeGenContext,vector<NExpression*> args){
    vector<llvm::Value *> *printf_args = getPrintfArgs(CodeGenContext, args);    
    return myBuilder.CreateCall(CodeGenContext.printf, *printf_args, "printf");
}

llvm:: Value* emitScanf(CodeGenContext &CodeGenContext,vector<NExpression*> args){
    //vector<llvm::Value *> *scanf_args = getScanfArgsAddr(CodeGenContext, args);    
    vector<llvm::Value *> *scanf_args = getScanfArgs(CodeGenContext, args);    
    return myBuilder.CreateCall(CodeGenContext.scanf, *scanf_args, "scanf");
}

llvm:: Value* emitGets(CodeGenContext &CodeGenContext,vector<NExpression*> args){
    //vector<llvm::Value *> *scanf_args = getScanfArgsAddr(CodeGenContext, args);    
    vector<llvm::Value *> *gets_args = getGetsArgs(CodeGenContext, args);    
    return myBuilder.CreateCall(CodeGenContext.gets, *gets_args, "gets");
}

llvm::Value* NInteger::CodeGen(CodeGenContext &CodeGenContext){
    cout << "Integer : " << value <<endl;
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(myContext),value,true);
}

llvm::Value* NFloat::CodeGen(CodeGenContext &CodeGenContext){
    cout << "NFloat : " << value <<endl;
    return llvm::ConstantFP::get(llvm::Type::getFloatTy(myContext),value);
}

llvm::Value* NChar::CodeGen(CodeGenContext &CodeGenContext){  //----------  -_-
    cout << "NChar : " << value <<endl;
    if (this->value.size() == 3)
        return myBuilder.getInt8(this->value.at(1));
    else {
        if (this->value.compare("'\\n'") == 0) {
            return myBuilder.getInt8('\n');
        } else if (this->value.compare("'\\\\'") == 0){
            return myBuilder.getInt8('\\');
        } else if (this->value.compare("'\\a'") == 0){
            return myBuilder.getInt8('\a');
        } else if (this->value.compare("'\\b'") == 0){
            return myBuilder.getInt8('\b');
        } else if (this->value.compare("'\\f'") == 0){
            return myBuilder.getInt8('\f');
        } else if (this->value.compare("'\\t'") == 0){
            return myBuilder.getInt8('\t');
        } else if (this->value.compare("'\\v'") == 0){
            return myBuilder.getInt8('\v');
        } else if (this->value.compare("'\\''") == 0){
            return myBuilder.getInt8('\'');
        } else if (this->value.compare("'\\\"'") == 0){
            return myBuilder.getInt8('\"');
        } else if (this->value.compare("'\\0'") == 0){
            return myBuilder.getInt8('\0');
        } else {
            throw logic_error("[ERROR] char not defined: " + this->value);
        }
    }
    return nullptr;
}

//辅助函数：处理字符串字面量
string StrProcess(string& s){
  int pos = s.find("\\");
  while(pos != string::npos) {
    switch(s[pos+1]){
      case 'n':
        s = s.replace(pos, 2, "\n");
        break;
      case '\\':
        s = s.replace(pos, 2, "\\");
        break;
      case 'a':
        s = s.replace(pos, 2, "\a");
        break;
      case 'b':
        s = s.replace(pos, 2, "\b");
        break;
      case 'f':
        s = s.replace(pos, 2, "\f");
        break;
      case 't':
        s = s.replace(pos, 2, "\t");
        break;
      case 'v':
        s = s.replace(pos, 2, "\v");
        break;
      case '"':
        s = s.replace(pos, 2, "\"");
        break;
      case '\'':
        s = s.replace(pos, 2, "\'");
        break;
      case '0':
        s = s.replace(pos, 2, "\0");
        break;
    }
    pos = s.find("\\", pos+1);
  }
  return s;
}

//创建llvm字符串常量并返回首地址
llvm::Value* NString::CodeGen(CodeGenContext &CodeGenContext) {
    cout << "NString : " << value <<endl;
    string str = value.substr(1, value.length() - 2);//remove ""
    str = StrProcess(str);
    llvm::Constant *strConst = llvm::ConstantDataArray::getString(myContext, str);
    
    //制作全局变量:	GlobalVariable ctor - If a parent module is specified, the global is automatically inserted into the end of the specified modules global list.
    llvm::Value *globalVar = new llvm::GlobalVariable(*(CodeGenContext.myModule), strConst->getType(), true, llvm::GlobalValue::PrivateLinkage, strConst, "_Const_String_");
    vector<llvm::Value*> idList;
    idList.push_back(myBuilder.getInt32(0));
    idList.push_back(myBuilder.getInt32(0));
    llvm::Value * varPtr = myBuilder.CreateInBoundsGEP(globalVar, llvm::ArrayRef<llvm::Value*>(idList), "tmpstring");// The first operand indexes through the pointer; the second operand indexes the field str[0] of the structure
    return varPtr;
}

llvm::Value* NIdentifier::CodeGen(CodeGenContext &CodeGenContext){
    cout << "IdentifierNode : " << name << endl;

    llvm::Value* variable = CodeGenContext.findVariable(name);
    if(variable == nullptr){
        std::cerr << "undeclared variable " << name << endl;
        return nullptr;
    }
    llvm::Type* tp = variable->getType()->getPointerElementType();
    llvm::outs()<<"ident type:"<<*tp;
    cout<<endl;

    llvm::Value* res = nullptr;
    // 如果传入的是一个数组的 ID
    if(tp->isArrayTy()) {
        vector<llvm::Value*> indexList;
        indexList.push_back(myBuilder.getInt32(0));
        indexList.push_back(myBuilder.getInt32(0));
        res = myBuilder.CreateInBoundsGEP(variable, indexList, "arrayPtr");//返回数组0号元素位置
    }
    else {
        res = new llvm::LoadInst(tp, variable, "LoadInst", false, myBuilder.GetInsertBlock());//向当前block中插入语句
    }
    return res;
}

llvm::Value* NIdentifier::GetAddr(CodeGenContext &CodeGenContext){
    cout << "IdentifierNode : " << name << endl;

    llvm::Value* variable = CodeGenContext.findVariable(name);
    if(variable == nullptr){
        std::cerr << "undeclared variable " << name << endl;
        return nullptr;
    }
    return variable;
}

// 数组在表达式中返回值
llvm::Value* NArrayElement::CodeGen(CodeGenContext &CodeGenContext){
    llvm::Value* elePtr = GetAddr(CodeGenContext);
    return myBuilder.CreateLoad(elePtr->getType()->getPointerElementType(), elePtr, "tmpvar");
}

llvm::Value* NArrayElement::GetAddr(CodeGenContext &CodeGenContext){
    cout<<"get arrayElement Addr:"<<ident.name<<"[]"<<endl;
    llvm::Value* arrayValue = CodeGenContext.findVariable(ident.name);
    if(arrayValue == nullptr){
        cerr << "undeclared array " << ident.name << endl;
		return nullptr;
    }
    //利用虚函数获得返回值
    llvm::Value* indexValue = idx.CodeGen(CodeGenContext);//执行NExpression获得id
    vector<llvm::Value*> indexList;
    // 如果是一个指针
    if(arrayValue->getType()->getPointerElementType()->isPointerTy()) {//指针也具有[]方法：取得指向的地址+idx 
        arrayValue = myBuilder.CreateLoad(arrayValue->getType()->getPointerElementType(), arrayValue);
        indexList.push_back(indexValue);    
    }
    // 如果是一个数组 
    else {
        indexList.push_back(myBuilder.getInt32(0));//数组基地址
        indexList.push_back(indexValue);    
    }
    llvm::Value* elePtr =  myBuilder.CreateInBoundsGEP(arrayValue, llvm::ArrayRef<llvm::Value*>(indexList), "elePtr");
    return elePtr;
}

llvm::Value* NGetArrayAddr::CodeGen(CodeGenContext &CodeGenContext){
    cout<<"get Array Addr:"<< ident.name << "[]" <<endl;
    return NArrayElement(ident, idx, lineno).GetAddr(CodeGenContext);
}

llvm::Value* NGetAddr::CodeGen(CodeGenContext &CodeGenContext){
    cout << "getAddrNode : " << re.name << endl;
    // 在符号表和全局变量中查找
    llvm::Value* result = CodeGenContext.findVariable(re.name);
    if(result == nullptr){
        cerr << "undeclared variable " << re.name << endl;
		return nullptr;
    }
    return result;
}

llvm::Value* NArrayElementAssign::CodeGen(CodeGenContext &CodeGenContext){
    llvm::Value* left =  NArrayElement(ident, idx, lineno).GetAddr(CodeGenContext);
    llvm::Value *right = re.CodeGen(CodeGenContext);//
    llvm::outs()<<*(left->getType()->getPointerElementType());
    if (right->getType() != left->getType()->getPointerElementType())
        right = typeCast(right, left->getType()->getPointerElementType());
    return myBuilder.CreateStore(right, left);
}

// ident = expression
llvm::Value* NAssignment::CodeGen(CodeGenContext &CodeGenContext){
    cout << "AssignmentNode,le: " << li.name << endl;
    // 在符号表和全局变量中查找
    llvm::Value* result = CodeGenContext.findVariable(li.name);
    if(result == nullptr){
        cerr << "undeclared variable " << li.name << endl;
		return nullptr;
    }

    llvm::Value* right = ri.CodeGen(CodeGenContext);
    // 定位 block
    auto CurrentBlock = myBuilder.GetInsertBlock();
    
    if (right->getType() != result->getType()->getPointerElementType())
    {
        right = typeCast(right, result->getType()->getPointerElementType());
    }
        
    cout<<"check succeed"<<endl;
    return new llvm::StoreInst(right, result, false, CurrentBlock);
}

llvm::Value* NFunctionCall::CodeGen(CodeGenContext &CodeGenContext){
    if(ident.name == "printf"){ //若调用 printf 函数
        return emitPrintf(CodeGenContext, args);
    } else if(ident.name == "scanf"){ //若调用 scanf 函数
        return emitScanf(CodeGenContext, args);
    } else if(ident.name == "gets") { // 若调用 gets 函数
        return emitGets(CodeGenContext, args);
    }

    //在module中查找以identifier命名的函数
    llvm::Function *func = CodeGenContext.myModule->getFunction(ident.name.c_str());
    if (func == NULL) {
		std::cerr << "no such function " << ident.name << endl;
	}

    vector<llvm::Value*> tmp;
    vector<NExpression*>::iterator i;
    for(auto i : args){  //对每个ExpressionNode进行emit 并将结果存入tmp中
        tmp.push_back((*i).CodeGen(CodeGenContext));
    }
    //调用
    try{
        llvm::CallInst::Create(func,llvm::makeArrayRef(tmp),"",myBuilder.GetInsertBlock());
    }
    catch(...){
        cout<<"error in call:"<<lineno<<endl;
        throw;
    }
    cout << "Creating method call: " << ident.name << endl;
    return llvm::CallInst::Create(func,llvm::makeArrayRef(tmp),"",myBuilder.GetInsertBlock());
}

llvm::Value* NBinaryOperator::CodeGen(CodeGenContext &CodeGenContext){
    cout << "NBinaryOperator : " << op << endl;
    llvm::Value* left = le.CodeGen(CodeGenContext);
    llvm::Value* right = re.CodeGen(CodeGenContext);
    llvm::Instruction::BinaryOps bi_op;

    if(op == PLUS || op == MINUS || op == MUL || op == DIV){
        if (left->getType() != right->getType()) {
            if (left->getType() == llvm::Type::getFloatTy(myContext)) {
                right = typeCast(right, llvm::Type::getFloatTy(myContext));
            } else {
                if (right->getType() == llvm::Type::getFloatTy(myContext)) {
                    left = typeCast(left, llvm::Type::getFloatTy(myContext));
                } else {
                    if (left->getType() == llvm::Type::getInt32Ty(myContext)) {
                        right = typeCast(right, llvm::Type::getInt32Ty(myContext));
                    } else if(right->getType() == llvm::Type::getInt32Ty(myContext)) {
                        left = typeCast(left, llvm::Type::getInt32Ty(myContext));
                    } else {
                        throw logic_error("cann't use bool in +-*/");
                    }
                }
            }
        }
        if(op == PLUS){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FAdd : llvm::Instruction::Add;}
        else if(op == MINUS){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FSub : llvm::Instruction::Sub;}
        else if(op == MUL){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FMul : llvm::Instruction::Mul;}
        else if(op == DIV){bi_op = left->getType()->isFloatTy() ? llvm::Instruction::FDiv : llvm::Instruction::SDiv;}
        return llvm::BinaryOperator::Create(bi_op,left,right,"", myBuilder.GetInsertBlock());
    }
    else if(op == AND){
        if (left->getType() != llvm::Type::getInt1Ty(myContext) || right->getType() != llvm::Type::getInt1Ty(myContext)) {
                    throw logic_error("cannot use types other than bool in and exp");
                }
                return myBuilder.CreateAnd(left, right, "tmpAnd");
    }
    else if (op == OR) {
        if (left->getType() != llvm::Type::getInt1Ty(myContext) || right->getType() != llvm::Type::getInt1Ty(myContext)) {
                    throw logic_error("cannot use types other than bool in and exp");
                }
                return myBuilder.CreateOr(left, right, "tmpOR");
    }
    else{  //LT、GT、EQ、NEQ、LE、GE
        cout << "0" << endl;
        if (left->getType() != right->getType()) { //若左右的type类型不一致
            cout << "1" << endl;
            if (left->getType() == llvm::Type::getFloatTy(myContext)) 
            { 
                cout << "2" << endl;
                right = typeCast(right, llvm::Type::getFloatTy(myContext));
            } 
            else {
                if (right->getType() == llvm::Type::getFloatTy(myContext)) 
                {
                    cout << "3" << endl;
                    left = typeCast(left, llvm::Type::getFloatTy(myContext));
                } 
                else {
                    cout << "4" << endl;

                    if (left->getType() == llvm::Type::getInt32Ty(myContext)) {
                        right = typeCast(right, llvm::Type::getInt32Ty(myContext));
                    } else if(right->getType() == llvm::Type::getInt32Ty(myContext)) {
                        left = typeCast(left, llvm::Type::getInt32Ty(myContext));
                    } else {
                        throw logic_error("cann't use bool in == != >= <= < >");
                    }
                }
            }
        }
        else if (op == EQU) {
            return (left->getType() == llvm::Type::getFloatTy(myContext)) ? myBuilder.CreateFCmpOEQ(left, right, "fcmptmp") : myBuilder.CreateICmpEQ(left, right, "icmptmp");
        }
        else if (op == GEQ) {
            return (left->getType() == llvm::Type::getFloatTy(myContext)) ? myBuilder.CreateFCmpOGE(left, right, "fcmptmp") : myBuilder.CreateICmpSGE(left, right, "icmptmp");
        }
        else if (op == LEQ) {
            return (left->getType() == llvm::Type::getFloatTy(myContext)) ? myBuilder.CreateFCmpOLE(left, right, "fcmptmp") : myBuilder.CreateICmpSLE(left, right, "icmptmp");
        }
        else if (op == GT) {
            return (left->getType() == llvm::Type::getFloatTy(myContext)) ? myBuilder.CreateFCmpOGT(left, right, "fcmptmp") : myBuilder.CreateICmpSGT(left, right, "icmptmp");
        }
        else if (op == LET) {
            return (left->getType() == llvm::Type::getFloatTy(myContext)) ? myBuilder.CreateFCmpOLT(left, right, "fcmptmp") : myBuilder.CreateICmpSLT(left, right, "icmptmp");
        }
        else if (op == NEQ) {
            return (left->getType() == llvm::Type::getFloatTy(myContext)) ? myBuilder.CreateFCmpONE(left, right, "fcmptmp") : myBuilder.CreateICmpNE(left, right, "icmptmp");
        }
        return NULL;
    }
}

llvm::Value* NBlock::CodeGen(CodeGenContext &CodeGenContext){
    llvm::Value* tmp = NULL;
    for(auto i : stmts){
        cout << "Generating code for " << typeid(*i).name() << endl;
        tmp = (*i).CodeGen(CodeGenContext);
        // 若当前语句为 reutrn , 则后面的语句需要截断
        if(CodeGenContext.hasReturn == true)
            break;
    }
    cout << "" << endl;
	return tmp;
}

llvm::Value* NExpressionStatement::CodeGen(CodeGenContext &CodeGenContext){
    cout << "Generating code for " << typeid(expr).name() << endl;
	return expr.CodeGen(CodeGenContext);
}

llvm::Value* NBreakStatement::CodeGen(CodeGenContext &CodeGenContext){
    CodeGenContext.hasReturn = true;
    return myBuilder.CreateBr(GlobalAfterBB.top());
}

llvm::Value* NIfStatement::CodeGen(CodeGenContext &CodeGenContext){
    cout << "Generating code for if-only"<<endl;    
    llvm::Function *TheFunction = CodeGenContext.currentFunc;
    
    llvm::BasicBlock *IfBB = llvm::BasicBlock::Create(myContext, "if", TheFunction);
    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(myContext, "afterifonly",TheFunction);

    // 跳转判断语句
    llvm::Value *condValue = expr.CodeGen(CodeGenContext), *thenValue = nullptr, *elseValue = nullptr;
    condValue = myBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(myContext), 0, true), "ifCond");
    auto branch = myBuilder.CreateCondBr(condValue, IfBB, ThenBB);

    myBuilder.SetInsertPoint(IfBB);
    // 将 if 的域放入栈顶
    CodeGenContext.pushBlock();
    if_blk.CodeGen(CodeGenContext);
    CodeGenContext.popBlock();

    if(CodeGenContext.hasReturn) 
        CodeGenContext.hasReturn = false;
    // 跳过 else
    else
        myBuilder.CreateBr(ThenBB);

    myBuilder.SetInsertPoint(ThenBB);    
    return branch;
}

llvm::Value* NIfElseStatement::CodeGen(CodeGenContext &CodeGenContext){
    cout << "Generating code for if-else"<<endl;

    
    llvm::Function *TheFunction = CodeGenContext.currentFunc;
    
    llvm::BasicBlock *IfBB = llvm::BasicBlock::Create(myContext, "if", TheFunction);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(myContext, "else",TheFunction);
    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(myContext, "afterifelse",TheFunction);

    // 跳转判断语句
    llvm::Value *condValue = expr.CodeGen(CodeGenContext), *thenValue = nullptr, *elseValue = nullptr;
    condValue = myBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(myContext), 0, true), "ifCond");
    auto branch = myBuilder.CreateCondBr(condValue, IfBB, ElseBB);

    myBuilder.SetInsertPoint(IfBB);
    // 将 if 的域放入栈顶
    CodeGenContext.pushBlock();
    if_blk.CodeGen(CodeGenContext);
    CodeGenContext.popBlock();

    if(CodeGenContext.hasReturn)
        CodeGenContext.hasReturn = false;
    // 跳过 else
    else
        myBuilder.CreateBr(ThenBB);

    myBuilder.SetInsertPoint(ElseBB);
    // 将 else 的域放入栈顶
    CodeGenContext.pushBlock();
    else_blk.CodeGen(CodeGenContext);
    CodeGenContext.popBlock();

    if(CodeGenContext.hasReturn)
        CodeGenContext.hasReturn = false;
    else
        myBuilder.CreateBr(ThenBB);

    myBuilder.SetInsertPoint(ThenBB);    
    return branch;
}

llvm::Value*  NWhileStatement::CodeGen(CodeGenContext &CodeGenContext){
    cout << "Generating code for while "<<endl;

    llvm::Function *TheFunction = CodeGenContext.currentFunc;

    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(myContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(myContext, "loop", TheFunction);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(myContext, "afterLoop", TheFunction);

    GlobalAfterBB.push(afterBB);

    myBuilder.CreateBr(condBB);
    myBuilder.SetInsertPoint(condBB);

    llvm::Value *condValue = expr.CodeGen(CodeGenContext);
    condValue = myBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(myContext), 0, true), "whileCond");
    auto branch = myBuilder.CreateCondBr(condValue, loopBB, afterBB);
    condBB = myBuilder.GetInsertBlock();

    myBuilder.SetInsertPoint(loopBB);

    // 将 while 的域放入栈顶
    CodeGenContext.pushBlock();
    loop_blk.CodeGen(CodeGenContext);
    if(CodeGenContext.hasReturn)
        CodeGenContext.hasReturn = false;
    else
        myBuilder.CreateBr(condBB);

    // while 结束, 将 while 的域弹出栈顶
    CodeGenContext.popBlock();
    myBuilder.SetInsertPoint(afterBB);

    GlobalAfterBB.pop();
    return branch;
}

llvm::Value* NReturnStatement::CodeGen(CodeGenContext &CodeGenContext){

    cout << "Generating return code for " << typeid(expr).name() << endl;
	llvm::Value *rv = expr.CodeGen(CodeGenContext);
    if (rv->getType() != CodeGenContext.returnVal->getType()->getPointerElementType())
        rv = typeCast(rv, CodeGenContext.returnVal->getType()->getPointerElementType());
    myBuilder.CreateStore(rv, CodeGenContext.returnVal);

    CodeGenContext.hasReturn = true;
    return myBuilder.CreateBr(CodeGenContext.returnBB);
}

llvm::Value* NReturnVoidStatement::CodeGen(CodeGenContext &CodeGenContext){
    
    cout << "Generating return code for void " << endl;
    CodeGenContext.hasReturn = true;
    return myBuilder.CreateBr(CodeGenContext.returnBB);
}

// -----------------------------------------
llvm::Value* NVariableDeclaration::CodeGen(CodeGenContext &CodeGenContext) {  
    if(size == 0){ //普通变量
        llvm::Type* llvmType = getLLvmType(type.name);
        
        // 若当前函数为空, 说明是全局变量
        if(CodeGenContext.currentFunc == nullptr) {
            cout << "Creating global variable declaration " << type.name << " " << id.name<< endl;
            llvm::Value *tmp = CodeGenContext.myModule->getGlobalVariable(id.name, true);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Variable: " + id.name);
            }
            llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*(CodeGenContext.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, id.name);
            globalVar->setInitializer(llvm::ConstantInt::get(llvmType, 0));
            return nullptr;
        } else {
            cout << "Creating local variable declaration " << type.name << " " << id.name<< endl;
            auto *block = myBuilder.GetInsertBlock();
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(id.name.c_str()), block);
            // 
            if(CodeGenContext.getTop().count(id.name) != 0) {
                // 当前域中有该变量, 重复定义
                throw logic_error("Redefined Local Variable: " + id.name);
            }

            // 将新定义的变量类型和地址存入符号表中
            CodeGenContext.getTopType()[id.name] = llvmType;
            CodeGenContext.getTop()[id.name] = alloc;
            if (assin_expr != NULL) {
                NAssignment assn(id, *assin_expr,lineno);
                assn.CodeGen(CodeGenContext);
            }
            return alloc;
        }
    }
    else{ //数组
        llvm::Type* llvmType = getArrayLLvmType(type.name, size); 
        if(CodeGenContext.currentFunc == nullptr) { //当前函数为空，为全局数组定义
            cout << "Creating global array declaration " << type.name << " " << id.name<< endl;
            llvm::Value *tmp = CodeGenContext.myModule->getGlobalVariable(id.name, true);
            if(tmp != nullptr){
                throw logic_error("Redefined Global Array: " + id.name);
            }
            llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*(CodeGenContext.myModule), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, id.name);
            
            std::vector<llvm::Constant*> constArrayElem;
            llvm::Constant* constElem = llvm::ConstantInt::get(llvmType->getArrayElementType(), 0);
            for (int i = 0; i < llvmType->getArrayNumElements(); i++) {
                constArrayElem.push_back(constElem);
            }
            llvm::Constant* constArray = llvm::ConstantArray::get(llvm::ArrayType::get(llvmType->getArrayElementType(), llvmType->getArrayNumElements()), constArrayElem);
            globalVar->setInitializer(constArray);
            return nullptr;
            
        }
        else {
            if(CodeGenContext.getTop().count(id.name) != 0) {
                // 当前域中有该变量, 重复定义
                throw logic_error("Redefined Local Variable: " + id.name);
            }

            if(CodeGenContext.isArgs) {
                // 如果是函数中定义的数组需要返回 指针类型
                cout << "Creating args array declaration " << type.name << " " << id.name<< endl;
                llvmType = getPtrLLvmType(type.name);
            } else {
                cout << "Creating local array declaration " << type.name << " " << id.name<< endl;
            }
            CodeGenContext.getTopType()[id.name] = llvmType;
            auto *block = myBuilder.GetInsertBlock();
            llvm::AllocaInst *alloc = new llvm::AllocaInst(llvmType,block->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(),(id.name.c_str()), block);
            CodeGenContext.getTop()[id.name] = alloc;
            return alloc;
        }
    }

}

llvm::Value* NFunctionDeclaration::CodeGen(CodeGenContext &CodeGenContext){
    vector<llvm::Type*> argTypes;
    for(auto it : args){
        if(it->size == 0)
            argTypes.push_back(getLLvmType(it->type.name));
        else {
            argTypes.push_back(getPtrLLvmType(it->type.name));
        }
    }
	llvm::FunctionType *ftype = llvm::FunctionType::get(getLLvmType(type.name), makeArrayRef(argTypes), false);
	llvm::Function *function = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, id.name.c_str(), CodeGenContext.myModule);
	llvm::BasicBlock *bblock = llvm::BasicBlock::Create(myContext, "entry", function, 0);

    myBuilder.SetInsertPoint(bblock);
    CodeGenContext.currentFunc = function;
    CodeGenContext.returnBB = llvm::BasicBlock::Create(myContext, "return", function, 0);

    // 定义一个变量用来存储函数的返回值
    if(type.name.compare("void") != 0) {
        CodeGenContext.returnVal = new llvm::AllocaInst(getLLvmType(type.name), bblock->getParent()->getParent()->getDataLayout().getAllocaAddrSpace(), "", bblock);
    }
 
	CodeGenContext.pushBlock();//add new symble table

 
	llvm::Function::arg_iterator argsValues = function->arg_begin();
    llvm::Value* argumentValue;

    CodeGenContext.isArgs = true;
    for(auto it : args){
        (*it).CodeGen(CodeGenContext);
        argumentValue = &*argsValues++;
        argumentValue->setName((it)->id.name.c_str());
        llvm::StoreInst *inst = new llvm::StoreInst(argumentValue, CodeGenContext.getTop()[(it)->id.name], false, bblock);
	}
    CodeGenContext.isArgs = false;
	
	block.CodeGen(CodeGenContext);
    CodeGenContext.hasReturn = false;

    myBuilder.SetInsertPoint(CodeGenContext.returnBB);
    if(type.name.compare("void") == 0) {
        myBuilder.CreateRetVoid();
    } else {
        llvm::Value* ret = myBuilder.CreateLoad(getLLvmType(type.name), CodeGenContext.returnVal, "");
        myBuilder.CreateRet(ret);
    }

	CodeGenContext.popBlock();
    CodeGenContext.currentFunc = nullptr;
	std::cout << "Creating function: " << id.name << endl;
	return function;
}




/*
Json format (print with OrgChart):
    var datascource = {
      'name': 'Node's name',
      'value': 'Node's value',
      'children': [
        { 'name': 'Child-1's name', 'value': 'Child-1's value',
          'children': [
            ...
          ]
        },
        { 'name': 'Child-2's name', 'value': 'Child-2's value' },
        { 'name': 'Child-3's name', 'value': 'Child-3's value',
          'children': [
            ...
          ]
        }
      ]
    };
*/

void NInteger::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Integer\",\n");
    
    ss<<this->value;
    ss>>temp;
    s.append("\"value\" : \"" + temp + "\",\n");
    
    s.append("}");
}

void NFloat::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Float\",\n");
    
    ss<<this->value;
    ss>>temp;
    s.append("\"value\" : \"" + temp + "\",\n");
    
    s.append("}");
}

void NChar::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Char\",\n");
    
    ss<<this->value;
    ss>>temp;
    s.append("\"value\" : \"" + temp + "\",\n");
    
    s.append("}");
}

void NString::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-String\",\n");
    
    ss<<this->value;
    ss>>temp;
    s.append("\"value\" : \"" + temp + "\",\n");
    
    s.append("}");
}

void NIdentifier::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Identifier\",\n");
    
    ss<<this->name;
    ss>>temp;
    s.append("\"value\" : \"" + temp + "\",\n");
    
    s.append("}");
}

void NBinaryOperator::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Binop\",\n");
    
    ss<<this->op;
    ss>>temp;
    s.append("\"value\" : \"" + temp + "\",\n");
    
    s.append("\"children\" : \n[");
    this->le.generateJson(s);
    s.append(",");
    this->re.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NAssignment::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Assignment\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->li.generateJson(s);
    s.append(",");
    this->ri.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NArrayElement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-ArrayElement\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->ident.generateJson(s);
    s.append(",");
    this->idx.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NArrayElementAssign::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-ArrayElementAssign\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->ident.generateJson(s);
    s.append(",");
    this->idx.generateJson(s);
    s.append(",");
    this->re.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NFunctionCall::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-FunCall\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->ident.generateJson(s);
    if(!this->args.empty()) {
        s.append(",");
    }
    for(Node* node : this->args) {
        node->generateJson(s);
        if(node != this->args.back()) {
            s.append(",");
        }
    }
    s.append("\n]\n");
    
    s.append("}");
}

void NGetAddr::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-GetAddr\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->re.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NGetArrayAddr::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-GetArrayAddr\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->ident.generateJson(s);
    s.append(",");
    this->idx.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NBlock::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Block\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    for(Node* node : this->stmts) {
        node->generateJson(s);
        if(node != this->stmts.back()) {
            s.append(",");
        }
    }
    s.append("\n]\n");
    
    s.append("}");
}

void NExpressionStatement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Expr\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->expr.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NVariableDeclaration::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-VarDec\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->type.generateJson(s);
    s.append(",");
    this->id.generateJson(s);
    if(this->assin_expr != nullptr) {
        s.append(",");
        this->assin_expr->generateJson(s);
    }
    s.append("\n]\n");
    
    s.append("}");
}

void NFunctionDeclaration::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-FunDec\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->type.generateJson(s);
    s.append(",");
    this->id.generateJson(s);
    s.append(",");
    for(Node* node : this->args) {
        node->generateJson(s);
        s.append(",");
    }    
    this->block.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NBreakStatement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Break\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("}");
}

void NIfStatement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-If\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->expr.generateJson(s);
    s.append(",");
    this->if_blk.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NIfElseStatement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-IfElse\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->expr.generateJson(s);
    s.append(",");
    this->if_blk.generateJson(s);
    s.append(",");
    this->else_blk.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NWhileStatement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-While\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->expr.generateJson(s);
    s.append(",");
    this->loop_blk.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NReturnStatement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Return\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    this->expr.generateJson(s);
    s.append("\n]\n");
    
    s.append("}");
}

void NReturnVoidStatement::generateJson(string &s) {
    stringstream ss;
    string temp;
    s.append("\n{\n");
    
    ss<<this->lineno;
    ss>>temp;
    s.append("\"name\" : \"" + temp + "-Node's name\",\n");
    
    s.append("\"value\" : \" \",\n");
    
    s.append("\"children\" : \n[");
    s.append("\n]\n");
    
    s.append("}");
}