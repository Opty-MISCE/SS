#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void init();
char *get_flag();

int very_complex_function(char *password) {
    int result;
    char buffer[16];

    result = 0;
    strcpy(buffer, password);

    if (strcmp(buffer, get_flag()) == 0)
        result = 1;

    return result;
}

int main() {
    init();

    char pass[64] = {0};
    read(0, pass, 63);

    if (very_complex_function(pass)) {
        printf("Welcome back! Here is your token: %s\n", get_flag());
    } else {
        printf("Unauthorized user/passwd\n");
    }
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
