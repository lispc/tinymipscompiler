#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mcc.h"
#include "mcc.tab.h"

static int lbl;
static int lbs,lbe;
#define TB_SIZE 200
extern arrayNode* append(nodeType*,arrayNode*);
extern int length(arrayNode*);
typedef struct {
  char* name;
  int size;
} symtb_entry;
static symtb_entry symtb[TB_SIZE];
void p_symtb(char* s)
{
  symtb_entry* pp = symtb;
  while(pp->name)
  { 
    printf("%ld %s\n",pp-symtb,pp->name);
    pp++;
  }
  printf("looking %s\n",s);
}
int get_pos(char* s)
{
  int i=0;
  int pos=0;
  while(i<TB_SIZE)
  {
  if(!symtb[i].name)
  {
    return -1;
  }
  if(!strcmp(s,symtb[i].name))
    return pos;
  //check null?
  pos+=symtb[i++].size;
  }
  assert(1==0);
}
int insert_to_symtb(char* name,int size)
{
  symtb_entry* pp = symtb;
  while(pp->name)pp++;
  pp->name = name;
  pp->size = size;
  return get_pos(name);
}
int ex(nodeType *p) {
  int templbs=lbs;
  int templbe=lbe;
  int lblx, lbly, lbl1, lbl2;
  int pos;
  char* name;
  arrayNode* pp;
  if (!p) return 0;
  switch(p->type) {
  case typeCon:   
  printf("\tpush\t%d\n",p->con.value);
  break;
  case typeId:
  pos = get_pos(p->id.name); 
  printf("\tpush\tsb[%d]\n", pos); 
  break;
  case typeArr:
  pp = p->arr.list_head;
  while(pp){
    ex(pp->value);
    pp = pp->next;
  }
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
    pos = get_pos(name);
    if(pos==-1)
      insert_to_symtb(name,1);
    else{
      printf("\tpop\tsb[%d]\n",pos);
    } 
  break;
  case PRINT:   
    ex(p->opr.op[0]);
    printf("\tputi\n");
    break;
  case 
  case '=':
    name = p->opr.op[0]->id.name;
    pos = get_pos(name);
    if(p->opr.nops==3){
      assert(pos!=-1);
      ex(p->opr.op[2]);
      ex(p->opr.op[1]);
      printf("\tpush\t%d\n",pos);
      printf("\tadd\n");
      printf("\tpop\tin\n");
      printf("\tpop\tsb[in]\n");
    }else{
      ex(p->opr.op[1]);
      if(p->opr.op[1]->type==typeArr){
        assert(pos==-1);
        insert_to_symtb(name,length(p->opr.op[1]->arr.list_head));
      }else{
        if(pos==-1){
          insert_to_symtb(name,1);
        }else{
          printf("\tpop\tsb[%d]\n",pos);
        }
      }
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
