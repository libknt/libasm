NAME = libasm.a

SRCS = srcs/ft_read.s srcs/ft_strcmp.s srcs/ft_strcpy.s srcs/ft_strdup.s srcs/ft_strlen.s srcs/ft_write.s

OBJS = $(SRCS:.s=.o)

NASM = nasm

# OS detection
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_M),arm64)
	# Apple Silicon環境ではRosettaを使用してx86_64でビルド
	ARCH_PREFIX = arch -x86_64
	NASMFLAGS = -f macho64 -D MACOS
else ifeq ($(UNAME_M),x86_64)
	# Intel Macでは通常通りビルド
	ARCH_PREFIX = 
	NASMFLAGS = -f macho64 -D MACOS
else
	# その他のプラットフォーム（Linux等）
	ARCH_PREFIX = 
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
	rm -f $(NAME) a.out

re: fclean all

.PHONY: all clean fclean re
