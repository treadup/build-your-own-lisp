#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "mpc.h"

int main(int argc, char** argv) {

    /* Create some parsers */
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

    /* Define them with the following grammar. */
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                    \
          number   : /-?[0-9]+/ ;                            \
          operator : '+' | '-' | '*' | '/' ;                 \
          expr     : <number> | '(' <operator> <expr>+ ')' ; \
          lispy    : /^/ <operator> <expr>+ /$/ ;            \
        ",
        Number, Operator, Expr, Lispy);

    /* Print version and Exit information */
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while(1) {

        /* Output the prompt and get the input. */
        char *input = readline("lispy> ");

        if(strcmp(input, "\\quit") == 0) {
            break;
        }

        /* Add input to history */
        add_history(input);

        /* Echo the output back to the user */
        printf("No you are a %s\n", input);

        /* Free the retrieved input. */
        free(input);
    }

    /* Undefine and delete our parsers. */
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}
