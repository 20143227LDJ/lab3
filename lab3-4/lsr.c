#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void dir_print(DIR *pdir, char *path){
    DIR *temp;
    struct dirent *pde;
    char *buf[256];
    char *buf2[512];
    while((pde = readdir(pdir)) != NULL){
        if(!strcmp(pde->d_name, ".") || !strcmp(pde->d_name, "..")){
            continue;
        }
        if(pde->d_type == 4){
            sprintf(buf2, "D:%s/", pde->d_name);
            sprintf(buf, "%s/%s", path, pde->d_name);
            
            if((temp = opendir(buf)) == NULL){
                perror("opendir");
            }
            dir_print(temp, buf);
        }
        else{
            sprintf(buf2, "F:%s/\n", pde->d_name);   
        }
        printf("%s", buf2);
    }
}

int main(int argc, char *argv[]){
    DIR *dir;
    char *dir_name;

    if (argc == 1){
        strcpy(dir_name ,".");
    }
    if (argc == 2) {
        strcpy(dir_name, argv[1]);
    }
    if((dir = opendir(dir_name)) == NULL){
        perror("opendir");
        exit(1);
    }
        
    dir_print(dir, dir_name);
    printf("\n");
    return 0;
}
