#ifndef MCC_HEADER
#define MCC_HEADER
#include<stdlib.h>
typedef enum { typeCon=2000, typeId, typeOpr, typeArr/*, typeBlk*/ } nodeEnum;
typedef struct _arrayNode {
  struct _oprNodeType* value;
  struct _arrayNode* next;
} arrayNode;
typedef struct _oprNodeType{
  int type;           /* operator */
  int nops;  /* number of operands */
  void* data;
  struct _oprNodeType *op[1];  /* operands (expandable) */
} oprNodeType;
void freeNode(oprNodeType *p); 
void yyerror(char *s);
oprNodeType* uniopr(int type, void* d);
arrayNode* append(oprNodeType* val, arrayNode* xs); 
int length(arrayNode* xs);
oprNodeType *opr(int oper, int nops, ...); 
#endif
