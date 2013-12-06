#ifndef MCC_HEADER
#define MCC_HEADER
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <stdlib.h>
using namespace std;
typedef enum { typeCon=2000, typeId, typeOpr, typeArr/*, typeBlk*/ } nodeEnum;
typedef struct _Node{
  int type;           /* operator */
  int nops;  /* number of operands */
  void* data;
  struct _Node *op[1];  /* operands (expandable) */
} Node;
void freeNode(Node *p); 
void yyerror(char *s);
Node* uniopr(int type, void* d);
Node *opr(int oper, int nops, ...); 
#endif

