.section __TEXT,__text,regular,pure_instructions
.global _ft_strcpy
.align 2

_ft_strcpy:
    // プロローグ
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    
    // x0 = dst, x1 = src
    // 戻り値用にdstを保存
    mov x2, x0
    
loop:
    // src[offset]を1バイト読み込み
    ldrb w3, [x1], #1
    // dst[offset]に1バイト書き込み
    strb w3, [x0], #1
    // null terminatorチェック
    cbz w3, end
    // ループ継続
    b loop
    
end:
    // 戻り値にdstのポインタを設定
    mov x0, x2
    
    // エピローグ
    ldp x29, x30, [sp], #16
    ret 