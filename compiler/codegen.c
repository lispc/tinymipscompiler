#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "mcc.h"
#include "mcc.tab.h"
static int lbl;
static int lbs,lbe;
#define TB_SIZE 200
extern arrayNode* append(oprNodeType*,arrayNode*);
extern int length(arrayNode*);
typedef struct {
  char* name;
  int size;
} symtb_entry;
static symtb_entry symtb[TB_SIZE];
//typedef symtb_entry* Symtb;
/*
typedef struct _stb_list {
  symtb_entry* tb;
  struct _stb_list* next;
} stb_list;
static stb_list* stb_head;*/
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
/*
void get_pos(char* s, int* pos, int* global){
  stb_list* p = stb_head;
  while(p){
    int local_pos = get_pos_impl(s, p->tb);
    if(local_pos!=-1){
*/      
    
int stack_size(){
  int pos=0;
  int i=0;
  while(i<TB_SIZE&&symtb[i].name)
    pos+=symtb[i++].size;
  return pos;
}
  
int get_pos(char* s)//,symtb_entry symtb)
{
  //p_symtb(s);
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
int ex(oprNodeType *p) {
  int templbs=lbs;
  int templbe=lbe;
  int lblx, lbly, lbl1, lbl2;
  int pos;
  char* name;
  arrayNode* pp;
  if (!p) return 0;
  switch(p->type) {
  case typeCon:   
  printf("\tpush\t%ld\n",(long)p->data);
  break;
  case typeId:
  pos = get_pos(p->data); 
  printf("\tpush\tsb[%d]\n", pos); 
  break;
  case typeArr:
  pp = p->data;
  while(pp){
    ex(pp->value);
    pp = pp->next;
  }
  break;
  case FOR:
  ex(p->op[0]);
  printf("L%03d:\n", lblx = lbl++);
  ex(p->op[1]);
  printf("\tj0\tL%03d\n", lbly = lbl++);
  lbs = lbl++;
  lbe = lbly;
  ex(p->op[3]);
  printf("L%03d:\n", lbs);
  ex(p->op[2]);
  printf("\tjmp\tL%03d\n", lblx);
  printf("L%03d:\n", lbly);
  break;
  case DO:
  ex(p->op[0]);
  printf("L%03d:\n", lbl1 = lbl++);
  ex(p->op[1]);
  printf("\tj0\tL%03d\n", lbl2 = lbl++);
  lbs=lbl1;
  lbe=lbl2;
  ex(p->op[0]);
  printf("\tjmp\tL%03d\n", lbl1);
  printf("L%03d:\n", lbl2);
  break;
  case WHILE:
    printf("L%03d:\n", lbl1 = lbl++);
    ex(p->op[0]);
    printf("\tj0\tL%03d\n", lbl2 = lbl++);
    lbs=lbl1;
    lbe=lbl2;
    ex(p->op[1]);
    printf("\tjmp\tL%03d\n", lbl1);
    printf("L%03d:\n", lbl2);
    break;
  case BREAK:
    printf("\tjmp\tL%03d\n", lbe);
    break;
  case CONTINUE:
    printf("\tjmp\tL%03d\n", lbs);
    break;
  case '{':
    lbl1 = stack_size();
    ex(p->op[0]);
    lbl2 = stack_size()-lbl1;
    while(lbl2--)
      printf("\tpop\tin\n");
    break;
  case IF:
    ex(p->op[0]);
    if (p->nops > 2) {
    /* if else */
    printf("\tj0\tL%03d\n", lbl1 = lbl++);
    ex(p->op[1]);
    printf("\tjmp\tL%03d\n", lbl2 = lbl++);
    printf("L%03d:\n", lbl1);
    ex(p->op[2]);
    printf("L%03d:\n", lbl2);
    } else {
    /* if */
    printf("\tj0\tL%03d\n", lbl1 = lbl++);
    ex(p->op[1]);
    printf("L%03d:\n", lbl1);
    }
    break;
  case READ:
    printf("\tread\n");
    name = p->op[0]->data;
    pos = get_pos(name);
    if(pos==-1)
      insert_to_symtb(name,1);
    else{
      printf("\tpop\tsb[%d]\n",pos);
    } 
  break;
  case PRINT:   
    ex(p->op[0]);
    printf("\tputi\n");
    break;
  case '[':
    ex(p->op[1]);
    pos = get_pos(p->op[0]->data);
    printf("\tpush\t%d\n",pos);
    printf("\tadd\n");
    printf("\tpop\tin\n");
    printf("\tpush\tsb[in]\n");
    break;
  case '=':
    name = p->op[0]->data;
    pos = get_pos(name);
    if(p->nops==3){
      assert(pos!=-1);
      ex(p->op[2]);
      ex(p->op[1]);
      printf("\tpush\t%d\n",pos);
      printf("\tadd\n");
      printf("\tpop\tin\n");
      printf("\tpop\tsb[in]\n");
    }else{
      ex(p->op[1]);
      if(p->op[1]->type==typeArr){
        assert(pos==-1);
        insert_to_symtb(name,length(p->op[1]->data));
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
    ex(p->op[0]);
    printf("\tneg\n");
    break;
  default:
    ex(p->op[0]);
    ex(p->op[1]);
    switch(p->type) {
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
  lbs=templbs;
  lbe=templbe;
  return 0;
}
void yyerror(char *s){
  fprintf(stdout, "%s\n", s);
}
oprNodeType* uniopr(int type, void* d){
  oprNodeType *p = (oprNodeType*) malloc(sizeof(oprNodeType));
  p->type = type;
  p->data = d;
  return p;
}
arrayNode* append(oprNodeType* val, arrayNode* xs) {
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
oprNodeType *opr(int oper, int nops, ...) {
  va_list ap;
  size_t nodeSize = sizeof(oprNodeType) + (nops - 1) * sizeof(oprNodeType*);
  oprNodeType *p = (oprNodeType*) malloc(nodeSize); 
  int i;
  p->type = oper;
  p->nops = nops;
  va_start(ap, nops);
  for (i = 0; i < nops; i++)
  p->op[i] = va_arg(ap, oprNodeType*);
  va_end(ap);
  return p;
}

void freeNode(oprNodeType *p) {
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
