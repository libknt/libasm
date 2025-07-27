#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t ft_write(int fd, const void *buf, size_t count);

void test_basic_write() {
    printf("=== Basic Write Test ===\n");
    
    // Test with stdout
    const char *msg = "Hello, World!\n";
    ssize_t ft_result = ft_write(1, msg, strlen(msg));
    printf("ft_write returned: %zd\n", ft_result);
    
    // Compare with standard write
    ssize_t std_result = write(1, msg, strlen(msg));
    printf("write returned: %zd\n", std_result);
    
    assert(ft_result == std_result);
    printf("✓ Basic write test passed\n\n");
}

void test_write_to_file() {
    printf("=== File Write Test ===\n");
    
    // Create test file
    int fd = open("test_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create test file");
        return;
    }
    
    const char *content = "This is a test file content.\n";
    ssize_t ft_result = ft_write(fd, content, strlen(content));
    
    printf("ft_write to file returned: %zd\n", ft_result);
    assert(ft_result == (ssize_t)strlen(content));
    
    close(fd);
    
    // Verify file content
    fd = open("test_output.txt", O_RDONLY);
    char buffer[100];
    ssize_t read_bytes = read(fd, buffer, sizeof(buffer) - 1);
    buffer[read_bytes] = '\0';
    close(fd);
    
    assert(strcmp(buffer, content) == 0);
    printf("✓ File write test passed\n\n");
    
    // Clean up
    unlink("test_output.txt");
}

void test_empty_write() {
    printf("=== Empty Write Test ===\n");
    
    ssize_t ft_result = ft_write(1, "", 0);
    ssize_t std_result = write(1, "", 0);
    
    printf("ft_write(empty) returned: %zd\n", ft_result);
    printf("write(empty) returned: %zd\n", std_result);
    
    assert(ft_result == std_result);
    printf("✓ Empty write test passed\n\n");
}

void test_invalid_fd() {
    printf("=== Invalid FD Test ===\n");
    
    const char *msg = "test";
    errno = 0;
    ssize_t ft_result = ft_write(-1, msg, strlen(msg));
    int ft_errno = errno;
    
    errno = 0;
    ssize_t std_result = write(-1, msg, strlen(msg));
    int std_errno = errno;
    
    printf("ft_write(invalid fd) returned: %zd, errno: %d\n", ft_result, ft_errno);
    printf("write(invalid fd) returned: %zd, errno: %d\n", std_result, std_errno);
    
    assert(ft_result == std_result);
    assert(ft_errno == std_errno);
    printf("✓ Invalid FD test passed\n\n");
}

void test_large_write() {
    printf("=== Large Write Test ===\n");
    
    // Create a large buffer
    size_t size = 1024;
    char *buffer = malloc(size);
    memset(buffer, 'A', size - 1);
    buffer[size - 1] = '\0';
    
    ssize_t ft_result = ft_write(1, buffer, size - 1);
    printf("\nft_write(large) returned: %zd\n", ft_result);
    
    assert(ft_result == (ssize_t)(size - 1));
    printf("✓ Large write test passed\n\n");
    
    free(buffer);
}

int main() {
    printf("Starting ft_write tests...\n\n");
    
    test_basic_write();
    test_empty_write();
    test_write_to_file();
    test_invalid_fd();
    test_large_write();
    
    printf("All tests passed! ✨\n");
    return 0;
}  
