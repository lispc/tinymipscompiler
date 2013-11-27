	push	1
	push	2
	push	2
	push	3
	push	3
	push	3
	push	0
L000:
	push	sb[6]
	push	6
	compLT
	j0	L001
	push	sb[6]
	push	0
	add
	pop	in
	push	sb[in]
	puti
	push	sb[6]
	push	1
	add
	pop	sb[6]
	jmp	L000
L001:
	push	0
	pop	sb[6]
L002:
	push	sb[6]
	push	6
	compLT
	j0	L003
	push	sb[6]
	push	0
	add
	pop	in
	push	sb[in]
	push	1
	add
	push	sb[6]
	push	0
	add
	pop	in
	pop	sb[in]
	push	sb[6]
	push	1
	add
	pop	sb[6]
	jmp	L002
L003:
	push	0
	pop	sb[6]
L004:
	push	sb[6]
	push	6
	compLT
	j0	L005
	push	sb[6]
	push	0
	add
	pop	in
	push	sb[in]
	puti
	push	sb[6]
	push	1
	add
	pop	sb[6]
	jmp	L004
L005:
