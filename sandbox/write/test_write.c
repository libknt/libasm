#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

int ft_write(const char *s1, const char *s2);

void test_basic_write(void)
{
    printf("=== 基本的な書き込みテスト ===\n");
    
    // 基本的な文字列の書き込み
    int result = ft_write("Hello", "World");
    printf("ft_write(\"Hello\", \"World\") の戻り値: %d\n", result);
    
    // 単一文字列のテスト
    result = ft_write("Test", "");
    printf("ft_write(\"Test\", \"\") の戻り値: %d\n", result);
    
    // 空文字列のテスト
    result = ft_write("", "");
    printf("ft_write(\"\", \"\") の戻り値: %d\n", result);
}

void test_edge_cases(void)
{
    printf("\n=== エッジケースのテスト ===\n");
    
    // 長い文字列のテスト
    char long_str[1000];
    memset(long_str, 'A', 999);
    long_str[999] = '\0';
    
    int result = ft_write(long_str, "END");
    printf("長い文字列のテスト - 戻り値: %d\n", result);
    
    // 特殊文字のテスト
    result = ft_write("改行\nタブ\t文字", "特殊");
    printf("特殊文字のテスト - 戻り値: %d\n", result);
}

void test_null_cases(void)
{
    printf("\n=== NULLポインタのテスト ===\n");
    
    // NULLポインタのテスト（セグフォルトを避けるため注意深く）
    printf("注意: NULLポインタのテストは実装次第でセグフォルトする可能性があります\n");
    
    // コメントアウトしたテスト（必要に応じて有効化）
    /*
    int result = ft_write(NULL, "test");
    printf("ft_write(NULL, \"test\") の戻り値: %d\n", result);
    
    result = ft_write("test", NULL);
    printf("ft_write(\"test\", NULL) の戻り値: %d\n", result);
    
    result = ft_write(NULL, NULL);
    printf("ft_write(NULL, NULL) の戻り値: %d\n", result);
    */
}

void test_comparison_with_standard(void)
{
    printf("\n=== 標準関数との比較テスト ===\n");
    
    // 標準のwrite関数との動作比較（参考）
    printf("標準write関数の動作例:\n");
    ssize_t std_result = write(1, "Standard write: Hello\n", 22);
    printf("標準write関数の戻り値: %zd\n", std_result);
    
    printf("ft_write関数の動作:\n");
    int ft_result = ft_write("ft_write: Hello", "\n");
    printf("ft_write関数の戻り値: %d\n", ft_result);
}

void test_ft_write(void)
{
    printf("=== ft_write テスト開始 ===\n");
    
    test_basic_write();
    test_edge_cases();
    test_null_cases();
    test_comparison_with_standard();
    
    printf("\n=== 全テスト完了 ===\n");
    printf("注意: ft_write関数が未実装の場合、期待した結果が得られない可能性があります\n");
}

int main(void)
{
    test_ft_write();
    return 0;
} 