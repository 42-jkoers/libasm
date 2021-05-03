section .text
	global _ft_read

; ssize_t	 ft_read(int fd, void *buf, size_t n);
; 			_ft_read(rdi, rsi, rdx)

_ft_read:
	mov rax, 0x2000003		; set call to read --> rax = read(...)
	syscall					; execute call
	jc exit_error			; if (error) goto exit_error
	ret						; return rax

exit_error:
	mov 	rax, -1			; rax = -1
	ret						; return rax
