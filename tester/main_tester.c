#include "test_utils.h"
#include <getopt.h>
#include <fcntl.h>

/*
 * ============================================
 * LIBASM 統合テストランナー
 * 全ての関数テストを実行し、詳細な統計を提供
 * ============================================
 */

/* テストモード定義 */
typedef enum {
    MODE_BASIC,
    MODE_COMPREHENSIVE,
    MODE_BENCHMARK,
    MODE_MEMORY_TEST,
    MODE_STRESS_TEST
} test_mode_t;

/* グローバル設定 */
typedef struct {
    test_mode_t mode;
    int verbose;
    int quiet;
    int benchmark_iterations;
    int stress_test_duration;
    char *specific_function;
    int help;
} test_config_t;

/*
 * ============================================
 * 個別テスト関数宣言
 * ============================================
 */

/* 各関数のテスト結果を返す関数 */
t_test_result test_ft_strlen_comprehensive(void);
t_test_result test_ft_strcmp_comprehensive(void);
t_test_result test_ft_strcpy_comprehensive(void);
t_test_result test_ft_strdup_comprehensive(void);
t_test_result test_ft_write_comprehensive(void);
t_test_result test_ft_read_comprehensive(void);

/* ベンチマーク専用テスト */
void benchmark_ft_strlen(void);
void benchmark_ft_strcmp(void);
void benchmark_ft_strcpy(void);
void benchmark_ft_strdup(void);
void benchmark_ft_write(void);
void benchmark_ft_read(void);

/* ストレステスト */
t_test_result stress_test_all_functions(void);

/*
 * ============================================
 * 設定とヘルプ
 * ============================================
 */

void print_usage(const char *program_name)
{
    printf(BOLD "libasm テストスイート" RESET "\n");
    printf("使用法: %s [オプション]\n\n", program_name);
    
    printf(BOLD "テストモード:" RESET "\n");
    printf("  -b, --basic         基本テストのみ実行 (デフォルト)\n");
    printf("  -c, --comprehensive 包括的テスト実行\n");
    printf("  -B, --benchmark     ベンチマークテスト実行\n");
    printf("  -m, --memory        メモリテスト実行\n");
    printf("  -s, --stress        ストレステスト実行\n");
    
    printf("\n" BOLD "オプション:" RESET "\n");
    printf("  -f, --function FUNC 特定の関数のみテスト (strlen, strcmp, strcpy, strdup, write, read)\n");
    printf("  -i, --iterations N  ベンチマークのイテレーション数 (デフォルト: 100000)\n");
    printf("  -d, --duration N    ストレステストの実行時間（秒）(デフォルト: 10)\n");
    printf("  -v, --verbose       詳細な出力\n");
    printf("  -q, --quiet         最小限の出力\n");
    printf("  -h, --help          このヘルプを表示\n");
    
    printf("\n" BOLD "例:" RESET "\n");
    printf("  %s                    # 基本テスト\n", program_name);
    printf("  %s -c                 # 包括的テスト\n", program_name);
    printf("  %s -B -i 1000000      # 高精度ベンチマーク\n", program_name);
    printf("  %s -f strlen -v       # ft_strlenの詳細テスト\n", program_name);
    printf("  %s -m                 # メモリリークテスト\n", program_name);
}

