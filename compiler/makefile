#CC=clang++ -Wno-write-strings -Wno-format -Wno-deprecated-register -std=c++11
CC=g++-mp-4.8 -std=c++11
mcc: mcc.y mcc.c Node.cpp mcc.h
	bison -d -t mcc.y && flex mcc.l && $(CC) -o mcc mcc.tab.c lex.yy.c -lfl
mcc.c: mcc.y
	
clean:
	$(RM) mcc.tab.c mcc.tab.h lex.yy.c mcc
