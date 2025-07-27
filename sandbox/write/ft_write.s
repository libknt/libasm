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

    mov rax, 1

    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

.end_func:
    pop rbp
    ret


; https://qiita.com/tsuzuki_takaaki/items/f15c8ea5d24cec0d5539
; https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit