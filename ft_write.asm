section .text
	global _ft_write

; ssize_t	 ft_write(int fd, const void *buf, size_t n);
; 			_ft_write (rdi, rsi, rdx)

_ft_write:
	mov r8, rdx				; r8 = rdx
	mov rax, 0x2000004		; set call to write
    syscall					; execute call
	jc exit_error			; if error goto to exit_error
	jmp exit				; goto exit

exit_error:
	mov rax, -1				; rax = -1
	ret						; return rax

exit:
	mov rax, r8				; rax = r8
	ret						; return rax
