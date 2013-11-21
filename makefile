cc=clang
cc=gcc
nas: nas.c nas.tab.c
	$(cc) -o nas nas.c nas.tab.c

nas.c: nas.l
	flex -o nas.c nas.l

nas.tab.c: nas.y
	bison -d nas.y
cleanas:
	$(RM) nas.c nas.tab.c nas.tab.h nas
