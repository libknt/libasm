#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// アセンブリ関数のプロトタイプ宣言
char *ft_strcpy(char *dst, const char *src);

int main(void)
{
    char src[] = "Hello, World!";
    char dst1[50];
    char dst2[50];
    char *result;
    
    printf("=== ft_strcpy テスト ===\n");
    printf("src: \"%s\"\n", src);
    
    // ft_strcpyのテスト
    result = ft_strcpy(dst1, src);
    printf("\nft_strcpy結果:\n");
    printf("dst: \"%s\"\n", dst1);
    printf("戻り値: %p\n", result);
    printf("dstアドレス: %p\n", dst1);
    printf("戻り値 == dstアドレス: %s\n", (result == dst1) ? "OK" : "NG");
    
    // 標準strcpyとの比較
    strcpy(dst2, src);
    printf("\n標準strcpy結果: \"%s\"\n", dst2);
    printf("結果の比較: %s\n", (strcmp(dst1, dst2) == 0) ? "一致" : "不一致");
    
    // 空文字列のテスト
    char empty_src[] = "";
    char empty_dst1[10];
    char empty_dst2[10];
    
    ft_strcpy(empty_dst1, empty_src);
    strcpy(empty_dst2, empty_src);
    
    printf("\n空文字列テスト:\n");
    printf("ft_strcpy: \"%s\" (length: %zu)\n", empty_dst1, strlen(empty_dst1));
    printf("strcpy:    \"%s\" (length: %zu)\n", empty_dst2, strlen(empty_dst2));
    printf("結果の比較: %s\n", (strcmp(empty_dst1, empty_dst2) == 0) ? "一致" : "不一致");
    
    return 0;
} 