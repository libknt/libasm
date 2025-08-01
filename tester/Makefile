RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
BOLD = \033[1m

# プロジェクト設定
LIBASM = ../libasm.a
LIBASM_DIR = ..
LIBASM_LIB_DIR = ..

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -L$(LIBASM_LIB_DIR) -lasm

UNAME_M := $(shell uname -m)
ifeq ($(UNAME_M),arm64)
    # Apple Silicon環境ではRosettaを使用してx86_64でビルド
    ARCH_PREFIX = arch -x86_64
else
    # その他の環境では通常通りビルド
    ARCH_PREFIX = 
endif

MAIN_TEST = main_tester

COMMON_OBJS = test_utils.o

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    VALGRIND_CMD = # macOSではvalgrindは使用不可
    MEMORY_TEST_MSG = "メモリリークテストはLinuxでのみ利用可能"
else
    VALGRIND_CMD = valgrind --leak-check=full --error-exitcode=1
    MEMORY_TEST_MSG = "valgrindでメモリリークテストを実行中..."
endif

all: build test_exec

build: $(LIBASM) $(COMMON_OBJS)
	@echo "$(GREEN)$(BOLD)libasm テストスイートをビルド中...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strlen.c $(COMMON_OBJS) $(LDFLAGS) -o test_strlen
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strcmp.c $(COMMON_OBJS) $(LDFLAGS) -o test_strcmp
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strcpy.c $(COMMON_OBJS) $(LDFLAGS) -o test_strcpy
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strdup.c $(COMMON_OBJS) $(LDFLAGS) -o test_strdup
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_write.c $(COMMON_OBJS) $(LDFLAGS) -o test_write
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_read.c $(COMMON_OBJS) $(LDFLAGS) -o test_read
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) $(MAIN_TEST).c $(COMMON_OBJS) $(LDFLAGS) -o $(MAIN_TEST)

test_exec: build
	@echo "$(GREEN)$(BOLD)=====================================$(RESET)"
	@echo "$(GREEN)$(BOLD)  libasm テストスイート実行中  $(RESET)"
	@echo "$(GREEN)$(BOLD)=====================================$(RESET)"
	@./$(MAIN_TEST)

$(LIBASM):
	@echo "$(CYAN)$(BOLD)libasm.aをビルド中...$(RESET)"
	@$(ARCH_PREFIX) $(MAKE) -C $(LIBASM_DIR) all

test_utils.o: test_utils.c test_utils.h
	@echo "$(YELLOW)共通テストユーティリティをビルド中...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) -c test_utils.c -o test_utils.o



real: build

test: test_exec



memory_test: $(MAIN_TEST)
	@echo "$(MAGENTA)$(BOLD)================================$(RESET)"
	@echo "$(MAGENTA)$(BOLD)  メモリリークテスト実行中     $(RESET)"
	@echo "$(MAGENTA)$(BOLD)================================$(RESET)"
	@echo "$(YELLOW)$(MEMORY_TEST_MSG)$(RESET)"
ifneq ($(VALGRIND_CMD),)
	@$(VALGRIND_CMD) ./$(MAIN_TEST)
else
	@echo "$(YELLOW)macOSでのメモリテストはleaksコマンドを使用してください:$(RESET)"
	@echo "$(WHITE)leaks --atExit -- ./$(MAIN_TEST)$(RESET)"
endif

benchmark: $(MAIN_TEST)
	@echo "$(BLUE)$(BOLD)===============================$(RESET)"
	@echo "$(BLUE)$(BOLD)  パフォーマンステスト実行中  $(RESET)"
	@echo "$(BLUE)$(BOLD)===============================$(RESET)"
	@./$(MAIN_TEST) --benchmark

test_all: all
	@echo "$(GREEN)$(BOLD)============================================$(RESET)"
	@echo "$(GREEN)$(BOLD)  包括的テストスイート実行中（全モード）  $(RESET)"
	@echo "$(GREEN)$(BOLD)============================================$(RESET)"
	@$(MAKE) test
	@echo ""
	@$(MAKE) memory_test
	@echo ""
	@$(MAKE) benchmark

test:
	@echo "$(YELLOW)$(BOLD)=================================$(RESET)"
	@echo "$(YELLOW)$(BOLD)  libasm テストスイート実行中  $(RESET)"
	@echo "$(YELLOW)$(BOLD)=================================$(RESET)"
	@./test_strlen
	@./test_strcmp
	@./test_strcpy
	@./test_strdup
	@./test_write
	@./test_read
	@echo "$(GREEN)$(BOLD)テスト完了！$(RESET)"
help:
	@echo "$(BOLD)libasm テスタースイート v2.0$(RESET)"
	@echo ""
	@echo "$(BOLD)利用可能なターゲット:$(RESET)"
	@echo "  $(CYAN)all$(RESET)           - ビルドしてテスト実行（デフォルト）"
	@echo "  $(CYAN)build$(RESET)         - libasm使用版をビルドのみ"
	@echo "  $(CYAN)test$(RESET)          - テストスイートを実行"
	@echo "  $(CYAN)memory_test$(RESET)   - メモリリークテストを実行"
	@echo "  $(CYAN)benchmark$(RESET)     - パフォーマンステストを実行"
	@echo "  $(CYAN)test_all$(RESET)      - 全ての種類のテストを実行"
	@echo "  $(CYAN)clean$(RESET)         - 生成ファイルを削除"
	@echo "  $(CYAN)fclean$(RESET)        - 完全クリーンアップ"
	@echo "  $(CYAN)re$(RESET)            - リビルド"
	@echo "  $(CYAN)help$(RESET)          - このヘルプを表示"
	@echo ""
	@echo "$(BOLD)例:$(RESET)"
	@echo "  make                    # ビルド&テスト実行"
	@echo "  make all                # 同上"
	@echo "  make build              # ビルドのみ"
	@echo "  make test               # テスト実行のみ"

clean:
	@echo "$(RED)テストファイルを削除中...$(RESET)"
	@rm -f $(MAIN_TEST)
	@rm -f *.o *.tmp test_*.txt

fclean: clean
	@echo "$(RED)完全クリーンアップ中...$(RESET)"
	@$(MAKE) -C $(LIBASM_DIR) fclean

re: fclean all

.PHONY: all build test_exec real test memory_test benchmark test_all help clean fclean re

.DEFAULT_GOAL := all
