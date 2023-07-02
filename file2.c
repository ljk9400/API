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

// 
int fun_fgetc()
{
    printf("*** test file fget ***\n");
    FILE *file = fopen(TEST_FILE_NAME, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    int ch;

    // 使用 fgetc 逐字符读取文件内容
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }
    printf("\n");
    fclose(file);

    // 使用 getc 逐字符读取标准输入
    while ((ch = getc(stdin)) != EOF) {
        printf("%c", ch);
        if(ch == '\n')
            break;
    }

    // 使用 getchar 逐字符读取标准输入
    while ((ch = getchar()) != EOF) {
        printf("%c", ch);
        if(ch == '\n')
            break;
    }
    
    return 0;
}

// 
int fun_fput()
{
    printf("*** test file fput ***\n");
    char ch = 'A';
    FILE *file = fopen(TEST_FILE_NAME, "w");

    // 使用 fputc 将字符写入文件
    if (fputc(ch, file) != EOF) {
        printf("written to file: %c\n", ch);
    } 
    else {
        perror("fputc");
    }

    fclose(file);

    // 使用 putc 将字符写入标准输出
    if (putc(ch, stdout) == EOF) {
        perror("putc");
    }

    // 使用 putchar 将字符写入标准输出
    putchar('\n');
    putchar(ch);
    putchar('\n');
    
    return 0;
}

int fun_fgets()
{
    printf("*** test file fgets ***\n");
    char buffer[100];
    FILE *file = fopen(TEST_FILE_NAME, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // 使用 fgets 读取文件中的一行字符串
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Read line from file: %s\n", buffer);
    } 
    else {
        perror("fgets");
    }

    fclose(file);

    FILE *outputFile = fopen(TEST_FILE_NAME, "w");
    if (outputFile == NULL) {
        perror("fopen");
        return 1;
    }

    // 使用 fputs 将字符串写入文件
    if (fputs("Hello, World!", outputFile) == EOF) {
        perror("fputs");
    }

    fclose(outputFile);

    return 0;
}


// %*[^0-9]跳过非数字
int fun_print()
{
    printf("*** test file print ***\n");
    int   number = 10, number1=0, number3=0;
    char  buffer[100]; 
    float pi = 3.14159;

    // 使用 fprintf 将格式化的数据输出到标准输出
    sprintf(buffer, "Number: %d\n", number);
    fprintf(stdout, "Pi: %f, %s\n", pi, buffer);

    printf("please input a number\n");
    scanf("%d\n", &number1);
    printf("scanf %d\n", number1);

    fscanf(stdin, "%d\n", &number3);
    printf("fscanf %d\n", number3);

    const char *str = "John Doe 25";
    char name[50];
    int number2;

    // 使用 sscanf 解析字符串中的数据
    int num = sscanf(str, "%s%*[^0-9]%d", name, &number2);

    if (num == 2) {
        printf("Name: %s\n", name);
        printf("Number: %d\n", number2);
    } 
    else {
        printf("Failed to parse data.\n");
    }

    return 0;
}


// fgetpos fsetpos rewind freopen setvbuf remove
int fun_qx()
{
    return 0;
}


int main(int argc, char* argv[])
{
    fun_fwrite();
    fun_fgetc();
    fun_fput();
    fun_fgets();
    fun_print();

    return 0;
}