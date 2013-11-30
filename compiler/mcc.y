%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mcc.h"
int ex(Node *p);
int yylex(void);
void yyerror(char *s);
%}

%union {
  Node *nPtr;     /* node pointer */
  arrayNode *aPtr;
};

%token <nPtr> VARIABLE INTEGER
%token FOR WHILE IF PRINT READ DO CONTINUE BREAK ARRAY
%nonassoc IFX
%nonassoc ELSE

%left AND OR

%left GE LE EQ NE '>' '<'
%left ','
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list array_literal block
%type <aPtr> elem_list 

%%

program:
  function    { exit(0); }
  ;

function:
    function stmt   { ex($2); freeNode($2); }
  | /* NULL */
  ;

stmt:
    ';'        { $$ = opr(';', 2, NULL, NULL); }
  | expr ';'         { $$ = NULL; }
  | PRINT expr ';'     { $$ = opr(PRINT, 1, $2); }
  | READ VARIABLE ';'   { $$ = opr(READ, 1, $2); }
  | VARIABLE '=' expr ';'    { $$ = opr('=', 2, $1, $3); }
  | VARIABLE /*'[' ']'*/ '=' array_literal ';' { $$ = opr('=', 2, $1, $3); }/*, con($3); }*/
/*  | VARIABLE '[' INTEGER ']' '[' INTEGER ']' '=' array_literal ';' { $$ = */
  | VARIABLE '[' expr ']' '=' expr ';' { $$ = opr('=', 3, $1, $3, $6); }
  | FOR '(' stmt expr ';' stmt ')' stmt { $$ = opr(FOR, 4, $3, $4, $6, $8); }
  | DO stmt WHILE '(' expr ')' ';' { $$ = opr(DO,2,$2,$5);}
  | BREAK ';'         { $$ = opr(BREAK,0);}
  | CONTINUE  ';'       { $$ = opr(CONTINUE,0);}
  | WHILE '(' expr ')' stmt  { $$ = opr(WHILE, 2, $3, $5); }
  | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
  | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
  | block       { $$ = $1; }
  ;


block:
   '{' stmt_list '}'      { $$ = opr('{', 1, $2); }
  ;
stmt_list:
    stmt      { $$ = $1; }
  | stmt_list stmt  { $$ = opr(';', 2, $1, $2); }
  ;

array_literal:
    '[' elem_list ']' { $$ = uniopr(typeArr,$2);}
  ;

elem_list:
    elem_list ',' INTEGER { $$ = append($3,$1); }
  | INTEGER          { $$ = append($1,NULL); }
  ;

expr:
    INTEGER     
  | VARIABLE '[' expr ']' { $$ = opr('[', 2, $1, $3); }
  | VARIABLE   
  | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
  | expr '+' expr   { $$ = opr('+', 2, $1, $3); }
  | expr '-' expr   { $$ = opr('-', 2, $1, $3); }
  | expr '*' expr   { $$ = opr('*', 2, $1, $3); }
  | expr '%' expr   { $$ = opr('%', 2, $1, $3); }
  | expr '/' expr   { $$ = opr('/', 2, $1, $3); }
  | expr '<' expr   { $$ = opr('<', 2, $1, $3); }
  | expr '>' expr   { $$ = opr('>', 2, $1, $3); }
  | expr GE expr    { $$ = opr(GE, 2, $1, $3); }
  | expr LE expr    { $$ = opr(LE, 2, $1, $3); }
  | expr NE expr    { $$ = opr(NE, 2, $1, $3); }
  | expr EQ expr    { $$ = opr(EQ, 2, $1, $3); }
  | expr AND expr  { $$ = opr(AND, 2, $1, $3); }
  | expr OR expr  { $$ = opr(OR, 2, $1, $3); }
  | '(' expr ')'    { $$ = $2; }
  ;

%%


int main(int argc, char **argv) {
  extern FILE* yyin;
  int yydebug=1;
  yyin = fopen(argv[1], "r");
  yyparse();
  return 0;
}
