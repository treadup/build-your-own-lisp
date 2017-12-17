#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "mpc.h"

int main(int argc, char** argv) {

    /* Print version and Exit information */
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while(1) {

        /* Output the prompt and get the input. */
        char *input = readline("lispy> ");

        /* Add input to history */
        add_history(input);

        /* Echo the output back to the user */
        printf("No you are a %s\n", input);

        /* Free the retrieved input. */
        free(input);
    }

    return 0;
}
