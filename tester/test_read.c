#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t ft_read(int fd, void *buf, size_t count);

void test_read_normal_file() {
    printf("Testing normal file read...\n");
    
    // テスト用ファイルを作成
    int fd = open("test_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    assert(fd != -1);
    write(fd, "Hello, World!", 13);
    close(fd);
    
    // ファイルを読み取り用に開く
    fd = open("test_file.txt", O_RDONLY);
    assert(fd != -1);
    
    char buf[20];
    memset(buf, 0, sizeof(buf));
    
    // ft_readでファイルを読み取り
    ssize_t bytes_read = ft_read(fd, buf, 13);
    
    printf("  Expected: 13 bytes, Got: %zd bytes\n", bytes_read);
    printf("  Content: '%s'\n", buf);
    
    assert(bytes_read == 13);
    assert(strcmp(buf, "Hello, World!") == 0);
    
    close(fd);
    unlink("test_file.txt");
    printf("  ✓ Normal file read test passed\n\n");
}

void test_read_partial() {
    printf("Testing partial read...\n");
    
    // テスト用ファイルを作成
    int fd = open("test_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    assert(fd != -1);
    write(fd, "Hello, World!", 13);
    close(fd);
    
    // ファイルを読み取り用に開く
    fd = open("test_file.txt", O_RDONLY);
    assert(fd != -1);
    
    char buf[10];
    memset(buf, 0, sizeof(buf));
    
    // 部分的に読み取り
    ssize_t bytes_read = ft_read(fd, buf, 5);
    
    printf("  Expected: 5 bytes, Got: %zd bytes\n", bytes_read);
    printf("  Content: '%s'\n", buf);
    
    assert(bytes_read == 5);
    assert(strncmp(buf, "Hello", 5) == 0);
    
    close(fd);
    unlink("test_file.txt");
    printf("  ✓ Partial read test passed\n\n");
}

void test_read_zero_bytes() {
    printf("Testing zero byte read...\n");
    
    // テスト用ファイルを作成
    int fd = open("test_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    assert(fd != -1);
    write(fd, "Hello", 5);
    close(fd);
    
    fd = open("test_file.txt", O_RDONLY);
    assert(fd != -1);
    
    char buf[10];
    memset(buf, 0, sizeof(buf));
    
    // 0バイト読み取り
    ssize_t bytes_read = ft_read(fd, buf, 0);
    
    printf("  Expected: 0 bytes, Got: %zd bytes\n", bytes_read);
    
    assert(bytes_read == 0);
    
    close(fd);
    unlink("test_file.txt");
    printf("  ✓ Zero byte read test passed\n\n");
}

void test_read_invalid_fd() {
    printf("Testing invalid file descriptor...\n");
    
    char buf[10];
    errno = 0;
    
    // 無効なファイルディスクリプタで読み取り
    ssize_t bytes_read = ft_read(-1, buf, 10);
    
    printf("  Expected: -1, Got: %zd\n", bytes_read);
    printf("  errno: %d (%s)\n", errno, strerror(errno));
    
    assert(bytes_read == -1);
    assert(errno == EBADF);
    
    printf("  ✓ Invalid file descriptor test passed\n\n");
}

void test_read_null_buffer() {
    printf("Testing NULL buffer...\n");
    
    // テスト用ファイルを作成
    int fd = open("test_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    assert(fd != -1);
    write(fd, "Hello", 5);
    close(fd);
    
    fd = open("test_file.txt", O_RDONLY);
    assert(fd != -1);
    
    errno = 0;
    
    // NULLバッファで読み取り
    ssize_t bytes_read = ft_read(fd, NULL, 5);
    
    printf("  Expected: -1, Got: %zd\n", bytes_read);
    printf("  errno: %d (%s)\n", errno, strerror(errno));
    
    assert(bytes_read == -1);
    assert(errno == EFAULT);
    
    close(fd);
    unlink("test_file.txt");
    printf("  ✓ NULL buffer test passed\n\n");
}

void test_read_stdin() {
    printf("Testing stdin read (manual test - requires user input)...\n");
    printf("  This test is skipped in automated testing\n");
    printf("  To manually test: echo 'test' | ./test_program\n\n");
}

int main() {
    printf("=== ft_read function tests ===\n\n");
    
    test_read_normal_file();
    test_read_partial();
    test_read_zero_bytes();
    test_read_invalid_fd();
    test_read_null_buffer();
    test_read_stdin();
    
    printf("=== All tests passed! ===\n");
    return 0;
}
