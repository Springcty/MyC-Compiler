%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<iostream>
    #include"node.h"
    using namespace std;

    NBlock *programBlock; // the top level root node of our final AST
    extern int yylex();
    extern int yylineno;
    void yyerror(const char *s) {
        printf("ERROR: %s\n", s);
    }
%}

// Represents the many different ways we can access our data
%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    NIdentifier *ident;
    NVariableDeclaration *val_decl;
    vector<NVariableDeclaration*> *var_list;
    vector<NExpression*> *exp_list;
    string *string;
    int tokens;
}

// Define terminal symbols (tokens) which match token.l lex file. 
// And we define the node type they represent.
%token <string> IDENTIFIER TINTEGER TFLOAT TCHAR TSTRING
%token <token> PLUS MINUS MUL DIV
%token <token> AND OR
%token <token> NOT GAD LE GT LEQ GEQ NEQ EQU
%token <token> IF ELSE WHILE BREAK RETURN

// user defined non-terminal
// The types refer to the %union declaration above.
// Ex: when we call an ident, we are calling NIdentifier*.
%type <ident> ident
%type <expr> const_value expr
%type <stmt> stmt var_decl func_decl
%type <var_list> func_decl_args
%type <exp_list> call_args
%type <block> program statements block
// %type <tokens> operator

// operator precedence for mathematical operators
%left PLUS MINUS MUL DIV
%left OR AND
%left EQU NEQ LE GT LEQ GEQ
%left '(' ')' '[' ']'
%right '!'

%start program

%%

program:
    statements { programBlock = $1;}
    ;

statements: 
    stmt { $$ = new NBlock(yylineno); $$->stmts.push_back($<stmt>1);}
    | statements stmt { $1->stmts.push_back($<stmt>2);}
    ;

block:
    '{' statements '}' { $$ = $2;}
    | '{' '}' { $$ = new NBlock(yylineno);}
    ;

stmt: 
    var_decl ';' 
    | func_decl
    | expr ';' { $$ = new NExpressionStatement(*$1, yylineno);}
    | IF '(' expr ')' block { $$ = new NIfStatement(*$3, *$5, yylineno);}
    | IF '(' expr ')' block ELSE block { $$ = new NIfElseStatement(*$3, *$5, *$7, yylineno);}
    | WHILE '(' expr ')' block { $$ = new NWhileStatement(*$3, *$5, yylineno);}
    | BREAK ';' { $$ = new NBreakStatement(yylineno);}
    | RETURN ';' { $$ = new NReturnVoidStatement(yylineno);}
    | RETURN expr ';' { $$ = new NReturnStatement(*$2, yylineno);}
    ;
    
var_decl:
    ident ident { $$ = new NVariableDeclaration(*$1, *$2, yylineno);} // int a;
    | ident ident '=' expr { $$ = new NVariableDeclaration(*$1, *$2, $4, yylineno);} // int a = b + 2;
    | ident ident '[' TINTEGER ']' { $$ = new NVariableDeclaration(*$1, *$2, $4, yylineno);} // int a[10]
    ;

func_decl:
    ident ident '(' func_decl_args ')' block { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6, yylineno); delete $4;} // int f(args){}
    ;

func_decl_args:
    /*no args*/ {$$ = new VariableList();} // no args
    | var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1);} // int a
    | func_decl_args ',' var_decl { $1->push_back($<var_decl>3);}       // int a, int b
    ;

ident:
    IDENTIFIER { $$ = new NIdentifier(*$1, yylineno); delete $1;}
    ;

const_value:
    TINTEGER { $$ = new NInteger(atol($1->c_str()), yylineno); delete $1;}
    | TFLOAT { $$ = new NFloat(atof($1->c_str())), yylineno); delete $1;}
    | TCHAR { $$ = new NChar(*$1, yylineno); delete $1;}
    | TSTRING { $$ = new NString(*$1, yylineno); delete $1};
    ;

expr:
    const_value // 12
    | expr PLUS expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr MINUS expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr MUL expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr DIV expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr EQU expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr LEQ expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr GEQ expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr NEQ expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr LE expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr GT expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr AND expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | expr OR expr { $$ = new NBinaryOperator($2, *$1, *$3, yylineno);} // a+2
    | '(' expr ')' { $$ = $2;} // (a+b)
    | ident '=' expr { $$ = new NAssignment(*$<ident>1, *$3, yylineno);} // a = a + 2
    | ident '(' ')' { $$ = NFunctionCall(*$1, yylineno);}
    | ident '(' call_args ')' { $$ = NFunctionCall(*$1, *$3, yylineno); delete $3;} // f(a, b)
    | ident { $<ident>$ = $1;} // a
    | ident '[' expr ']' { $$ = NArrayElement(*$1, *$3, yylineno);}
    | ident '[' expr ']' '=' expr { $$ = new NArrayElementAssign(*$1, *$3, *$6, yylineno);}
    | GAD ident { $$ = new NGetAddr(*$2, yylineno);}
    | GAD ident '[' expr ']' { $$ = new NGetArrayAddr(*$2, *$4, yylineno);}
    ;

call_args:
    /*no args*/ { $$ = new ExpressionList();}
    | expr { $$ = new ExpressionList(); $$->push_back($1);}
    | call_args ',' expr { $1->push_back($3);}
    ;

// operator:
//     '+' | '-' | '*' | '/' | '==' | '<=' | '>=' | '!=' | '<' | '>' | '||' | '&&'
//     ;

%%