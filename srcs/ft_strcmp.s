; ----------------------------------------
; ft_strcmp.s
; ----------------------------------------
; manual: man strcmp
; ----------------------------------------

section .text

%ifdef MACOS
global _ft_strcmp
_ft_strcmp:
%else
global ft_strcmp
ft_strcmp:
%endif
    ; スタックフレームの設定
    push rbp                    ; 現在のベースポインタを保存
    mov rbp, rsp               ; 新しいスタックフレームを設定

.loop_start:
    ; 両方の文字列から1文字ずつ読み込み
    mov al, byte [rdi]         ; s1[i] を al レジスタに読み込み
    mov bl, byte [rsi]         ; s2[i] を bl レジスタに読み込み
    
    ; 文字を比較
    cmp al, bl                 ; s1[i] と s2[i] を比較
    jne .not_equal_chars       ; 文字が異なる場合は差を計算へジャンプ

    ; 両方の文字が同じ場合、null終端文字かどうかをチェック
    cmp al, 0                  ; 現在の文字が '\0' かどうか確認
    je .zero_strings           ; null文字なら文字列終端に到達（同じ文字列）

    ; まだ文字がある場合、次の文字へ進む
    inc rdi                    ; s1 のポインタを次の文字へ
    inc rsi                    ; s2 のポインタを次の文字へ
    jmp .loop_start            ; ループの先頭に戻る

.not_equal_chars:
    ; 文字が異なる場合の処理
    movzx rax, al              ; s1[i] を32ビットに拡張してraxに格納
    movzx rcx, bl              ; s2[i] を32ビットに拡張してrcxに格納

    ; 差を計算
    sub rax, rcx               ; s1[i] - s2[i] の差を計算
    jmp .end_func              ; 関数終了へ

.zero_strings:
    ; 両方の文字列が同じで終端に到達した場合
    xor rax, rax               ; rax = 0 (文字列が同じ)

.end_func:
    ; スタックフレームの復元
    pop rbp                    ; 元のベースポインタを復元
    ret                        ; 呼び出し元に戻る (戻り値はraxに格納済み)
