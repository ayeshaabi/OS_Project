#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int res = symlink("file1", "link1");
    if(res < 0){
        printf("symlink failed\n");
    } else {
        printf("symlink created\n");
    }
    exit(0);
}
