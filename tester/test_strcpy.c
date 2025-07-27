#include "test_utils.h"

/*
 * ============================================
 * ft_strcpy テストスイート
 * 統一的なテストフレームワークを使用
 * ============================================
 */

// 基本機能テスト
t_test_result test_strcpy_basic(void)
{
    char dest1[100], dest2[100];
    
    // 通常の文字列コピー
    strcpy(dest1, "Hello, World!");
    ft_strcpy(dest2, "Hello, World!");
    ASSERT_STR_EQ(dest1, dest2, "通常文字列のコピー結果が一致しない");
    
    // 空文字列
    strcpy(dest1, "");
    ft_strcpy(dest2, "");
    ASSERT_STR_EQ(dest1, dest2, "空文字列のコピー結果が一致しない");
    
    // 単一文字
    strcpy(dest1, "A");
    ft_strcpy(dest2, "A");
    ASSERT_STR_EQ(dest1, dest2, "単一文字のコピー結果が一致しない");
    
    // 数字文字列
    strcpy(dest1, "123456789");
    ft_strcpy(dest2, "123456789");
    ASSERT_STR_EQ(dest1, dest2, "数字文字列のコピー結果が一致しない");
    
    return TEST_PASS;
}

// 戻り値テスト
t_test_result test_strcpy_return_value(void)
{
    char dest1[100], dest2[100];
    char *ret1, *ret2;
    
    // 戻り値がdestと一致するかテスト
    ret1 = strcpy(dest1, "Return test");
    ret2 = ft_strcpy(dest2, "Return test");
    
    if (ret1 != dest1) {
        printf("  ✗ 標準strcpyの戻り値が期待値と違う（テストエラー）\n");
        return TEST_ERROR;
    }
    
    if (ret2 != dest2) {
        printf("  ✗ ft_strcpyの戻り値がdestポインタと一致しない\n");
        return TEST_FAIL;
    }
    
    ASSERT_STR_EQ(dest1, dest2, "戻り値テスト時の文字列が一致しない");
    
    return TEST_PASS;
}

// 特殊文字テスト
t_test_result test_strcpy_special_chars(void)
{
    char dest1[200], dest2[200];
    
    // 改行・タブ文字
    strcpy(dest1, "Hello\nWorld");
    ft_strcpy(dest2, "Hello\nWorld");
    ASSERT_STR_EQ(dest1, dest2, "改行を含む文字列のコピーが一致しない");
    
    strcpy(dest1, "Tab\tSeparated");
    ft_strcpy(dest2, "Tab\tSeparated");
    ASSERT_STR_EQ(dest1, dest2, "タブを含む文字列のコピーが一致しない");
    
    // 特殊記号
    strcpy(dest1, "!@#$%^&*()_+{}|:\"<>?");
    ft_strcpy(dest2, "!@#$%^&*()_+{}|:\"<>?");
    ASSERT_STR_EQ(dest1, dest2, "特殊記号のコピーが一致しない");
    
    // 複合特殊文字
    strcpy(dest1, "Mixed\t\n\r!@#");
    ft_strcpy(dest2, "Mixed\t\n\r!@#");
    ASSERT_STR_EQ(dest1, dest2, "複合特殊文字のコピーが一致しない");
    
    // エスケープシーケンス
    strcpy(dest1, "Quote\"Test\\Path");
    ft_strcpy(dest2, "Quote\"Test\\Path");
    ASSERT_STR_EQ(dest1, dest2, "エスケープシーケンスのコピーが一致しない");
    
    return TEST_PASS;
}

// 境界値テスト
t_test_result test_strcpy_boundary(void)
{
    // 長い文字列テスト
    char *long_src = generate_large_string(1000);
    if (long_src) {
        char *dest1 = malloc(1001);
        char *dest2 = malloc(1001);
        
        if (dest1 && dest2) {
            strcpy(dest1, long_src);
            ft_strcpy(dest2, long_src);
            
            if (strcmp(dest1, dest2) != 0) {
                free(long_src);
                free(dest1);
                free(dest2);
                return TEST_FAIL;
            }
        }
        
        free(long_src);
        free(dest1);
        free(dest2);
    }
    
    // 固定サイズ境界値
    char boundary_src[512];
    char dest1[512], dest2[512];
    
    memset(boundary_src, 'X', 511);
    boundary_src[511] = '\0';
    
    strcpy(dest1, boundary_src);
    ft_strcpy(dest2, boundary_src);
    ASSERT_STR_EQ(dest1, dest2, "511文字の境界値文字列のコピーが一致しない");
    
    return TEST_PASS;
}

