; ----------------------------------------
; ft_strdup.s
; ----------------------------------------
; manual: man strdup
; ----------------------------------------

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
    ; スタックフレームの設定
    push rbp                    ; 現在のベースポインタを保存
    mov rbp, rsp               ; 新しいスタックフレームを設定

    ; NULL pointer チェック
    test rdi, rdi              ; src が NULL かどうかテスト
    jz .error_null             ; Jump if Zero

    ; 文字列の長さを計算するため、src を保存
    push rdi                   ; src ポインタをスタックに保存

%ifdef MACOS
    call _ft_strlen            ; ft_strlen(src) を呼び出し
%else
    call ft_strlen             ; ft_strlen(src) を呼び出し
%endif
    inc rax                    ; 長さ + 1
    mov rdi, rax               ; malloc に渡すサイズを設定

.memory_allocation:
    ; スタックアライメントの調整
    mov r8, rsp                ; 現在のスタックポインタを保存
    and r8, 15                 ; 16バイト境界からのオフセットを計算
    sub rsp, r8                ; スタックを調整
    push r8                    ; オフセット値を保存

%ifdef MACOS
    call _malloc               ; malloc(size) を呼び出し
%else
    call malloc                ; malloc(size) を呼び出し
%endif

    ; スタックアライメントの復元
    pop r8                     ; オフセット値を復元
    add rsp, r8                ; スタックを元に戻す

    ; malloc の結果をチェック
    test rax, rax              ; malloc が成功したかテスト
    jz .error                  ; Jump if Zero

    ; strcpy の準備
    mov rdi, rax               ; dest = malloc で確保したメモリ
    pop rsi                    ; src = スタックから復元

    ; strcpy を実行するため rax (dest) を保存
    push rax                   ; 戻り値用に dest を保存

%ifdef MACOS
    call _ft_strcpy            ; ft_strcpy(dest, src) を呼び出し
%else
    call ft_strcpy             ; ft_strcpy(dest, src) を呼び出し
%endif
    pop rax                    ; 戻り値 (dest) を復元
    jmp .end_func              ; Jump to end_func

.error:
    ; malloc 失敗時の処理
    pop rdi                    ; スタックから src を削除

    mov rdi, 12                ; errno = ENOMEM (12)

%ifdef MACOS
    call ___error              ; __error() を呼び出し
%else
    call __errno_location      ; __errno_location() を呼び出し
%endif

    mov dword [rax], 12        ; errno に ENOMEM を設定
    xor rax, rax               ; 戻り値 = NULL
    jmp .end_func              ; Jump to end_func

.error_null:
    ; NULL pointer エラーの処理
    mov rdi, 22                ; errno = EINVAL (22)

%ifdef MACOS
    call ___error              ; __error() を呼び出し
%else
    call __errno_location      ; __errno_location() を呼び出し
%endif

    mov dword [rax], 22        ; errno に EINVAL を設定

    xor rax, rax               ; 戻り値 = NULL

.end_func:
    ; スタックフレームの復元
    pop rbp                    ; 元のベースポインタを復元
    ret                        ; 呼び出し元に戻る (戻り値はraxに格納済み)
