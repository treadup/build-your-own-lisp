#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "mpc.h"

/* Use operator string to see which operator to use */
long eval_op(long x, char* op, long y) {
    if(strcmp(op, "+") == 0) { return x + y; }
    if(strcmp(op, "-") == 0) { return x - y; }
    if(strcmp(op, "*") == 0) { return x * y; }
    if(strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

long eval(mpc_ast_t* t) {

    /* If tagged as number return it directly */
   if(strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    /* The operator is always the second child */
    char* op = t->children[1]->contents;

    /* We store the third child in the variable x */
    long x = eval(t->children[2]);

    /* Iterate the remaining children and combining */
    int i = 3;
    while(strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}

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

        /* Attempt to parse the user input */
        mpc_result_t r;
        if(mpc_parse("<stdin>", input, Lispy, &r)) {
            /* On Success Evaluate the AST */
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
        } else {
            /* Otherwise Print the Error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        /* Free the retrieved input. */
        free(input);
    }

    /* Undefine and delete our parsers. */
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}
