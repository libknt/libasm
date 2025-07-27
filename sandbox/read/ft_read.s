section .text

%ifdef MACOS
global _ft_read
_ft_read:
extern __error
%else
global ft_read
ft_read:
extern __errno_location
%endif
    push rbp
    mov rbp, rsp



.end_func:
    pop rbp
    ret
