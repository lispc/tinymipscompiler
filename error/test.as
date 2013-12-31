//pushing 10 0s
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
//pushing 10 0s
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
//pushing 10 0s
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	push	0
	jmp	L000
L001:
	push	0
	push	fp[-6]
	pop	fp[0]
	push	0
	push	fp[-5]
	pop	fp[1]
	push	fp[-4]
	push	'i'
	CompEQ
	j0	L002
	push	0
	push	fp[-6]
	push	fp[-5]
	Add
	push	2
	Div
	push	0
	add
	pop	in
	push	sb[in]
	pop	fp[2]
L003:
	push	fp[0]
	push	fp[1]
	CompLE
	j0	L004
L005:
L006:
	push	fp[0]
	push	0
	add
	pop	in
	push	sb[in]
	push	fp[2]
	CompLT
	j0	L007
L008:
	push	fp[0]
	push	1
	Add
	pop	fp[0]
	jmp	L006
L007:
L009:
	push	fp[1]
	push	0
	add
	pop	in
	push	sb[in]
	push	fp[2]
	CompGT
	j0	L010
L011:
	push	fp[1]
	push	1
	Sub
	pop	fp[1]
	jmp	L009
L010:
	push	fp[0]
	push	fp[1]
	CompLE
	j0	L012
	push	0
	push	fp[0]
	push	0
	add
	pop	in
	push	sb[in]
	pop	fp[3]
	push	fp[1]
	push	0
	add
	pop	in
	push	sb[in]
	push	fp[0]
	push	0
	add
	pop	in
	pop	sb[in]
	push	fp[3]
	push	fp[1]
	push	0
	add
	pop	in
	pop	sb[in]
	push	fp[0]
	push	1
	Add
	pop	fp[0]
	push	fp[1]
	push	1
	Sub
	pop	fp[1]
//ss=1
	pop	in
//end block
L012:
//ss=0
//end block
	jmp	L003
L004:
//ss=1
	pop	in
//end block
	jmp	L013
L002:
	push	fp[-4]
	push	'c'
	CompEQ
	j0	L014
	push	0
	push	fp[-6]
	push	fp[-5]
	Add
	push	2
	Div
	push	10
	add
	pop	in
	push	sb[in]
	pop	fp[2]
L015:
	push	fp[0]
	push	fp[1]
	CompLE
	j0	L016
L017:
L018:
	push	fp[0]
	push	10
	add
	pop	in
	push	sb[in]
	push	fp[2]
	CompLT
	j0	L019
L020:
	push	fp[0]
	push	1
	Add
	pop	fp[0]
	jmp	L018
L019:
L021:
	push	fp[1]
	push	10
	add
	pop	in
	push	sb[in]
	push	fp[2]
	CompGT
	j0	L022
L023:
	push	fp[1]
	push	1
	Sub
	pop	fp[1]
	jmp	L021
L022:
	push	fp[0]
	push	fp[1]
	CompLE
	j0	L024
	push	0
	push	fp[0]
	push	10
	add
	pop	in
	push	sb[in]
	pop	fp[3]
	push	fp[1]
	push	10
	add
	pop	in
	push	sb[in]
	push	fp[0]
	push	10
	add
	pop	in
	pop	sb[in]
	push	fp[3]
	push	fp[1]
	push	10
	add
	pop	in
	pop	sb[in]
	push	fp[0]
	push	1
	Add
	pop	fp[0]
	push	fp[1]
	push	1
	Sub
	pop	fp[1]
//ss=1
	pop	in
//end block
L024:
//ss=0
//end block
	jmp	L015
L016:
//ss=1
	pop	in
//end block
	jmp	L025
L014:
	push	fp[-4]
	push	's'
	CompEQ
	j0	L026
	push	0
	push	fp[-6]
	push	fp[-5]
	Add
	push	2
	Div
	push	20
	add
	pop	in
	push	sb[in]
	pop	fp[2]
L027:
	push	fp[0]
	push	fp[1]
	CompLE
	j0	L028
L029:
L030:
	push	fp[0]
	push	20
	add
	pop	in
	push	sb[in]
	push	fp[2]
	sCompLT
	j0	L031
L032:
	push	fp[0]
	push	1
	Add
	pop	fp[0]
	jmp	L030
L031:
L033:
	push	fp[1]
	push	20
	add
	pop	in
	push	sb[in]
	push	fp[2]
	sCompGT
	j0	L034
L035:
	push	fp[1]
	push	1
	Sub
	pop	fp[1]
	jmp	L033
L034:
	push	fp[0]
	push	fp[1]
	CompLE
	j0	L036
	push	0
	push	fp[0]
	push	20
	add
	pop	in
	push	sb[in]
	pop	fp[3]
	push	fp[1]
	push	20
	add
	pop	in
	push	sb[in]
	push	fp[0]
	push	20
	add
	pop	in
	pop	sb[in]
	push	fp[3]
	push	fp[1]
	push	20
	add
	pop	in
	pop	sb[in]
	push	fp[0]
	push	1
	Add
	pop	fp[0]
	push	fp[1]
	push	1
	Sub
	pop	fp[1]
