#include "mcc.h"
#include "mcc.tab.h"
static long lbl;
static long lbs,lbe;
static vector<pair<string,long>> symtb;
long adder(const long t,const pair<string,long>& p)
{
  return t+p.second;
}
long stack_size(){
  return accumulate(symtb.begin(),symtb.end(),0,adder);
}
long get_pos(char* s)
{
  //show_tb(s);
  auto i = find_if(begin(symtb),end(symtb),[=](const pair<string,long>& p){return p.first==s;});
  if(i==symtb.end())
    return -1;
  else 
    return accumulate(symtb.begin(),i,0,adder);
}
long insert_to_symtb(char* name,long size)
{
  symtb.push_back(make_pair(name,size)); 
  return get_pos(name);
}
long ex(Node *p) {
  long templbs=lbs;
  long templbe=lbe;
  long lblx, lbly, lbl1, lbl2;
  long pos;
  char* name;
  if (!p) return 0;
  switch(p->type) {
  case typeCon:   
  printf("\tpush\t%ld\n",(long)p->data);
  break;
  case typeId:
  pos = get_pos((char*)p->data); 
  printf("\tpush\tsb[%d]\n", pos); 
  break;
  case typeArr:
  for_each(begin(*(vector<Node*>*)p->data),((vector<Node*>*)p->data)->end(),ex);
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
    if (p->op.size() > 2) {
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
    name = (char*)p->op[0]->data;
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
    pos = get_pos((char*)p->op[0]->data);
    printf("\tpush\t%d\n",pos);
    printf("\tadd\n");
    printf("\tpop\tin\n");
    printf("\tpush\tsb[in]\n");
    break;
  case '=':
    ex(p->op[1]);
    ex(p->op[0]);
    break;
  case typeRA:
    name = (char*)p->op[0]->data;
    pos = get_pos(name);
    assert(pos!=-1);
    ex(p->op[1]);
    printf("\tpush\t%d\n",pos);
    printf("\tadd\n");
    printf("\tpop\tin\n");
    printf("\tpop\tsb[in]\n");
    break;
  case typeRV:
    name = (char*)p->op[0]->data;
    pos = get_pos(name);
    if(pos==-1){
      insert_to_symtb(name,1);
    }else{
      printf("\tpop\tsb[%d]\n",pos);
    }
    break;
  case typeDA:
    name = (char*)p->op[0]->data;
    assert(get_pos(name)==-1);
    pos = (long)p->op[1]->data;
    insert_to_symtb(name,pos);
    while(pos--)
      printf("\tpush\t0\n");
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
void yyerror(char* s)
{
  cerr<<s<<endl;
}
