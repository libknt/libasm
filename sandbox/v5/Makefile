NAME = libasm.a

SRCS = ft_strlen.s

OBJS = $(SRCS:.s=.o)

BONUS_OBJS = $(BOUNS_SRCS:.s=.o)

NASM = nasm

NAASMFLAGS = -f elf64

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(NASM) $(NAASMFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME) a.out

re: fclean all

.PHONY: all clean fclean re
