mcc: lex.yy.c mcc.tab.c mcc.c
	gcc -o mcc mcc.c mcc.tab.c lex.yy.c -lfl

lex.yy.c: mcc.l
	flex mcc.l

mcc.tab.c: mcc.y
	bison -d mcc.y

clean:
	$(RM) mcc.tab.c mcc.tab.h lex.yy.c mcc
