%option debug
%{
#include "mcc.h"
#include "mcc.tab.h"
extern void yyerror(char*);
char text[500];
%}

%x S

%%

0           {
                yylval = new Constant(atol(yytext));
                return INTEGER;
            }

[1-9][0-9]* {
                yylval = new Constant(atol(yytext));

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
"def"           return DEF;
"return"        return RETURN;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"read"          return READ;
"&&"            return AND;
"||"            return OR;
\"		{ BEGIN S; *text = 0; }
<S>[^"\\]*	{ strcat(text, yytext); }
<S>\"		{ yylval = new Str(strdup(text)); BEGIN 0; return STR; }
<S>\\\"		{ strcat(text, "\""); }
<S>\\n		{ strcat(text, "\n"); }
<S>\\t		{ strcat(text, "\t"); }
<S>\\		{ strcat(text, "\\"); }
'\\n'		{ yylval = new Chr('\n'); return CHR; }
'\\t'		{ yylval = new Chr('\t'); return CHR; }
'\\''		{ yylval = new Chr('\''); return CHR; }
''		    { yylval = new Chr('\0'); return CHR; }
'[^']'		{ yylval = new Chr(yytext[1]); return CHR; }
"int"           { yylval = new Type(TINT); return TYPE;}
"char"          { yylval = new Type(TCHR); return TYPE;}
"str"           { yylval = new Type(TSTR); return TYPE;}
[a-zA-Z_][a-zA-Z0-9]*  { 
                yylval = new Identifier(strdup(yytext));
                return VARIABLE;
            }


\/\/.*\n        ;  /* skip comments */

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
