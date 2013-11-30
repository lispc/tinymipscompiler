%option 
%{
#include <stdlib.h>
#include <string.h>
#include "mcc.h"
#include "mcc.tab.h"
%}

%%

0           {
                yylval.nPtr = uniopr(typeCon,(void*)atol(yytext));
                return INTEGER;
            }

[1-9][0-9]* {
                yylval.nPtr = uniopr(typeCon,(void*)atol(yytext));
                return INTEGER;
            }

[-\[\]()<>=+*/;{}.%,] {
                return *yytext;
             }

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"for"           return FOR;
"do"            return DO;
"break"         return BREAK;
"continue"      return CONTINUE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"read"          return READ;
"&&"            return AND;
"||"            return OR;
"Array"         return ARRAY;
[a-zA-Z_][a-zA-Z0-9]*  { 
                yylval.nPtr = uniopr(typeId,strdup(yytext));
                return VARIABLE;
            }


\/\/.*\n        ;  /* skip comments */

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
