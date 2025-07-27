#include "test_utils.h"
#include <fcntl.h>
#include <signal.h>

/*
 * ============================================
 * グローバル変数とデータ構造
 * ============================================
 */

/* グローバル統計変数 */
t_test_stats g_stats = {0, 0, 0, 0, 0.0, NULL};

/* メモリトラッキング用 */
static int allocated_blocks = 0;
static size_t total_allocated = 0;

/* 一時ファイルトラッキング */
static char temp_files[256][256];
static int temp_file_count = 0;

/*
 * ============================================
 * 基本テスト機能の実装
 * ============================================
 */

void init_test_stats(void)
{
    g_stats.total_tests = 0;
    g_stats.passed_tests = 0;
    g_stats.failed_tests = 0;
    g_stats.skipped_tests = 0;
    g_stats.total_time = 0.0;
    if (g_stats.current_function)
        free(g_stats.current_function);
    g_stats.current_function = NULL;
}

void reset_test_stats(void)
{
    init_test_stats();
}

void set_current_function(const char *func_name)
{
    if (g_stats.current_function)
        free(g_stats.current_function);
    g_stats.current_function = func_name ? strdup(func_name) : NULL;
}

void record_test_result(t_test_result result)
{
    g_stats.total_tests++;
    switch (result) {
        case TEST_PASS:
            g_stats.passed_tests++;
            break;
        case TEST_FAIL:
        case TEST_ERROR:
            g_stats.failed_tests++;
            break;
        case TEST_SKIP:
            g_stats.skipped_tests++;
            break;
    }
}

void run_test(const char *test_name, t_test_result (*test_func)(void))
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    t_test_result result = test_func();
    
    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 + 
                       (end.tv_usec - start.tv_usec) / 1000.0;
    g_stats.total_time += time_taken;
    
    record_test_result(result);
    
    // テスト結果の詳細表示
    switch (result) {
        case TEST_PASS:
            printf("    " GREEN "✓ PASS" RESET " %s (%.2fms)\n", test_name, time_taken);
            break;
        case TEST_FAIL:
            printf("    " RED "✗ FAIL" RESET " %s (%.2fms)\n", test_name, time_taken);
            break;
        case TEST_SKIP:
            printf("    " YELLOW "⊘ SKIP" RESET " %s (%.2fms)\n", test_name, time_taken);
            break;
        case TEST_ERROR:
            printf("    " BRIGHT_RED "⚠ ERROR" RESET " %s (%.2fms)\n", test_name, time_taken);
            break;
    }
}

void print_test_stats(void)
{
    int success_rate = g_stats.total_tests > 0 ? 
        (g_stats.passed_tests * 100) / g_stats.total_tests : 0;
    
    printf("\n");
    print_header("テスト実行結果サマリー");
    
    printf("  " BOLD "総テスト数:" RESET "   %d\n", g_stats.total_tests);
    printf("  " GREEN BOLD "成功:" RESET "        %d\n", g_stats.passed_tests);
    printf("  " RED BOLD "失敗:" RESET "        %d\n", g_stats.failed_tests);
    printf("  " YELLOW BOLD "スキップ:" RESET "    %d\n", g_stats.skipped_tests);
    printf("  " CYAN BOLD "実行時間:" RESET "    %.2fms\n", g_stats.total_time);
    
    if (success_rate >= 90) {
        printf("  " GREEN BOLD "成功率:" RESET "      %d%% " GREEN "🎉" RESET "\n", success_rate);
    } else if (success_rate >= 70) {
        printf("  " YELLOW BOLD "成功率:" RESET "      %d%% " YELLOW "⚠️" RESET "\n", success_rate);
    } else {
        printf("  " RED BOLD "成功率:" RESET "      %d%% " RED "❌" RESET "\n", success_rate);
    }
    
    printf("\n");
}

/*
 * ============================================
 * 色付き出力機能の実装
 * ============================================
 */

void print_header(const char *title)
{
    size_t len = strlen(title);
    size_t padding = (60 - len) / 2;
    
    printf("\n" BOLD CYAN);
    for (size_t i = 0; i < 60; i++) printf("=");
    printf(RESET "\n");
    
    printf(BOLD CYAN);
    for (size_t i = 0; i < padding; i++) printf(" ");
    printf("%s", title);
    for (size_t i = 0; i < 60 - len - padding; i++) printf(" ");
    printf(RESET "\n");
    
    printf(BOLD CYAN);
    for (size_t i = 0; i < 60; i++) printf("=");
    printf(RESET "\n");
}

