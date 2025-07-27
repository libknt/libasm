section .text

%ifdef MACOS
global _ft_strdup
_ft_strdup:
extern _ft_strlen
extern _ft_strcpy
extern _malloc
extern ___error
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

    test rdi, rdi
    jz .error_null

    push rdi

%ifdef MACOS
    call _ft_strlen
%else
    call ft_strlen
%endif
    inc rax
    mov rdi, rax


.memory_allocation:

    sub rsp, 0x8

%ifdef MACOS
    call _malloc
%else
    call malloc
%endif
    test rax, rax
    jz .error

    pop rsi
    mov rdi, rax

%ifdef MACOS
    call _ft_strcpy
%else
    call ft_strcpy
%endif
    pop rax
    jmp .end_func

.error:
    pop rdi

    mov rdi, 12

%ifdef MACOS
    call ___error
%else
    call __errno_location
%endif

    mov [rax], edi
    xor rax, rax
    jmp .end_func

.error_null:
    mov rdi, 22

%ifdef MACOS
    call ___error
%else
    call __errno_location
%endif

    mov [rax], edi

    xor rax, rax


.end_func:
    pop rbp
    ret
