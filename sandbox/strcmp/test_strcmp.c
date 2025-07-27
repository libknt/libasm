#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int ft_strcmp(const char *s1, const char *s2);

void test_ft_strcmp(void)
{
    printf("=== ft_strcmp テスト開始 ===\n");
    
    // テスト1: 同じ文字列の比較
    printf("テスト1: 同じ文字列の比較\n");
    assert(ft_strcmp("hello", "hello") == strcmp("hello", "hello"));
    assert(ft_strcmp("", "") == strcmp("", ""));
    assert(ft_strcmp("42", "42") == strcmp("42", "42"));
    printf("  ✓ 同じ文字列の比較: 成功\n");
    
    // テスト2: 異なる文字列の比較 (第1引数 < 第2引数)
    printf("テスト2: 第1引数 < 第2引数\n");
    assert((ft_strcmp("abc", "abd") < 0) == (strcmp("abc", "abd") < 0));
    assert((ft_strcmp("hello", "world") < 0) == (strcmp("hello", "world") < 0));
    assert((ft_strcmp("A", "B") < 0) == (strcmp("A", "B") < 0));
    printf("  ✓ 第1引数 < 第2引数: 成功\n");
    
    // テスト3: 異なる文字列の比較 (第1引数 > 第2引数)
    printf("テスト3: 第1引数 > 第2引数\n");
    assert((ft_strcmp("abd", "abc") > 0) == (strcmp("abd", "abc") > 0));
    assert((ft_strcmp("world", "hello") > 0) == (strcmp("world", "hello") > 0));
    assert((ft_strcmp("B", "A") > 0) == (strcmp("B", "A") > 0));
    printf("  ✓ 第1引数 > 第2引数: 成功\n");
    
    // テスト4: 空文字列との比較
    printf("テスト4: 空文字列との比較\n");
    assert((ft_strcmp("", "hello") < 0) == (strcmp("", "hello") < 0));
    assert((ft_strcmp("hello", "") > 0) == (strcmp("hello", "") > 0));
    printf("  ✓ 空文字列との比較: 成功\n");
    
    // テスト5: 長さが異なる文字列の比較
    printf("テスト5: 長さが異なる文字列\n");
    assert((ft_strcmp("hello", "hello world") < 0) == (strcmp("hello", "hello world") < 0));
    assert((ft_strcmp("hello world", "hello") > 0) == (strcmp("hello world", "hello") > 0));
    assert(ft_strcmp("test", "test") == strcmp("test", "test"));
    printf("  ✓ 長さが異なる文字列: 成功\n");
    
    // テスト6: 数値文字列の比較
    printf("テスト6: 数値文字列の比較\n");
    assert(ft_strcmp("123", "123") == strcmp("123", "123"));
    assert((ft_strcmp("123", "124") < 0) == (strcmp("123", "124") < 0));
    assert((ft_strcmp("124", "123") > 0) == (strcmp("124", "123") > 0));
    printf("  ✓ 数値文字列の比較: 成功\n");
    
    // テスト7: 特殊文字を含む文字列
    printf("テスト7: 特殊文字を含む文字列\n");
    assert(ft_strcmp("hello!", "hello!") == strcmp("hello!", "hello!"));
    assert((ft_strcmp("hello!", "hello?") < 0) == (strcmp("hello!", "hello?") < 0));
    assert((ft_strcmp("test\n", "test\t") > 0) == (strcmp("test\n", "test\t") > 0));
    printf("  ✓ 特殊文字を含む文字列: 成功\n");
    
    // テスト8: 大文字小文字の比較
    printf("テスト8: 大文字小文字の比較\n");
    assert((ft_strcmp("Hello", "hello") < 0) == (strcmp("Hello", "hello") < 0));
    assert((ft_strcmp("hello", "Hello") > 0) == (strcmp("hello", "Hello") > 0));
    assert(ft_strcmp("HELLO", "HELLO") == strcmp("HELLO", "HELLO"));
    printf("  ✓ 大文字小文字の比較: 成功\n");
    
    printf("=== 全テスト完了 ===\n");
}

int main(void)
{
    test_ft_strcmp();
    return 0;
} 