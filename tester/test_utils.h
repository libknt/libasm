#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <assert.h>
# include <errno.h>

/*
 * ============================================
 * LIBASM テストユーティリティ
 * 統合テストフレームワーク用の共通機能
 * ============================================
 */

/* カラーコード定義 */
# define RESET      "\033[0m"
# define BOLD       "\033[1m"
# define DIM        "\033[2m"
# define UNDERLINE  "\033[4m"
# define BLINK      "\033[5m"

/* 前景色 */
# define BLACK      "\033[30m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"
# define WHITE      "\033[37m"

/* 明るい前景色 */
# define BRIGHT_BLACK   "\033[90m"
# define BRIGHT_RED     "\033[91m"
# define BRIGHT_GREEN   "\033[92m"
# define BRIGHT_YELLOW  "\033[93m"
# define BRIGHT_BLUE    "\033[94m"
# define BRIGHT_MAGENTA "\033[95m"
# define BRIGHT_CYAN    "\033[96m"
# define BRIGHT_WHITE   "\033[97m"

/* 背景色 */
# define BG_BLACK       "\033[40m"
# define BG_RED         "\033[41m"
# define BG_GREEN       "\033[42m"
# define BG_YELLOW      "\033[43m"
# define BG_BLUE        "\033[44m"
# define BG_MAGENTA     "\033[45m"
# define BG_CYAN        "\033[46m"
# define BG_WHITE       "\033[47m"

/* テスト統計構造体 */
typedef struct s_test_stats {
    int total_tests;
    int passed_tests;
    int failed_tests;
    int skipped_tests;
    double total_time;
    char *current_function;
} t_test_stats;

/* ベンチマーク構造体 */
typedef struct s_benchmark {
    struct timeval start_time;
    struct timeval end_time;
    double duration_ms;
    size_t iterations;
    char *test_name;
} t_benchmark;

/* テスト結果列挙型 */
typedef enum e_test_result {
    TEST_PASS,
    TEST_FAIL,
    TEST_SKIP,
    TEST_ERROR
} t_test_result;

/* グローバル統計変数 */
extern t_test_stats g_stats;

/*
 * ============================================
 * 基本テスト機能
 * ============================================
 */

/* テスト統計の初期化と管理 */
void        init_test_stats(void);
void        print_test_stats(void);
void        reset_test_stats(void);

/* テスト実行と結果記録 */
void        run_test(const char *test_name, t_test_result (*test_func)(void));
void        record_test_result(t_test_result result);
void        set_current_function(const char *func_name);

/*
 * ============================================
 * 色付き出力機能
 * ============================================
 */

/* 基本的な色付き出力 */
void        print_header(const char *title);
void        print_subheader(const char *title);
void        print_success(const char *message);
void        print_error(const char *message);
void        print_warning(const char *message);
void        print_info(const char *message);

/* テスト結果の表示 */
void        print_test_result(const char *test_name, t_test_result result, const char *details);
void        print_pass(const char *test_name);
void        print_fail(const char *test_name, const char *reason);
void        print_skip(const char *test_name, const char *reason);

/* プログレスバー */
void        print_progress_bar(int current, int total, const char *task);

/*
 * ============================================
 * ベンチマーク機能
 * ============================================
 */

/* ベンチマーク実行 */
void        benchmark_start(t_benchmark *bench, const char *test_name);
void        benchmark_end(t_benchmark *bench);
void        benchmark_print_result(const t_benchmark *bench);

/* パフォーマンステスト */
void        performance_test_function(const char *func_name, 
                                    void (*test_func)(void), 
                                    size_t iterations);

/*
 * ============================================
 * メモリテスト支援
 * ============================================
 */

/* メモリリーク検出支援 */
void        *tracked_malloc(size_t size);
void        tracked_free(void *ptr);
void        print_memory_stats(void);
int         check_memory_leaks(void);

/*
 * ============================================
 * アサーション機能
 * ============================================
 */

/* 詳細なアサーション */
# define ASSERT_EQ(actual, expected, message) \
    assert_equal(__FILE__, __LINE__, #actual, actual, expected, message)

# define ASSERT_NEQ(actual, expected, message) \
    assert_not_equal(__FILE__, __LINE__, #actual, actual, expected, message)

# define ASSERT_STR_EQ(actual, expected, message) \
    assert_string_equal(__FILE__, __LINE__, #actual, actual, expected, message)

# define ASSERT_NULL(ptr, message) \
    assert_null(__FILE__, __LINE__, #ptr, ptr, message)

# define ASSERT_NOT_NULL(ptr, message) \
    assert_not_null(__FILE__, __LINE__, #ptr, ptr, message)

/* アサーション実装関数 */
void        assert_equal(const char *file, int line, const char *expr, 
                        long actual, long expected, const char *message);
void        assert_not_equal(const char *file, int line, const char *expr, 
                            long actual, long expected, const char *message);
void        assert_string_equal(const char *file, int line, const char *expr, 
                               const char *actual, const char *expected, const char *message);
void        assert_null(const char *file, int line, const char *expr, 
                       const void *ptr, const char *message);
void        assert_not_null(const char *file, int line, const char *expr, 
                           const void *ptr, const char *message);

/*
 * ============================================
 * ユーティリティ関数
 * ============================================
 */

/* ファイル操作ヘルパー */
int         create_temp_file(const char *content, char *filename_buffer);
void        cleanup_temp_files(void);

/* 文字列生成ヘルパー */
char        *generate_random_string(size_t length);
char        *generate_large_string(size_t size);

/* エラーハンドリング */
void        test_errno(const char *operation);
void        save_errno(int *saved_errno);
void        restore_errno(int saved_errno);

/*
 * ============================================
 * テストマクロ
 * ============================================
 */

/* 関数テスト用マクロ */
# define BEGIN_TEST_SUITE(name) \
    do { \
        print_header("テストスイート: " name); \
        set_current_function(name); \
    } while(0)

# define END_TEST_SUITE() \
    do { \
        print_info("テストスイート完了"); \
        printf("\n"); \
    } while(0)

# define TEST_CASE(name, test_func) \
    do { \
        printf("  " CYAN "テストケース: " name RESET "\n"); \
        run_test(name, test_func); \
    } while(0)

# define PERFORMANCE_TEST(name, func, iterations) \
    do { \
        printf("  " BLUE "パフォーマンステスト: " name RESET "\n"); \
        performance_test_function(name, func, iterations); \
        g_stats.total_tests++; \
        g_stats.passed_tests++; \
        printf("    ✓ PASS " name "\n"); \
    } while(0)

/*
 * ============================================
 * 外部関数宣言 (libasm関数)
 * ============================================
 */

/* libasmで実装された関数のプロトタイプ宣言 */
size_t      ft_strlen(const char *s);
int         ft_strcmp(const char *s1, const char *s2);
char        *ft_strcpy(char *dest, const char *src);
char        *ft_strdup(const char *s);
ssize_t     ft_write(int fd, const void *buf, size_t count);
ssize_t     ft_read(int fd, void *buf, size_t count);

#endif /* TEST_UTILS_H */ 