section .text

%ifdef MACOS
global _ft_strcpy
_ft_strcpy:
%else
global ft_strcpy
ft_strcpy:
%endif
    push rbp
    mov rbp, rsp


.loop_start:
    mov al, byte [rdi]
    cmp al, byte [rsi]
    jne .not_equal_chars

    cmp al, 0
    jmp .end_func

    inc rdi
    inc rsi
    jmp .loop_start

.not_equal_chars:
    movzx rax, byte [rdi]
    movzx rcx, byte [rsi]

    sub rax, rcx


.end_func:
    pop rbp
    ret
