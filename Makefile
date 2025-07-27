NAME = libasm.a

SRCS = ft_read.s ft_strcmp.s ft_strcpy.s ft_strdup.s ft_strlen.s

OBJS = $(SRCS:.s=.o)

BONUS_OBJS = $(BOUNS_SRCS:.s=.o)

NASM = nasm

NAASMFLAGS = -f elf64

CC = cc

CFLAGS = -Wall -Wextra -Werror

TEST_EXEC = test_strlen

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): test_strlen.c $(OBJS)
	$(CC) $(CFLAGS) test_strlen.c $(OBJS) -o $(TEST_EXEC)

%.o: %.s
	$(NASM) $(NAASMFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_EXEC) a.out

re: fclean all

.PHONY: all clean fclean re test
