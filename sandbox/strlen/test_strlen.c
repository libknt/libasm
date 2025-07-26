#include <stdio.h>
#include <string.h>
#include <assert.h>

// アセンブリで実装したft_strlen関数の宣言
size_t ft_strlen(const char *s);

void test_ft_strlen(void)
{
    printf("=== ft_strlen テスト開始 ===\n");
    
    // テストケース1: 空文字列
    const char *test1 = "";
    size_t result1 = ft_strlen(test1);
    size_t expected1 = strlen(test1);
    printf("テスト1 (空文字列): ft_strlen=%zu, strlen=%zu ", result1, expected1);
    if (result1 == expected1) {
        printf("✓ PASS\n");
    } else {
        printf("✗ FAIL\n");
    }
    
    // テストケース2: 短い文字列
    const char *test2 = "Hello";
    size_t result2 = ft_strlen(test2);
    size_t expected2 = strlen(test2);
    printf("テスト2 (Hello): ft_strlen=%zu, strlen=%zu ", result2, expected2);
    if (result2 == expected2) {
        printf("✓ PASS\n");
    } else {
        printf("✗ FAIL\n");
    }
    
    // テストケース3: 長い文字列
    const char *test3 = "This is a longer string for testing purposes.";
    size_t result3 = ft_strlen(test3);
    size_t expected3 = strlen(test3);
    printf("テスト3 (長い文字列): ft_strlen=%zu, strlen=%zu ", result3, expected3);
    if (result3 == expected3) {
        printf("✓ PASS\n");
    } else {
        printf("✗ FAIL\n");
    }
    
    // テストケース4: 1文字
    const char *test4 = "A";
    size_t result4 = ft_strlen(test4);
    size_t expected4 = strlen(test4);
    printf("テスト4 (1文字): ft_strlen=%zu, strlen=%zu ", result4, expected4);
    if (result4 == expected4) {
        printf("✓ PASS\n");
    } else {
        printf("✗ FAIL\n");
    }
    
    // テストケース5: 数字と記号
    const char *test5 = "123!@#$%^&*()";
    size_t result5 = ft_strlen(test5);
    size_t expected5 = strlen(test5);
    printf("テスト5 (数字と記号): ft_strlen=%zu, strlen=%zu ", result5, expected5);
    if (result5 == expected5) {
        printf("✓ PASS\n");
    } else {
        printf("✗ FAIL\n");
    }
    
    printf("=== テスト完了 ===\n");
}

int main(void)
{
    test_ft_strlen();
    return 0;
} 