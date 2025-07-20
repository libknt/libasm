; helloworld_macos.s
;
; 64-bit "Hello, world!" for macOS.
; Assembled with NASM using Intel syntax.

section .data
    hello_msg db 'Hello, world!', 0xa   ; The string to print (0xa is newline)
    hello_len equ $ - hello_msg         ; The length of the string

section .text
    global _main                        ; Entry point for macOS is _main

_main:
    ; --- sys_write syscall ---
    ; On macOS, syscall numbers are prefixed with 0x2000000
    mov rax, 0x2000004          ; macOS syscall number for write
    mov rdi, 1                  ; File descriptor 1 = stdout
    lea rsi, [rel hello_msg]    ; Address of the message to write (PIE-compliant)
    mov rdx, hello_len          ; Number of bytes to write
    syscall

    ; --- sys_exit syscall ---
    mov rax, 0x2000001          ; macOS syscall number for exit
    xor rdi, rdi                ; Exit code 0
    syscall