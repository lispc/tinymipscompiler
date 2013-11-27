	push 1
	call L000, 1
	jmp	L004
L000:
	push	fp[-4]
	push	6
	compLT
	j0	L001
	push	fp[-4]
	puti
	push	fp[-4]
	push 1
	call L002, 2
	push 	fp[-4]
	push	1
	add
	pop	fp[-4]
	jmp	L000
L002:
	push	fp[-4]
	push	fp[-5]
	compLT
	j0	L003
	push	fp[-4]
	puti
	push	fp[-4]
	push	1
	add
	pop	fp[-4]
	jmp	L002
L003:
	ret
L001:
	ret
L004:
