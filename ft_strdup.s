section .text
	extern _malloc
	extern _ft_strlen
	extern _ft_strcpy
	global _ft_strdup

; char		*ft_strdup(const char *s);
; 			_ft_strdup(rsi)

_ft_strdup:
	push	rdi
	call	_ft_strlen			; rax = ft_strlen()
	inc		rax
	mov		rdi, rax			; rdi = rax

	call	_malloc				; call malloc
	pop		rdi

	mov		rsi, rdi			; rsi = rdi
	mov		rdi, rax			; rdi = rax
	call	_ft_strcpy			; ft_strcpy(rsi, rdi)
	ret							; return rax