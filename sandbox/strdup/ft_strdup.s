section .text

%ifdef MACOS
global _ft_strdup
_ft_strdup:
%else
global ft_strdup
ft_strdup:
%endif
    push rbp
    mov rbp, rsp


.end_func:
    pop rbp
    ret
