%option noyywrap


%{
#include<stdio.h>
#include<iostream>
#include<string>
#include"node.h"
#include"parser.hpp"
using namespace std;

#define SAVE_TOKEN yylval.str = new string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
%}

%option yylineno
alpha       [a-zA-Z_]
digits      [0-9]
alnum       [a-zA-Z0-9_]

%%

"if"        { return TOKEN(IF); }
"else"      { return TOKEN(ELSE); }
"while"     { return TOKEN(WHILE); }
"break"     { return TOKEN(BREAK); }
"return"    { return TOKEN(RETURN); }

[ \t\n]                                                 ;
{alpha}({alnum}*)                                     { SAVE_TOKEN; return IDENTIFIER;}
({digits}+"."{digits}*)|({digits}*"."{digits}+)         { SAVE_TOKEN; return TFLOAT;}
([1-9]{digits}*)|[0]                                    { SAVE_TOKEN; return TINTEGER;}
\'.\'|\'\\.\'                                           { SAVE_TOKEN; return TCHAR;} // matches either a single character enclosed in single quotes or an escape sequence enclosed in single quotes
\"(\\.|[^"\\])*\"                                       { SAVE_TOKEN; return TSTRING;} //

"&&"            { return TOKEN(AND); }
"||"            { return TOKEN(OR); }
"<"             { return TOKEN(LET); }
">"             { return TOKEN(GT); }
"<="            { return TOKEN(LEQ); }
">="            { return TOKEN(GEQ); }
"=="            { return TOKEN(EQU); }
"!="            { return TOKEN(NEQ); }
";"             { return TOKEN(';'); }
"{"             { return TOKEN('{'); }
"}"             { return TOKEN('}'); }
","             { return TOKEN(','); }
":"             { return TOKEN(':'); }
"="             { return TOKEN('='); }
"("             { return TOKEN('('); }
")"             { return TOKEN(')'); }
"["             { return TOKEN('['); }
"]"             { return TOKEN(']'); }
"."             { return TOKEN('.'); }
"&"             { return TOKEN(GAD); }
"!"             { return TOKEN(NOT); }
"~"             { return TOKEN('~'); }
"-"             { return TOKEN(MINUS); }
"+"             { return TOKEN(PLUS); }
"*"             { return TOKEN(MUL); }
"/"             { return TOKEN(DIV); }
"%"             { return TOKEN('%'); }
"^"             { return TOKEN('^'); }
"|"             { return TOKEN('|'); }
"?"             { return TOKEN('?'); }



.               { printf("Unknown token: %s in line: %d\n", yytext, yylineno); }

%%