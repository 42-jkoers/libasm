section .text
	global _ft_strlen

; size_t	 ft_strlen(const char *s);
;			_ft_strlen(rdi)

_ft_strlen:
		mov		rax, -1				; rax = -1
loop:	inc		rax					; rax++
		mov		cl, byte [rdi+rax]	; cl = str[rax]
		cmp		cl, 0				; if cl == \0
		jne		loop				; then loop
		ret							; return rax
