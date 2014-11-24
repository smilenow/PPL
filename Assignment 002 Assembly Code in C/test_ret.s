	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	leaq	L_.str(%rip), %rdi
	movl	$0, -4(%rbp)
	movl	$5, -8(%rbp)
	movl	-8(%rbp), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str1(%rip), %rdi
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %esi
	movb	$0, %al
	callq	_printf
	movl	$0, %esi
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	movl	%esi, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_x                      ## @x
	.align	2
_x:
	.long	3                       ## 0x3

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"x = %d"

L_.str1:                                ## @.str1
	.asciz	"ret = %d"


.subsections_via_symbols
