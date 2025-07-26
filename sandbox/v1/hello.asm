; macOS x86-64 assembly with printf
; -------------------------------------

extern _printf   ; Cのprintf関数を外部シンボルとして宣言

section .data
    message db "Hello, world!", 0x0a, 0  ; 表示する文字列 (0x0aは改行、0は終端)

section .text
    global _main      ; リンカに公開するエントリーポイント(_main)

_main:
    ; --- printf呼び出しの準備 ---
    ; 第1引数 (RDI): 書式文字列のアドレス
    lea rdi, [rel message]
    
    ; 浮動小数点数の引数はないのでXMMレジスタをクリア
    xor rax, rax

    ; --- printfの呼び出し ---
    call _printf

    ; --- プログラムの終了 ---
    ; 戻り値 (RAX) を0にする
    xor rax, rax
    ret
    