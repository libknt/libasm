# libasm

libasmは、標準Cライブラリの関数をx86-64アセンブリ言語で実装したプロジェクト

## アセンブリ言語とは？
アセンブリ言語は、コンピューターのCPUが直接理解する「機械語」を、人間が分かりやすいように記号で表した低水準プログラミング言語です。
コンピューターへの具体的な指示を出すために使われます。非常に高速なプログラムを作れますが、CPUの構造に詳しくないと書けず、読みにくいのが特徴です。
OSの起動部分や、特定のハードウェアを動かすプログラム、組込みシステムなどで使われます。

# refs
- [独習アセンブラ](https://www.shoeisha.co.jp/book/detail/9784798170299)
- [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [This file is a user guide to the GNU assembler as (GNU Binutils) version 2.45.](https://sourceware.org/binutils/docs/as/)
- [Linux System Call Table for x86 64](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)
- [https://ja.wikipedia.org/wiki/Netwide_Assembler](https://ja.wikipedia.org/wiki/Netwide_Assembler)
- [nasm github](https://github.com/netwide-assembler/nasm)
- [This is the project webpage for the Netwide Assembler (NASM)](https://www.nasm.us/)
- [NASM - The Netwide Assembler](https://www.nasm.us/xdoc/2.16.03/html/nasmdoc0.html)

## 実装された関数

- `ft_strlen` - 文字列の長さを計算
    - [man strlen](https://man7.org/linux/man-pages/man3/strlen.3.html)
- `ft_strcpy` - 文字列をコピー  
    - [man strcpy](https://man7.org/linux/man-pages/man3/strcpy.3p.html)
- `ft_strcmp` - 文字列を比較
    - [man strcmp](https://www.man7.org/linux/man-pages/man3/strcmp.3.html)
- `ft_write` - ファイルディスクリプタに書き込み
    - [man write](https://man7.org/linux/man-pages/man2/write.2.html)
- `ft_read` - ファイルディスクリプタから読み込み
    - [man read](https://man7.org/linux/man-pages/man2/read.2.html)
- `ft_strdup` - 文字列を複製
    - [man strdup](https://man7.org/linux/man-pages/man3/strdup.3.html)

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
スタックアライメント: 関数呼び出し時、RSPは16バイト境界に配置
```

### スタックアライメント
64ビットシステムでは、ライブラリ関数呼び出し前にスタックを16バイト境界に合わせる必要があります

```c
// C言語では自動的に処理される
char *ptr = malloc(100);    // コンパイラがアライメントを保証
```

```assembly
; アセンブリでは手動でアライメント調整が必要
; malloc()呼び出し前の準備
mov r8, rsp                ; 現在のスタックポインタを保存
and r8, 15                 ; 16バイト境界からのオフセットを計算
sub rsp, r8                ; スタックを16バイト境界に調整
push r8                    ; 元に戻すためオフセット値を保存

; malloc()呼び出し
call malloc

; スタックアライメントの復元
pop r8                     ; 保存したオフセット値を復元
add rsp, r8                ; 元のスタック位置に戻す
```

### 16バイト境界とは？
メモリアドレスが16の倍数になること

```
16バイト境界の例
0x7fff12345670  ✓ (16の倍数)
0x7fff12345680  ✓ (16の倍数)  
0x7fff12345690  ✓ (16の倍数)

16バイト境界ではない例
0x7fff12345671  ✗ (16の倍数 + 1)
0x7fff12345678  ✗ (16の倍数 + 8)
0x7fff1234567A  ✗ (16の倍数 + 10)
```

### なぜ16バイト境界が必要？
1. **CPU最適化**: 16バイト単位でデータを処理するよう設計
2. **ライブラリ要件**: malloc等の関数が16バイト境界を前提
3. **パフォーマンス**: 境界に合っていないと処理が遅くなる
4. **クラッシュ防止**: 一部の関数は境界違反でエラーになる

### 具体的な計算例
```assembly
; 現在のスタックポインタの例
RSP = 0x7fff12345678

; 16での余りを計算
0x7fff12345678 & 15 = 8    ; 16で割った余りが8

; 16バイト境界に調整
0x7fff12345678 - 8 = 0x7fff12345670  ; これで16の倍数

; 確認: 0x7fff12345670 ÷ 16 = 整数（余りなし）
```

### アライメント調整の流れ
```assembly
mov r8, rsp                ; r8 = 0x7fff12345678
and r8, 15                 ; r8 = 8 (余り)
sub rsp, r8                ; RSP = 0x7fff12345670 (16バイト境界)
push r8                    ; 8を保存（後で元に戻すため）

call malloc                ; 安全に呼び出し可能

pop r8                     ; r8 = 8
add rsp, r8                ; RSP = 0x7fff12345678 (元の位置)

### エラーハンドリング
- システムコールが失敗すると負の値を返す
- `errno`の設定は別途必要（`__errno_location`を呼び出し）

### システムコールとerrno
```c
// C言語
ssize_t result = read(fd, buffer, count);
if (result == -1) {
    // errno が自動的に設定される
    perror("read failed");
}
```

### システムコール番号
OS毎に異なるシステムコール番号：
```assembly
%ifdef MACOS
    mov rax, 0x2000003     ; macOS read
%else  
    mov rax, 0             ; Linux read
%endif

%ifdef MACOS
    mov rax, 0x2000004     ; macOS write  
%else
    mov rax, 1             ; Linux write
%endif
```

### errno設定の流れ
1. システムコールが失敗 → 負のエラーコードが返る
2. `neg rax` でエラーコードを正の値に変換  
3. `__errno_location()` で errno のアドレスを取得
4. そのアドレスにエラーコードを書き込み
5. 戻り値として -1 を返す

### よく使われる命令
- **mov**: データ移動（代入）
- **cmp**: 比較（if文の条件）
- **je/jne**: 条件ジャンプ（equal/not equal）
- **call/ret**: 関数呼び出し/戻り
- **push/pop**: スタック操作
- **movzx**: ゼロ拡張付きデータ移動（unsigned キャスト）
- **movsx**: 符号拡張付きデータ移動（signed キャスト）

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

### データ拡張命令（movzx/movsx）
小さいサイズから大きいサイズへの型変換：

```c
// C言語
unsigned char c = 0xFF;    // 255
unsigned int ui = c;       // 255 (ゼロ拡張)
signed char sc = -1;       // 0xFF (2の補数)
signed int si = sc;        // -1 (符号拡張)
```

```assembly
; アセンブリ
movzx eax, byte [rdi]      ; unsigned int = (unsigned int)unsigned_char
movsx eax, byte [rdi]      ; signed int = (signed int)signed_char

; 具体例
mov al, 0xFF               ; al = 255 (0xFF)
movzx eax, al              ; eax = 0x000000FF (255)
movsx eax, al              ; eax = 0xFFFFFFFF (-1, 符号拡張)
```

### 拡張のパターン
```assembly
movzx ax, bl               ; 8bit → 16bit (ゼロ拡張)
movzx eax, bl              ; 8bit → 32bit (ゼロ拡張)  
movzx rax, bl              ; 8bit → 64bit (ゼロ拡張)
movzx eax, bx              ; 16bit → 32bit (ゼロ拡張)

movsx ax, bl               ; 8bit → 16bit (符号拡張)
movsx eax, bl              ; 8bit → 32bit (符号拡張)
movsx rax, bl              ; 8bit → 64bit (符号拡張)
```

## CコンパイラによるC言語から機械語へのコンパイルの流れ
- [mermaid](https://mermaid.live/edit#pako:eNqlVF1L21AY_ivheFtL82HahCHY9BN2td2t9SJtUhtMkxJTpisFe3KholDHtu5iQ7Hb0La4DWTgmO7PnDXWf7GTk6zRC7e1DYE8532fj5yE8zZB2VRUIII1S65XqcdPigaFr5UCgtfIuULwO4IXHnD2HpWsZWl8tj0eHK1Si4vLVLI5On876nwan35wjw5vnTOP4Z7uu92dSanl-yWJQCr8ujy_7b4an5zddH56bH89uu6NrjqrPlUi1FTBfb992-6PDrrYJWilSCv9Py5pQs0UJm9_8_rY3T0MvTKEkH1gnwj2EPyBHFzqImcQ7NpXZokyV7jP6QfdHOnmcXfg1eElgqcIfkHOLnLeIHiC4EfkDMmX6h-7va--r6_dsLd0lVqhKpquiwuVSiWyYVvmuiousCwb4MXnmmJXRaa-GbE2xSXvseU97jokAwdFUf7qcFcjzZ2amiE1PXdqZobU7NypuRlS8zOm-h66Zqw_JT4xKlCXdLm8_kBkSKenozPT0dnp6Nx09KXp6Px09Pi_6MHfa5T84Th6d0FHWUoikwLfL8lZ7qP2EMFdBPeD4Yja-wjuTU43al-i9uf7miGuuN_aCB74Ed6laJZatjXTmAxhMohDmAyhFMJUCNMhzIQwG8JcCPM-VA0FRPDs1xQg2lZDjYCaatVkbwmaHqUI7KpaU4tAxFBRK3JDt4ugaLSwrC4bz0yz9kdpmY21KhArsr6BV426IttqSpPxt6tNqhYOVC3JbBg2EOm4QEyA2ASbQBSiAsMxtMDHeXqJp5l4BGwBMcFHOYHnYyyucXQsTrci4AVJjUUTNENzDB9jEizLMZzQ-g3gA5cD)


## 論理式

C言語の論理式・条件文とアセンブリでの実装方法の対応

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

### Carry Flag（CF）の詳細
Carry Flagは複数の用途で使用される重要なフラグ：

#### 1. 算術演算での桁上がり・桁下がり
```c
// C言語の例
unsigned char a = 200;
unsigned char b = 100;  
unsigned char sum = a + b;    // 300 → 44 (256でオーバーフロー)
// この時CFが1に設定される
```

```assembly
; アセンブリ
mov al, 200               ; al = 200
add al, 100               ; al = 44, CF = 1 (桁上がり発生)
jc overflow_occurred      ; CF=1 なら分岐
```

#### 2. システムコールのエラー判定
```assembly
; システムコール実行後
syscall                   ; システムコール実行
jc .error                 ; CF=1 ならエラー（多くのOSで使用）
```

#### 3. unsigned比較での使用
```assembly
; unsigned比較: a < b
cmp rax, rbx              ; rax - rbx を計算
jb  a_is_less             ; CF=1 なら rax < rbx (unsigned)
jc  a_is_less             ; 同じ意味（jbとjcは同じ）
```

#### 4. CFの状態変化例
```assembly
; 例1: 桁上がりなし
mov al, 50
add al, 30                ; al = 80, CF = 0

; 例2: 桁上がりあり  
mov al, 200
add al, 100               ; al = 44, CF = 1 (256 - 256 = 44)

; 例3: 比較での使用
mov rax, 5
cmp rax, 10               ; 5 - 10 = -5 (unsigned では借用発生)
                          ; CF = 1 (5 < 10 in unsigned)
```

#### 5. よく使うCF関連の条件ジャンプ
```assembly
jc   label                ; CF=1 なら分岐（Carry）
jnc  label                ; CF=0 なら分岐（No Carry）
jb   label                ; CF=1 なら分岐（Below, unsigned <）
jae  label                ; CF=0 なら分岐（Above or Equal, unsigned >=）
```

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