section .text
	global _ft_strcpy
	extern _ft_strlen

; char	 *ft_strcpy(char *dst, const char *src);
; 		_ft_strcpy(rdi, rsi)

_ft_strcpy:
		push 	rdi					; push rdi to stack
		mov 	rdi, rsi			; rdi = rsi
		call 	_ft_strlen 			; rax = ft_strlen(rdi)
		mov 	rcx, rax			; rcx = rax
		pop 	rdi					; get rdi from stack
		mov 	rax, rdi			; rax = rdi

		mov		r8, 0				; r8 = 0
paste:	mov		cl, byte [rsi + r8]	; cl = rsi[r8]
		mov		byte [rdi + r8], cl	; rdi[r8] = cl
		inc		r8					; r8++
		cmp		cl, 0
		jne		paste				; if (cl != 0) goto paste

		ret