void print_subheader(const char *title)
{
    printf("\n" BOLD YELLOW "--- %s ---" RESET "\n", title);
}

void print_success(const char *message)
{
    printf(GREEN "✓ %s" RESET "\n", message);
}

void print_error(const char *message)
{
    printf(RED "✗ %s" RESET "\n", message);
}

void print_warning(const char *message)
{
    printf(YELLOW "⚠ %s" RESET "\n", message);
}

void print_info(const char *message)
{
    printf(CYAN "ℹ %s" RESET "\n", message);
}

void print_test_result(const char *test_name, t_test_result result, const char *details)
{
    const char *status_color;
    const char *status_symbol;
    
    switch (result) {
        case TEST_PASS:
            status_color = GREEN;
            status_symbol = "✓";
            break;
        case TEST_FAIL:
            status_color = RED;
            status_symbol = "✗";
            break;
        case TEST_SKIP:
            status_color = YELLOW;
            status_symbol = "⊘";
            break;
        case TEST_ERROR:
            status_color = BRIGHT_RED;
            status_symbol = "⚠";
            break;
    }
    
    printf("  %s%s %s" RESET, status_color, status_symbol, test_name);
    if (details)
        printf(" " DIM "(%s)" RESET, details);
    printf("\n");
}

void print_pass(const char *test_name)
{
    print_test_result(test_name, TEST_PASS, NULL);
}

void print_fail(const char *test_name, const char *reason)
{
    print_test_result(test_name, TEST_FAIL, reason);
}

void print_skip(const char *test_name, const char *reason)
{
    print_test_result(test_name, TEST_SKIP, reason);
}

void print_progress_bar(int current, int total, const char *task)
{
    int bar_width = 40;
    int progress = current * bar_width / total;
    int percentage = current * 100 / total;
    
    printf("\r" CYAN "%s: " RESET "[", task);
    for (int i = 0; i < bar_width; i++) {
        if (i < progress)
            printf(GREEN "█" RESET);
        else
            printf(DIM "░" RESET);
    }
    printf("] %d%% (%d/%d)", percentage, current, total);
    fflush(stdout);
    
    if (current == total)
        printf("\n");
}

/*
 * ============================================
 * ベンチマーク機能の実装
 * ============================================
 */

void benchmark_start(t_benchmark *bench, const char *test_name)
{
    bench->test_name = strdup(test_name);
    bench->iterations = 0;
    gettimeofday(&bench->start_time, NULL);
}

void benchmark_end(t_benchmark *bench)
{
    gettimeofday(&bench->end_time, NULL);
    bench->duration_ms = (bench->end_time.tv_sec - bench->start_time.tv_sec) * 1000.0 + 
                        (bench->end_time.tv_usec - bench->start_time.tv_usec) / 1000.0;
}

void benchmark_print_result(const t_benchmark *bench)
{
    double avg_time_per_iteration = bench->iterations > 0 ? 
        bench->duration_ms / bench->iterations : bench->duration_ms;
    
    printf("  " BLUE "📊 ベンチマーク結果: %s" RESET "\n", bench->test_name);
    printf("    総実行時間: %.3fms\n", bench->duration_ms);
    if (bench->iterations > 0) {
        printf("    イテレーション数: %zu\n", bench->iterations);
        printf("    平均実行時間: %.6fms/回\n", avg_time_per_iteration);
        printf("    スループット: %.0f ops/sec\n", 1000.0 / avg_time_per_iteration);
    }
}

void performance_test_function(const char *func_name, void (*test_func)(void), size_t iterations)
{
    t_benchmark bench;
    benchmark_start(&bench, func_name);
    bench.iterations = iterations;
    
    for (size_t i = 0; i < iterations; i++) {
        test_func();
        if (i % (iterations / 10) == 0) {
            print_progress_bar(i, iterations, "パフォーマンステスト");
        }
    }
    print_progress_bar(iterations, iterations, "パフォーマンステスト");
    
    benchmark_end(&bench);
    benchmark_print_result(&bench);
    
    free(bench.test_name);
}

/*
 * ============================================
 * メモリテスト支援の実装
 * ============================================
 */

void *tracked_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr) {
        allocated_blocks++;
        total_allocated += size;
    }
    return ptr;
}

void tracked_free(void *ptr)
{
    if (ptr) {
        allocated_blocks--;
        free(ptr);
    }
}

