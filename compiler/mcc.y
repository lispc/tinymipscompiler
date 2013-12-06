%{
#include "mcc.h"
extern int ex(Node *p);
extern int yylex();
extern void yyerror(char*);
%}
%token VARIABLE INTEGER FOR WHILE IF PRINT READ DO CONTINUE BREAK ARRAY
%nonassoc IFX
%nonassoc ELSE
%left AND OR
%left GE LE EQ NE '>' '<'
%left ','
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%%

program:
  function    { exit(0); }
  ;

function:
    function stmt   { ex($2); }
  | /* NULL */
  ;

stmt:
    ';'        { $$ = NULL; }
  | expr ';'         { $$ = NULL; }
  | PRINT expr ';'     { $$ = new Node(PRINT, {$2}); }
  | READ VARIABLE ';'   { $$ = new Node(READ, {$2}); }
  | ARRAY VARIABLE '[' INTEGER ']' ';' { $$ = new Node(typeDA,{$2,$4}); }
  | left '=' right ';' { $$ = new Node('=',{$1,$3}); }
  | FOR '(' stmt expr ';' stmt ')' stmt { $$ = new Node(FOR, {$3, $4, $6, $8}); }
  | DO stmt WHILE '(' expr ')' ';' { $$ = new Node(DO,{$2,$5});}
  | BREAK ';'         { $$ = new Node(BREAK,0);}
  | CONTINUE  ';'       { $$ = new Node(CONTINUE,0);}
  | WHILE '(' expr ')' stmt  { $$ = new Node(WHILE, {$3, $5}); }
  | IF '(' expr ')' stmt %prec IFX { $$ = new Node(IF, {$3, $5}); }
  | IF '(' expr ')' stmt ELSE stmt { $$ = new Node(IF, {$3, $5, $7}); }
  | '{' stmt_list '}'      { $$ = new Node('{',{$2}); }
  ;

left:
    VARIABLE { $$ = new Node(typeRV,{$1}); }
  | VARIABLE '[' expr ']' { $$ = new Node(typeRA,{$1,$3}); }
  ;

right:
    expr
  ;

stmt_list:
    stmt      { $$ = $1; }
  | stmt_list stmt  { $$ = new Node(';',{$1, $2}); }
  ;


expr:
    INTEGER     
  | VARIABLE '[' expr ']' { $$ = new Node('[', {$1,$3}); }
  | VARIABLE   
  | '-' expr %prec UMINUS { $$ = new Node(UMINUS,{$2}); }
  | expr '+' expr   { $$ = new Node('+', {$1,$3}); }
  | expr '-' expr   { $$ = new Node('-', {$1,$3}); }
  | expr '*' expr   { $$ = new Node('*', {$1,$3}); }
  | expr '%' expr   { $$ = new Node('%', {$1,$3}); }
  | expr '/' expr   { $$ = new Node('/', {$1,$3}); }
  | expr '<' expr   { $$ = new Node('<', {$1,$3}); }
  | expr '>' expr   { $$ = new Node('>', {$1,$3}); }
  | expr GE expr    { $$ = new Node(GE, {$1,$3}); }
  | expr LE expr    { $$ = new Node(LE, {$1,$3}); }
  | expr NE expr    { $$ = new Node(NE, {$1,$3}); }
  | expr EQ expr    { $$ = new Node(EQ, {$1,$3}); }
  | expr AND expr  { $$ = new Node(AND, {$1,$3}); }
  | expr OR expr  { $$ = new Node(OR, {$1,$3}); }
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