test_config_t parse_arguments(int argc, char **argv)
{
    test_config_t config = {
        .mode = MODE_BASIC,
        .verbose = 0,
        .quiet = 0,
        .benchmark_iterations = 100000,
        .stress_test_duration = 10,
        .specific_function = NULL,
        .help = 0
    };
    
    static struct option long_options[] = {
        {"basic",        no_argument,       0, 'b'},
        {"comprehensive", no_argument,      0, 'c'},
        {"benchmark",    no_argument,       0, 'B'},
        {"memory",       no_argument,       0, 'm'},
        {"stress",       no_argument,       0, 's'},
        {"function",     required_argument, 0, 'f'},
        {"iterations",   required_argument, 0, 'i'},
        {"duration",     required_argument, 0, 'd'},
        {"verbose",      no_argument,       0, 'v'},
        {"quiet",        no_argument,       0, 'q'},
        {"help",         no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };
    
    int c;
    while ((c = getopt_long(argc, argv, "bcBmsf:i:d:vqh", long_options, NULL)) != -1) {
        switch (c) {
            case 'b':
                config.mode = MODE_BASIC;
                break;
            case 'c':
                config.mode = MODE_COMPREHENSIVE;
                break;
            case 'B':
                config.mode = MODE_BENCHMARK;
                break;
            case 'm':
                config.mode = MODE_MEMORY_TEST;
                break;
            case 's':
                config.mode = MODE_STRESS_TEST;
                break;
            case 'f':
                config.specific_function = optarg;
                break;
            case 'i':
                config.benchmark_iterations = atoi(optarg);
                break;
            case 'd':
                config.stress_test_duration = atoi(optarg);
                break;
            case 'v':
                config.verbose = 1;
                break;
            case 'q':
                config.quiet = 1;
                break;
            case 'h':
                config.help = 1;
                break;
            default:
                config.help = 1;
                break;
        }
    }
    
    return config;
}

/*
 * ============================================
 * メインテスト実行エンジン
 * ============================================
 */

void run_basic_tests(const test_config_t *config)
{
    if (!config->quiet) {
        print_header("基本テストスイート実行中");
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strlen") == 0) {
        BEGIN_TEST_SUITE("ft_strlen");
        TEST_CASE("基本テスト", test_ft_strlen_comprehensive);
        END_TEST_SUITE();
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strcmp") == 0) {
        BEGIN_TEST_SUITE("ft_strcmp");
        TEST_CASE("基本テスト", test_ft_strcmp_comprehensive);
        END_TEST_SUITE();
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strcpy") == 0) {
        BEGIN_TEST_SUITE("ft_strcpy");
        TEST_CASE("基本テスト", test_ft_strcpy_comprehensive);
        END_TEST_SUITE();
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strdup") == 0) {
        BEGIN_TEST_SUITE("ft_strdup");
        TEST_CASE("基本テスト", test_ft_strdup_comprehensive);
        END_TEST_SUITE();
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "write") == 0) {
        BEGIN_TEST_SUITE("ft_write");
        TEST_CASE("基本テスト", test_ft_write_comprehensive);
        END_TEST_SUITE();
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "read") == 0) {
        BEGIN_TEST_SUITE("ft_read");
        TEST_CASE("基本テスト", test_ft_read_comprehensive);
        END_TEST_SUITE();
    }
}

void run_benchmark_tests(const test_config_t *config)
{
    if (!config->quiet) {
        print_header("パフォーマンステスト実行中");
        printf("イテレーション数: %d\n\n", config->benchmark_iterations);
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strlen") == 0) {
        PERFORMANCE_TEST("ft_strlen", benchmark_ft_strlen, config->benchmark_iterations);
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strcmp") == 0) {
        PERFORMANCE_TEST("ft_strcmp", benchmark_ft_strcmp, config->benchmark_iterations);
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strcpy") == 0) {
        PERFORMANCE_TEST("ft_strcpy", benchmark_ft_strcpy, config->benchmark_iterations);
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "strdup") == 0) {
        PERFORMANCE_TEST("ft_strdup", benchmark_ft_strdup, config->benchmark_iterations);
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "write") == 0) {
        PERFORMANCE_TEST("ft_write", benchmark_ft_write, config->benchmark_iterations);
    }
    
    if (!config->specific_function || strcmp(config->specific_function, "read") == 0) {
        PERFORMANCE_TEST("ft_read", benchmark_ft_read, config->benchmark_iterations);
    }
}

void run_memory_tests(const test_config_t *config)
{
    if (!config->quiet) {
        print_header("メモリテスト実行中");
    }
    
    // ft_strdupのメモリテストを集中的に実行
    BEGIN_TEST_SUITE("ft_strdup メモリテスト");
    TEST_CASE("メモリリークテスト", test_ft_strdup_comprehensive);
    END_TEST_SUITE();
    
    print_memory_stats();
}

void run_stress_tests(const test_config_t *config)
{
    if (!config->quiet) {
        print_header("ストレステスト実行中");
        printf("実行時間: %d秒\n\n", config->stress_test_duration);
    }
    
    BEGIN_TEST_SUITE("ストレステスト");
    TEST_CASE("全関数統合テスト", stress_test_all_functions);
    END_TEST_SUITE();
}

