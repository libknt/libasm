#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ft_strcpy(char *dst, const char *src);

int test_case(const char *description, const char *src) {
    char dst1[1000];
    char dst2[1000];
    char *result;
    
    printf("\n--- %s ---\n", description);
    printf("src: \"%s\" (length: %zu)\n", src, strlen(src));
    
    // ft_strcpyのテスト
    result = ft_strcpy(dst1, src);
    
    // 標準strcpyとの比較
    strcpy(dst2, src);
    
    printf("ft_strcpy: \"%s\"\n", dst1);
    printf("strcpy:    \"%s\"\n", dst2);
    
    int match = (strcmp(dst1, dst2) == 0);
    int return_match = (result == dst1);
    
    printf("文字列一致: %s\n", match ? "✅" : "❌");
    printf("戻り値一致: %s\n", return_match ? "✅" : "❌");
    
    return match && return_match;
}

int main(void) {
    int total_tests = 0;
    int passed_tests = 0;
    
    printf("=== ft_strcpy 詳細テスト ===\n");
    
    // テストケース一覧
    struct {
        const char *description;
        const char *src;
    } tests[] = {
        {"空文字列", ""},
        {"1文字", "a"},
        {"短い文字列", "abc"},
        {"標準的な文字列", "Hello, World!"},
        {"長い文字列", "This is a very long string to test the strcpy function with many characters."},
        {"数字文字列", "1234567890"},
        {"特殊文字", "!@#$%^&*()"},
        {"空白文字", "   spaces   "},
        {"改行を含む", "line1\nline2"},
        {"タブを含む", "before\tafter"},
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < num_tests; i++) {
        total_tests++;
        if (test_case(tests[i].description, tests[i].src)) {
            passed_tests++;
        }
    }
    
    printf("\n=== テスト結果 ===\n");
    printf("実行: %d/%d\n", passed_tests, total_tests);
    if (passed_tests == total_tests) {
        printf("🎉 全テスト成功！\n");
    } else {
        printf("❌ %d個のテストが失敗\n", total_tests - passed_tests);
    }
    
    return (passed_tests == total_tests) ? 0 : 1;
} 