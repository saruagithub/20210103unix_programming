/*************************************************************************
	> File Name: 3_ls.c
	> Author: wangxue
	> Mail: 
	> Created Time: Wed Jan 13 20:41:31 2021
 ************************************************************************/

#include <stdio.h>
#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
void do_ls(char []);
void do_stat(char* );
void show_file_info(char* ,struct stat*);
void mode_to_letters(int ,char[]);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);

int main(int argc,char*argv[])
{
    if(argc == 1)
        do_ls(".");
    else {
         while(--argc)
            printf("%s：\n",*++argv);
        do_ls(*argv);
    }
    return 0;
}
  
void do_ls(char dirname[]){
    /*list files in directory called dirname*/
    DIR* dir_ptr;
    struct dirent * direntp; /*each entry*/
    if((dir_ptr = opendir(dirname)) == NULL)
        perror("opendir fails");
    while((direntp = readdir(dir_ptr)) !=NULL)
        do_stat(direntp->d_name);
    closedir(dir_ptr);
  }
   
void do_stat(char* filename)
{
    struct stat info;
    if((stat(filename,&info)) == -1)
        perror(filename);
    else
        show_file_info(filename,&info);

}
    
void show_file_info(char* filename,struct stat * info_p) {
    /*display the info about filename . the info is stored in struct at * info_p*/
    char modestr[11];
    mode_to_letters(info_p->st_mode,modestr);
    printf("%s",modestr);
    printf("%4d ",(int)info_p->st_nlink);
    printf("%-8s ",uid_to_name(info_p->st_uid));
    printf("%-8s ",gid_to_name(info_p->st_gid));
    printf("%8ld ",(long)info_p->st_size);
    printf("%.12s ",ctime(&info_p->st_mtime)+4);
    printf("%s\n",filename);
}
 
void mode_to_letters(int mode,char str[])
{
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0] = 'd';  //"directory ?"
    if(S_ISCHR(mode)) str[0] = 'c';  //"char decices"?
    if(S_ISBLK(mode)) str[0] = 'b';  //block device?

    //3 bits for user
    if(mode&S_IRUSR) str[1] = 'r';
    if(mode&S_IWUSR) str[2] = 'w';
    if(mode&S_IXUSR) str[3] = 'x';
    
    //3 bits for group
    if(mode&S_IRGRP) str[4] = 'r';
    if(mode&S_IWGRP) str[5] = 'w';
    if(mode&S_IXGRP) str[6] = 'x';

    //3 bits for other
    if(mode&S_IROTH) str[7] = 'r';
    if(mode&S_IWOTH) str[8] = 'w';
    if(mode&S_IXOTH) str[9] = 'x';
}
 
 char* uid_to_name(uid_t uid)
 {
    struct passwd* pw_ptr;
    static char numstr[10];
    if((pw_ptr =getpwuid(uid)) == NULL) {
        sprintf(numstr,"%d",uid);
        printf("world");
        return numstr;  
    }
    return pw_ptr->pw_name;
 }
  
char* gid_to_name(gid_t gid) {
    /*returns pointer to group number gid, used getgrgid*/
    struct group* grp_ptr;
    static char numstr[10];
    if((grp_ptr =getgrgid(gid)) == NULL) {
        printf("hello wofjl");
        sprintf(numstr,"%d",gid);
        return numstr;
    }
    else return grp_ptr->gr_name;
}
