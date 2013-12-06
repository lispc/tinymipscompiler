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
struct Add:Node{
  using Node::Node;
  void ex();
};
struct Sub:Node{
  using Node::Node;
  void ex();
};
struct Mul:Node{
  using Node::Node;
  void ex();
};
struct Div:Node{
  using Node::Node;
  void ex();
};
struct Mod:Node{
  using Node::Node;
  void ex();
};
struct CompLT:Node{
  using Node::Node;
  void ex();
};
struct CompGT:Node{
  using Node::Node;
  void ex();
};
struct CompNE:Node{
  using Node::Node;
  void ex();
};
struct CompGE:Node{
  using Node::Node;
  void ex();
};
struct CompLE:Node{
  using Node::Node;
  void ex();
};
struct CompEQ:Node{
  using Node::Node;
  void ex();
};
struct And:Node{
  using Node::Node;
  void ex();
};
struct Or:Node{
  using Node::Node;
  void ex();
};
#endif
