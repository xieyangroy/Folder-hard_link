#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>

void trave_fli();
void trave_dir();

int main(int argc,char **argv){
    if(argc != 3){
        printf("error:argc !=3");
        exit(1);
    }
    trave_fli(argv[1],argv[2]);
    return 0;
}

void trave_fli(const char *source_address,const char *target_address){
    errno=0;
    struct stat a;
    stat(source_address,&a);
    if (S_ISDIR(a.st_mode)) {
        trave_dir(source_address,target_address);
    } else if(S_ISREG(a.st_mode)){
        link(source_address,target_address);
        // printf("link:%s\t%s\n",source_address,target_address);
        // printf("link:%d\n",S_ISREG(a.st_mode));

    }
}
void trave_dir(const char *source_address,const char *target_address){
    
    struct stat a;
    DIR *current_address;
    struct dirent *operation_address;
    current_address = opendir(source_address);
    while ((operation_address = readdir(current_address)) != NULL){
        if ((!strncmp(operation_address->d_name,".",1)||(!strncmp(operation_address->d_name,"..",2)))) {
            continue;
        }
    
        char b[1024],c[1024];
        memset(b,'\0',sizeof(b));
        memset(c,'\0',sizeof(c));
        strcat(b,source_address);
        strcat(c,target_address);
        // printf("%s\t%s\n",b,c);
        if (b[strlen(b)-1] != '/')
        {
            strcat(b,"/");
        }
        if (c[strlen(c)-1] != '/')
        {
            strcat(c,"/");
        }
        strcat(b,operation_address->d_name);
        strcat(c,operation_address->d_name);
        stat(b,&a);
        if (opendir(c)==NULL && S_ISDIR(a.st_mode))
        {
            // printf("dir:%d\n",S_ISDIR(a.st_mode));
            // printf("dirlink:%d\n",S_ISREG(a.st_mode));

            // printf("dir:%s\n",c);
            mkdir(c,0777);
        }
        trave_fli(b,c);

    }
    closedir(current_address);
}
