	push	3
	pop	i
L000:
	push	i
	push	6
	compLT
	jz	L001
	push	0
	pop	j
L003:
	push	j
	push	i
	compLE
	jz	L004
	push	j
	puti
L005:
	push	j
	push	1
	add
	pop	j
	jmp	L003
L004:
L002:
	push	i
	push	1
	add
	pop	i
	jmp	L000
L001:
