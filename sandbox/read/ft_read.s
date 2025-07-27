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

%ifdef MACOS
    mov rax, 0x2000003
%else
    mov rax, 0
%endif

    syscall
    
    cmp rax, 0
    jl .error

    jc .error

    jmp .success

.success:
    mov rax, rdx

    jmp .end_func

.error:
    neg rax

    mov rdi, rax

%ifdef MACOS
    call __error
%else
    call __errno_location
%endif

    mov [rax], dword rdi

    mov rax, -1

.end_func:
    pop rbp
    ret
