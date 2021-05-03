section .text
	global _ft_strcmp

; int	 ft_strcmp(const char *s1, const char *s2);
; 		_ft_strcmp(rdi, rsi)

_ft_strcmp:
		mov 	rax, 0			; rax = 0
next:	mov		al, BYTE [rdi]	; al = *rdi
		mov		bl, BYTE [rsi]	; bl = *rsi

		cmp		al, 0
		je		exit			; if (al == 0) goto exit

		cmp		bl, 0
		je		exit			; if (bl == 0) goto exit

		cmp 	al, bl
		jne 	exit			; if (al != bl) goto exit

		inc 	rdi				; rdi++
		inc 	rsi				; rsi++
		jmp 	next			; goto next

exit:
	movzx	rax, al				; rax = al
    movzx	rbx, bl				; rbx = bl
    sub		rax, rbx			; rax = rax - rbx
	ret							; return rax
