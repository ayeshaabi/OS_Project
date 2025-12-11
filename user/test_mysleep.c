#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int t = 50;  // sleep 50 ticks
    printf("Sleeping for %d ticks...\n", t);
    mysleep(t);
    printf("Woke up!\n");
    exit(0);
}
