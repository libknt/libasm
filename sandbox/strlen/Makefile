# アセンブル
nasm -f macho64 ft_strlen.asm -o ft_strlen.o

# main.cをコンパイル
gcc -arch x86_64 -c main.c -o main.o

# 直接ldでリンク
ld -o my_strlen_nasm ft_strlen.o main.o -lSystem -syslibroot $(shell xcrun --show-sdk-path) -e _main -arch x86_64 -platform_version macos 11.0.0 11.0.0