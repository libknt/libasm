section .text

%ifdef MACOS
global _ft_strdup
_ft_strdup:
extern _ft_strlen
extern _ft_strcpy
extern _malloc
extern __error
%else
global ft_strdup
ft_strdup:
extern ft_strlen
extern ft_strcpy
extern malloc
extern __errno_location

%endif
    push rbp
    mov rbp, rsp

    xor rax, rax

.memory_allocation:

    sub rsp, 0x8
    push rdi

%ifdef MACOS
    call _ft_strlen
%else
    call ft_strlen
%endif
    mov rdi, rax
    inc rdi

%ifdef MACOS
    call _malloc
%else
    call malloc
%endif
    jz .error
    mov rdi, rax

    pop rsi
%ifdef MACOS
    call _ft_strcpy
%else
    call ft_strcpy
%endif

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

    mov rax, 0

.end_func:
    pop rbp
    ret
