#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mcc.h"
#include "mcc.tab.h"

static int lbl;
static int lbs,lbe;
#define TB_SIZE 200
static char* symtb[TB_SIZE];
void p_symtb(char* s)
{
  char** pp = symtb;
  while(*pp)
  { 
    printf("%ld %s\n",pp-symtb,*pp);
    pp++;
  }
  printf("looking %s\n",s);
}
int get_index(char* s)
{
  int i=0;
  while(i<TB_SIZE)
  {
  if(!symtb[i])
  {
    return -1;
  }
  if(!strcmp(s,symtb[i]))
    return i;
  //check null?
  i++;
  }
  assert(1==0);
}
int insert_to_symtb(char* s)
{
  char** pp = symtb;
  while(*pp)pp++;
  *pp = s;
  return pp-symtb;
}
int ex(nodeType *p) {
  int templbs=lbs;
  int templbe=lbe;
  int lblx, lbly, lbl1, lbl2;
  int index;
  char* name;
  if (!p) return 0;
  switch(p->type) {
  case typeCon:   
  printf("\tpush\t%d\n",p->con.value);
  break;
  case typeId:
  index = get_index(p->id.name); 
  printf("\tpush\tsb[%d]\n", index); 
  break;
  case typeOpr:
  switch(p->opr.oper) {
  case FOR:
  ex(p->opr.op[0]);
  printf("L%03d:\n", lblx = lbl++);
  ex(p->opr.op[1]);
  printf("\tj0\tL%03d\n", lbly = lbl++);
  lbs = lbl++;
  lbe = lbly;
  ex(p->opr.op[3]);
  printf("L%03d:\n", lbs);
  ex(p->opr.op[2]);
  printf("\tjmp\tL%03d\n", lblx);
  printf("L%03d:\n", lbly);
  break;
  case DO:
  ex(p->opr.op[0]);
  printf("L%03d:\n", lbl1 = lbl++);

    ex(p->opr.op[1]);
    printf("\tj0\tL%03d\n", lbl2 = lbl++);
  lbs=lbl1;
  lbe=lbl2;
  ex(p->opr.op[0]);
  printf("\tjmp\tL%03d\n", lbl1);
  printf("L%03d:\n", lbl2);
    break;

  case WHILE:
    printf("L%03d:\n", lbl1 = lbl++);

    ex(p->opr.op[0]);
    printf("\tj0\tL%03d\n", lbl2 = lbl++);
    lbs=lbl1;
    lbe=lbl2;
    ex(p->opr.op[1]);
    printf("\tjmp\tL%03d\n", lbl1);
    printf("L%03d:\n", lbl2);
    break;
  case BREAK:
    printf("\tjmp\tL%03d\n", lbe);
    break;
  case CONTINUE:
    printf("\tjmp\tL%03d\n", lbs);
    break;
  case IF:
    ex(p->opr.op[0]);
    if (p->opr.nops > 2) {
    /* if else */
    printf("\tj0\tL%03d\n", lbl1 = lbl++);
    ex(p->opr.op[1]);
    printf("\tjmp\tL%03d\n", lbl2 = lbl++);
    printf("L%03d:\n", lbl1);
    ex(p->opr.op[2]);
    printf("L%03d:\n", lbl2);
    } else {
    /* if */
    printf("\tj0\tL%03d\n", lbl1 = lbl++);
    ex(p->opr.op[1]);
    printf("L%03d:\n", lbl1);
    }
    break;
  case READ:
  printf("\tread\n");
    name = p->opr.op[0]->id.name;
    index = get_index(name);
    if(index==-1)
      index = insert_to_symtb(name);
    //printf("\tpop\tsb[%d]\n",index); 
  break;
  case PRINT:   
    ex(p->opr.op[0]);
    printf("\tputi\n");
    break;
  case '=':
    name = p->opr.op[0]->id.name;
    index = get_index(name);
    if(index==-1)
    { 
      index = insert_to_symtb(name);
      ex(p->opr.op[1]);
    }
    else
    {
      ex(p->opr.op[1]);
      printf("\tpop\tsb[%d]\n", index);
    }
    break;
  case UMINUS:  
    ex(p->opr.op[0]);
    printf("\tneg\n");
    break;
  default:
    ex(p->opr.op[0]);
    ex(p->opr.op[1]);
    switch(p->opr.oper) {
    case '+':   printf("\tadd\n"); break;
    case '-':   printf("\tsub\n"); break; 
    case '*':   printf("\tmul\n"); break;
    case '/':   printf("\tdiv\n"); break;
    case '%':   printf("\tmod\n"); break;
    case '<':   printf("\tcompLT\n"); break;
    case '>':   printf("\tcompGT\n"); break;
    case GE:  printf("\tcompGE\n"); break;
    case LE:  printf("\tcompLE\n"); break;
    case NE:  printf("\tcompNE\n"); break;
    case EQ:  printf("\tcompEQ\n"); break;
    case AND:   printf("\tand\n"); break;
    case OR:  printf("\tor\n"); break;
    }
  }
  }
  lbs=templbs;
  lbe=templbe;
  return 0;
}
