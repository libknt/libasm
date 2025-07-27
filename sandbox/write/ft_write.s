section .text

%ifdef MACOS
global _ft_write
_ft_write:
extern ___error
%else
global ft_write
ft_write:
extern ___errno_location
%endif
    push rbp
    mov rbp, rsp

%ifdef MACOS
    mov rax, 0x2000004
%else
    mov rax, 1
%endif

    syscall
    
    jc .error

    jmp .success


.error
    mov rax, -1

.success
    mov rax, rdx

.end_func:
    pop rbp
    ret


; https://qiita.com/tsuzuki_takaaki/items/f15c8ea5d24cec0d5539
; https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit