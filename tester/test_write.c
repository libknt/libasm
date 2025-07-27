#include "test_utils.h"
#include <fcntl.h>

/*
 * ============================================
 * ft_write テストスイート
 * 統一的なテストフレームワークを使用
 * ファイルI/Oとエラーハンドリングテストを含む
 * ============================================
 */

// 基本機能テスト
t_test_result test_write_basic(void)
{
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_WRONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    // 基本的な書き込み
    const char *test_data = "Hello, World!";
    ssize_t ft_result = ft_write(fd, test_data, strlen(test_data));
    close(fd);
    
    // 結果確認
    fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    char buffer[100];
    ssize_t read_bytes = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    buffer[read_bytes] = '\0';
    
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, (ssize_t)strlen(test_data), "書き込みバイト数が期待値と一致しない");
    ASSERT_STR_EQ(buffer, test_data, "書き込まれた内容が期待値と一致しない");
    
    return TEST_PASS;
}

// 標準出力テスト
t_test_result test_write_stdout(void)
{
    // 標準出力への書き込み（目視確認）
    const char *msg = "ft_write stdout test\n";
    ssize_t ft_result = ft_write(1, msg, strlen(msg));
    ssize_t std_result = write(1, msg, strlen(msg));
    
    ASSERT_EQ(ft_result, std_result, "標準出力への書き込み結果が一致しない");
    ASSERT_EQ(ft_result, (ssize_t)strlen(msg), "標準出力書き込みバイト数が期待値と一致しない");
    
    return TEST_PASS;
}

// 空データ書き込みテスト
t_test_result test_write_empty(void)
{
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_WRONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    // 空データの書き込み
    ssize_t ft_result = ft_write(fd, "", 0);
    close(fd);
    
    // 標準関数との比較
    fd = open(temp_file, O_WRONLY | O_TRUNC);
    ssize_t std_result = write(fd, "", 0);
    close(fd);
    
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, std_result, "空データ書き込み結果が一致しない");
    ASSERT_EQ(ft_result, 0, "空データ書き込みが0バイト以外を返した");
    
    return TEST_PASS;
}

// 大きなデータ書き込みテスト
t_test_result test_write_large_data(void)
{
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    // 大きなデータを生成
    size_t data_size = 4096;
    char *large_data = generate_large_string(data_size);
    if (!large_data) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_WRONLY);
    if (fd == -1) {
        free(large_data);
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    // 大きなデータの書き込み
    ssize_t ft_result = ft_write(fd, large_data, data_size);
    close(fd);
    
    // 結果確認
    fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        free(large_data);
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    char *buffer = malloc(data_size + 1);
    ssize_t read_bytes = read(fd, buffer, data_size);
    close(fd);
    buffer[read_bytes] = '\0';
    
    int comparison = strcmp(buffer, large_data);
    
    free(large_data);
    free(buffer);
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, (ssize_t)data_size, "大きなデータ書き込みバイト数が期待値と一致しない");
    ASSERT_EQ(comparison, 0, "大きなデータの書き込み内容が一致しない");
    
    return TEST_PASS;
}

// エラーハンドリングテスト
t_test_result test_write_error_handling(void)
{
    // 無効なファイルディスクリプタ
    errno = 0;
    ssize_t ft_result = ft_write(-1, "test", 4);
    int ft_errno = errno;
    
    errno = 0;
    ssize_t std_result = write(-1, "test", 4);
    int std_errno = errno;
    
    ASSERT_EQ(ft_result, std_result, "無効FDでの書き込み結果が一致しない");
    ASSERT_EQ(ft_result, -1, "無効FDでの書き込みが-1以外を返した");
    ASSERT_EQ(ft_errno, std_errno, "無効FDでのerrno設定が一致しない");
    
    // 閉じられたファイルディスクリプタ
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) == 0) {
        int fd = open(temp_file, O_WRONLY);
        if (fd != -1) {
            close(fd);  // ファイルを閉じる
            
            errno = 0;
            ft_result = ft_write(fd, "test", 4);
            ft_errno = errno;
            
            errno = 0;
            std_result = write(fd, "test", 4);
            std_errno = errno;
            
            unlink(temp_file);
            
            ASSERT_EQ(ft_result, std_result, "閉じられたFDでの書き込み結果が一致しない");
            ASSERT_EQ(ft_result, -1, "閉じられたFDでの書き込みが-1以外を返した");
        }
    }
    
    return TEST_PASS;
}

// 部分書き込みテスト
t_test_result test_write_partial(void)
{
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    int fd = open(temp_file, O_WRONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    const char *test_data = "Hello, World! This is a test.";
    size_t partial_len = 13;  // "Hello, World!" only
    
    ssize_t ft_result = ft_write(fd, test_data, partial_len);
    close(fd);
    
    // 結果確認
    fd = open(temp_file, O_RDONLY);
    if (fd == -1) {
        unlink(temp_file);
        return TEST_ERROR;
    }
    
    char buffer[100];
    ssize_t read_bytes = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    buffer[read_bytes] = '\0';
    
    unlink(temp_file);
    
    ASSERT_EQ(ft_result, (ssize_t)partial_len, "部分書き込みバイト数が期待値と一致しない");
    ASSERT_EQ(strlen(buffer), partial_len, "部分書き込み内容の長さが期待値と一致しない");
    if (strncmp(buffer, test_data, partial_len) != 0) {
        return TEST_FAIL;
    }
    
    return TEST_PASS;
}

// 特殊文字書き込みテスト
t_test_result test_write_special_chars(void)
{
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) != 0) {
        return TEST_ERROR;
    }
    
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
        int fd = open(temp_file, O_WRONLY | O_TRUNC);
        if (fd == -1) {
            unlink(temp_file);
            return TEST_ERROR;
        }
        
        size_t len = strlen(test_strings[i]);
        ssize_t ft_result = ft_write(fd, test_strings[i], len);
        close(fd);
        
        // 結果確認
        fd = open(temp_file, O_RDONLY);
        if (fd == -1) {
            unlink(temp_file);
            return TEST_ERROR;
        }
        
        char buffer[200];
        ssize_t read_bytes = read(fd, buffer, sizeof(buffer) - 1);
        close(fd);
        buffer[read_bytes] = '\0';
        
        if (ft_result != (ssize_t)len || strcmp(buffer, test_strings[i]) != 0) {
            printf("  ✗ 特殊文字テスト失敗[%d]: \"%s\"\n", i, test_strings[i]);
            unlink(temp_file);
            return TEST_FAIL;
        }
    }
    
    unlink(temp_file);
    return TEST_PASS;
}

