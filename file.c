#include "common.h"

#define TEST_DIR_PATH   "/mnt/hgfs/MyWork/github/API"
#define TEST_FILE_NAME  TEST_DIR_PATH "/" "a.txt"


int fun_write_test()
{
    char c;
    int in, out;
    in  = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    while(read(in, &c, 1) == 1)
        write(out, &c, 1);
    
    return 0;
}

// open read write close ioctl
// 0、1 和 2 标准输入、标准输出和标准错误
int fun_write()
{
    int fd; // 文件描述符

    // 打开文件（如果不存在则创建），返回文件描述符
    fd = open(TEST_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // 写入数据到文件
    const char* data = "Hello, World!";
    if (write(fd, data, sizeof("Hello, World!")) == -1) {
        perror("write");
        exit(1);
    } 

     // 刷新缓冲区并将数据写入磁盘 == fflush
    if (fsync(fd) == -1) {
        perror("fsync");
        exit(1);
    }
    
    // 关闭文件
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    
    return 0;
}

int fun_read()
{
    int fd; // 文件描述符
    char buffer[256]; // 缓冲区用于读取和写入文件

    // 重新打开文件进行读取
    fd = open(TEST_FILE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // 从文件中读取数据到缓冲区
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    }

    // 打印读取的数据
    printf("Data read from file: %.*s\n", (int)bytesRead, buffer);

    // 关闭文件
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}

int fun_lseek()
{
    int fd; // 文件描述符

    // 打开文件（如果不存在则创建），返回文件描述符
    fd = open(TEST_FILE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // 将文件指针移动到文件的开头
    off_t newOffset = lseek(fd, 0, SEEK_SET);
    if (newOffset == -1) {
        perror("lseek");
        exit(1);
    }

    printf("New file offset: %lld\n", (long long)newOffset);

    // 关闭文件
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}

// int fstat(int fd, struct stat *buf);  fd是描述符
// int lstat(const char *path, struct stat *buf);  是指软连接
int fun_stat()
{
    printf("*** test file stat ***\n");
    struct stat fileStat;

    if (stat(TEST_FILE_NAME, &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    printf("File Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("File Permissions: %o\n", fileStat.st_mode & 0777);
    printf("File Owner: %d\n", fileStat.st_uid);
    printf("File Group: %d\n", fileStat.st_gid);

    return 0;
}

int fun_dup()
{
    printf("*** test file dup ***\n");
    int fd1, fd2, fd3;

    // 打开文件 example.txt，并获取文件描述符 fd1
    fd1 = open(TEST_FILE_NAME, O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    // 使用 dup 复制文件描述符 fd1，创建一个新的文件描述符 fd2
    fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("dup");
        close(fd1);
        return 1;
    }

    // 使用 dup2 复制文件描述符 fd1，创建一个新的文件描述符 fd3
    fd3 = dup2(fd1, 5);
    if (fd3 == -1) {
        perror("dup2");
        close(fd1);
        close(fd2);
        return 1;
    }

    printf("fd1: %d\n", fd1);
    printf("fd2: %d\n", fd2);
    printf("fd3: %d\n", fd3);

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}

#include <fcntl.h>
#include <sys/ioctl.h>
// 
int fun_ioctl()
{
    printf("*** test file ioctl ***\n");
     int fd;  // 设备文件描述符
    int ret; // 返回值

    // 打开设备文件
    fd = open("/dev/device", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 发送一个控制命令
    //ret = ioctl(fd, IOCTL_COMMAND, arg);
    if (ret == -1) {
        perror("ioctl");
        close(fd);
        return 1;
    }

    // 关闭设备文件
    close(fd);

    return 0;
}

int main(int argc, char* argv[])
{
    fun_write();
    fun_read();
    fun_lseek();
    fun_stat();
    fun_dup();

    return 0;
}