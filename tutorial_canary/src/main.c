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

    printf("This binary is the same as the ret2win binary; however, stack canaries are enabled.\n\n");

    printf("Stack canaries are an exploit mitigation that prevents buffer overflows (or atleast tries to) by placing \
a random value at the bottom of the stack.\n");
    printf("Before the function returns, the canary is checked and the program will exit if \
there's a mismatch.\n\n");

    printf("If the stack canary is leaked through some type of memory leak, stack smashing detection \
can be defeated by placing the canary back where it's supposed to be.\n");
    printf("The function will check the canary, see it's correct and then return normally.\n");
    printf("You can now overwrite the saved return address with the win function and redirect code execution!\n\n");

    printf("Stack canary: %p (memory leak)\n", (size_t *)get_canary());
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
