global atomic_flag_test_and_set
global atomic_flag_clear

section .text

; _Bool atomic_flag_test_and_set(const atomic_flag* flag)
atomic_flag_test_and_set
	mov al, 1
	xchg [rdi], al
	ret

; void atomic_flag_clear(atomic_flag* flag)
atomic_flag_clear
	mov al, 0
	xchg [rdi], al
	ret
