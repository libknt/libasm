section .text

%ifdef MACOS
global _ft_write
_ft_write:
extern ___error
%else
global ft_write
ft_write:
extern __errno_location
%endif
    push rbp
    mov rbp, rsp

%ifdef MACOS
    mov rax, 0x2000004
%else
    mov rax, 1
%endif

    syscall

    cmp rax, 0
    jl .error
    
    jc .error

    jmp .success

.success:
    jmp .end_func

.error:
    neg rax

    mov rdi, rax

%ifdef MACOS
    call ___error
%else
    call __errno_location
%endif

    mov [rax], dword rdi

    mov rax, -1


.end_func:
    pop rbp
    ret


; https://qiita.com/tsuzuki_takaaki/items/f15c8ea5d24cec0d5539
; https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit