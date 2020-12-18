#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// https://github.com/MEhrn00/libvisualize
#include "libvisualize.h"

void callme1();
void callme2();
void vuln();

int check1 = 0;
int check2 = 0;

void callme2() {
    check2 = 1;
    if (!check1) {
        printf("You need to jump to callme1 first.\n");
        exit(EXIT_SUCCESS);
    }
}

__attribute__((constructor))
void setup() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
}


void win() {
    int fd;
    char *flag;
    int size;
    struct stat info;

    if ((fd = open("flag.txt", O_RDONLY)) < 0) {
        printf("Could not open flag file. If this error happens on the challenge server, contact admin.\n");
        exit(EXIT_FAILURE);
    }

    if (check1 == 0 && check2 == 0) {
        printf("You forgot to ROP to the callme1 and callme2 functions.\n");
        exit(EXIT_SUCCESS);
    }

    size = fstat(fd, &info);
    flag = malloc(info.st_size);
    read(fd, flag, info.st_size);

    printf("Good Job!\n");
    printf("Here's your flag: %s", flag);

    close(fd);
    free(flag);

    exit(EXIT_SUCCESS);
}

int main(void) {

    vuln();

    return 0;
}

void callme1() {
    check1 = 1;
}

void vuln() {

    char buffer[0x50];

    printf("This challenge is an exercise on ROP (return oriented programming).\n");
    printf("ROP allows you to chain function calls together in order to achieve a desired outcome.\n\n");

    printf("There exists 2 other functions along with the win function in this binary.\n");
    printf("These functions are callme1: %p and callme2: %p.\n", callme1, callme2);
    printf("Use ROP to call these functions in the order callme1, callme2 ");
    printf("and then jump to the win function %p to get the flag.\n", win);
    printf("Again PIE is disabled so these addresses will not change\n\n");

    printf("Your input starts at address: %p (top of the stack)\n\n", buffer);

    printf("Win function: %p\n", win);
    printf("callme1: %p\n", callme1);
    printf("callme2: %p", callme2);

    visualize_stack();
    printf("Input > ");
    gets(buffer);

    visualize_stack();
}
