#ifndef MCC_HEADER
#define MCC_HEADER
#include<stdlib.h>
typedef enum { typeCon=2000, typeId, typeOpr, typeArr/*, typeBlk*/ } nodeEnum;
typedef struct _arrayNode {
  struct _Node* value;
  struct _arrayNode* next;
} arrayNode;
typedef struct _Node{
  int type;           /* operator */
  int nops;  /* number of operands */
  void* data;
  struct _Node *op[1];  /* operands (expandable) */
} Node;
void freeNode(Node *p); 
void yyerror(char *s);
Node* uniopr(int type, void* d);
arrayNode* append(Node* val, arrayNode* xs); 
int length(arrayNode* xs);
Node *opr(int oper, int nops, ...); 
#endif
