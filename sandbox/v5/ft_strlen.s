section .text
global _ft_strlen

_ft_strlen:
    push rbp
    mov rbp, rsp
    xor rax, rax

.loop_start:
    cmp  byte [rdi + rax]
    je .end_func
    inc rax
    jmp loop_start


.end_func:
    pop rbp
    ret
