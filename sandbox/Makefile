build:
	nasm -f macho64 hello.asm -o hello.o
	ld -o hello hello.o -lSystem -syslibroot $(xcrun --show-sdk-path) -e _main -arch x86_64 -platform_version macos 10.15.0 10.15.0 -no_pie
