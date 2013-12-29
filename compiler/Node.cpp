#include "mcc.h"
#include "mcc.tab.h"
long Node::lbs,Node::lbe,Node::lbl;
vector<symtb> Node::tb_list;
vector<func> Node::functb;
bool idebug = true;
lctn* Node::location(char* s)
{
  /*if(tb_list.size()==0){
    //initialize the global table
    tb_list.push_back(symtb(0,"sb"));
  }*/
  for(vector<symtb>::reverse_iterator itr = tb_list.rbegin(); itr!=tb_list.rend(); itr++){
    long pos = loc(s, itr->tb);
    for(auto it=itr->tb.begin();it!=itr->tb.end();it++){
      if(get<0>(*it)==s){
      lctn* output;
      output = new lctn();
      output->num = pos+(itr->start_pos);
      output->type = strdup(itr->type);
      output->vtype = get<1>(*it);
      return output;
      }
    }
  }
  return NULL;
}

long Node::stack_size()
{
  long sum = 0;
  for(vector<symtb>::iterator itr = tb_list.begin(); itr!=tb_list.end(); itr++){
    sum += loc(NULL,itr->tb);
  }
  return sum;
}
long Node::frame_size()
{
  return loc(NULL,tb_list.back().tb);
}
long Node::loc(char* s, vector<tuple<string,_Typename,long>> &tb)
{
  auto adder = [](const int i,const tuple<string,_Typename,long>& p){return i+get<2>(p);};
  auto equaler = [=](const tuple<string,_Typename,long>& p){return get<0>(p)==s;};
  if(!s)
    return accumulate(tb.begin(),tb.end(),0,adder);
  auto i = find_if(begin(tb),end(tb),equaler);
  if(i==tb.end()){
    return -1;
  }
  else{
    return accumulate(tb.begin(),i,0,adder);
  }
}

void Node::insert_to_tb(char* name,_Typename type,long size,vector<tuple<string,_Typename,long>> &tb)
{
    tb.push_back(make_tuple(name,type,size)); 
}

func Node::func_loc(char* s)
{
  auto equaler = [=](const func& f){return !strcmp(f.name,s);};
  auto entry = find_if(begin(functb),end(functb),equaler);
  return *entry;
}

void Node::insert_to_frtb(char* name,char* line,long param_num,vector<func> &tb)
{
    tb.push_back(func(name,line,param_num));
}

