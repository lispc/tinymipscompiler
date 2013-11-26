typedef enum { typeCon, typeId, typeOpr, typeArr } nodeEnum;
struct nodeType;
/* constants */
typedef struct {
  int value;          /* value of constant */
} conNodeType;

/* identifiers */
typedef struct {
  char* name;            /* subscript to sym array */
} idNodeType;

typedef struct _arrayNode {
  nodeType* value;
  struct _arrayNode* next;
} arrayNode;

typedef struct arrayNodeType {
  arrayNode* list_head;
}
/* operators */
typedef struct {
  int oper;           /* operator */
  int nops;           /* number of operands */
  struct nodeTypeTag *op[1];  /* operands (expandable) */
} oprNodeType;

typedef struct nodeTypeTag {
  nodeEnum type;        /* type of node */

  /* union must be last entry in nodeType */
  /* because operNodeType may dynamically increase */
  union {
    conNodeType con;    /* constants */
    idNodeType id;      /* identifiers */
    oprNodeType opr;    /* operators */
    arrayNodeType arr;
  };
} nodeType;

extern int sym[26];
