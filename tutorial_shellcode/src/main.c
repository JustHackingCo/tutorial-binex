#include <stdio.h>

// https://github.com/MEhrn00/libvisualize
#include "libvisualize.h"

__attribute__((constructor))
void setup() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
}

void vuln() {

    char buffer[0x90];

    printf("For this challenge, there is no win function but there is still a way to get the flag.\n\n");
    printf("Since you are able to write bytes into memory, what's preventing you from writing \
code into memory and jumping to it?\n");
    printf("Well it turns out there's this exploit mitigation called DEP/NX (data execution prevention) \
which prevents user supplied code from being executed.\n");
    printf("I have turned DEP/NX off for this binary.\n\n");

    printf("To solve this challenge, try to write machine code on the stack that \
will either give you a shell on the system or read the flag file.\n\n");

    printf("Due to ASLR, the address of the stack is constantly changing.\n");
    printf("If you aren't using the python library, pwntools, I recommend using that to get the address of your input.\n");
    printf("pwntools: https://github.com/Gallopsled/pwntools\n\n");

    printf("Shellcode can be found at http://shell-storm.org/shellcode under the Linux/x86-64 section.\n\n");

    printf("Input = %p", buffer);
    visualize_stack();
    printf("Input > ");
    gets(buffer);

    visualize_stack();
}

int main(void) {

    vuln();

    return 0;
}
