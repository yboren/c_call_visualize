/*
 * an implement of ls 
 */
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string.h>

void ls(char *);
void dostat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letter(int, char *);
char * uid_to_name(uid_t);
char * gid_to_name(gid_t);

void ls(char *dirname)
{
    DIR *dirp;
    struct dirent *direntp;

    if((dirp = opendir(dirname)) == NULL){
        fprintf(stderr,"ls1:can not open %s\n",dirname);
    }
    else{
        while((direntp = readdir(dirp)) != NULL){
            dostat(direntp->d_name);
        }
        closedir(dirp);
    }
}

void dostat(char * filename)
{
    struct stat buf;
    if(stat(filename, &buf) == -1)
        perror(filename);
    else
        show_file_info(filename, &buf);
}

void show_file_info(char * filename, struct stat * statp)
{
    char *filemode(), *uid_to_name(), *gid_to_name(), *ctime();
    char modestr[11];

    mode_to_letter(statp->st_mode, modestr);

    printf("%s ", modestr);
    printf("%4d ", (int)statp->st_nlink);
    printf("%-8s ", uid_to_name(statp->st_uid));
    printf("%-8s ", gid_to_name(statp->st_gid));
    printf("%8ld ", (long)statp->st_size);
    printf("%.12s ", 4+ctime(&statp->st_mtime));
    printf("%s\n", filename);
}

void mode_to_letter(int mode, char *str)
{
    strcpy(str, "---------"); /*default 10 dashes*/
    if(S_ISDIR(mode))str[0] = 'd';
    if(S_ISCHR(mode))str[0] = 'c';
    if(S_ISBLK(mode))str[0] = 'b';

    if(mode & S_IRUSR)str[1] = 'r';
    if(mode & S_IWUSR)str[2] = 'w';
    if(mode & S_IXUSR)str[3] = 'x';

    if(mode & S_IRGRP)str[3] = 'r';
    if(mode & S_IWGRP)str[4] = 'w';
    if(mode & S_IXGRP)str[5] = 'x';

    if(mode & S_IROTH)str[6] = 'r';
    if(mode & S_IWOTH)str[7] = 'w';
    if(mode & S_IXOTH)str[8] = 'x';
}
#include<pwd.h>
char * uid_to_name(uid_t uid)
{
    struct passwd * pw_ptr;
    static char numstr[10];

    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr,"%d",uid);
        return numstr;
    }
    else
        return pw_ptr->pw_name;
}

#include<grp.h>
char * gid_to_name(gid_t gid)
{
    struct group *grp_ptr;
    static char grpstr[10];

    if((grp_ptr = getgrgid(1000)) == NULL){
            sprintf(grpstr,"%d",gid);
            return grpstr;
    }
    else
        return grp_ptr->gr_name;
}

int main(int argc,char **argv)
{
    if(argc == 1){
        ls(".");
    }
    else {
        while(--argc > 0){
            printf("%s:\n",*++argv);
            ls(*argv);
        }
    }
    return 0;
}


