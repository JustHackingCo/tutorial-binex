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

    printf("This binary is EXACTLY the same as the ROP binary however PIE (position independent execution) is enabled.\n\n");
    printf("With PIE enabled this means that ASLR (address space layout randomization) affects the binary.\n");
    printf("Even though ASLR makes the addresses of functions random, the OFFSETS \
to each function stay constant.\n\n");

    printf("For example: Through some type of memory leak it was found that the address of main with PIE enabled is 0x55d56ba213c6.\n");
    printf("Through analysis of the binary, you know that the address of the win function is located at main - 0x40.\n");
    printf("This would mean that the actual address of the win function is at main - 0x40 = 0x55d56ba21386.\n\n");

    printf("The address of the win function in this binary is: %p (memory leak!)\n", win);
    printf("Use this knowledge to calculate the addresses of callme1 and callme2 in order to defeat ASLR!\n\n");

    printf("Win function: %p", win);

    visualize_stack();
    printf("Input > ");
    gets(buffer);

    visualize_stack();
}
