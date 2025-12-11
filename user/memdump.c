#include "kernel/types.h"
#include "user/user.h"

void memdump(char *fmt, char *data, int len) {
    char *ptr = data;
    int i;
    for(i = 0; fmt[i]; i++){
        switch(fmt[i]){
            case 'i': 
                if(ptr + 4 <= data + len) {
                    printf("%d\n", *(int*)ptr); 
                    ptr += 4; 
                }
                break;
            case 'p': 
                if(ptr + 8 <= data + len) {
                    printf("%lx\n", *(uint64*)ptr); 
                    ptr += 8; 
                }
                break;
            case 'h': 
                if(ptr + 2 <= data + len) {
                    printf("%d\n", *(short*)ptr); 
                    ptr += 2; 
                }
                break;
            case 'c': 
                if(ptr + 1 <= data + len) {
                    printf("%c\n", *ptr); 
                    ptr += 1; 
                }
                break;
            case 's': 
                if(ptr + 8 <= data + len) {
                    printf("%s\n", *(char**)ptr); 
                    ptr += 8; 
                }
                break;
            case 'S': 
                printf("%s\n", ptr); 
                ptr += strlen(ptr); 
                break;
        }
    }
}

int main(int argc, char *argv[]){
    if(argc > 1){
        char buf[512];
        int n = read(0, buf, sizeof(buf));
        memdump(argv[1], buf, n);
        exit(0);
    }

    // Built-in test cases if no arguments
    char testdata1[8] = {0x32,0xf1,0x00,0x00,0xe9,0x07,0x00,0x00};
    char *teststr = "a string";

    printf("Example 1:\n"); 
    memdump("ii", testdata1, sizeof(testdata1));

    printf("Example 2:\n"); 
    memdump("S", teststr, strlen(teststr)+1);

    // You can add more built-in tests if needed
    exit(0);
}

