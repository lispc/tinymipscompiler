CC=clang -Wno-write-strings
mcc: mcc.y mcc.c codegen.c mcc.h
	bison -d mcc.y && flex mcc.l && $(CC) -o mcc codegen.c mcc.tab.c lex.yy.c -lfl
mcc.c: mcc.y
	
clean:
	$(RM) mcc.tab.c mcc.tab.h lex.yy.c mcc
