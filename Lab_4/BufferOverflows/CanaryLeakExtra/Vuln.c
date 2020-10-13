#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 64

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

void get_flag() {
    system("/bin/sh");
}

void canary_down() {
    char buf[BUF_SIZE] = {0};

    printf("Alert: Canary '%p' is dead!! Leave the mine!\n", ((int *) buf)[BUF_SIZE / sizeof(int)]);
    read(0, buf, 128);
    printf("Alert: %s\n", buf);
}

int main() {
    init();
    canary_down();
}
