NAME = libasm.a

SRCS = ft_strdup.s

OBJS = $(SRCS:.s=.o)

BONUS_OBJS = $(BOUNS_SRCS:.s=.o)

# OS detection for nasm format
UNAME_S := $(shell uname -s)

NASM = nasm

ifeq ($(UNAME_S),Linux)
	NASMFLAGS = -f elf64 -D LINUX
	CC = cc
	CFLAGS = -Wall -Wextra -Werror
else ifeq ($(UNAME_S),Darwin)
	NASMFLAGS = -f macho64 -D MACOS
	CC = cc
	CFLAGS = -Wall -Wextra -Werror -arch x86_64
	LDFLAGS = -lSystem -isysroot $(shell xcrun --show-sdk-path) -arch x86_64
endif

TEST_EXEC = test_strdup

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): test_strdup.c $(OBJS)
ifeq ($(UNAME_S),Darwin)
	$(CC) $(CFLAGS) test_strdup.c $(OBJS) $(LDFLAGS) -o $(TEST_EXEC)
else
	$(CC) $(CFLAGS) test_strdup.c $(OBJS) -o $(TEST_EXEC)
endif

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_EXEC) a.out

re: fclean all

info:
	@echo "OS: $(UNAME_S)"
	@echo "Assembler: $(NASM)"
	@echo "Assembler flags: $(NASMFLAGS)"
	@echo "C Compiler: $(CC)"
	@echo "C flags: $(CFLAGS)"
ifeq ($(UNAME_S),Darwin)
	@echo "Linker flags: $(LDFLAGS)"
endif

.PHONY: all clean fclean re test info
