section .text
	global _ft_write
	extern ___error

; ssize_t	 ft_write(int fd, const void *buf, size_t n);
; 			_ft_write (rdi, rsi, rdx)

_ft_write:
	mov r8, rdx				; r8 = rdx
	mov rax, 0x2000004		; set call to write
    syscall					; execute call
	jc exit_error			; if error goto to exit_error
	mov rax, r8				; rax = r8
	ret						; return rax

exit_error:
							; rax = some error code
 	mov r8, rax				; r8 = rax
	push r8
	call ___error			; rax = pointer to errno
	mov	[rax], r8			; *rax = r8
	mov rax, -1				; rax = -1
	pop r8
	ret						; return rax
