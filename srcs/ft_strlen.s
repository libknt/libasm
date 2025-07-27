; ----------------------------------------
; ft_strlen.s
; ----------------------------------------
; manual: man strlen
; ----------------------------------------

section .text

%ifdef MACOS
global _ft_strlen
_ft_strlen:
%else
global ft_strlen
ft_strlen:
%endif
    ; スタックフレームの設定
    push rbp                    ; 現在のベースポインタを保存
    mov rbp, rsp               ; 新しいスタックフレームを設定
    
    ; カウンタの初期化
    xor rax, rax               ; rax = 0 (文字列の長さを数えるカウンタ)

.loop_start:
    ; 現在の文字が null終端文字 ('\0') かどうかをチェック
    cmp  byte [rdi + rax], 0   ; str[rax] と 0 を比較
    je .end_func               ; Jump if Equal
    
    ; まだ文字がある場合
    inc rax                    ; カウンタをインクリメント (rax++)
    jmp .loop_start            ; Jump to loop_start

.end_func:
    ; スタックフレームの復元
    pop rbp                    ; 元のベースポインタを復元
    ret                        ; 呼び出し元に戻る (戻り値はraxに格納済み)
