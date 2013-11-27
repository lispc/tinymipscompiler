	push	3
	push	0
L000:
	push	sb[1]
	push	6
	compLT
	j0	L001
	push	sb[1]
	push	1
	add
	push	sb[1]
	push	0
	add
	pop	in
	pop	sb[in]
L002:
	push	sb[1]
	push	1
	add
	pop	sb[1]
	jmp	L000
L001:
	push	0
	pop	sb[1]
L003:
	push	sb[1]
	push	6
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
