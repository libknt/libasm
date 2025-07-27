# libasm

libasmは、標準Cライブラリの関数をx86-64アセンブリ言語で実装したプロジェクト

## アセンブリ言語とは？
アセンブリ言語は、コンピューターのCPUが直接理解する「機械語」を、人間が分かりやすいように記号で表した低水準プログラミング言語です。
コンピューターへの具体的な指示を出すために使われます。非常に高速なプログラムを作れますが、CPUの構造に詳しくないと書けず、読みにくいのが特徴です。
OSの起動部分や、特定のハードウェアを動かすプログラム、組込みシステムなどで使われます。

## 実装された関数

- `ft_strlen` - 文字列の長さを計算
- `ft_strcpy` - 文字列をコピー  
- `ft_strcmp` - 文字列を比較
- `ft_write` - ファイルディスクリプタに書き込み
- `ft_read` - ファイルディスクリプタから読み込み
- `ft_strdup` - 文字列を複製

## 64-bit アセンブリの特徴

> 参考: [Linux で64bitアセンブリプログラミング](https://www.mztn.org/lxasm64/amd00.html)

- **レジスタのビット数が64bitに倍増**
- **レジスタ本数が16本に倍増**
- **SSE2を標準搭載し、XMMレジスタの数が16個に倍増**
- **80386以降に追加された多くの命令(CMOVなど)が標準搭載**
- **オペランドサイズが64 ビットの時、即値は64 ビットに符号拡張される**
- **mov 命令は64ビット即値を64ビットレジスタに設定できる**

## 2種類の構文
> 参考: [x64 Assembly Language](https://ynitta.com/class/arch/pdf/x64.pdf)
- AT&T構文
	- レジスタ名の前に%をつける。
	- Operation Source Destination の順である。
	- レジスタ間接アドレッシングは、レジスタ名に"()"をつけて表現する。
- Intel構文
	- レジスタ名の前に%をつけない。
	- Operation Destination Source の順である。
	- レジスタ間接アドレッシングは、レジスタ名に"[]"をつけて表現する。

## PIE 非PIE
> 参考: [pie](https://jp.xlsoft.com/documents/intel/compiler/18/cpp_18_win_lin/GUID-EFCC2954-F3C9-4A85-A227-62B30A077109.html)
- 実行ファイルにリンクされる位置に依存しないコードを生成するかどうかを指定します。

### レジスタ
- **RAX, RBX, RCX, RDX**: 汎用レジスタ
- **RSI, RDI**: 文字列操作やシステムコール引数用
- **RSP**: スタックポインタ（現在のスタック位置）
- **RBP**: ベースポインタ（関数のローカル変数へのアクセス用）

### System V AMD64 呼び出し規約
```
引数の順序: RDI → RSI → RDX → RCX → R8 → R9 → スタック
戻り値: RAX（エラー時は負の値）
```

### エラーハンドリング
- システムコールが失敗すると負の値を返す
- `errno`の設定は別途必要（`__errno_location`を呼び出し）

### よく使われる命令
- **mov**: データ移動（代入）
- **cmp**: 比較（if文の条件）
- **je/jne**: 条件ジャンプ（equal/not equal）
- **call/ret**: 関数呼び出し/戻り
- **push/pop**: スタック操作

### メモリアドレッシング
```assembly
mov rax, [rbx]          ; *rbx (ポインタ参照)
mov rax, [rbx + 8]      ; *(rbx + 8) (配列アクセス)
lea rax, [rbx + 8]      ; &(rbx + 8) (アドレス計算)
```

### データサイズ指定子
メモリアクセス時にデータサイズを明示的に指定：
```assembly
mov al, byte [rdi]      ; *(char*)rdi - 1バイト読み取り
mov ax, word [rdi]      ; *(short*)rdi - 2バイト読み取り  
mov eax, dword [rdi]    ; *(int*)rdi - 4バイト読み取り
mov rax, qword [rdi]    ; *(long*)rdi - 8バイト読み取り
```

```c
// C言語との対応
char c = *(char*)ptr;           // byte [rdi]
short s = *(short*)ptr;         // word [rdi]  
int i = *(int*)ptr;             // dword [rdi]
long l = *(long*)ptr;           // qword [rdi]
```

### 文字列操作での使用例
```assembly
; 文字列の1文字ずつ処理 (ft_strlen等)
mov al, byte [rdi]      ; *str
cmp al, 0               ; if (*str == '\0')
je  end_of_string
inc rdi                 ; str++
jmp loop_start

; 配列アクセス
mov al, byte [rdi + 1]  ; str[1] 
mov bl, byte [rdi + 2]  ; str[2]
```

## CコンパイラによるC言語から機械語へのコンパイルの流れ
- [mermaid](https://mermaid.live/edit#pako:eNqlVF1L21AY_ivheFtL82HahCHY9BN2td2t9SJtUhtMkxJTpisFe3KholDHtu5iQ7Hb0La4DWTgmO7PnDXWf7GTk6zRC7e1DYE8532fj5yE8zZB2VRUIII1S65XqcdPigaFr5UCgtfIuULwO4IXHnD2HpWsZWl8tj0eHK1Si4vLVLI5On876nwan35wjw5vnTOP4Z7uu92dSanl-yWJQCr8ujy_7b4an5zddH56bH89uu6NrjqrPlUi1FTBfb992-6PDrrYJWilSCv9Py5pQs0UJm9_8_rY3T0MvTKEkH1gnwj2EPyBHFzqImcQ7NpXZokyV7jP6QfdHOnmcXfg1eElgqcIfkHOLnLeIHiC4EfkDMmX6h-7va--r6_dsLd0lVqhKpquiwuVSiWyYVvmuiousCwb4MXnmmJXRaa-GbE2xSXvseU97jokAwdFUf7qcFcjzZ2amiE1PXdqZobU7NypuRlS8zOm-h66Zqw_JT4xKlCXdLm8_kBkSKenozPT0dnp6Nx09KXp6Px09Pi_6MHfa5T84Th6d0FHWUoikwLfL8lZ7qP2EMFdBPeD4Yja-wjuTU43al-i9uf7miGuuN_aCB74Ed6laJZatjXTmAxhMohDmAyhFMJUCNMhzIQwG8JcCPM-VA0FRPDs1xQg2lZDjYCaatVkbwmaHqUI7KpaU4tAxFBRK3JDt4ugaLSwrC4bz0yz9kdpmY21KhArsr6BV426IttqSpPxt6tNqhYOVC3JbBg2EOm4QEyA2ASbQBSiAsMxtMDHeXqJp5l4BGwBMcFHOYHnYyyucXQsTrci4AVJjUUTNENzDB9jEizLMZzQ-g3gA5cD)


## 読んだ参考書
- [独習アセンブラ](https://www.shoeisha.co.jp/book/detail/9784798170299)

## 論理式

C言語の論理式・条件文とアセンブリでの実装方法の対応：

### ビット演算
```c
// C言語
int a = x & y;      // ビット論理積
int b = x | y;      // ビット論理和  
int c = x ^ y;      // ビット排他的論理和
int d = ~x;         // ビット反転
```

```assembly
; アセンブリ
and rax, rbx        ; rax = rax & rbx
or  rax, rbx        ; rax = rax | rbx
xor rax, rbx        ; rax = rax ^ rbx
not rax             ; rax = ~rax
```

### 条件分岐
```c
// C言語 if文
if (a == b) {
    // 処理
}
```

```assembly
; アセンブリ
cmp rax, rbx        ; a - b を計算（結果は保存せず、フラグのみ設定）
je  equal_label     ; ZF=1 なら equal_label へジャンプ
; else部分の処理
jmp end_label
equal_label:
; if部分の処理
end_label:
```

### フラグレジスタ
比較結果は以下のフラグで判定：
- **ZF (Zero Flag)**: 結果が0なら1（等しい場合）
- **CF (Carry Flag)**: 桁上がりで1（unsigned比較用）
- **SF (Sign Flag)**: 結果が負なら1（signed比較用）
- **OF (Overflow Flag)**: オーバーフロー時1

### 条件ジャンプ命令
```c
// C言語の比較演算子との対応
if (a == b)  // je  (Jump if Equal)
if (a != b)  // jne (Jump if Not Equal)
if (a < b)   // jl  (Jump if Less, signed)
if (a > b)   // jg  (Jump if Greater, signed)
if (a <= b)  // jle (Jump if Less or Equal, signed)
if (a >= b)  // jge (Jump if Greater or Equal, signed)
```

### 論理演算 (&&, ||)
```c
// C言語
if (a && b) { /* 処理 */ }
```

```assembly
; アセンブリ（短絡評価）
test rax, rax       ; a をテスト
jz   end_label      ; a が 0 なら終了
test rbx, rbx       ; b をテスト  
jz   end_label      ; b が 0 なら終了
; 両方とも真の場合の処理
end_label:
```

## その他
```asm
push rbp                    ; 現在のベースポインタを保存
mov rbp, rsp               ; 新しいスタックフレームを設定
...
pop rbp                    ; 元のベースポインタを復元
ret                        ; 呼び出し元に戻る (戻り値はraxに格納済み)
```