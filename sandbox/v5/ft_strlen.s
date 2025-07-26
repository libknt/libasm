section .text
global ft_strlen

ft_strlen:
    push rbp
    mov rbp, rsp
    xor rax, rax

.loop_start:
    cmp  byte [rdi + rax], 0
    je .end_func
    inc rax
    jmp .loop_start

.end_func:
    pop rbp
    ret
