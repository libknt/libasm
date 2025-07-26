NAME = test_strcpy
EXTENDED_NAME = extended_test
ASM_FILE = ft_strcpy.s
C_FILE = test_strcpy.c
EXTENDED_C_FILE = extended_test.c
OBJ_ASM = ft_strcpy.o
OBJ_C = test_strcpy.o
EXTENDED_OBJ_C = extended_test.o

AS = as
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_ASM) $(OBJ_C)
	$(CC) $(OBJ_ASM) $(OBJ_C) -o $(NAME)

$(EXTENDED_NAME): $(OBJ_ASM) $(EXTENDED_OBJ_C)
	$(CC) $(OBJ_ASM) $(EXTENDED_OBJ_C) -o $(EXTENDED_NAME)

$(OBJ_ASM): $(ASM_FILE)
	$(AS) $(ASM_FILE) -o $(OBJ_ASM)

$(OBJ_C): $(C_FILE)
	$(CC) $(CFLAGS) -c $(C_FILE) -o $(OBJ_C)

$(EXTENDED_OBJ_C): $(EXTENDED_C_FILE)
	$(CC) $(CFLAGS) -c $(EXTENDED_C_FILE) -o $(EXTENDED_OBJ_C)

clean:
	rm -f $(OBJ_ASM) $(OBJ_C) $(EXTENDED_OBJ_C)

fclean: clean
	rm -f $(NAME) $(EXTENDED_NAME)

re: fclean all

test: $(NAME)
	./$(NAME)

extended: $(EXTENDED_NAME)
	./$(EXTENDED_NAME)

all_tests: test extended

.PHONY: all clean fclean re test extended all_tests 