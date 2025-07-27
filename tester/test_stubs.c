#include "test_utils.h"

/*
 * ============================================
 * LIBASM関数のスタブ実装（テスト用）
 * 実際のアセンブリ実装の代わりに標準ライブラリを使用
 * ============================================
 */

size_t ft_strlen(const char *s)
{
    return strlen(s);
}

int ft_strcmp(const char *s1, const char *s2)
{
    return strcmp(s1, s2);
}

char *ft_strcpy(char *dest, const char *src)
{
    return strcpy(dest, src);
}

char *ft_strdup(const char *s)
{
    return strdup(s);
}

ssize_t ft_write(int fd, const void *buf, size_t count)
{
    return write(fd, buf, count);
}

ssize_t ft_read(int fd, void *buf, size_t count)
{
    return read(fd, buf, count);
} 