# ===============================================
# libasm テスター Makefile v2.0
# スタブ版と本番版の両方に対応
# ===============================================

# 色定義
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

# コンパイラ設定
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# アーキテクチャ検出
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_M),arm64)
    # Apple Silicon環境ではRosettaを使用してx86_64でビルド
    ARCH_PREFIX = arch -x86_64
else
    # その他の環境では通常通りビルド
    ARCH_PREFIX = 
endif

# テストファイル
TEST_SOURCES = test_strlen.c test_strcmp.c test_strcpy.c test_strdup.c test_write.c test_read.c
TEST_NAMES = test_strlen test_strcmp test_strcpy test_strdup test_write test_read
MAIN_TEST = main_tester

# 共通オブジェクトファイル
COMMON_OBJS = test_utils.o test_stubs.o

# OS検出
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    VALGRIND_CMD = # macOSではvalgrindは使用不可
    MEMORY_TEST_MSG = "メモリリークテストはLinuxでのみ利用可能"
else
    VALGRIND_CMD = valgrind --leak-check=full --error-exitcode=1
    MEMORY_TEST_MSG = "valgrindでメモリリークテストを実行中..."
endif

# デフォルトターゲット
all: $(COMMON_OBJS) $(TEST_NAMES) $(MAIN_TEST)

# libasmライブラリのビルド
$(LIBASM):
	@echo "$(CYAN)$(BOLD)libasm.aをビルド中...$(RESET)"
	@$(ARCH_PREFIX) $(MAKE) -C $(LIBASM_DIR) all

# 共通オブジェクトファイルのビルド
test_utils.o: test_utils.c test_utils.h
	@echo "$(YELLOW)共通テストユーティリティをビルド中...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) -c test_utils.c -o test_utils.o

test_stubs.o: test_stubs.c test_utils.h
	@echo "$(YELLOW)テスト用スタブをビルド中...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) -c test_stubs.c -o test_stubs.o

# 個別テスト実行ファイルのビルド（スタブ版）
test_strlen: test_strlen.c $(COMMON_OBJS)
	@echo "$(YELLOW)test_strlen をビルド中（スタブ版）...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strlen.c $(COMMON_OBJS) -o test_strlen

test_strcmp: test_strcmp.c $(COMMON_OBJS)
	@echo "$(YELLOW)test_strcmp をビルド中（スタブ版）...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strcmp.c $(COMMON_OBJS) -o test_strcmp

test_strcpy: test_strcpy.c $(COMMON_OBJS)
	@echo "$(YELLOW)test_strcpy をビルド中（スタブ版）...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strcpy.c $(COMMON_OBJS) -o test_strcpy

test_strdup: test_strdup.c $(COMMON_OBJS)
	@echo "$(YELLOW)test_strdup をビルド中（スタブ版）...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strdup.c $(COMMON_OBJS) -o test_strdup

test_write: test_write.c $(COMMON_OBJS)
	@echo "$(YELLOW)test_write をビルド中（スタブ版）...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_write.c $(COMMON_OBJS) -o test_write

test_read: test_read.c $(COMMON_OBJS)
	@echo "$(YELLOW)test_read をビルド中（スタブ版）...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_read.c $(COMMON_OBJS) -o test_read

# メインテストランナーのビルド（スタブ版）
$(MAIN_TEST): $(MAIN_TEST).c $(COMMON_OBJS)
	@echo "$(YELLOW)メインテストランナーをビルド中（スタブ版）...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) $(MAIN_TEST).c $(COMMON_OBJS) -o $(MAIN_TEST)

# 本番版ビルド（libasm使用）
real: $(LIBASM) test_utils.o
	@echo "$(GREEN)$(BOLD)本番版（libasm使用）をビルド中...$(RESET)"
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strlen.c test_utils.o $(LIBASM) -o test_strlen_real
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strcmp.c test_utils.o $(LIBASM) -o test_strcmp_real
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strcpy.c test_utils.o $(LIBASM) -o test_strcpy_real
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_strdup.c test_utils.o $(LIBASM) -o test_strdup_real
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_write.c test_utils.o $(LIBASM) -o test_write_real
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) test_read.c test_utils.o $(LIBASM) -o test_read_real
	@$(ARCH_PREFIX) $(CC) $(CFLAGS) $(MAIN_TEST).c test_utils.o $(LIBASM) -o $(MAIN_TEST)_real

# 全テスト実行
test: all
	@echo "$(GREEN)$(BOLD)=====================================$(RESET)"
	@echo "$(GREEN)$(BOLD)  libasm 統合テストスイート実行中  $(RESET)"
	@echo "$(GREEN)$(BOLD)=====================================$(RESET)"
	@./$(MAIN_TEST)

