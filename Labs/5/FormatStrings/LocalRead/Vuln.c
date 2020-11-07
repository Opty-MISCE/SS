#include <stdio.h>
#include <unistd.h>
#define BUFFER_LEN 128
void init();
char *get_flag();

char buffer[BUFFER_LEN] = {0};

void vuln() {
    char *secret_value = get_flag();
    printf(buffer);
}

int main() {
    read(0, buffer, BUFFER_LEN-1);
    vuln();
}

/* Aux Functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

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
