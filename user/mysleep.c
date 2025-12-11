#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: mysleep <ticks>\n");
        exit(1);
    }

    int t = atoi(argv[1]);
    printf("Sleeping for %d ticks...\n", t);

    mysleep(t);

    printf("Done sleeping!\n");
    exit(0);
}