// オーバーライトテスト
t_test_result test_strcpy_overwrite(void)
{
    char dest1[100], dest2[100];
    
    // 既存の内容を上書き
    strcpy(dest1, "Original Content");
    strcpy(dest2, "Original Content");
    
    strcpy(dest1, "New");
    ft_strcpy(dest2, "New");
    ASSERT_STR_EQ(dest1, dest2, "オーバーライト後の文字列が一致しない");
    
    // 長い文字列から短い文字列へ
    strcpy(dest1, "Very long original string");
    strcpy(dest2, "Very long original string");
    
    strcpy(dest1, "Short");
    ft_strcpy(dest2, "Short");
    ASSERT_STR_EQ(dest1, dest2, "長→短オーバーライト後の文字列が一致しない");
    
    // NULL終端の確認
    if (strlen(dest1) != strlen(dest2)) {
        return TEST_FAIL;
    }
    
    return TEST_PASS;
}

// 比較一致テスト
t_test_result test_strcpy_comparison(void)
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
        "非常に長い文字列をテストしています。この文字列は標準ライブラリのstrcpy関数と完全に同じ結果になるべきです。",
        "!@#$%^&*()_+{}|:\"<>?[]\\;',./`~",
        " Leading and trailing spaces ",
        "\t\n\r\0Mixed\0Hidden", // NULL文字までしかコピーされない
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        char dest1[1000], dest2[1000];
        
        // バッファを初期化（ゴミデータで）
        memset(dest1, 0xFF, sizeof(dest1));
        memset(dest2, 0xFF, sizeof(dest2));
        
        char *ret1 = strcpy(dest1, test_strings[i]);
        char *ret2 = ft_strcpy(dest2, test_strings[i]);
        
        // 戻り値チェック
        if (ret1 != dest1 || ret2 != dest2) {
            printf("  ✗ 戻り値失敗[%d]: 標準=%p(期待%p) ft=%p(期待%p)\n", 
                   i, (void*)ret1, (void*)dest1, (void*)ret2, (void*)dest2);
            return TEST_FAIL;
        }
        
        // 内容チェック
        if (strcmp(dest1, dest2) != 0) {
            printf("  ✗ 内容失敗[%d]: \"%s\" 標準=\"%s\" ft=\"%s\"\n", 
                   i, test_strings[i], dest1, dest2);
            return TEST_FAIL;
        }
    }
    
    return TEST_PASS;
}

// パフォーマンステスト
t_test_result test_strcpy_performance(void)
{
    const char *perf_strings[] = {
        "短い",
        "中程度の長さの文字列でパフォーマンステスト実行",
        "これは非常に長い文字列です。パフォーマンステストのために使用します。この文字列を何度もコピーしてft_strcpy関数の性能を測定します。"
    };
    
    for (int i = 0; i < 3; i++) {
        t_benchmark bench;
        char test_name[64];
        char dest[1000];
        
        snprintf(test_name, sizeof(test_name), "strcpy_perf_%d", i);
        
        benchmark_start(&bench, test_name);
        bench.iterations = 10000;
        
        for (size_t j = 0; j < bench.iterations; j++) {
            ft_strcpy(dest, perf_strings[i]);
        }
        
        benchmark_end(&bench);
        benchmark_print_result(&bench);
    }
    
    return TEST_PASS;
}

// メインテスト実行関数
void test_ft_strcpy(void)
{
    BEGIN_TEST_SUITE("ft_strcpy");
    
    TEST_CASE("基本機能", test_strcpy_basic);
    TEST_CASE("戻り値", test_strcpy_return_value);
    TEST_CASE("特殊文字", test_strcpy_special_chars);
    TEST_CASE("境界値", test_strcpy_boundary);
    TEST_CASE("オーバーライト", test_strcpy_overwrite);
    TEST_CASE("比較一致", test_strcpy_comparison);
    TEST_CASE("パフォーマンス", test_strcpy_performance);
    
    END_TEST_SUITE();
}

int main(void)
{
    init_test_stats();
    test_ft_strcpy();
    print_test_stats();
    
    cleanup_temp_files();
    return (g_stats.failed_tests == 0) ? 0 : 1;
} 