void print_memory_stats(void)
{
    printf("\n" MAGENTA "📊 メモリ統計:" RESET "\n");
    printf("  未解放ブロック数: %d\n", allocated_blocks);
    printf("  総確保メモリ: %zu bytes\n", total_allocated);
    
    if (allocated_blocks == 0) {
        print_success("メモリリークは検出されませんでした");
    } else {
        print_error("メモリリークが検出されました！");
    }
}

int check_memory_leaks(void)
{
    return allocated_blocks;
}

/*
 * ============================================
 * アサーション機能の実装
 * ============================================
 */

void assert_equal(const char *file, int line, const char *expr, 
                 long actual, long expected, const char *message)
{
    if (actual != expected) {
        printf(RED "アサーション失敗 at %s:%d" RESET "\n", file, line);
        printf("  式: %s\n", expr);
        printf("  期待値: %ld\n", expected);
        printf("  実際値: %ld\n", actual);
        if (message)
            printf("  メッセージ: %s\n", message);
        abort();
    }
}

void assert_not_equal(const char *file, int line, const char *expr, 
                     long actual, long expected, const char *message)
{
    if (actual == expected) {
        printf(RED "アサーション失敗 at %s:%d" RESET "\n", file, line);
        printf("  式: %s\n", expr);
        printf("  期待しない値: %ld\n", expected);
        printf("  実際値: %ld\n", actual);
        if (message)
            printf("  メッセージ: %s\n", message);
        abort();
    }
}

void assert_string_equal(const char *file, int line, const char *expr, 
                        const char *actual, const char *expected, const char *message)
{
    if (!actual || !expected || strcmp(actual, expected) != 0) {
        printf(RED "文字列アサーション失敗 at %s:%d" RESET "\n", file, line);
        printf("  式: %s\n", expr);
        printf("  期待値: \"%s\"\n", expected ? expected : "(null)");
        printf("  実際値: \"%s\"\n", actual ? actual : "(null)");
        if (message)
            printf("  メッセージ: %s\n", message);
        abort();
    }
}

void assert_null(const char *file, int line, const char *expr, 
                const void *ptr, const char *message)
{
    if (ptr != NULL) {
        printf(RED "NULLアサーション失敗 at %s:%d" RESET "\n", file, line);
        printf("  式: %s\n", expr);
        printf("  期待値: NULL\n");
        printf("  実際値: %p\n", ptr);
        if (message)
            printf("  メッセージ: %s\n", message);
        abort();
    }
}

void assert_not_null(const char *file, int line, const char *expr, 
                    const void *ptr, const char *message)
{
    if (ptr == NULL) {
        printf(RED "非NULLアサーション失敗 at %s:%d" RESET "\n", file, line);
        printf("  式: %s\n", expr);
        printf("  期待: 非NULL値\n");
        printf("  実際値: NULL\n");
        if (message)
            printf("  メッセージ: %s\n", message);
        abort();
    }
}

/*
 * ============================================
 * ユーティリティ関数の実装
 * ============================================
 */

int create_temp_file(const char *content, char *filename_buffer)
{
    static int temp_counter = 0;
    
    snprintf(filename_buffer, 256, "test_temp_%d_%d.tmp", getpid(), temp_counter++);
    
    int fd = open(filename_buffer, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        return -1;
    
    if (content) {
        write(fd, content, strlen(content));
    }
    close(fd);
    
    // 一時ファイルを記録
    strcpy(temp_files[temp_file_count], filename_buffer);
    temp_file_count++;
    
    return 0;
}

void cleanup_temp_files(void)
{
    for (int i = 0; i < temp_file_count; i++) {
        unlink(temp_files[i]);
    }
    temp_file_count = 0;
}

char *generate_random_string(size_t length)
{
    if (length == 0)
        return strdup("");
    
    char *str = malloc(length + 1);
    if (!str)
        return NULL;
    
    for (size_t i = 0; i < length; i++) {
        str[i] = 'A' + (rand() % 26);
    }
    str[length] = '\0';
    
    return str;
}

char *generate_large_string(size_t size)
{
    char *str = malloc(size + 1);
    if (!str)
        return NULL;
    
    // パターンを繰り返して大きな文字列を作成
    const char *pattern = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
    size_t pattern_len = strlen(pattern);
    
    for (size_t i = 0; i < size; i++) {
        str[i] = pattern[i % pattern_len];
    }
    str[size] = '\0';
    
    return str;
}

void test_errno(const char *operation)
{
    if (errno != 0) {
        printf("  errno after %s: %d (%s)\n", operation, errno, strerror(errno));
    }
}

void save_errno(int *saved_errno)
{
    *saved_errno = errno;
}

void restore_errno(int saved_errno)
{
    errno = saved_errno;
} 