//ss=1
	pop	in
//end block
L036:
//ss=0
//end block
	jmp	L027
L028:
//ss=1
	pop	in
//end block
L026:
L025:
L013:
	push	fp[-6]
	push	fp[1]
	CompLT
	j0	L037
	push	fp[-6]
	push	fp[1]
	push	fp[-4]
	call L001, 3
//ss=0
//end block
L037:
	push	fp[-5]
	push	fp[0]
	CompGT
	j0	L038
	push	fp[0]
	push	fp[-5]
	push	fp[-4]
	call L001, 3
//ss=0
//end block
L038:
	push	0
	ret
L000:
	push	0
	push	"Please enter the type of elements you want to sort:"
	puts
	push	"(i for integer, c for character, s for string)"
	puts
	getc
	pop	sb[30]
	push	0
	gets
	pop	sb[31]
	push	0
	push	sb[30]
	push	'i'
	CompEQ
	j0	L039
	push	"Please enter 10 integers for sorting:"
	puts
	push	0
	pop	sb[32]
L040:
	push	sb[32]
	push	10
	CompLT
	j0	L041
	push	0
	geti
	pop	fp[33]
	push	fp[33]
	push	sb[32]
	push	0
	add
	pop	in
	pop	sb[in]
//ss=1
	pop	in
//end block
L042:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L040
L041:
	push	"originally:"
	puts
	push	0
	pop	sb[32]
L043:
	push	sb[32]
	push	10
	CompLT
	j0	L044
	push	sb[32]
	push	0
	add
	pop	in
	push	sb[in]
	puti
//ss=0
//end block
L045:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L043
L044:
	push	0
	push	9
	push	'i'
	call L001, 3
//ss=0
//end block
	push	"after sorting:"
	puts
	push	0
	pop	sb[32]
L046:
	push	sb[32]
	push	10
	CompLT
	j0	L047
	push	sb[32]
	push	0
	add
	pop	in
	push	sb[in]
	puti
//ss=0
//end block
L048:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L046
L047:
//ss=0
//end block
	jmp	L049
L039:
	push	sb[30]
	push	'c'
	CompEQ
	j0	L050
	push	"Please enter 10 characters for sorting:"
	puts
	push	0
	pop	sb[32]
L051:
	push	sb[32]
	push	10
	CompLT
	j0	L052
	push	0
	getc
	pop	fp[33]
	push	fp[33]
	push	'
'
	CompEQ
	j0	L054
	push	sb[32]
	push	1
	Sub
	pop	sb[32]
//ss=0
//end block
	jmp	L055
L054:
	push	fp[33]
	push	sb[32]
	push	10
	add
	pop	in
	pop	sb[in]
//ss=0
//end block
L055:
//ss=1
	pop	in
//end block
L053:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L051
L052:
	push	"originally:"
	puts
	push	0
	pop	sb[32]
L056:
	push	sb[32]
	push	10
	CompLT
	j0	L057
	push	sb[32]
	push	10
	add
	pop	in
	push	sb[in]
	putc
//ss=0
//end block
L058:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L056
L057:
	push	0
	push	9
	push	'c'
	call L001, 3
//ss=0
//end block
	push	"after sorting:"
	puts
	push	0
	pop	sb[32]
L059:
	push	sb[32]
	push	10
	CompLT
	j0	L060
	push	sb[32]
	push	10
	add
	pop	in
	push	sb[in]
	putc
//ss=0
//end block
L061:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L059
L060:
//ss=0
//end block
	jmp	L062
L050:
	push	sb[30]
	push	's'
	CompEQ
	j0	L063
	push	"Please enter 10 strings for sorting:"
	puts
	push	0
	pop	sb[32]
L064:
	push	sb[32]
	push	10
	CompLT
	j0	L065
	push	0
	gets
	pop	fp[33]
	push	fp[33]
	push	sb[32]
	push	20
	add
	pop	in
	pop	sb[in]
//ss=1
	pop	in
//end block
L066:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L064
L065:
	push	"originally:"
	puts
	push	0
	pop	sb[32]
L067:
	push	sb[32]
	push	10
	CompLT
	j0	L068
	push	sb[32]
	push	20
	add
	pop	in
	push	sb[in]
	puts
//ss=0
//end block
L069:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L067
L068:
	push	0
	push	9
	push	's'
	call L001, 3
//ss=0
//end block
	push	"after sorting:"
	puts
	push	0
	pop	sb[32]
L070:
	push	sb[32]
	push	10
	CompLT
	j0	L071
	push	sb[32]
	push	20
	add
	pop	in
	push	sb[in]
	puts
//ss=0
//end block
L072:
	push	sb[32]
	push	1
	Add
	pop	sb[32]
	jmp	L070
L071:
//ss=0
//end block
L063:
L062:
L049:
