	push	3
	pop	i
L000:
	push	i
	push	6
	compLT
	j0	L001
	push	i
	puti
L002:
	push	i
	push	1
	add
	pop	i
	jmp	L000
L001:
