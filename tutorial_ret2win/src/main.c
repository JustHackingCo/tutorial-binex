#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// https://github.com/MEhrn00/libvisualize
#include "libvisualize.h"

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

    size = fstat(fd, &info);
    flag = malloc(info.st_size);
    read(fd, flag, info.st_size);

    printf("Good Job!\n");
    printf("Here's your flag: %s", flag);

    close(fd);
    free(flag);

    exit(EXIT_SUCCESS);
}

void vuln() {

    char buffer[0x30];

    printf("This challenge is meant to teach the concepts of a basic buffer overflow. \n");
    printf("Buffer overflows allow the attacker to redirect program execution by ");
    printf("overwriting the saved return address (labelled in red) located on the stack.\n\n");
    printf("In this example, your input will start at address %p ", buffer);
    printf("and there is no limit on the number of bytes you are able to input!\n");

    printf("The address you are trying to replace the return address with is: %p\n", win);
    printf("This address never changes due to PIE being disabled in the binary.\n\n");

    printf("See if you can overflow the buffer and overwrite the saved return \
address in order to redirect code execution and jump to the win function!\n\n");

    printf("Win function: %p", win);

    visualize_stack();
    printf("Input > ");
    gets(buffer);

    visualize_stack();
}

int main(void) {

    vuln();

    return 0;
}
