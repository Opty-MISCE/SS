#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void init();
char *get_flag();

int main() {
    init();
    int control;
    char buffer[64];

    printf("You win this game if you can change variable control to the value 0x61626364\n");

    control = 0;
    gets(buffer);

    if (control == 0x61626364) {
        printf("Congratulations, you win!!! You correctly got the variable to the right value\n");
        printf("Flag: %s\n", get_flag());
    } else {
        printf("Try again, you got 0x%08x\n, instead of 0x61626364", control);
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
