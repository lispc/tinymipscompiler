mcc: mcc.c mcc.tab.c
	gcc -o mcc mcc.c mcc.tab.c

mcc.c: mcc.l
	flex -o mcc.c mcc.l

mcc.tab.c: mcc.y
	bison -d mcc.y

cleanmcc:
	$(RM) mcc.c mcc.tab.c mcc.tab.h mcc
