#ifndef _NODE_HEAD_
#define _NODE_HEAD_

#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>
using namespace std;

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef vector<NStatement*> StatementList;
typedef vector<NExpression*> ExpressionList;
typedef vector<NVariableDeclaration*> VariableList;

class Node
{
public:
    int lineno;

    Node(int lineno): lineno(lineno) {}
    virtual ~Node() {}
    virtual llvm::Value *CodeGen(CodeGenContext &context) {}
};

class NExpression : public Node
{
public:
    NExpression(int lineno): Node(lineno) {}
    virtual llvm::Value * GetAddr(CodeGenContext &context) {}
};

class NStatement : public Node
{
public:
    NStatement(int lineno): Node(lineno) {}
};

class NInteger : public NExpression
{
public:
    long long value;

    NInteger(long long value, int lineno): value(value), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NFloat : public NExpression
{
public:
    double value;

    NFloat(double value, int lineno): value(value), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NChar: public NExpression
{
public:
    string value;

    NChar(string &value, int lineno): value(value), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NString: public NExpression
{
public:
    string value;

    NString(string &value, int lineno): value(value), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
    llvm::Value *GetAddr(CodeGenContext &context);
};

class NIdentifier : public NExpression
{
public:
    string name;

    NIdentifier(const string &name, int lineno): name(name), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
    llvm::Value *GetAddr(CodeGenContext &context);
};

class NBinaryOperator : public NExpression
{
public:
    int op;
    NExpression &le;
    NExpression &re;
    NBinaryOperator(int op, NExpression &l, NExpression &r, int lineno): op(op), le(l), re(r), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NAssignment : public NExpression
{
public:
    NIdentifier &li;
    NIdentifier &ri;
    NAssignment(NIdentifier &l, NIdentifier &r, int lineno): li(l), ri(r), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NArrayElement: public NExpression
{
public:
    NIdentifier &ident;
    NExpression &idx;

    NArrayElement(NIdentifier &id, NExpression &idx, int lineno): ident(id), idx(idx), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
    llvm::Value *GetAddr(CodeGenContext &context);
};

class NArrayElementAssign: public NExpression
{
public:
    NIdentifier &ident;
    NExpression &idx;
    NExpression &re;
    
    NArrayElementAssign(NIdentifier &ident, NExpression &idx, NExpression &re, int lineno): ident(ident), idx(idx), re(re), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NFunctionCall: public NExpression
{
public:
    NIdentifier &ident;
    ExpressionList args;

    NFunctionCall(NIdentifier &ident, int lineno): ident(ident), NExpression(lineno) {}
    NFunctionCall(NIdentifier &ident, ExpressionList &args, int lineno): ident(ident), args(args), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NGetAddr: public NExpression
{
public:
    NIdentifier &re;

    NGetAddr(NIdentifier &re, int lineno): re(re), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NGetArrayAddr: public NExpression
{
public:
    NIdentifier &ident;
    NExpression &idx;

    NGetArrayAddr(NIdentifier &ident, NExpression &idx, int lineno): ident(ident), idx(idx), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NBlock : public NExpression
{
public:
    StatementList stmts;
    NBlock(int lineno): NExpression(lineno) {}
    NBlock(StatementList stmts, int lineno): stmts(stmts), NExpression(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NExpressionStatement : public NStatement
{
public:
    NExpression &expr;
    NExpressionStatement(NExpression &expr, int lineno): expr(expr), NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NVariableDeclaration : public NStatement
{
public:
    int size;
    const NIdentifier &type;
    NIdentifier &id;
    NExpression *assin_expr;

    NVariableDeclaration(const NIdentifier &type, NIdentifier &id, int lineno): type(type), id(id), NStatement(lineno) {}
    NVariableDeclaration(const NIdentifier &type, NIdentifier &id, NExpression *assin_expr, int lineno): type(type), id(id), assin_expr(assin_expr), NStatement(lineno) {}
    NVariableDeclaration(const NIdentifier &type, NIdentifier &id, int size, int lineno): type(type), id(id), size(size), NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NFunctionDeclaration : public NStatement
{
public:
    const NIdentifier &type;
    const NIdentifier &id;
    VariableList args;
    NBlock &block;
    NFunctionDeclaration(const NIdentifier &type, const NIdentifier &id, const VariableList &args, NBlock &block, int lineno): type(type), id(id), args(args), block(block), NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NBreakStatement: public NStatement
{
public:
    NBreakStatement(int lineno): NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NIfStatement: public NStatement
{
public:
    NExpression &expr;
    NBlock &if_blk;

    NIfStatement(NExpression &expr, NBlock &if_blk, int lineno): expr(expr), if_blk(if_blk), NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NIfElseStatement: public NStatement
{
public:
    NExpression &expr;
    NBlock &if_blk;
    NBlock &else_blk;

    NIfElseStatement(NExpression &expr, NBlock &if_blk, NBlock &else_blk, int lineno):
        expr(expr), if_blk(if_blk), else_blk(else_blk), NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NWhileStatement: public NStatement
{
public:
    NExpression &expr;
    NBlock &loop_blk;

    NWhileStatement(NExpression &expr, NBlock &loop_blk, int lineno): expr(expr), loop_blk(loop_blk), NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NReturnStatement: public NStatement
{
public:
    NExpression &expr;

    NReturnStatement(NExpression &expr, int lineno): expr(expr), NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

class NReturnVoidStatement: public NStatement
{
public:
    NReturnVoidStatement(int lineno): NStatement(lineno) {}
    llvm::Value *CodeGen(CodeGenContext &context);
};

#endif