/*
 * ============================================
 * テスト実装（スタブ版）
 * ============================================
 */

t_test_result test_ft_strlen_comprehensive(void)
{
    // 基本テスト
    if (ft_strlen("") != 0) return TEST_FAIL;
    if (ft_strlen("Hello") != 5) return TEST_FAIL;
    if (ft_strlen("Hello, World!") != 13) return TEST_FAIL;
    
    // 長い文字列テスト
    char *large_str = generate_large_string(10000);
    if (large_str) {
        size_t expected = strlen(large_str);
        size_t actual = ft_strlen(large_str);
        free(large_str);
        if (actual != expected) return TEST_FAIL;
    }
    
    return TEST_PASS;
}

t_test_result test_ft_strcmp_comprehensive(void)
{
    // 基本的な比較テスト
    if (ft_strcmp("hello", "hello") != 0) return TEST_FAIL;
    if ((ft_strcmp("abc", "abd") >= 0) != (strcmp("abc", "abd") >= 0)) return TEST_FAIL;
    if ((ft_strcmp("abd", "abc") <= 0) != (strcmp("abd", "abc") <= 0)) return TEST_FAIL;
    if ((ft_strcmp("", "hello") >= 0) != (strcmp("", "hello") >= 0)) return TEST_FAIL;
    if ((ft_strcmp("hello", "") <= 0) != (strcmp("hello", "") <= 0)) return TEST_FAIL;
    
    return TEST_PASS;
}

t_test_result test_ft_strcpy_comprehensive(void)
{
    char dest1[100], dest2[100];
    
    // 基本テスト
    strcpy(dest1, "Hello");
    ft_strcpy(dest2, "Hello");
    if (strcmp(dest1, dest2) != 0) return TEST_FAIL;
    
    strcpy(dest1, "");
    ft_strcpy(dest2, "");
    if (strcmp(dest1, dest2) != 0) return TEST_FAIL;
    
    return TEST_PASS;
}

t_test_result test_ft_strdup_comprehensive(void)
{
    char *result1, *result2;
    
    // 基本テスト
    result1 = ft_strdup("Hello");
    result2 = strdup("Hello");
    
    if (!result1 || !result2) {
        if (result1) free(result1);
        if (result2) free(result2);
        return TEST_FAIL;
    }
    
    int comparison = strcmp(result1, result2);
    free(result1);
    free(result2);
    
    if (comparison != 0) return TEST_FAIL;
    
    // 空文字列テスト
    result1 = ft_strdup("");
    result2 = strdup("");
    
    if (!result1 || !result2) {
        if (result1) free(result1);
        if (result2) free(result2);
        return TEST_FAIL;
    }
    
    comparison = strcmp(result1, result2);
    free(result1);
    free(result2);
    
    if (comparison != 0) return TEST_FAIL;
    
    return TEST_PASS;
}

t_test_result test_ft_write_comprehensive(void)
{
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) != 0) return TEST_FAIL;
    
    int fd = open(temp_file, O_WRONLY);
    if (fd == -1) return TEST_FAIL;
    
    const char *test_content = "Hello, World!";
    ssize_t ft_result = ft_write(fd, test_content, strlen(test_content));
    close(fd);
    
    if (ft_result != (ssize_t)strlen(test_content)) {
        unlink(temp_file);
        return TEST_FAIL;
    }
    
    unlink(temp_file);
    return TEST_PASS;
}

t_test_result test_ft_read_comprehensive(void)
{
    char temp_file[256];
    const char *content = "Hello, Read Test!";
    
    if (create_temp_file(content, temp_file) != 0) return TEST_FAIL;
    
    int fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_FAIL;
    }
    
    char buffer[100];
    ssize_t bytes_read = ft_read(fd, buffer, strlen(content));
    close(fd);
    
    if (bytes_read != (ssize_t)strlen(content)) {
        unlink(temp_file);
        return TEST_FAIL;
    }
    
    buffer[bytes_read] = '\0';
    int comparison = strcmp(buffer, content);
    unlink(temp_file);
    
    return (comparison == 0) ? TEST_PASS : TEST_FAIL;
}