// 比較一致テスト
t_test_result test_write_comparison(void)
{
    const char *test_data[] = {
        "",
        "a",
        "short",
        "Hello, World!",
        "1234567890",
        "特殊文字テスト",
        "改行\n文字\t含む\r混合",
        "非常に長い文字列をテストしています。この文字列はft_write関数の動作を確認するために使用されます。",
        "!@#$%^&*()_+{}|:\"<>?[]\\;',./`~",
        NULL
    };
    
    for (int i = 0; test_data[i] != NULL; i++) {
        char temp_file1[256], temp_file2[256];
        
        if (create_temp_file(NULL, temp_file1) != 0 || 
            create_temp_file(NULL, temp_file2) != 0) {
            return TEST_ERROR;
        }
        
        // ft_writeでファイル書き込み
        int fd1 = open(temp_file1, O_WRONLY);
        if (fd1 == -1) {
            unlink(temp_file1);
            unlink(temp_file2);
            return TEST_ERROR;
        }
        
        size_t len = strlen(test_data[i]);
        ssize_t ft_result = ft_write(fd1, test_data[i], len);
        close(fd1);
        
        // 標準writeでファイル書き込み
        int fd2 = open(temp_file2, O_WRONLY);
        if (fd2 == -1) {
            unlink(temp_file1);
            unlink(temp_file2);
            return TEST_ERROR;
        }
        
        ssize_t std_result = write(fd2, test_data[i], len);
        close(fd2);
        
        // 結果比較
        if (ft_result != std_result) {
            printf("  ✗ 書き込みバイト数失敗[%d]: ft=%zd std=%zd\n", i, ft_result, std_result);
            unlink(temp_file1);
            unlink(temp_file2);
            return TEST_FAIL;
        }
        
        // ファイル内容比較
        fd1 = open(temp_file1, O_RDONLY);
        fd2 = open(temp_file2, O_RDONLY);
        
        if (fd1 == -1 || fd2 == -1) {
            if (fd1 != -1) close(fd1);
            if (fd2 != -1) close(fd2);
            unlink(temp_file1);
            unlink(temp_file2);
            return TEST_ERROR;
        }
        
        char buffer1[1000], buffer2[1000];
        ssize_t read1 = read(fd1, buffer1, sizeof(buffer1) - 1);
        ssize_t read2 = read(fd2, buffer2, sizeof(buffer2) - 1);
        close(fd1);
        close(fd2);
        
        buffer1[read1] = '\0';
        buffer2[read2] = '\0';
        
        if (strcmp(buffer1, buffer2) != 0) {
            printf("  ✗ ファイル内容失敗[%d]: \"%s\"\n", i, test_data[i]);
            unlink(temp_file1);
            unlink(temp_file2);
            return TEST_FAIL;
        }
        
        unlink(temp_file1);
        unlink(temp_file2);
    }
    
    return TEST_PASS;
}

// パフォーマンステスト
t_test_result test_write_performance(void)
{
    char temp_file[256];
    if (create_temp_file(NULL, temp_file) != 0) {
        return TEST_ERROR;
    }
    
    const char *perf_data[] = {
        "短い",
        "中程度の長さの文字列でパフォーマンステスト実行",
        "これは非常に長い文字列です。パフォーマンステストのために使用します。この文字列を何度も書き込んでft_write関数の性能を測定します。"
    };
    
    for (int i = 0; i < 3; i++) {
        t_benchmark bench;
        char test_name[64];
        
        snprintf(test_name, sizeof(test_name), "write_perf_%d", i);
        
        benchmark_start(&bench, test_name);
        bench.iterations = 1000;
        
        for (size_t j = 0; j < bench.iterations; j++) {
            int fd = open(temp_file, O_WRONLY | O_TRUNC);
            if (fd != -1) {
                ft_write(fd, perf_data[i], strlen(perf_data[i]));
                close(fd);
            }
        }
        
        benchmark_end(&bench);
        benchmark_print_result(&bench);
    }
    
    unlink(temp_file);
    return TEST_PASS;
}

// メインテスト実行関数
void test_ft_write(void)
{
    BEGIN_TEST_SUITE("ft_write");
    
    TEST_CASE("基本機能", test_write_basic);
    TEST_CASE("標準出力", test_write_stdout);
    TEST_CASE("空データ", test_write_empty);
    TEST_CASE("大きなデータ", test_write_large_data);
    TEST_CASE("エラーハンドリング", test_write_error_handling);
    TEST_CASE("部分書き込み", test_write_partial);
    TEST_CASE("特殊文字", test_write_special_chars);
    TEST_CASE("比較一致", test_write_comparison);
    TEST_CASE("パフォーマンス", test_write_performance);
    
    END_TEST_SUITE();
}

int main(void)
{
    init_test_stats();
    test_ft_write();
    print_test_stats();
    
    cleanup_temp_files();
    return (g_stats.failed_tests == 0) ? 0 : 1;
}  
