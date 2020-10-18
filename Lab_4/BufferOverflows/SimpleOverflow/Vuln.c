#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void init();
char *get_flag();

int main() {
    init();
    int control;
    char buffer[64];

    printf("You win this game if you can change variable control\n");

    control = 0;
    gets(buffer);

    if (control != 0) {
        printf("YOU WIN!\n");
        printf("Take my secrets: %s\n", get_flag());
    } else {
        printf("Try again...\n");
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
