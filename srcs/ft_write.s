; ----------------------------------------
; ft_write.s
; ----------------------------------------
; manual: man 2 write
; ----------------------------------------

section .text

%ifdef MACOS
global _ft_write
_ft_write:
extern ___error
    ; スタックフレームの設定
    push rbp                    ; 現在のベースポインタを保存
    mov rbp, rsp               ; 新しいスタックフレームを設定

    ; システムコール番号の設定
    mov rax, 0x2000004         ; macOS の write システムコール番号

    ; write システムコールを実行
    syscall                    ; システムコール実行 (fd=rdi, buf=rsi, count=rdx)
    jnc .end_func              ; Jump if not Carry flag set

.error:
    ; エラー処理
    mov edi, eax               ; errno（positive）

    ; errno の設定
    call ___error              ; __error() を呼び出し

    mov [rax], edi             ; errno にエラーコードを設定

    mov rax, -1                ; 戻り値 = -1 (エラー)

.end_func:
    ; スタックフレームの復元
    pop rbp                    ; 元のベースポインタを復元
    ret                        ; 呼び出し元に戻る (戻り値はraxに格納済み)

%else
global ft_write
ft_write:
extern __errno_location
    ; スタックフレームの設定
    push rbp                    ; 現在のベースポインタを保存
    mov rbp, rsp               ; 新しいスタックフレームを設定

    ; システムコール番号の設定
    mov rax, 1                 ; Linux の write システムコール番号

    ; write システムコールを実行
    syscall                    ; システムコール実行 (fd=rdi, buf=rsi, count=rdx)
    cmp rax, 0                 ; 戻り値が負の値かどうか確認
    jl .error                  ; Jump if Less than zero

.error:
    ; エラー処理
    neg rax                    ; Negate rax

    mov edi, eax               ; エラーコードを引数として設定

    ; errno の設定
    call __errno_location      ; __errno_location() を呼び出し

    mov [rax], edi             ; errno にエラーコードを設定

    mov rax, -1                ; 戻り値 = -1 (エラー)

.end_func:
    ; スタックフレームの復元
    pop rbp                    ; 元のベースポインタを復元
    ret                        ; 呼び出し元に戻る (戻り値はraxに格納済み)

%endif