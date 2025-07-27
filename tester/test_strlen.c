#include "test_utils.h"

/*
 * ============================================
 * ft_strlen テストスイート
 * 統一的なテストフレームワークを使用
 * ============================================
 */

// 基本機能テスト
t_test_result test_strlen_basic(void)
{
    // 空文字列
    ASSERT_EQ(ft_strlen(""), strlen(""), "空文字列の長さが一致しない");
    
    // 単一文字
    ASSERT_EQ(ft_strlen("A"), strlen("A"), "単一文字の長さが一致しない");
    
    // 通常の文字列
    ASSERT_EQ(ft_strlen("Hello"), strlen("Hello"), "通常文字列の長さが一致しない");
    ASSERT_EQ(ft_strlen("Hello, World!"), strlen("Hello, World!"), "長い文字列の長さが一致しない");
    
    // 数字文字列
    ASSERT_EQ(ft_strlen("123456789"), strlen("123456789"), "数字文字列の長さが一致しない");
    
    return TEST_PASS;
}

// 特殊文字テスト
t_test_result test_strlen_special_chars(void)
{
    // 改行・タブ文字
    ASSERT_EQ(ft_strlen("\n"), strlen("\n"), "改行文字の長さが一致しない");
    ASSERT_EQ(ft_strlen("\t"), strlen("\t"), "タブ文字の長さが一致しない");
    ASSERT_EQ(ft_strlen("\r"), strlen("\r"), "復帰文字の長さが一致しない");
    
    // 複合特殊文字
    ASSERT_EQ(ft_strlen("Hello\nWorld"), strlen("Hello\nWorld"), "改行を含む文字列の長さが一致しない");
    ASSERT_EQ(ft_strlen("Tab\tSeparated"), strlen("Tab\tSeparated"), "タブを含む文字列の長さが一致しない");
    
    // 記号文字
    ASSERT_EQ(ft_strlen("!@#$%^&*()"), strlen("!@#$%^&*()"), "記号文字列の長さが一致しない");
    ASSERT_EQ(ft_strlen("[]{}|\\"), strlen("[]{}|\\"), "特殊記号の長さが一致しない");
    
    // 空白文字
    ASSERT_EQ(ft_strlen("   "), strlen("   "), "空白文字の長さが一致しない");
    ASSERT_EQ(ft_strlen(" Hello World "), strlen(" Hello World "), "前後空白を含む文字列の長さが一致しない");
    
    return TEST_PASS;
}

// 境界値テスト
t_test_result test_strlen_boundary(void)
{
    // 長い文字列（動的生成）
    char *long_str = generate_large_string(1000);
    if (long_str) {
        size_t expected = strlen(long_str);
        size_t actual = ft_strlen(long_str);
        free(long_str);
        ASSERT_EQ(actual, expected, "1000文字の長い文字列の長さが一致しない");
    }
    
    // 非常に長い文字列
    char *very_long_str = generate_large_string(10000);
    if (very_long_str) {
        size_t expected = strlen(very_long_str);
        size_t actual = ft_strlen(very_long_str);
        free(very_long_str);
        ASSERT_EQ(actual, expected, "10000文字の非常に長い文字列の長さが一致しない");
    }
    
    // 固定サイズの境界値
    char boundary_str[256];
    memset(boundary_str, 'X', 255);
    boundary_str[255] = '\0';
    ASSERT_EQ(ft_strlen(boundary_str), strlen(boundary_str), "255文字の境界値文字列の長さが一致しない");
    
    return TEST_PASS;
}

// 比較一致テスト
t_test_result test_strlen_comparison(void)
{
    const char *test_strings[] = {
        "",
        "a",
        "ab",
        "abc",
        "Hello, World!",
        "1234567890",
        "特殊文字テスト",
        "改行\n文字\t含む\r混合",
        "非常に長い文字列をテストしています。この文字列は標準ライブラリのstrlen関数と完全に同じ結果を返すべきです。",
        "!@#$%^&*()_+{}|:\"<>?[]\\;',./`~",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        size_t ft_result = ft_strlen(test_strings[i]);
        size_t std_result = strlen(test_strings[i]);
        
        if (ft_result != std_result) {
            printf("  ✗ 比較失敗[%d]: \"%s\" ft_strlen=%zu strlen=%zu\n", 
                   i, test_strings[i], ft_result, std_result);
            return TEST_FAIL;
        }
    }
    
    return TEST_PASS;
}

// パフォーマンステスト
t_test_result test_strlen_performance(void)
{
    const char *perf_strings[] = {
        "短い",
        "中程度の長さの文字列でパフォーマンステスト",
        "これは非常に長い文字列です。パフォーマンステストのために使用します。この文字列を何度も処理してft_strlen関数の性能を測定します。"
    };
    
    for (int i = 0; i < 3; i++) {
        t_benchmark bench;
        char test_name[64];
        snprintf(test_name, sizeof(test_name), "strlen_perf_%d", i);
        
        benchmark_start(&bench, test_name);
        bench.iterations = 10000;
        
        for (size_t j = 0; j < bench.iterations; j++) {
            ft_strlen(perf_strings[i]);
        }
        
        benchmark_end(&bench);
        benchmark_print_result(&bench);
    }
    
    return TEST_PASS;
}

// メインテスト実行関数
void test_ft_strlen(void)
{
    BEGIN_TEST_SUITE("ft_strlen");
    
    TEST_CASE("基本機能", test_strlen_basic);
    TEST_CASE("特殊文字", test_strlen_special_chars);
    TEST_CASE("境界値", test_strlen_boundary);
    TEST_CASE("比較一致", test_strlen_comparison);
    TEST_CASE("パフォーマンス", test_strlen_performance);
    
    END_TEST_SUITE();
}

int main(void)
{
    init_test_stats();
    test_ft_strlen();
    print_test_stats();
    
    cleanup_temp_files();
    return (g_stats.failed_tests == 0) ? 0 : 1;
} 