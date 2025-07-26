section .text
global ft_strcpy

ft_strcpy:
    push rbp
    mov rbp, rsp

    mov rax, rdi

    cmp rdi, 0
    je .end_func

    cmp rsi., 0
    je .end_func

.loop_start:
    mov al, byte [rsi]
    mov byte [rdi], al
    inc rsi
    inc rdi

    cmp rdi 0
    jnz loop_start

    je .end_func


.end_func:
    pop rbp
    ret
