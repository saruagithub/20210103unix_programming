/*************************************************************************
	> File Name: 1_getopt.c
	> Author: wangxue
	> Mail: 
	> Created Time: Mon Jan  4 19:47:42 2021
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <time.h>

void showdir(char filename[]);
void show_stat(char* filename);
void mode_to_letters(mode_t ,char[]);
char* uid_name(uid_t);
char* gid_name(gid_t);

// 获取参数getopt，合法性判断，保存选项值，参数个数（缺省）
int a_flag = 0, l_flag = 0;

// show dir and files
void showdir(char filename[]){
    DIR* directory_ptr;
    struct dirent* dirent_ptr;
    if ( (directory_ptr = opendir(filename)) == NULL ){
        fprintf(stderr, "ls: cannot open %s\n", filename);
    }
    // fortmat control
    if (!a_flag && !l_flag) {
        while ( (dirent_ptr = readdir(directory_ptr)) != NULL ){
            // qsort the filename
            // char d_name[] , name of entry
            //if (dirent_ptr->d_name == "." || dirent_ptr->d_name == "..") continue;
            if (strcmp(dirent_ptr->d_name, ".") == 0 || strcmp(dirent_ptr->d_name, "..") == 0 ) continue;
            else printf("%-10s", dirent_ptr->d_name);
        }
    }
    else if (a_flag && !l_flag) {
        while ( (dirent_ptr = readdir(directory_ptr)) != NULL ){
            printf("%-10s", dirent_ptr->d_name);
        }
    }
    else if (a_flag && l_flag) { 
        while ( (dirent_ptr = readdir(directory_ptr)) != NULL ){
            show_stat(dirent_ptr->d_name);
        }
    }
    else { 
        while ( (dirent_ptr = readdir(directory_ptr)) != NULL ){
            if (strcmp(dirent_ptr->d_name, ".") == 0 || strcmp(dirent_ptr->d_name, "..") == 0 ) continue;
            else show_stat(dirent_ptr->d_name);
        }
    }
    closedir(directory_ptr);
}

// show details of file
void show_stat(char* filename) {
    struct stat info;
    if ((stat(filename, &info)) ==  -1) {
        perror(filename);
    }
    else {
        char modestr[11];
        struct stat* pinfo = &info;
        mode_to_letters(pinfo->st_mode, modestr);
        printf("%s ", modestr);
        printf("%4d ", (int)pinfo->st_nlink);
        printf("%-8s ",uid_name(pinfo->st_uid));
        printf("%-8s ",gid_name(pinfo->st_gid));
        printf("%8ld ",(long)pinfo->st_size);
        printf("%.16s ", ctime(&pinfo->st_mtime));
        printf("%s\n",filename);
    }
}

void mode_to_letters(mode_t mode, char str[]) {
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0] = 'd';  //"directory ?"
    if(S_ISCHR(mode)) str[0] = 'c';  //"char decices"?
    if(S_ISBLK(mode)) str[0] = 'b';  //block device?
    
    if(mode&S_IRUSR) str[1] = 'r';
    if(mode&S_IWUSR) str[2] = 'w';
    if(mode&S_IXUSR) str[3] = 'x';

    if(mode&S_IRGRP) str[4] = 'r';
    if(mode&S_IWGRP) str[5] = 'w';
    if(mode&S_IXGRP) str[6] = 'x';
    
    if(mode&S_IROTH) str[7] = 'r';
    if(mode&S_IWOTH) str[8] = 'w';
    if(mode&S_IXOTH) str[9] = 'x';
}

char* uid_name(uid_t uid) {
    struct passwd* pw_ptr;
    static char numstr[10];
    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else return pw_ptr->pw_name;
}

char* gid_name(gid_t gid) {
    struct group* grp_ptr;
    static char numstr[10];
    if ((grp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else return grp_ptr->gr_name;
}

int main(int argc, char *argv[]){ 
    // parse the argv, parse the filename ??
    int opt;
    while ( (opt = getopt(argc, argv, "alm:o::")) != -1 ) {
        switch (opt) {
            case 'a':
                a_flag = 1;
                break;
            case 'l':
                l_flag = 1;
                break;
            case 'm':
                printf("optarg = %s\n", optarg);
                break;
            case 'o':
                printf("optarg = %s\n", optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -al\n", argv[0]);
                exit(1);
        }
    }
    // parse the filename
    showdir(".");
    //printf("a_flag=%d, l_flag=%d, argc=%d, optind=%d, opterr=%d, optopt=%d \n",a_flag, l_flag, optind, opterr, optopt);
}