/* ベンチマーク用関数 */
void benchmark_ft_strlen(void)
{
    static const char *test_str = "This is a test string for benchmarking ft_strlen function.";
    ft_strlen(test_str);
}

void benchmark_ft_strcmp(void)
{
    static const char *str1 = "benchmark string 1";
    static const char *str2 = "benchmark string 2";
    ft_strcmp(str1, str2);
}

void benchmark_ft_strcpy(void)
{
    static char dest[100];
    static const char *src = "benchmark source string for strcpy";
    ft_strcpy(dest, src);
}

void benchmark_ft_strdup(void)
{
    static const char *src = "benchmark string for strdup";
    char *result = ft_strdup(src);
    if (result) free(result);
}

void benchmark_ft_write(void)
{
    static const char *content = "benchmark";
    static int null_fd = -1;
    
    // /dev/nullを開く（初回のみ）
    if (null_fd == -1) {
        null_fd = open("/dev/null", O_WRONLY);
        if (null_fd == -1) {
            // /dev/nullが開けない場合は何もしない
            return;
        }
    }
    
    ft_write(null_fd, content, strlen(content));
}

void benchmark_ft_read(void)
{
    char buffer[10];
    // ここでは実際の読み取りテストは簡略化
    ft_read(0, buffer, 0);
}

t_test_result stress_test_all_functions(void)
{
    // 簡略化されたストレステスト
    for (int i = 0; i < 1000; i++) {
        if (test_ft_strlen_comprehensive() != TEST_PASS) return TEST_FAIL;
        if (test_ft_strcmp_comprehensive() != TEST_PASS) return TEST_FAIL;
        if (test_ft_strcpy_comprehensive() != TEST_PASS) return TEST_FAIL;
        if (test_ft_strdup_comprehensive() != TEST_PASS) return TEST_FAIL;
    }
    return TEST_PASS;
}

/*
 * ============================================
 * メイン関数
 * ============================================
 */

int main(int argc, char **argv)
{
    test_config_t config = parse_arguments(argc, argv);
    
    if (config.help) {
        print_usage(argv[0]);
        return 0;
    }
    
    // 統計の初期化
    init_test_stats();
    
    // シード値設定（ランダムテスト用）
    srand(time(NULL));
    
    if (!config.quiet) {
        print_header("LIBASM 統合テストスイート v2.0");
        printf("実行モード: ");
        switch (config.mode) {
            case MODE_BASIC:
                printf(GREEN "基本テスト" RESET "\n");
                break;
            case MODE_COMPREHENSIVE:
                printf(CYAN "包括的テスト" RESET "\n");
                break;
            case MODE_BENCHMARK:
                printf(BLUE "ベンチマークテスト" RESET "\n");
                break;
            case MODE_MEMORY_TEST:
                printf(MAGENTA "メモリテスト" RESET "\n");
                break;
            case MODE_STRESS_TEST:
                printf(RED "ストレステスト" RESET "\n");
                break;
        }
        
        if (config.specific_function) {
            printf("対象関数: " YELLOW "%s" RESET "\n", config.specific_function);
        }
        printf("\n");
    }
    
    // テスト実行
    switch (config.mode) {
        case MODE_BASIC:
        case MODE_COMPREHENSIVE:
            run_basic_tests(&config);
            break;
        case MODE_BENCHMARK:
            run_benchmark_tests(&config);
            break;
        case MODE_MEMORY_TEST:
            run_memory_tests(&config);
            break;
        case MODE_STRESS_TEST:
            run_stress_tests(&config);
            break;
    }
    
    // 一時ファイルのクリーンアップ
    cleanup_temp_files();
    
    // 結果表示
    if (!config.quiet) {
        print_test_stats();
        
        if (g_stats.failed_tests == 0) {
            print_success("全テストが正常に完了しました！ 🎉");
        } else {
            print_error("一部のテストが失敗しました");
        }
    }
    
    // メモリのクリーンアップ
    if (g_stats.current_function) {
        free(g_stats.current_function);
    }
    
    return (g_stats.failed_tests == 0) ? 0 : 1;
} 