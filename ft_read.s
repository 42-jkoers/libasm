section .text
	global _ft_read
	extern ___error

; ssize_t	 ft_read(int fd, void *buf, size_t n);
; 			_ft_read(rdi, rsi, rdx)

_ft_read:
	mov rax, 0x2000003		; set call to read --> rax = read(...)
	syscall					; execute call
	jc exit_error			; if (error) goto exit_error
	ret						; return rax

exit_error:
							; rax = some error code
 	mov r8, rax				; save errno
	push r8
	call ___error			; rax = pointer to errno
	mov	[rax], r8			; *rax = r8
	mov rax, -1				; rax = -1
	pop r8
	ret						; return rax
