#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define BUF_SIZE 64
#define PASS_LEN 32
void init();

char pass[PASS_LEN];

void get_flag() {
    system("/bin/sh");
}

void canary_down(int should_succeed) {
    char user_pass[PASS_LEN] = {0};

    while (1) {
        if (should_succeed == 0x5EAF000D) {
            get_flag();
        } else {
            puts("Password incorrect, try again.");
            printf("Pass: ");
            read(0, user_pass, BUF_SIZE);
        }
    }
}

int main() {
    init();

    char user_pass[BUF_SIZE] = {0};
    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, pass, PASS_LEN);

    printf("Pass: ");
    read(0, user_pass, BUF_SIZE);

    canary_down(memcmp(pass, user_pass, PASS_LEN));
}

/* Aux Functions */
#include <stdio.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}
