#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void init();
char *get_flag();

void win() {
    printf("Congratulations, you win!!! You successfully changed the code flow\n");
    printf("Flag, %s\n", get_flag());
}

int challenge() {
    char buffer[64];
    printf("You win this game if you are able to call the function win.'\n");
    gets(buffer);
}

int main() {
    init();
    challenge();
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
