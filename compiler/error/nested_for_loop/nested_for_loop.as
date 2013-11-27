	push	1
L000:
	push	sb[0]
	push	6
	compLT
	j0	L001
	push	sb[0]
	puti
	push	1
L003:
	push	sb[1]
	push	sb[0]
	compLT
	j0	L004
	push	sb[1]
	puti
L005:
	push	sb[1]
	push	1
	add
	pop	sb[1]
	jmp	L003
L004:
L002:
	push	sb[0]
	push	1
	add
	pop	sb[0]
	jmp	L000
L001:
