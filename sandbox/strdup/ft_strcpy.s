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
    mov rax, rdi

    cmp rdi, 0
    je .end_func

    cmp rsi, 0
    je .end_func

.loop_start:
    mov dl, byte [rsi]
    mov byte [rdi], dl
    
    cmp dl, 0
    je .end_func
    
    inc rdi
    inc rsi
    jmp .loop_start

.end_func:
    pop rbp
    ret
