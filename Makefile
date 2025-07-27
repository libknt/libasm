NAME = libasm.a

SRCS = srcs/ft_read.s srcs/ft_strcmp.s srcs/ft_strcpy.s srcs/ft_strdup.s srcs/ft_strlen.s srcs/ft_write.s

OBJS = $(SRCS:.s=.o)

NASM = nasm

# OS detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_M),arm64)
	# Apple Silicon環境ではRosettaを使用してx86_64でビルド
	ARCH_PREFIX = arch -x86_64
	NASMFLAGS = -f macho64 -D MACOS
else ifeq ($(UNAME_S),Darwin)
    NASMFLAGS = -f macho64 -D MACOS
else
    NASMFLAGS = -f elf64
endif


CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(ARCH_PREFIX) $(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
