#include "libvisualize.h"

static uint64_t *search(uint64_t token, uint64_t *start, uint64_t *end) {
    int delta = end - start;

    for (int i = 0; i <= delta; i++) {
        if (start[i] == token) {
            return start + i;
        }
    }

    return NULL;
}

static uint64_t get_canary() {
    long canary = 0;
    __asm__("movq %%fs:0x28, %0;" :"=r"(canary));

    return canary;
}

void visualize_stack() {
    uint64_t *rbp;
    uint64_t *rsp;
    uint64_t *ret_p;
    int delta;

    // Get the value of RBP
    rbp = __builtin_frame_address(1);

    // Get the value of RBP (Is there a better way of doing this?)
    rsp = __builtin_frame_address(0) + 0x10;

    // Get the saved return address
    ret_p = rbp + 1;

    // Calculate the difference between RBP and RSP
    delta = rbp - rsp;

    printf("\n");

    // Print the legend at the top containing the registers and return address
    printf("RSP = %p\n", rsp);
    printf("RBP = %p\n", rbp);

    // Get the canary and print it
    if (canary == NULL || !(rsp <= canary && canary <= rbp))
        canary = search(get_canary(), rsp, rbp);

    if (canary == NULL) {
        printf("Canary not found.\n");
    } else {
        printf("Canary = %p -> ", canary);
        printf(COLOR_YELLOW);
        printf("%#018lx\n", *canary);
        printf(COLOR_RESET);
    }

    // Print out the return address
    printf("RET = %p -> ", ret_p);
    printf(COLOR_RED);
    printf("%#018lx", *ret_p);
    printf(COLOR_RESET);
    printf("\n\n");

    // Print out a hexdump of the stack
    printf("Stack:\n");
    for (int i = 0; i <= delta - 2; i++) {
        printf("%p | ", rsp);
        for (int j = 0; j < 8; j++) {
            printf("%02x ", *((uint8_t *)rsp + j));
        }
        printf("|\n");
        rsp++;
    }

    // Print out the canary
    if (canary != NULL) {
        printf("%p | ", rsp);
        printf(COLOR_YELLOW);
        for (int i = 0; i < 8; i++) {
            printf("%02x ", *((uint8_t *)rsp + i));
        }
        printf(COLOR_RESET);
        printf("|\n");
        rsp++;
    }

    // Print out the rest of the stack
    delta = ret_p - rsp;
    for (int i = 0; i < delta; i++) {
        printf("%p | ", rsp);
        for (int j = 0; j < 8; j++) {
            printf("%02x ", *((uint8_t *)rsp + j));
        }
        printf("|\n");
        rsp++;
    }

    // Print out the return address
    printf("%p | ", rsp);
    printf(COLOR_RED);
    for (int i = 0; i < 8; i++) {
        printf("%02x ", *((uint8_t *)rsp + i));
    }
    printf(COLOR_RESET);
    printf("| <- callme1\n");
    rsp++;

    printf("%p | ", rsp);
    for (int i = 0; i < 8; i++) {
        printf("%02x ", *((uint8_t *)rsp + i));
    }
    printf("| <- callme2\n");
    rsp++;

    printf("%p | ", rsp);
    for (int i = 0; i < 8; i++) {
        printf("%02x ", *((uint8_t *)rsp + i));
    }
    printf("| <- win\n");

    printf("\n");
}
