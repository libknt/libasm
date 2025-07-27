#include "test_utils.h"
#include <fcntl.h>

/*
 * ============================================
 * ft_read テストスイート
 * 統一的なテストフレームワークを使用
 * ファイルI/Oとエラーハンドリングテストを含む
 * ============================================
 */

// 基本機能テスト
t_test_result test_read_basic(void)
{
    char temp_file[256];
    const char *test_data = "Hello, World!";
    
    if (create_temp_file(test_data, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    // 基本的な読み込み
    char ft_buffer[100];
    ssize_t ft_result = ft_read(fd, ft_buffer, sizeof(ft_buffer) - 1);
    close(fd);
    
    ft_buffer[ft_result] = '\0';
    
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, (ssize_t)strlen(test_data), "読み込みバイト数が期待値と一致しない");
    ASSERT_STR_EQ(ft_buffer, test_data, "読み込まれた内容が期待値と一致しない");
    
    return TEST_PASS;
}

// 標準入力テスト（非対話的）
t_test_result test_read_stdin_simulation(void)
{
    // 標準入力のテストは非対話的に行うため、
    // パイプを使用してシミュレーション
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return TEST_ERROR;
    }
    
    const char *test_input = "Standard input test\n";
    write(pipefd[1], test_input, strlen(test_input));
    close(pipefd[1]);
    
    char ft_buffer[100];
    ssize_t ft_result = ft_read(pipefd[0], ft_buffer, sizeof(ft_buffer) - 1);
    close(pipefd[0]);
    
    ft_buffer[ft_result] = '\0';
    
    ASSERT_EQ(ft_result, (ssize_t)strlen(test_input), "パイプ読み込みバイト数が期待値と一致しない");
    ASSERT_STR_EQ(ft_buffer, test_input, "パイプ読み込み内容が期待値と一致しない");
    
    return TEST_PASS;
}

// 空ファイル読み込みテスト
t_test_result test_read_empty_file(void)
{
    char temp_file[256];
    if (create_temp_file("", temp_file) != 0) {
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    char ft_buffer[100];
    ssize_t ft_result = ft_read(fd, ft_buffer, sizeof(ft_buffer));
    close(fd);
    
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, 0, "空ファイル読み込みが0バイト以外を返した");
    
    return TEST_PASS;
}

// 大きなファイル読み込みテスト
t_test_result test_read_large_file(void)
{
    char temp_file[256];
    
    // 大きなデータを生成
    size_t data_size = 4096;
    char *large_data = generate_large_string(data_size);
    if (!large_data) {
        return TEST_ERROR;
    }
    
    if (create_temp_file(large_data, temp_file) != 0) {
        free(large_data);
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        free(large_data);
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    char *ft_buffer = malloc(data_size + 1);
    ssize_t ft_result = ft_read(fd, ft_buffer, data_size);
    close(fd);
    
    ft_buffer[ft_result] = '\0';
    
    int comparison = strcmp(ft_buffer, large_data);
    
    free(large_data);
    free(ft_buffer);
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, (ssize_t)data_size, "大きなファイル読み込みバイト数が期待値と一致しない");
    ASSERT_EQ(comparison, 0, "大きなファイルの読み込み内容が一致しない");
    
    return TEST_PASS;
}

