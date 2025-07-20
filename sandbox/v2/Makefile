all:
	nasm -f macho64 hello.s -o hello.o
	ld -o hello hello.o -lSystem -syslibroot $(shell xcrun --show-sdk-path) -e _main -arch x86_64 -platform_version macos 11.0.0 11.0.0

clean:
	rm -f *.o

fclean: clean
	rm -f hello

re: fclean all