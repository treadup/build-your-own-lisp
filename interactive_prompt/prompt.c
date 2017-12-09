
#include <stdio.h>

/* Declare a buffer for user input of size 2048 */
static char input[2048];

int main(int argc, char** argv) {

    /* Print version and Exit information */
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while(1) {
        /* Output the prompt */
        fputs("lispy> ", stdout);

        /* Read a line of user input of maximum size 2048 */
        fgets(input, 2048, stdin);

        /* Echo the output back to the user */
        printf("No you are a %s", input);
    }

    return 0;
}