// 部分読み込みテスト
t_test_result test_read_partial(void)
{
    char temp_file[256];
    const char *test_data = "Hello, World! This is a long test string.";
    
    if (create_temp_file(test_data, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    // 部分読み込み（最初の13バイト）
    char ft_buffer[20];
    size_t partial_len = 13;
    ssize_t ft_result = ft_read(fd, ft_buffer, partial_len);
    close(fd);
    
    ft_buffer[ft_result] = '\0';
    
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, (ssize_t)partial_len, "部分読み込みバイト数が期待値と一致しない");
    if (strncmp(ft_buffer, test_data, partial_len) != 0) {
        return TEST_FAIL;
    }
    
    return TEST_PASS;
}

// 複数回読み込みテスト
t_test_result test_read_multiple(void)
{
    char temp_file[256];
    const char *test_data = "First line\nSecond line\nThird line\n";
    
    if (create_temp_file(test_data, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    // 複数回に分けて読み込み
    char total_buffer[200] = {0};
    size_t total_read = 0;
    
    for (int i = 0; i < 3; i++) {
        char chunk_buffer[20];
        ssize_t chunk_result = ft_read(fd, chunk_buffer, sizeof(chunk_buffer) - 1);
        
        if (chunk_result > 0) {
            memcpy(total_buffer + total_read, chunk_buffer, chunk_result);
            total_read += chunk_result;
        } else {
            break;
        }
    }
    
    close(fd);
    total_buffer[total_read] = '\0';
    
    unlink(temp_file);
    
    ASSERT_STR_EQ(total_buffer, test_data, "複数回読み込みで内容が一致しない");
    
    return TEST_PASS;
}

// エラーハンドリングテスト
t_test_result test_read_error_handling(void)
{
    // 無効なファイルディスクリプタ
    char buffer[100];
    errno = 0;
    ssize_t ft_result = ft_read(-1, buffer, sizeof(buffer));
    int ft_errno = errno;
    
    errno = 0;
    ssize_t std_result = read(-1, buffer, sizeof(buffer));
    int std_errno = errno;
    
    ASSERT_EQ(ft_result, std_result, "無効FDでの読み込み結果が一致しない");
    ASSERT_EQ(ft_result, -1, "無効FDでの読み込みが-1以外を返した");
    ASSERT_EQ(ft_errno, std_errno, "無効FDでのerrno設定が一致しない");
    
    // 閉じられたファイルディスクリプタ
    char temp_file[256];
    if (create_temp_file("test", temp_file) == 0) {
        int fd = open(temp_file, O_RDONLY);
        if (fd != -1) {
            close(fd);  // ファイルを閉じる
            
            errno = 0;
            ft_result = ft_read(fd, buffer, sizeof(buffer));
            ft_errno = errno;
            
            errno = 0;
            std_result = read(fd, buffer, sizeof(buffer));
            std_errno = errno;
            
            unlink(temp_file);
            
            ASSERT_EQ(ft_result, std_result, "閉じられたFDでの読み込み結果が一致しない");
            ASSERT_EQ(ft_result, -1, "閉じられたFDでの読み込みが-1以外を返した");
        }
    }
    
    return TEST_PASS;
}

// 特殊文字読み込みテスト
t_test_result test_read_special_chars(void)
{
    const char *test_strings[] = {
        "Hello\nWorld",
        "Tab\tSeparated",
        "Quote\"Test",
        "Path\\Separator",
        "!@#$%^&*()",
        "\x01\x02\x03\x04",  // 制御文字
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        char temp_file[256];
        
        if (create_temp_file(test_strings[i], temp_file) != 0) {
            return TEST_ERROR;
        }
        
        int fd = open(temp_file, O_RDONLY);
        if (fd == -1) {
            unlink(temp_file);
            return TEST_ERROR;
        }
        
        char ft_buffer[200];
        ssize_t ft_result = ft_read(fd, ft_buffer, sizeof(ft_buffer) - 1);
        close(fd);
        
        ft_buffer[ft_result] = '\0';
        
        if (ft_result != (ssize_t)strlen(test_strings[i]) || 
            strcmp(ft_buffer, test_strings[i]) != 0) {
            printf("  ✗ 特殊文字テスト失敗[%d]: \"%s\"\n", i, test_strings[i]);
            unlink(temp_file);
            return TEST_FAIL;
        }
        
        unlink(temp_file);
    }
    
    return TEST_PASS;
}

// 比較一致テスト
t_test_result test_read_comparison(void)
{
    const char *test_data[] = {
        "",
        "a",
        "short",
        "Hello, World!",
        "1234567890",
        "特殊文字テスト",
        "改行\n文字\t含む\r混合",
        "非常に長い文字列をテストしています。この文字列はft_read関数の動作を確認するために使用されます。",
        "!@#$%^&*()_+{}|:\"<>?[]\\;',./`~",
        NULL
    };
    
    for (int i = 0; test_data[i] != NULL; i++) {
        char temp_file[256];
        
        if (create_temp_file(test_data[i], temp_file) != 0) {
            return TEST_ERROR;
        }
        
        // ft_readでファイル読み込み
        int fd1 = open(temp_file, O_RDONLY);
        if (fd1 == -1) {
            unlink(temp_file);
            return TEST_ERROR;
        }
        
        char ft_buffer[1000];
        ssize_t ft_result = ft_read(fd1, ft_buffer, sizeof(ft_buffer) - 1);
        close(fd1);
        ft_buffer[ft_result] = '\0';
        
        // 標準readでファイル読み込み
        int fd2 = open(temp_file, O_RDONLY);
        if (fd2 == -1) {
            unlink(temp_file);
            return TEST_ERROR;
        }
        
        char std_buffer[1000];
        ssize_t std_result = read(fd2, std_buffer, sizeof(std_buffer) - 1);
        close(fd2);
        std_buffer[std_result] = '\0';
        
        unlink(temp_file);
        
        // 結果比較
        if (ft_result != std_result) {
            printf("  ✗ 読み込みバイト数失敗[%d]: ft=%zd std=%zd\n", i, ft_result, std_result);
            return TEST_FAIL;
        }
        
        if (strcmp(ft_buffer, std_buffer) != 0) {
            printf("  ✗ ファイル内容失敗[%d]: \"%s\"\n", i, test_data[i]);
            return TEST_FAIL;
        }
        
        // 元のデータとの一致確認
        if (strcmp(ft_buffer, test_data[i]) != 0) {
            printf("  ✗ 元データ不一致[%d]: \"%s\"\n", i, test_data[i]);
            return TEST_FAIL;
        }
    }
    
    return TEST_PASS;
}

// バッファサイズテスト
t_test_result test_read_buffer_sizes(void)
{
    char temp_file[256];
    const char *test_data = "This is a test string for buffer size testing.";
    
    if (create_temp_file(test_data, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    // 様々なバッファサイズでテスト
    size_t buffer_sizes[] = {1, 5, 10, 20, 50, 100, 1000};
    size_t num_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);
    
    for (size_t i = 0; i < num_sizes; i++) {
        int fd = open(temp_file, O_RDONLY);
        if (fd == -1) {
            unlink(temp_file);
            return TEST_ERROR;
        }
        
        char *buffer = malloc(buffer_sizes[i] + 1);
        ssize_t read_bytes = ft_read(fd, buffer, buffer_sizes[i]);
        close(fd);
        
        buffer[read_bytes] = '\0';
        
        // 読み込めた分だけ元データと一致するか確認
        if (strncmp(buffer, test_data, read_bytes) != 0) {
            printf("  ✗ バッファサイズテスト失敗[%zu]: サイズ=%zu\n", i, buffer_sizes[i]);
            free(buffer);
            unlink(temp_file);
            return TEST_FAIL;
        }
        
        free(buffer);
    }
    
    unlink(temp_file);
    return TEST_PASS;
}

// パフォーマンステスト
t_test_result test_read_performance(void)
{
    const char *perf_data[] = {
        "短い",
        "中程度の長さの文字列でパフォーマンステスト実行",
        "これは非常に長い文字列です。パフォーマンステストのために使用します。この文字列を何度も読み込んでft_read関数の性能を測定します。"
    };
    
    for (int i = 0; i < 3; i++) {
        char temp_file[256];
        
        if (create_temp_file(perf_data[i], temp_file) != 0) {
            continue;
        }
        
        t_benchmark bench;
        char test_name[64];
        
        snprintf(test_name, sizeof(test_name), "read_perf_%d", i);
        
        benchmark_start(&bench, test_name);
        bench.iterations = 1000;
        
        for (size_t j = 0; j < bench.iterations; j++) {
            int fd = open(temp_file, O_RDONLY);
            if (fd != -1) {
                char buffer[1000];
                ft_read(fd, buffer, sizeof(buffer));
                close(fd);
            }
        }
        
        benchmark_end(&bench);
        benchmark_print_result(&bench);
        
        unlink(temp_file);
    }
    
    return TEST_PASS;
}

// メインテスト実行関数
void test_ft_read(void)
{
    BEGIN_TEST_SUITE("ft_read");
    
    TEST_CASE("基本機能", test_read_basic);
    TEST_CASE("標準入力シミュレーション", test_read_stdin_simulation);
    TEST_CASE("空ファイル", test_read_empty_file);
    TEST_CASE("大きなファイル", test_read_large_file);
    TEST_CASE("部分読み込み", test_read_partial);
    TEST_CASE("複数回読み込み", test_read_multiple);
    TEST_CASE("エラーハンドリング", test_read_error_handling);
    TEST_CASE("特殊文字", test_read_special_chars);
    TEST_CASE("比較一致", test_read_comparison);
    TEST_CASE("バッファサイズ", test_read_buffer_sizes);
    TEST_CASE("パフォーマンス", test_read_performance);
    
    END_TEST_SUITE();
}

int main(void)
{
    init_test_stats();
    test_ft_read();
    print_test_stats();
    
    cleanup_temp_files();
    return (g_stats.failed_tests == 0) ? 0 : 1;
}
