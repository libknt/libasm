#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

char * ft_strdup(const char *str);

void test_ft_strdup(void)
{
    printf("=== ft_strdup テスト開始 ===\n");
    
    // テスト1: 通常の文字列の複製
    printf("テスト1: 通常の文字列の複製\n");
    const char *test1 = "Hello, World!";
    char *result1 = ft_strdup(test1);
    char *expected1 = strdup(test1);
    if (result1 != NULL && expected1 != NULL) {
        printf("  元の文字列: \"%s\"\n", test1);
        printf("  ft_strdup: \"%s\"\n", result1);
        printf("  strdup: \"%s\"\n", expected1);
        if (strcmp(result1, expected1) == 0 && result1 != test1) {
            printf("  ✓ 通常の文字列の複製: 成功\n");
        } else {
            printf("  ✗ 通常の文字列の複製: 失敗\n");
        }
        free(result1);
        free(expected1);
    } else {
        printf("  ✗ 通常の文字列の複製: メモリ確保失敗\n");
    }
    
    // テスト2: 空文字列の複製
    printf("テスト2: 空文字列の複製\n");
    const char *test2 = "";
    char *result2 = ft_strdup(test2);
    char *expected2 = strdup(test2);
    if (result2 != NULL && expected2 != NULL) {
        printf("  元の文字列: \"%s\" (長さ: %zu)\n", test2, strlen(test2));
        printf("  ft_strdup: \"%s\" (長さ: %zu)\n", result2, strlen(result2));
        if (strcmp(result2, expected2) == 0 && strlen(result2) == 0) {
            printf("  ✓ 空文字列の複製: 成功\n");
        } else {
            printf("  ✗ 空文字列の複製: 失敗\n");
        }
        free(result2);
        free(expected2);
    } else {
        printf("  ✗ 空文字列の複製: メモリ確保失敗\n");
    }
    
    // テスト3: 長い文字列の複製
    printf("テスト3: 長い文字列の複製\n");
    const char *test3 = "This is a very long string for testing the ft_strdup function implementation. It contains multiple words and punctuation marks to ensure proper duplication.";
    char *result3 = ft_strdup(test3);
    char *expected3 = strdup(test3);
    if (result3 != NULL && expected3 != NULL) {
        printf("  元の文字列長: %zu\n", strlen(test3));
        printf("  ft_strdup長: %zu\n", strlen(result3));
        if (strcmp(result3, expected3) == 0 && strlen(result3) == strlen(test3)) {
            printf("  ✓ 長い文字列の複製: 成功\n");
        } else {
            printf("  ✗ 長い文字列の複製: 失敗\n");
        }
        free(result3);
        free(expected3);
    } else {
        printf("  ✗ 長い文字列の複製: メモリ確保失敗\n");
    }
    
    // テスト4: 特殊文字を含む文字列
    printf("テスト4: 特殊文字を含む文字列\n");
    const char *test4 = "Hello\nWorld\t!@#$%^&*()";
    char *result4 = ft_strdup(test4);
    char *expected4 = strdup(test4);
    if (result4 != NULL && expected4 != NULL) {
        printf("  元の文字列: \"%s\"\n", test4);
        printf("  ft_strdup: \"%s\"\n", result4);
        if (strcmp(result4, expected4) == 0) {
            printf("  ✓ 特殊文字を含む文字列: 成功\n");
        } else {
            printf("  ✗ 特殊文字を含む文字列: 失敗\n");
        }
        free(result4);
        free(expected4);
    } else {
        printf("  ✗ 特殊文字を含む文字列: メモリ確保失敗\n");
    }
    
    // テスト5: 1文字の文字列
    printf("テスト5: 1文字の文字列\n");
    const char *test5 = "A";
    char *result5 = ft_strdup(test5);
    char *expected5 = strdup(test5);
    if (result5 != NULL && expected5 != NULL) {
        printf("  元の文字列: \"%s\"\n", test5);
        printf("  ft_strdup: \"%s\"\n", result5);
        if (strcmp(result5, expected5) == 0) {
            printf("  ✓ 1文字の文字列: 成功\n");
        } else {
            printf("  ✗ 1文字の文字列: 失敗\n");
        }
        free(result5);
        free(expected5);
    } else {
        printf("  ✗ 1文字の文字列: メモリ確保失敗\n");
    }
    
    // テスト6: 数値文字列
    printf("テスト6: 数値文字列\n");
    const char *test6 = "1234567890";
    char *result6 = ft_strdup(test6);
    char *expected6 = strdup(test6);
    if (result6 != NULL && expected6 != NULL) {
        printf("  元の文字列: \"%s\"\n", test6);
        printf("  ft_strdup: \"%s\"\n", result6);
        if (strcmp(result6, expected6) == 0) {
            printf("  ✓ 数値文字列: 成功\n");
        } else {
            printf("  ✗ 数値文字列: 失敗\n");
        }
        free(result6);
        free(expected6);
    } else {
        printf("  ✗ 数値文字列: メモリ確保失敗\n");
    }
    
    // テスト7: メモリアドレスの違いを確認
    printf("テスト7: メモリアドレスの違いを確認\n");
    const char *test7 = "Address test";
    char *result7 = ft_strdup(test7);
    if (result7 != NULL) {
        printf("  元の文字列のアドレス: %p\n", (void*)test7);
        printf("  ft_strdupのアドレス: %p\n", (void*)result7);
        if (result7 != test7 && strcmp(result7, test7) == 0) {
            printf("  ✓ メモリアドレスの違い: 成功（正しく新しいメモリが確保されています）\n");
        } else {
            printf("  ✗ メモリアドレスの違い: 失敗\n");
        }
        free(result7);
    } else {
        printf("  ✗ メモリアドレスの違い: メモリ確保失敗\n");
    }
    
    printf("=== 全テスト完了 ===\n");
}

int main(void)
{
    test_ft_strdup();
    return 0;
}