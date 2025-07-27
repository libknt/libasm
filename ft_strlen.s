section .text

%ifdef MACOS
global _ft_strlen
_ft_strlen:
%else
global ft_strlen
ft_strlen:
%endif
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
