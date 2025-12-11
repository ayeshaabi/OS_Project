#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

// Helper: find last occurrence of character c in string s
char* my_strrchr(char *s, char c) {
    char *last = 0;
    for(; *s; s++){
        if(*s == c) last = s;
    }
    return last;
}

void find(char *path, char *target){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    // open file or directory
    if((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    // get file/directory metadata
    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
    case T_FILE:
        // extract last component of path
        p = my_strrchr(path, '/');
        if(p) p++; else p = path;
        // compare with target
        if(strcmp(p, target) == 0)
            printf("%s\n", path);
        break;

    case T_DIR:
        // check buffer size
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';

        // read each directory entry
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0) continue;
            // skip "." and ".."
            if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;

            // build full path
            int i;
            for(i = 0; i < DIRSIZ && de.name[i] != '\0'; i++)
                p[i] = de.name[i];
            p[i] = 0;

            // recursive call
            find(buf, target);
        }
        break;
    }

    close(fd);
}

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(2, "Usage: find <path> <filename>\n");
        exit(1);
    }

    find(argv[1], argv[2]);
    exit(0);
}

