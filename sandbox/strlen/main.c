#include <stdio.h>
#include <string.h> // 標準のstrlenと比較するため

// アセンブリで実装する関数を宣言
extern size_t ft_strlen(const char *str);

int main() {
    const char *s1 = "Hello, World!";
    const char *s2 = "programming";
    const char *s3 = ""; // 空文字列
    const char *s4 = "a"; // 1文字

    size_t my_len;
    size_t lib_len;

    printf("--- Test ft_strlen ---\n");

    // Test 1
    my_len = ft_strlen(s1);
    lib_len = strlen(s1);
    printf("String: \"%s\"\n", s1);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen (lib): %zu\n", lib_len);
    printf("  Match: %s\n\n", (my_len == lib_len) ? "YES" : "NO");

    // Test 2
    my_len = ft_strlen(s2);
    lib_len = strlen(s2);
    printf("String: \"%s\"\n", s2);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen (lib): %zu\n", lib_len);
    printf("  Match: %s\n\n", (my_len == lib_len) ? "YES" : "NO");

    // Test 3: Empty string
    my_len = ft_strlen(s3);
    lib_len = strlen(s3);
    printf("String: \"%s\" (empty)\n", s3);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen (lib): %zu\n", lib_len);
    printf("  Match: %s\n\n", (my_len == lib_len) ? "YES" : "NO");

    // Test 4: Single character string
    my_len = ft_strlen(s4);
    lib_len = strlen(s4);
    printf("String: \"%s\" (single char)\n", s4);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen (lib): %zu\n", lib_len);
    printf("  Match: %s\n\n", (my_len == lib_len) ? "YES" : "NO");

    return 0;
}
