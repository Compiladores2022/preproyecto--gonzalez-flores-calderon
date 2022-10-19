	.globl	main
	.type	main, @function
main:
.LFB0:
ENTER $(8 * 4), $0
MOV $3, %r10
IMUL $5, %r10
MOV %r10, -8(%rbp)
MOV $1, %r10
ADD -8(%rbp), %r10
MOV %r10, -16(%rbp)
MOV $2, %r10
IMUL $2, %r10
MOV %r10, -24(%rbp)
MOV -16(%rbp), %r10
SUB -24(%rbp), %r10
MOV %r10, -32(%rbp)
LEAVE
RET
