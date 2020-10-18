#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 64
#define CMD_MAX_SIZE 128
void init();

void get_flag() {
    system("/bin/sh");
}

void canary_down() {
    char c;
    char buf[BUF_SIZE] = {0};
    int leave = 0;

    while (!leave) {
        printf("\nInput: ");

        do {
            c = getchar();
        } while (c == '\n');


        // Eat until a '\n'.
        while (getchar() != '\n') {}

        switch (c) {
            case 'p':
            case 'P':
                printf("%s", buf);
                break;
            case 'w':
            case 'W':
                read(0, buf, CMD_MAX_SIZE);
                break;
            case 'e':
            case 'E':
                leave = 1;
                break;
            default:
                printf("Unknown command '%c'.\n", c);
                printf("Usage: 'w' for writting, 'p' for reading, 'e' for exiting.\n");
        }
    }
}

int main() {
    init();
    canary_down();
}

/* Aux Functions */
#include <stdio.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}
