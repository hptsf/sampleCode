	.file	"switchcase.c"
	.text
	.section	.rodata
.LC0:
	.string	"Usage: cmd param[a|b|c|d]\n"
.LC1:
	.string	"get param [a]\n"
.LC2:
	.string	"get param [b]\n"
.LC3:
	.string	"get param [c]\n"
.LC4:
	.string	"get param [d]\n"
.LC5:
	.string	"Invalid param\n"
.LC6:
	.string	"Will exit\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movb	$0, -1(%rbp)
	cmpl	$2, -20(%rbp)
	je	.L2
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$26, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	movl	$0, %eax
	jmp	.L3
.L2:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$98, %eax
	je	.L5
	cmpl	$98, %eax
	jg	.L6
	cmpl	$97, %eax
	je	.L7
	jmp	.L4
.L6:
	cmpl	$99, %eax
	je	.L8
	cmpl	$100, %eax
	je	.L9
	jmp	.L4
.L7:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$14, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rdi
	call	fwrite@PLT
	jmp	.L10
.L5:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$14, %edx
	movl	$1, %esi
	leaq	.LC2(%rip), %rdi
	call	fwrite@PLT
	jmp	.L10
.L8:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$14, %edx
	movl	$1, %esi
	leaq	.LC3(%rip), %rdi
	call	fwrite@PLT
	jmp	.L10
.L9:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$14, %edx
	movl	$1, %esi
	leaq	.LC4(%rip), %rdi
	call	fwrite@PLT
	jmp	.L10
.L4:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$14, %edx
	movl	$1, %esi
	leaq	.LC5(%rip), %rdi
	call	fwrite@PLT
	nop
.L10:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$10, %edx
	movl	$1, %esi
	leaq	.LC6(%rip), %rdi
	call	fwrite@PLT
	movl	$0, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