void _ex(Node *p) {
  if (!p) return; 
  else p->ex();
}
void Node::ex(){
  _ex(op[0]);
  _ex(op[1]);
  auto t1 = op[1]->ret;
  auto t2 = op[2]->ret;
  if(t1!=t2)
    cerr<<"binary operator with different types"<<endl;
  ret = t1;
  printf("\t%s\n",typeid(*this).name()+1);
}
void Constant::ex(){
  printf("\tpush\t%ld\n",d);
}
void Str::ex(){
  printf("\tpush\t\"%s\"\n",(char*)data);
}
void Chr::ex(){
  printf("\tpush\t\'%c\'\n",d);
}
void Identifier::ex(){
  lctn* l = location((char*)data);
  printf("\tpush\t%s[%d]\n", l->type, l->num); 
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
    long s = frame_size();
    tb_list.push_back(symtb(frame_size()+tb_list.back().start_pos,"fp"));
    _ex(op[0]);
    pop_stack(frame_size());
    tb_list.pop_back();
    if(idebug)cout<<"end block"<<endl;
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
    auto name = (char*)op[0]->data;
    lctn *l = location(name);
    if(l==NULL)
      cerr<<"input undeclared variable!"<<endl;
      //insert_to_tb(name,1,tb_list.back().tb);
    else{
      switch(l->vtype){
        case TINT:
          printf("\tgeti\n");
          break;
        case TCHR:
          printf("\tgetc\n");
          break;
        case TSTR:
          printf("\tgets\n");
        default:
          cerr<<"invalid type"<<endl;
      }
      printf("\tpop\t%s[%d]\n",l->type,l->num);
    } 
}
void Print::ex(){
    _ex(op[0]);
    switch (op[0]->ret){
      case TINT:
        printf("\tputi\n");
        break;
      case TCHR:
        printf("\tputc\n");
        break;
      case TSTR:
        printf("\tputs\n");
        break;
      default:
        cerr<<"invalid type"<<endl;
    }
}
void Index::ex(){
    _ex(op[1]);
    lctn *l = location((char*)op[0]->data);
    printf("\tpush\t%d\n",l->num);
    printf("\tadd\n");
    printf("\tpop\tin\n");
    printf("\tpush\t%s[in]\n",l->type);
}
void Assignment::ex(){
    _ex(op[1]);
    _ex(op[0]);
}
void ArrayLhs::ex(){
    auto name = (char*)op[0]->data;
    lctn *l = location(name);
    assert(l!=NULL);
    _ex(op[1]);
    printf("\tpush\t%d\n",l->num);
    printf("\tadd\n");
    printf("\tpop\tin\n");
    printf("\tpop\t%s[in]\n",l->type);
}
void Lhs::ex(){
    auto name = (char*)op[0]->data;
    lctn *l = location(name);
    if(l==NULL){
      cerr<<"assign value to undeclared variable"<<endl;
      //insert_to_tb(name,1,tb_list.back().tb);
    }else{
      printf("\tpop\t%s[%d]\n",l->type,l->num);
    }
}
void ArrayDecl::ex(){
    auto type = ((Type*)op[0])->d;
    auto name = (char*)op[1]->data;
    if(loc(name,tb_list.back().tb)!=-1)
      cerr<<"The variable has been declared already in the same scope!"<<endl;
    auto size = (long)op[2]->data;
    insert_to_tb(name,type,size,tb_list.back().tb);
    while(size--)
      printf("\tpush\t0\n");
}
void Decl::ex(){
	auto type = ((Type*)op[0])->d;
	auto name = (char*)op[1]->data;
    if(loc(name,tb_list.back().tb)!=-1)
      cerr<<"The variable has been declared already in the same scope!"<<endl;
    insert_to_tb(name,type,1,tb_list.back().tb);
    printf("\tpush\t0\n");
}
void Param::ex(){
  if(op[0]!=NULL)
    insert_to_tb((char*)op[1]->data,((Type*)op[0])->d,1,tb_list.back().tb);
}
void Params::ex(){
  op[0]->ex();
  insert_to_tb((char*)op[2]->data,((Type*)op[1])->d,1,tb_list.back().tb);
}
void Return::ex(){
  if(op[0] != NULL)
    op[0]->ex();
  printf("\tret\n");
}
void FuncDecl::ex(){
  long s = stack_size();
  tb_list.push_back(symtb(0,"fp"));
  long templbl = lbl++;
  printf("\tjmp\tL%03d\n",templbl);
  long templbl2 = lbl++;
  printf("L%03d:\n",templbl2);  
  char *line = (char*)malloc(5*sizeof(char));
  sprintf(line,"L%03d",templbl2);
  op[1]->ex();
  insert_to_tb("caller's sp",TVOID,1,tb_list.back().tb);
  insert_to_tb("caller's fp",TVOID,1,tb_list.back().tb);
  insert_to_tb("caller's pc",TVOID,1,tb_list.back().tb);
  long ss = s-stack_size();
  long sss = stack_size()-s-3;
  insert_to_frtb((char*)op[0]->data,line,sss,functb);
  tb_list.back().start_pos = ss;
  op[2]->ex();
  printf("L%03d:\n",templbl);
  tb_list.pop_back();
}
void Var::ex(){
  if(op[0]!=NULL)
    op[0]->ex();
}
void Vars::ex(){
  op[0]->ex();
  op[1]->ex();
}
void FuncCall::ex(){
  op[1]->ex();
  func f = func_loc((char*)op[0]->data);
  printf("\tcall %s, %d\n",f.line,f.param_num);
}
void Uminus::ex(){
    _ex(op[0]);
    if(op[0]->ret!=TINT){
      cerr<<"minus sign with wrong type"<<endl;
    }
    ret = TINT;
    printf("\tneg\n");
}
void Statements::ex(){
    op[0]->ex();
    op[1]->ex();
}
void Add::ex(){
  Node::ex();
}
void Sub::ex(){
  Node::ex();
}
void Mul::ex(){
  Node::ex();
}
void Div::ex(){
  Node::ex();
}
void Mod::ex(){
  Node::ex();
}
void CompLT::ex(){
  Node::ex();
}
void CompGT::ex(){
  Node::ex();
}
void CompNE::ex(){
  Node::ex();
}
void CompGE::ex(){
  Node::ex();
}
void CompLE::ex(){
  Node::ex();
}
void CompEQ::ex(){
  Node::ex();
}
void And::ex(){
  Node::ex();
}
void Or::ex(){
  Node::ex();
}
void Type::ex()
{
  Node::ex();
}
void yyerror(char* s)
{
  cerr<<s<<endl;
}
void pop_stack(int ss)
{
  printf("//ss=%d\n",ss);
  while(ss-->0)
    printf("\tpop\tin\n");
}

