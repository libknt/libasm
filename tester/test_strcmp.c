#include "test_utils.h"

/*
 * ============================================
 * ft_strcmp テストスイート
 * 統一的なテストフレームワークを使用
 * ============================================
 */

// 基本機能テスト
t_test_result test_strcmp_basic(void)
{
    // 同じ文字列の比較
    ASSERT_EQ(ft_strcmp("hello", "hello"), strcmp("hello", "hello"), "同じ文字列の比較結果が一致しない");
    ASSERT_EQ(ft_strcmp("", ""), strcmp("", ""), "空文字列同士の比較結果が一致しない");
    ASSERT_EQ(ft_strcmp("42", "42"), strcmp("42", "42"), "数字文字列の比較結果が一致しない");
    
    // 大小関係の一致確認（符号のみチェック）
    int ft_result = ft_strcmp("abc", "abd");
    int std_result = strcmp("abc", "abd");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    ft_result = ft_strcmp("abd", "abc");
    std_result = strcmp("abd", "abc");
    if ((ft_result > 0) != (std_result > 0)) {
        return TEST_FAIL;
    }
    
    return TEST_PASS;
}

// 空文字列テスト
t_test_result test_strcmp_empty_strings(void)
{
    // 空文字列との比較
    int ft_result = ft_strcmp("", "hello");
    int std_result = strcmp("", "hello");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    ft_result = ft_strcmp("hello", "");
    std_result = strcmp("hello", "");
    if ((ft_result > 0) != (std_result > 0)) {
        return TEST_FAIL;
    }
    
    // 両方空文字列
    ASSERT_EQ(ft_strcmp("", ""), strcmp("", ""), "両方空文字列の比較結果が一致しない");
    
    return TEST_PASS;
}

// 長さ違いテスト
t_test_result test_strcmp_different_lengths(void)
{
    // 長さが異なる文字列
    int ft_result = ft_strcmp("hello", "hello world");
    int std_result = strcmp("hello", "hello world");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    ft_result = ft_strcmp("hello world", "hello");
    std_result = strcmp("hello world", "hello");
    if ((ft_result > 0) != (std_result > 0)) {
        return TEST_FAIL;
    }
    
    // プレフィックス関係
    ft_result = ft_strcmp("test", "testing");
    std_result = strcmp("test", "testing");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    return TEST_PASS;
}

// 特殊文字テスト
t_test_result test_strcmp_special_chars(void)
{
    // 特殊文字を含む文字列
    ASSERT_EQ(ft_strcmp("hello!", "hello!"), strcmp("hello!", "hello!"), "感嘆符付き文字列の比較が一致しない");
    
    int ft_result = ft_strcmp("hello!", "hello?");
    int std_result = strcmp("hello!", "hello?");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    // 改行とタブ
    ft_result = ft_strcmp("test\n", "test\t");
    std_result = strcmp("test\n", "test\t");
    if ((ft_result > 0) != (std_result > 0)) {
        return TEST_FAIL;
    }
    
    // 数字と記号
    ASSERT_EQ(ft_strcmp("123", "123"), strcmp("123", "123"), "数字文字列の比較が一致しない");
    
    ft_result = ft_strcmp("123", "124");
    std_result = strcmp("123", "124");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    return TEST_PASS;
}

// 大文字小文字テスト
t_test_result test_strcmp_case_sensitivity(void)
{
    // 大文字小文字の比較（ASCIIコード順）
    int ft_result = ft_strcmp("Hello", "hello");
    int std_result = strcmp("Hello", "hello");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    ft_result = ft_strcmp("hello", "Hello");
    std_result = strcmp("hello", "Hello");
    if ((ft_result > 0) != (std_result > 0)) {
        return TEST_FAIL;
    }
    
    // 同じケース
    ASSERT_EQ(ft_strcmp("HELLO", "HELLO"), strcmp("HELLO", "HELLO"), "大文字同士の比較が一致しない");
    ASSERT_EQ(ft_strcmp("hello", "hello"), strcmp("hello", "hello"), "小文字同士の比較が一致しない");
    
    return TEST_PASS;
}

