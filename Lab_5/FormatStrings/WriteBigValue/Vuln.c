#include <stdio.h>
#include <unistd.h>
#define BUFFER_LEN 128
char *get_flag();

unsigned int target_before = 0;
unsigned int target = 0;
unsigned int target_after = 0;

void vuln() {
    char buffer[BUFFER_LEN] = {0};
    read(0, buffer, BUFFER_LEN-1);

    printf(buffer);

    if (target == 0x0f5f1aa9) {
        printf("Success! You hit the target!\n");
        printf("Here is your flag: %s\n", get_flag());
    } else {
        printf("Oops, not quite! Target was: %08x", target);
    }
}

int main() {
    vuln();
}

/* Aux Functions */
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char *get_flag() {
    char *secret = calloc(50, 1);

    int fd = open("/home/ctf/flag", O_RDONLY);
    if (fd == -1) {
        char *default_flag = "STT{The_Correct_Flag_is_On_The_Server}";
        memcpy(secret, default_flag, strlen(default_flag));
    } else {
        read(fd, secret, 49);
        close(fd);
    }

    return secret;
}
