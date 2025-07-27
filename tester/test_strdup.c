#include "test_utils.h"

/*
 * ============================================
 * ft_strdup テストスイート
 * 統一的なテストフレームワークを使用
 * メモリ管理テストを含む
 * ============================================
 */

// 基本機能テスト
t_test_result test_strdup_basic(void)
{
    // 通常の文字列複製
    char *ft_result = ft_strdup("Hello, World!");
    char *std_result = strdup("Hello, World!");
    
    ASSERT_NOT_NULL(ft_result, "ft_strdupがNULLを返した");
    ASSERT_NOT_NULL(std_result, "strdupがNULLを返した");
    ASSERT_STR_EQ(ft_result, std_result, "複製された文字列が一致しない");
    
    // メモリアドレスが異なることを確認（const char* との比較を避けるため文字列リテラルのアドレスチェック）
    const char *original_literal = "Hello, World!";
    if (ft_result == original_literal) {
        free(ft_result);
        free(std_result);
        printf("  ✗ ft_strdupが新しいメモリを確保していない\n");
        return TEST_FAIL;
    }
    
    free(ft_result);
    free(std_result);
    
    // 空文字列
    ft_result = ft_strdup("");
    std_result = strdup("");
    
    ASSERT_NOT_NULL(ft_result, "空文字列のft_strdupがNULLを返した");
    ASSERT_NOT_NULL(std_result, "空文字列のstrdupがNULLを返した");
    ASSERT_STR_EQ(ft_result, std_result, "空文字列の複製が一致しない");
    
    free(ft_result);
    free(std_result);
    
    // 単一文字
    ft_result = ft_strdup("A");
    std_result = strdup("A");
    
    ASSERT_NOT_NULL(ft_result, "単一文字のft_strdupがNULLを返した");
    ASSERT_NOT_NULL(std_result, "単一文字のstrdupがNULLを返した");
    ASSERT_STR_EQ(ft_result, std_result, "単一文字の複製が一致しない");
    
    free(ft_result);
    free(std_result);
    
    return TEST_PASS;
}

// メモリアドレステスト
t_test_result test_strdup_memory_addresses(void)
{
    const char *original = "Memory address test";
    char *ft_result = ft_strdup(original);
    
    ASSERT_NOT_NULL(ft_result, "ft_strdupがNULLを返した");
    
    // アドレスが異なることを確認
    if (ft_result == original) {
        free(ft_result);
        printf("  ✗ ft_strdupが元の文字列と同じアドレスを返した\n");
        return TEST_FAIL;
    }
    
    // 内容が同じことを確認
    ASSERT_STR_EQ(ft_result, original, "複製された文字列の内容が異なる");
    
    // 複製を変更しても元に影響しないことを確認
    ft_result[0] = 'X';
    if (original[0] == 'X') {
        free(ft_result);
        printf("  ✗ 複製の変更が元の文字列に影響した\n");
        return TEST_FAIL;
    }
    
    free(ft_result);
    return TEST_PASS;
}

// 特殊文字テスト
t_test_result test_strdup_special_chars(void)
{
    const char *test_strings[] = {
        "Hello\nWorld",
        "Tab\tSeparated",
        "Quote\"Test",
        "Path\\Separator",
        "!@#$%^&*()",
        "Mixed\t\n\r!@#",
        "\x01\x02\x03\x04",  // 制御文字
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        char *ft_result = ft_strdup(test_strings[i]);
        char *std_result = strdup(test_strings[i]);
        
        ASSERT_NOT_NULL(ft_result, "特殊文字文字列のft_strdupがNULLを返した");
        ASSERT_NOT_NULL(std_result, "特殊文字文字列のstrdupがNULLを返した");
        
        if (strcmp(ft_result, std_result) != 0) {
            printf("  ✗ 特殊文字テスト失敗[%d]: \"%s\"\n", i, test_strings[i]);
            free(ft_result);
            free(std_result);
            return TEST_FAIL;
        }
        
        free(ft_result);
        free(std_result);
    }
    
    return TEST_PASS;
}

// 境界値テスト
t_test_result test_strdup_boundary(void)
{
    // 長い文字列テスト
    char *long_src = generate_large_string(1000);
    if (long_src) {
        char *ft_result = ft_strdup(long_src);
        char *std_result = strdup(long_src);
        
        ASSERT_NOT_NULL(ft_result, "長い文字列のft_strdupがNULLを返した");
        ASSERT_NOT_NULL(std_result, "長い文字列のstrdupがNULLを返した");
        
        if (strcmp(ft_result, std_result) != 0) {
            free(long_src);
            free(ft_result);
            free(std_result);
            return TEST_FAIL;
        }
        
        free(long_src);
        free(ft_result);
        free(std_result);
    }
    
    // 非常に長い文字列
    char *very_long_src = generate_large_string(10000);
    if (very_long_src) {
        char *ft_result = ft_strdup(very_long_src);
        char *std_result = strdup(very_long_src);
        
        ASSERT_NOT_NULL(ft_result, "非常に長い文字列のft_strdupがNULLを返した");
        ASSERT_NOT_NULL(std_result, "非常に長い文字列のstrdupがNULLを返した");
        
        if (strcmp(ft_result, std_result) != 0) {
            free(very_long_src);
            free(ft_result);
            free(std_result);
            return TEST_FAIL;
        }
        
        free(very_long_src);
        free(ft_result);
        free(std_result);
    }
    
    return TEST_PASS;
}

