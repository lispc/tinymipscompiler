%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mcc.h"


/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(char *s);
nodeType *con(int value);
nodeType *array(arrayNode *);
arrayNode *cons(nodeType*, arrayNode*);
arrayNode * append(nodeType*, arrayNode*);
//nodeType *array();
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];      /* symbol table */
%}

%union {
  int iValue;     /* integer value */
  char* vName;    /* symbol table index */
  nodeType *nPtr;     /* node pointer */
  arrayNode *aPtr;
};

%token <iValue> INTEGER
%token <vName> VARIABLE
%token FOR WHILE IF PRINT READ DO CONTINUE BREAK ARRAY
%nonassoc IFX
%nonassoc ELSE

%left AND OR

%left GE LE EQ NE '>' '<'
%left ','
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list array_literal
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
  | expr ';'         { $$ = $1; }
  | PRINT expr ';'     { $$ = opr(PRINT, 1, $2); }
  | READ VARIABLE ';'   { $$ = opr(READ, 1, id($2)); }
  | VARIABLE '=' expr ';'    { $$ = opr('=', 2, id($1), $3); }
  | VARIABLE '=' array_literal ';' { $$ = opr('=', 2, id($1), $3); }
  | VARIABLE '[' expr ']' '=' expr ';' { $$ = opr('=', 3, id($1), $3, $6); }
  | FOR '(' stmt stmt stmt ')' stmt { $$ = opr(FOR, 4, $3, $4,
$5, $7); }
  | DO stmt WHILE '(' expr ')' ';' { $$ = opr(DO,2,$2,$5);}
  | BREAK ';'         { $$ = opr(BREAK,0);}
  | CONTINUE  ';'       { $$ = opr(CONTINUE,0);}
  | WHILE '(' expr ')' stmt  { $$ = opr(WHILE, 2, $3, $5); }
  | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
  | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
  | '{' stmt_list '}'      { $$ = $2; }
  ;

stmt_list:
    stmt      { $$ = $1; }
  | stmt_list stmt  { $$ = opr(';', 2, $1, $2); }
  ;

array_literal:
    '[' elem_list ']' { $$ = array($2);}
  ;

elem_list:
    elem_list ',' INTEGER { $$ = append(con($3),$1); }
  | INTEGER          { $$ = append(con($1),NULL); }
  ;

expr:
    INTEGER       { $$ = con($1); }
  | VARIABLE '[' expr ']' { $$ = opr('[', 2, $1, $3); }
  | VARIABLE      { $$ = id($1); }
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

#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *con(int value) {
  nodeType *p;
  size_t nodeSize;

  /* allocate node */
  nodeSize = SIZEOF_NODETYPE + sizeof(conNodeType);
  if ((p = (nodeType*) malloc(nodeSize)) == NULL)
  yyerror("out of memory");

  /* copy information */
  p->type = typeCon;
  p->con.value = value;

  return p;
}

nodeType *array(arrayNode* aPtr) {
  nodeType *p;
  size_t nodeSize;
  nodeSize = SIZEOF_NODETYPE + sizeof(arrayNodeType);
  if ((p = (nodeType*) malloc(nodeSize)) == NULL)
  yyerror("out of memory");
  p->type = typeArr;
  p->arr.list_head = aPtr;
  return p;
}

arrayNode* cons(nodeType* val, arrayNode* xs) {
  arrayNode* p = (arrayNode*) malloc(sizeof(arrayNode));
  p->value = val;
  p->next = xs;
  return p;
}
arrayNode* append(nodeType* val, arrayNode* xs) {
  arrayNode *p, *p0;
  p = (arrayNode*) malloc(sizeof(arrayNode));
  p->value = val;
  p->next = NULL;
  if(!xs)
    return p;
  p0 = xs;
  while(p0->next){
    p0 = p0->next;
  }
  p0->next = p;
  return xs;
}
int length(arrayNode* xs){
  int l=0;
  while(xs){
    l++;
    xs = xs->next;
  }
  return l;
}
nodeType *id(char* s) {
  nodeType *p;
  size_t nodeSize;

  /* allocate node */
  nodeSize = SIZEOF_NODETYPE + sizeof(idNodeType);
  if ((p = (nodeType*) malloc(nodeSize)) == NULL)
  yyerror("out of memory");

  /* copy information */
  p->type = typeId;
  p->id.name = s;

  return p;
}

nodeType *opr(int oper, int nops, ...) {
  va_list ap;
  nodeType *p;
  size_t nodeSize;
  int i;

  /* allocate node */
  nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) +
  (nops - 1) * sizeof(nodeType*);
  if ((p = (nodeType*) malloc(nodeSize)) == NULL)
  yyerror("out of memory");

  /* copy information */
  p->type = typeOpr;
  p->opr.oper = oper;
  p->opr.nops = nops;
  va_start(ap, nops);
  for (i = 0; i < nops; i++)
  p->opr.op[i] = va_arg(ap, nodeType*);
  va_end(ap);
  return p;
}

void freeNode(nodeType *p) {
  /*
  int i;

  if (!p) return;
  if (p->type == typeOpr) {
  for (i = 0; i < p->opr.nops; i++)
    freeNode(p->opr.op[i]);
  }
  free (p);
  */
}

void yyerror(char *s) {
  fprintf(stdout, "%s\n", s);
}

int main(int argc, char **argv) {
  extern FILE* yyin;
  int yydebug=1;
  yyin = fopen(argv[1], "r");
  yyparse();
  return 0;
}
