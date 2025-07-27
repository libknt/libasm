#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

char *ft_strcpy(char *dest, const char *src);

void test_ft_strcpy(void)
{
    printf("=== ft_strcpy テスト開始 ===\n");
    
    // テスト1: 通常の文字列コピー
    {
        char dest1[50];
        char dest2[50];
        const char *src = "Hello, World!";
        
        strcpy(dest1, src);
        ft_strcpy(dest2, src);
        
        assert(strcmp(dest1, dest2) == 0);
        printf("✓ テスト1 (通常の文字列): '%s'\n", dest2);
    }
    
    // テスト2: 空文字列
    {
        char dest1[10];
        char dest2[10];
        const char *src = "";
        
        strcpy(dest1, src);
        ft_strcpy(dest2, src);
        
        assert(strcmp(dest1, dest2) == 0);
        printf("✓ テスト2 (空文字列): '%s'\n", dest2);
    }
    
    // テスト3: 一文字の文字列
    {
        char dest1[10];
        char dest2[10];
        const char *src = "A";
        
        strcpy(dest1, src);
        ft_strcpy(dest2, src);
        
        assert(strcmp(dest1, dest2) == 0);
        printf("✓ テスト3 (一文字): '%s'\n", dest2);
    }
    
    // テスト4: 数字を含む文字列
    {
        char dest1[20];
        char dest2[20];
        const char *src = "42Tokyo";
        
        strcpy(dest1, src);
        ft_strcpy(dest2, src);
        
        assert(strcmp(dest1, dest2) == 0);
        printf("✓ テスト4 (数字を含む文字列): '%s'\n", dest2);
    }
    
    // テスト5: 特殊文字を含む文字列
    {
        char dest1[30];
        char dest2[30];
        const char *src = "Hello\n\tWorld!@#$%";
        
        strcpy(dest1, src);
        ft_strcpy(dest2, src);
        
        assert(strcmp(dest1, dest2) == 0);
        printf("✓ テスト5 (特殊文字を含む文字列): OK\n");
    }
    
    // テスト6: 戻り値の確認
    {
        char dest[20];
        const char *src = "Return test";
        char *result = ft_strcpy(dest, src);
        
        assert(result == dest);
        assert(strcmp(dest, src) == 0);
        printf("✓ テスト6 (戻り値の確認): OK\n");
    }
    
    printf("=== 全テスト完了 ===\n");
}

int main(void)
{
    test_ft_strcpy();
    return 0;
} 