#include <stdio.h>
#include <stdlib.h>
void init();
char *get_flag();

void i_am_rly_leet() {
    printf("You found me!\nGood job!\n");
    printf("Here is your flag: %s!\n", get_flag());
    return;
}

void challenge() {
    char my_string[16];
    printf("Win Func @ %p\n", i_am_rly_leet);
    fgets(my_string, 40, stdin);
}

int main() {
    init();
    challenge();
    return 0;
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
