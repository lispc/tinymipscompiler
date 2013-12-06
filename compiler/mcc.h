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
#define YYSTYPE Node*
using namespace std;
typedef enum { typeCon=2000, typeId, typeOpr, typeArr, typeDA, typeRA, typeRV} nodeEnum;
class Node{
  public:
  int type;   
  void* data;
  vector<Node*> op;
  Node(int type, initializer_list<Node*> l):type(type),op(l){}
  Node(int type, void* d):type(type),data(d){}
};
#endif

