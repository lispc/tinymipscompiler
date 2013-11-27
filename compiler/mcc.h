typedef enum { typeCon, typeId, typeOpr, typeArr/*, typeBlk*/ } nodeEnum;
/* constants */
typedef struct {
  int value;          /* value of constant */
} conNodeType;

/* identifiers */
typedef struct {
  char* name;            /* subscript to sym array */
} idNodeType;

typedef struct _arrayNode {
  struct nodeTypeTag* value;
  struct _arrayNode* next;
} arrayNode;

typedef struct {
  arrayNode* list_head;
} arrayNodeType; 
/* operators */
typedef struct {
  int oper;           /* operator */
  int nops;           /* number of operands */
  struct nodeTypeTag *op[1];  /* operands (expandable) */
} oprNodeType;
/*
typedef struct {
  struct nodeTypeTag* list_head;
} blockNodeType;
*/
typedef struct nodeTypeTag {
  nodeEnum type;        /* type of node */

  /* union must be last entry in nodeType */
  /* because operNodeType may dynamically increase */
  union {
    conNodeType con;    /* constants */
    idNodeType id;      /* identifiers */
    oprNodeType opr;    /* operators */
    arrayNodeType arr;
    //blockNodeType blk;
  };
} nodeType;

extern int sym[26];
