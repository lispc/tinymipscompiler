%{
#include "mcc.h"
#include "Node.cpp"
#include <cstdio>
extern void _ex(Node *p);
extern int yylex();
extern void yyerror(char*);
%}
%token VARIABLE INTEGER CHR STR FOR WHILE IF PRINT READ DO CONTINUE BREAK ARRAY DEF RETURN TYPE 
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
  | function func_declare    { _ex($2); }
  | /* NULL */
  ;

func_declare:
  DEF TYPE VARIABLE '(' param_list ')' '{' stmt_list '}' { $$ = new FuncDecl({$2,$3, $5, $8}); }
  ;

param_list:
    TYPE VARIABLE  { $$ = new Param({$1,$2});}
  | param_list ',' TYPE VARIABLE  { $$ = new Params({$1,$3,$4});}
  | /*NULL*/  { $$ = new Param({NULL}); }
  ;

var_list:
    expr  { $$ = new Vars({$1});  }
  | var_list ',' expr  { $1->op.push_back($3); $$ = $1;  }
  | /*NULL*/  { $$ = new Vars();  }
  ;

stmt:
    ';'        { $$ = NULL; }
  | TYPE VARIABLE ';'  { $$ = new Decl({$1,$2}); }
  | TYPE VARIABLE '=' expr ';' { Node* t1 = new Decl({$1,$2}); Node* t2 = new Assignment({(new Lhs({$2})),$4}); $$ = new Statements({t1,t2}); }
  | expr ';'         { $$ = new Block({$1}); }
  | PRINT expr ';'     { $$ = new Print({$2}); }
  | READ VARIABLE ';'   { $$ = new Read({$2}); }
  | TYPE VARIABLE '[' INTEGER ']' ';' { $$ = new ArrayDecl({$1,$2,$4}); }
  | left '=' right ';' { $$ = new Assignment({$1,$3}); }
  | FOR '(' stmt expr ';' stmt ')' stmt { $$ = new For({$3, $4, $6, $8}); }
  | DO stmt WHILE '(' expr ')' ';' { $$ = new For({$2,$5,$2,NULL});}
  | BREAK ';'         { $$ = new Break();}
  | CONTINUE  ';'       { $$ = new Continue();}
  | RETURN  ';'        { $$ = new Return({NULL});}
  | RETURN expr ';'  { $$ = new Return({$2}); }
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
  | CHR
  | STR 
  | VARIABLE '[' expr ']' { $$ = new Index({$1,$3}); }
  | VARIABLE   
  | VARIABLE '(' var_list ')'    { $$ = new FuncCall({$1,$3});  }
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
  setbuf(stdout,NULL);
  setbuf(stderr,NULL);
  Node::tb_list.push_back(symtb(0,"sb"));
  yyparse();
  return 0;
}