// メモリリークテスト
t_test_result test_strdup_memory_leak(void)
{
    // 多数の文字列を複製して解放
    const char *test_str = "Memory leak test string";
    
    for (int i = 0; i < 100; i++) {
        char *result = ft_strdup(test_str);
        ASSERT_NOT_NULL(result, "メモリリークテスト中にNULLが返された");
        ASSERT_STR_EQ(result, test_str, "メモリリークテスト中に内容が異なる");
        free(result);
    }
    
    // 異なるサイズの文字列でテスト
    for (int len = 1; len < 1000; len *= 2) {
        char *test_src = generate_large_string(len);
        if (test_src) {
            char *result = ft_strdup(test_src);
            ASSERT_NOT_NULL(result, "可変長文字列の複製でNULLが返された");
            
            if (strcmp(result, test_src) != 0) {
                free(test_src);
                free(result);
                return TEST_FAIL;
            }
            
            free(test_src);
            free(result);
        }
    }
    
    return TEST_PASS;
}

// 比較一致テスト
t_test_result test_strdup_comparison(void)
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
        "非常に長い文字列をテストしています。この文字列は標準ライブラリのstrdup関数と完全に同じ結果になるべきです。",
        "!@#$%^&*()_+{}|:\"<>?[]\\;',./`~",
        " Leading and trailing spaces ",
        "\t\n\r Mixed special chars",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        char *ft_result = ft_strdup(test_strings[i]);
        char *std_result = strdup(test_strings[i]);
        
        // NULLチェック
        if (!ft_result || !std_result) {
            printf("  ✗ NULL結果[%d]: ft=%p std=%p\n", i, (void*)ft_result, (void*)std_result);
            if (ft_result) free(ft_result);
            if (std_result) free(std_result);
            return TEST_FAIL;
        }
        
        // 内容チェック
        if (strcmp(ft_result, std_result) != 0) {
            printf("  ✗ 内容失敗[%d]: \"%s\" ft=\"%s\" std=\"%s\"\n", 
                   i, test_strings[i], ft_result, std_result);
            free(ft_result);
            free(std_result);
            return TEST_FAIL;
        }
        
        // 長さチェック
        if (strlen(ft_result) != strlen(std_result)) {
            printf("  ✗ 長さ失敗[%d]: ft=%zu std=%zu\n", 
                   i, strlen(ft_result), strlen(std_result));
            free(ft_result);
            free(std_result);
            return TEST_FAIL;
        }
        
        free(ft_result);
        free(std_result);
    }
    
    return TEST_PASS;
}

// パフォーマンステスト
t_test_result test_strdup_performance(void)
{
    const char *perf_strings[] = {
        "短い",
        "中程度の長さの文字列でパフォーマンステスト実行",
        "これは非常に長い文字列です。パフォーマンステストのために使用します。この文字列を何度も複製してft_strdup関数の性能を測定します。メモリ確保と文字列コピーの両方の処理時間を計測します。"
    };
    
    for (int i = 0; i < 3; i++) {
        t_benchmark bench;
        char test_name[64];
        
        snprintf(test_name, sizeof(test_name), "strdup_perf_%d", i);
        
        benchmark_start(&bench, test_name);
        bench.iterations = 1000;  // メモリ確保を伴うので回数を減らす
        
        for (size_t j = 0; j < bench.iterations; j++) {
            char *result = ft_strdup(perf_strings[i]);
            if (result) {
                free(result);
            }
        }
        
        benchmark_end(&bench);
        benchmark_print_result(&bench);
    }
    
    return TEST_PASS;
}

// メインテスト実行関数
void test_ft_strdup(void)
{
    BEGIN_TEST_SUITE("ft_strdup");
    
    TEST_CASE("基本機能", test_strdup_basic);
    TEST_CASE("メモリアドレス", test_strdup_memory_addresses);
    TEST_CASE("特殊文字", test_strdup_special_chars);
    TEST_CASE("境界値", test_strdup_boundary);
    TEST_CASE("メモリリーク", test_strdup_memory_leak);
    TEST_CASE("比較一致", test_strdup_comparison);
    TEST_CASE("パフォーマンス", test_strdup_performance);
    
    END_TEST_SUITE();
}

int main(void)
{
    init_test_stats();
    test_ft_strdup();
    print_test_stats();
    print_memory_stats();
    
    cleanup_temp_files();
    return (g_stats.failed_tests == 0) ? 0 : 1;
}