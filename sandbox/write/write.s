section .text

%ifdef MACOS
global _ft_write
_ft_write:
%else
global ft_write
ft_write:
%endif
    push rbp
    mov rbp, rsp

.end_func:
    pop rbp
    ret
