#include <stdio.h>
#include <string.h>
#include <unistd.h>
void init();

void challenge() {
    char leaky[16];
    read(0, leaky, 16);

    printf("Leaky buffer: %s\n", leaky);
    printf("Did you manage to leak anything?\n");

    fgets(leaky, 64, stdin);
}

int main() {
    init();
    challenge();
    return 0;
}

/* Aux Functions */
#include <stdio.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}
