section .text

%ifdef MACOS
global _ft_strcmp
_ft_strcmp:
%else
global ft_strcmp
ft_strcmp:
%endif
    push rbp
    mov rbp, rsp


.loop_start:
    mov al, byte [rdi]
    mov bl, byte [rsi]
    cmp al, bl  
    jne .not_equal_chars

    cmp al, 0
    je .zero_strings

    inc rdi
    inc rsi
    jmp .loop_start

.not_equal_chars:
    movzx rax, al
    movzx rcx, bl

    sub rax, rcx
    jmp .end_func

.zero_strings
    xor rax, rax

.end_func:
    pop rbp
    ret
