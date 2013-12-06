%{
#include "mcc.h"
#include "Node.cpp"
extern void _ex(Node *p);
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
    function stmt   { _ex($2); }
  | /* NULL */
  ;

stmt:
    ';'        { $$ = NULL; }
  | expr ';'         { $$ = NULL; }
  | PRINT expr ';'     { $$ = new Print({$2}); }
  | READ VARIABLE ';'   { $$ = new Read({$2}); }
  | ARRAY VARIABLE '[' INTEGER ']' ';' { $$ = new ArrayDecl({$2,$4}); }
  | left '=' right ';' { $$ = new Assignment({$1,$3}); }
  | FOR '(' stmt expr ';' stmt ')' stmt { $$ = new For({$3, $4, $6, $8}); }
  | DO stmt WHILE '(' expr ')' ';' { $$ = new For({$2,$5,$2,NULL});}
  | BREAK ';'         { $$ = new Break();}
  | CONTINUE  ';'       { $$ = new Continue();}
  | WHILE '(' expr ')' stmt  { $$ = new For({NULL,$3, $5,NULL}); }
  | IF '(' expr ')' stmt %prec IFX { $$ = new If({$3, $5}); }
  | IF '(' expr ')' stmt ELSE stmt { $$ = new If({$3, $5, $7}); }
  | '{' stmt_list '}'      { $$ = new Block({$2}); }
  ;

left:
    VARIABLE { $$ = new Lhs({$1}); }
  | VARIABLE '[' expr ']' { $$ = new ArrayLhs({$1,$3}); }
  ;

right:
    expr
  ;

stmt_list:
    stmt      { $$ = $1; }
  | stmt_list stmt  { $$ = new Statements({$1, $2}); }
  ;


expr:
    INTEGER     
  | VARIABLE '[' expr ']' { $$ = new Index({$1,$3}); }
  | VARIABLE   
  | '-' expr %prec UMINUS { $$ = new Uminus({$2}); }
  | expr '+' expr   { $$ = new Add({$1,$3}); }
  | expr '-' expr   { $$ = new Sub({$1,$3}); }
  | expr '*' expr   { $$ = new Mul({$1,$3}); }
  | expr '%' expr   { $$ = new Mod({$1,$3}); }
  | expr '/' expr   { $$ = new Div({$1,$3}); }
  | expr '<' expr   { $$ = new CompLT({$1,$3}); }
  | expr '>' expr   { $$ = new CompGT({$1,$3}); }
  | expr GE expr    { $$ = new CompGE({$1,$3}); }
  | expr LE expr    { $$ = new CompLE({$1,$3}); }
  | expr NE expr    { $$ = new CompNE({$1,$3}); }
  | expr EQ expr    { $$ = new CompEQ({$1,$3}); }
  | expr AND expr  { $$ = new And({$1,$3}); }
  | expr OR expr  { $$ = new Or({$1,$3}); }
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
