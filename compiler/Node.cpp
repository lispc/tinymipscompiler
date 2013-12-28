#include "mcc.h"
#include "mcc.tab.h"
long Node::lbs,Node::lbe,Node::lbl;
vector<pair<string,long>> Node::symtb;
long Node::stack_loc(char* s)
{
  auto adder = [](const int i,const pair<string,long>& p){return i+p.second;};
  auto equaler = [=](const pair<string,long>& p){return p.first==s;};
  if(!s)
    return accumulate(symtb.begin(),symtb.end(),0,adder);
  auto i = find_if(begin(symtb),end(symtb),equaler);
  if(i==symtb.end())
    return -1;
  else 
    return accumulate(symtb.begin(),i,0,adder);
}
void Node::insert_to_symtb(char* name,long size)
{
  symtb.push_back(make_pair(name,size)); 
}
void _ex(Node *p) {
  if (!p) return; 
  else p->ex();
}
void Node::ex(){
  _ex(op[0]);
  _ex(op[1]);
  printf("\t%s\n",typeid(*this).name()+1);
}
void Constant::ex(){
  printf("\tpush\t%ld\n",(long)data);
}
void Identifier::ex(){
  printf("\tpush\tsb[%d]\n", stack_loc((char*)data)); 
}
void For::ex(){
  long templbs=lbs;
  long templbe=lbe;
  long lblx,lbly;
  _ex(op[0]);
  printf("L%03d:\n", lblx = lbl++);
  _ex(op[1]);
  printf("\tj0\tL%03d\n", lbly = lbl++);
  lbs = lbl++;
  lbe = lbly;
  _ex(op[3]);
  printf("L%03d:\n", lbs);
  _ex(op[2]);
  printf("\tjmp\tL%03d\n", lblx);
  printf("L%03d:\n", lbly);
  lbs=templbs;
  lbe=templbe;
}
void Break::ex(){
    printf("\tjmp\tL%03d\n", lbe);
}
void Continue::ex(){
    printf("\tjmp\tL%03d\n", lbs);
}
void Block::ex(){
    auto s = stack_loc(NULL);
    _ex(op[0]);
    auto ss = stack_loc(NULL)-s;
    while(ss--)
      printf("\tpop\tin\n");
}
void If::ex(){
    int lb1,lb2;
    _ex(op[0]);
    if (op.size() > 2) {
    printf("\tj0\tL%03d\n", lb1 = lbl++);
    _ex(op[1]);
    printf("\tjmp\tL%03d\n", lb2 = lbl++);
    printf("L%03d:\n", lb1);
    _ex(op[2]);
    printf("L%03d:\n", lb2);
    } else {
    printf("\tj0\tL%03d\n", lb1 = lbl++);
    _ex(op[1]);
    printf("L%03d:\n", lb1);
    }
}
void Read::ex(){
    printf("\tread\n");
    auto name = (char*)op[0]->data;
    auto pos = stack_loc(name);
    if(pos==-1)
      insert_to_symtb(name,1);
    else{
      printf("\tpop\tsb[%d]\n",pos);
    } 
}
void Print::ex(){
    _ex(op[0]);
    printf("\tputi\n");
}
void Index::ex(){
    _ex(op[1]);
    auto pos = stack_loc((char*)op[0]->data);
    printf("\tpush\t%d\n",pos);
    printf("\tadd\n");
    printf("\tpop\tin\n");
    printf("\tpush\tsb[in]\n");
}
void Assignment::ex(){
    _ex(op[1]);
    _ex(op[0]);
}
void ArrayLhs::ex(){
    auto name = (char*)op[0]->data;
    auto pos = stack_loc(name);
    assert(pos!=-1);
    _ex(op[1]);
    printf("\tpush\t%d\n",pos);
    printf("\tadd\n");
    printf("\tpop\tin\n");
    printf("\tpop\tsb[in]\n");
}
void Lhs::ex(){
    auto name = (char*)op[0]->data;
    auto pos = stack_loc(name);
    if(pos==-1){
      insert_to_symtb(name,1);
    }else{
      printf("\tpop\tsb[%d]\n",pos);
    }
}
void ArrayDecl::ex(){
    auto name = (char*)op[0]->data;
    assert(stack_loc(name)==-1);
    auto pos = (long)op[1]->data;
    insert_to_symtb(name,pos);
    while(pos--)
      printf("\tpush\t0\n");
}
void Uminus::ex(){
    _ex(op[0]);
    printf("\tneg\n");
}
void Statements::ex(){
    op[0]->ex();
    op[1]->ex();
}
void Bi_op::ex(){
    op[0]->ex();
    op[1]->ex();
    printf("\t%s\n",opname.c_str());
}
void yyerror(char* s)
{
  cerr<<s<<endl;
}
