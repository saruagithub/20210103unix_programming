/*************************************************************************
	> File Name: 2_cp.c
	> Author: wangxue
	> Mail: 
	> Created Time: Tue Jan 26 16:16:52 2021
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int rd_fd, wr_fd;
    char buf[128] = {0};
    int rd_ret = 0;

    if (argc < 3) {
        printf("please input src file and des file!\n");
        return -1;
    }
    // open source File
    rd_fd = open(argv[1], O_RDONLY);
    if (rd_fd < 0) {
        printf("open src file %s failed!\n", argv[1]);
        return -2;
    }
    printf("open src file %s succ, rd_fd = %d\n", argv[1], rd_fd);

    // open des File
    wr_fd = open(argv[2], O_WRONLY|O_CREAT);
    if (wr_fd < 0) {
        printf("open des file %s failed!\n", argv[2]);
        return -3;
    }
    printf("open des file %s succ, rd_fd = %d\n", argv[2], wr_fd);

    while(1) {
        rd_ret = read(rd_fd, buf, 128);
        if (rd_ret < 128) break; // judge reading is finished
        write(wr_fd, buf, rd_ret);
        memset(buf, 0, 128); // release the buf
    }
    write(wr_fd, buf, rd_ret);// the last write

    // close fd
    close(wr_fd);
    close(rd_fd);
    return 0;
}

