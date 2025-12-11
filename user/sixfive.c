#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"

int is_separator(char c) {
    // separators: " -\r\t\n./,"
    return c == ' ' || c == '-' || c == '\r' || c == '\t' ||
           c == '\n' || c == '.' || c == '/' || c == ',';
}

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Usage: sixfive <filename>\n");
        exit(1);
    }

    int fd = open(argv[1], 0); // read-only
    if(fd < 0){
        printf("Cannot open file %s\n", argv[1]);
        exit(1);
    }

    char buf[1];       // read one character at a time
    char num_str[32];  // buffer to store number as string
    int idx = 0;

    while(read(fd, buf, 1) == 1){
        char c = buf[0];
        if(c >= '0' && c <= '9'){
            // accumulate digits
            num_str[idx++] = c;
        } else if(idx > 0 && is_separator(c)){
            // end of number
            num_str[idx] = 0;   // null-terminate
            int num = atoi(num_str);
            if(num % 5 == 0 || num % 6 == 0)
                printf("%d\n", num);
            idx = 0;             // reset for next number
        } else {
            // separator without number, do nothing
            if(idx > 0){
                num_str[idx] = 0;
                int num = atoi(num_str);
                if(num % 5 == 0 || num % 6 == 0)
                    printf("%d\n", num);
                idx = 0;
            }
        }
    }

    // handle last number if file ends without separator
    if(idx > 0){
        num_str[idx] = 0;
        int num = atoi(num_str);
        if(num % 5 == 0 || num % 6 == 0)
            printf("%d\n", num);
    }

    close(fd);
    exit(0);
}