# 本番版テスト実行
test_real: real
	@echo "$(GREEN)$(BOLD)========================================$(RESET)"
	@echo "$(GREEN)$(BOLD)  libasm 本番版テストスイート実行中  $(RESET)"
	@echo "$(GREEN)$(BOLD)========================================$(RESET)"
	@./$(MAIN_TEST)_real

# 個別テスト実行
run_strlen: test_strlen
	@echo "$(CYAN)$(BOLD)=== ft_strlen テスト実行 ====$(RESET)"
	@./test_strlen

run_strcmp: test_strcmp
	@echo "$(CYAN)$(BOLD)=== ft_strcmp テスト実行 ====$(RESET)"
	@./test_strcmp

run_strcpy: test_strcpy
	@echo "$(CYAN)$(BOLD)=== ft_strcpy テスト実行 ====$(RESET)"
	@./test_strcpy

run_strdup: test_strdup
	@echo "$(CYAN)$(BOLD)=== ft_strdup テスト実行 ====$(RESET)"
	@./test_strdup

run_write: test_write
	@echo "$(CYAN)$(BOLD)=== ft_write テスト実行 ====$(RESET)"
	@./test_write

run_read: test_read
	@echo "$(CYAN)$(BOLD)=== ft_read テスト実行 ====$(RESET)"
	@./test_read

# メモリリークテスト
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

# パフォーマンステスト
benchmark: $(MAIN_TEST)
	@echo "$(BLUE)$(BOLD)===============================$(RESET)"
	@echo "$(BLUE)$(BOLD)  パフォーマンステスト実行中  $(RESET)"
	@echo "$(BLUE)$(BOLD)===============================$(RESET)"
	@./$(MAIN_TEST) --benchmark

# 詳細テスト（全てのオプション付き）
test_all: all
	@echo "$(GREEN)$(BOLD)============================================$(RESET)"
	@echo "$(GREEN)$(BOLD)  包括的テストスイート実行中（全モード）  $(RESET)"
	@echo "$(GREEN)$(BOLD)============================================$(RESET)"
	@$(MAKE) test
	@echo ""
	@$(MAKE) memory_test
	@echo ""
	@$(MAKE) benchmark

# ヘルプ
help:
	@echo "$(BOLD)libasm テスタースイート v2.0$(RESET)"
	@echo ""
	@echo "$(BOLD)利用可能なターゲット:$(RESET)"
	@echo "  $(CYAN)all$(RESET)           - 全テストをビルド（スタブ版）"
	@echo "  $(CYAN)real$(RESET)          - 本番版（libasm使用）をビルド"
	@echo "  $(CYAN)test$(RESET)          - 基本テストスイートを実行（スタブ版）"
	@echo "  $(CYAN)test_real$(RESET)     - 本番版テストスイートを実行"
	@echo "  $(CYAN)run_<func>$(RESET)    - 特定の関数テストを実行 (strlen, strcmp, strcpy, strdup, write, read)"
	@echo "  $(CYAN)memory_test$(RESET)   - メモリリークテストを実行"
	@echo "  $(CYAN)benchmark$(RESET)     - パフォーマンステストを実行"
	@echo "  $(CYAN)test_all$(RESET)      - 全ての種類のテストを実行"
	@echo "  $(CYAN)clean$(RESET)         - 生成ファイルを削除"
	@echo "  $(CYAN)fclean$(RESET)        - 完全クリーンアップ"
	@echo "  $(CYAN)re$(RESET)            - リビルド"
	@echo "  $(CYAN)help$(RESET)          - このヘルプを表示"
	@echo ""
	@echo "$(BOLD)例:$(RESET)"
	@echo "  make test               # スタブ版でテスト"
	@echo "  make real && make test_real  # 本番版でテスト"
	@echo "  make run_strlen         # ft_strlen のみテスト"

# クリーンアップ
clean:
	@echo "$(RED)テストファイルを削除中...$(RESET)"
	@rm -f $(TEST_NAMES) $(MAIN_TEST)
	@rm -f *_real
	@rm -f *.o *.tmp test_*.txt

fclean: clean
	@echo "$(RED)完全クリーンアップ中...$(RESET)"
	@$(MAKE) -C $(LIBASM_DIR) fclean

re: fclean all

# Phonyターゲット
.PHONY: all real test test_real run_strlen run_strcmp run_strcpy run_strdup run_write run_read memory_test benchmark test_all help clean fclean re

# デフォルトターゲット
.DEFAULT_GOAL := help
