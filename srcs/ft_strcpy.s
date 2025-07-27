; ----------------------------------------
; ft_strcpy.s
; ----------------------------------------
; manual: man strcpy
; ----------------------------------------

section .text

%ifdef MACOS
global _ft_strcpy
_ft_strcpy:
%else
global ft_strcpy
ft_strcpy:
%endif
    ; スタックフレームの設定
    push rbp                    ; 現在のベースポインタを保存
    mov rbp, rsp               ; 新しいスタックフレームを設定
    mov rax, rdi               ; 戻り値用にdestination pointerを保存

    ; NULL pointer チェック (destination)
    cmp rdi, 0                 ; dest が NULL かどうか確認
    je .end_func               ; Jump if Equal

    ; NULL pointer チェック (source)
    cmp rsi, 0                 ; src が NULL かどうか確認
    je .end_func               ; Jump if Equal

.loop_start:
    ; 1文字をsrcからdestにコピー
    mov dl, byte [rsi]         ; src[i] を dl レジスタに読み込み
    mov byte [rdi], dl         ; dest[i] に dl の値を書き込み
    
    ; null終端文字かどうかをチェック
    cmp dl, 0                  ; コピーした文字が '\0' かどうか確認
    je .end_func               ; Jump if Equal
    
    ; 次の文字へ進む
    inc rdi                    ; dest のポインタを次の文字へ
    inc rsi                    ; src のポインタを次の文字へ
    jmp .loop_start            ; Jump to loop_start

.end_func:
    ; スタックフレームの復元
    pop rbp                    ; 元のベースポインタを復元
    ret                        ; 呼び出し元に戻る (戻り値はraxに格納済み)
