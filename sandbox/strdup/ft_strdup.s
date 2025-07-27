section .text

%ifdef MACOS
global _ft_strdup
_ft_strdup:
extern _ft_strlen
extern _ft_strcpy
extern _malloc

%else
global ft_strdup
ft_strdup:
extern ft_strlen
extern ft_strcpy
extern malloc
%endif
    push rbp
    mov rbp, rsp

    xor rax, rax

.memory_allocation:

    sub rsp, 0x8
    push rdi

    call ft_strlen
    mov rdi, rax
    inc rdi

    call malloc
    jc .error
    mov rdi, rax

    pop rsi
    call ft_strcpy

    jmp .end_func

.error:


.end_func:
    pop rbp
    ret