// 境界値・エッジケーステスト
t_test_result test_strcmp_edge_cases(void)
{
    // 1文字ずつの比較
    int ft_result = ft_strcmp("a", "b");
    int std_result = strcmp("a", "b");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    ft_result = ft_strcmp("z", "a");
    std_result = strcmp("z", "a");
    if ((ft_result > 0) != (std_result > 0)) {
        return TEST_FAIL;
    }
    
    // ASCII境界値
    ft_result = ft_strcmp("9", "A");  // '9' < 'A' in ASCII
    std_result = strcmp("9", "A");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    ft_result = ft_strcmp("Z", "a");  // 'Z' < 'a' in ASCII
    std_result = strcmp("Z", "a");
    if ((ft_result < 0) != (std_result < 0)) {
        return TEST_FAIL;
    }
    
    return TEST_PASS;
}

// 比較一致テスト
t_test_result test_strcmp_comparison(void)
{
    const char *test_pairs[][2] = {
        {"", ""},
        {"a", "a"},
        {"abc", "abc"},
        {"hello", "hello"},
        {"Hello", "hello"},
        {"hello", "Hello"},
        {"abc", "abd"},
        {"abd", "abc"},
        {"", "hello"},
        {"hello", ""},
        {"test", "testing"},
        {"testing", "test"},
        {"123", "123"},
        {"123", "124"},
        {"!", "?"},
        {"\n", "\t"},
        {NULL, NULL}
    };
    
    for (int i = 0; test_pairs[i][0] != NULL; i++) {
        int ft_result = ft_strcmp(test_pairs[i][0], test_pairs[i][1]);
        int std_result = strcmp(test_pairs[i][0], test_pairs[i][1]);
        
        // 符号の一致をチェック
        if ((ft_result == 0) != (std_result == 0) ||
            (ft_result < 0) != (std_result < 0) ||
            (ft_result > 0) != (std_result > 0)) {
            printf("  ✗ 比較失敗[%d]: \"%s\" vs \"%s\" ft_strcmp=%d strcmp=%d\n", 
                   i, test_pairs[i][0], test_pairs[i][1], ft_result, std_result);
            return TEST_FAIL;
        }
    }
    
    return TEST_PASS;
}

// パフォーマンステスト
t_test_result test_strcmp_performance(void)
{
    const char *perf_pairs[][2] = {
        {"短い1", "短い2"},
        {"中程度の長さの文字列1", "中程度の長さの文字列2"},
        {"これは非常に長い文字列です。パフォーマンステストのために使用します。", 
         "これは非常に長い文字列です。パフォーマンステストのために使用します。"}
    };
    
    for (int i = 0; i < 3; i++) {
        t_benchmark bench;
        char test_name[64];
        snprintf(test_name, sizeof(test_name), "strcmp_perf_%d", i);
        
        benchmark_start(&bench, test_name);
        bench.iterations = 10000;
        
        for (size_t j = 0; j < bench.iterations; j++) {
            ft_strcmp(perf_pairs[i][0], perf_pairs[i][1]);
        }
        
        benchmark_end(&bench);
        benchmark_print_result(&bench);
    }
    
    return TEST_PASS;
}

// メインテスト実行関数
void test_ft_strcmp(void)
{
    BEGIN_TEST_SUITE("ft_strcmp");
    
    TEST_CASE("基本機能", test_strcmp_basic);
    TEST_CASE("空文字列", test_strcmp_empty_strings);
    TEST_CASE("長さ違い", test_strcmp_different_lengths);
    TEST_CASE("特殊文字", test_strcmp_special_chars);
    TEST_CASE("大文字小文字", test_strcmp_case_sensitivity);
    TEST_CASE("境界値", test_strcmp_edge_cases);
    TEST_CASE("比較一致", test_strcmp_comparison);
    TEST_CASE("パフォーマンス", test_strcmp_performance);
    
    END_TEST_SUITE();
}

int main(void)
{
    init_test_stats();
    test_ft_strcmp();
    print_test_stats();
    
    cleanup_temp_files();
    return (g_stats.failed_tests == 0) ? 0 : 1;
} 