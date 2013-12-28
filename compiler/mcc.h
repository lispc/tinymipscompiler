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
#include <initializer_list>
#include <stdlib.h>
#include <typeinfo>
#define YYSTYPE Node*
using namespace std;
struct Node{  
  void* data;
  vector<Node*> op;
  Node(){}
  Node(initializer_list<Node*> l):op(l){}
  Node(void* d):data(d){}
  virtual void ex();
  static long lbs,lbe,lbl;
  static vector<pair<string,long>> symtb;
  long stack_loc(char*);
  void insert_to_symtb(char*,long);
};
void _ex(Node*);
struct Constant:Node{
  using Node::Node;
  void ex();
};
struct Identifier:Node{
  using Node::Node;
  void ex();
}; 
struct For:Node{
  using Node::Node;
  void ex();
};
struct Break:Node{
  using Node::Node;
  void ex();
};
struct Continue:Node{
  using Node::Node;
  void ex();
};
struct Block:Node{
  using Node::Node;
  void ex();
};
struct If:Node{
  using Node::Node;
  void ex();
};
struct Read:Node{
  using Node::Node;
  void ex();
};
struct Print:Node{
  using Node::Node;
  void ex();
};
struct Index:Node{
  using Node::Node;
  void ex();
};
struct Assignment:Node{
  using Node::Node;
  void ex();
};
struct ArrayLhs:Node{
  using Node::Node;
  void ex();
};
struct Lhs:Node{
  using Node::Node;
  void ex();
};
struct ArrayDecl:Node{
  using Node::Node;
  void ex();
};
struct Uminus:Node{
  using Node::Node;
  void ex();
};
struct Statements:Node{
  using Node::Node;
  void ex();
};
struct Bi_op:Node{
  string opname;
  Bi_op(string s,initializer_list<Node*> l):opname(s),Node(l){}
  void ex();
};
#endif
