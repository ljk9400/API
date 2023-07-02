#include "common.h"

#define TEST_DIR_PATH   "/mnt/hgfs/MyWork/github/API"
#define TEST_FILE_NAME  TEST_DIR_PATH "/" "a.txt"


int fun_fwrite()
{
    printf("*** test file fwrite fread ***\n");
    const char* data = "Hello, World!";
    char buffer[256]; // 缓冲区用于读取和写入文件
    
    FILE *file = fopen(TEST_FILE_NAME, "w+");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }
    
    // 使用 fwrite 将整数数组写入文件
    size_t elementsWritten = fwrite(data, sizeof(char), sizeof("Hello, World!"), file);
    if (elementsWritten <= 0) {
        perror("fwrite");
        fclose(file);
        return 1;
    }
    
    // 刷新文件缓冲区，确保数据被写入文件
    if (fflush(file) != 0) {
        perror("fflush");
        fclose(file);
        return 1;
    }
    
    // 将读取位置指针从文件开头移动到第10个字节处
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("fseek");
        fclose(file);
        return 1;
    }

    // 使用 fread 从文件中读取整数数组
    size_t elementsRead = fread(buffer, sizeof(char), sizeof(buffer), file);
    if (elementsRead <= 0) {
        perror("fread");
        fclose(file);
        return 1;
    }

     // 获取文件指针的当前偏移量
    long offset = ftell(file);
    if (offset == -1L) {
        perror("ftell");
        fclose(file);
        return 1;
    }

    fclose(file);

    // 打印读取的整数数组
    printf("Read numbers: %s, len: %ld\n", buffer, offset);
    
    return 0;
}




int main(int argc, char* argv[])
{
    fun_fwrite();

    return 0;
}