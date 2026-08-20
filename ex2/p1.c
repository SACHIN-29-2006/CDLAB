%{
#include <stdio.h>
%}

%%
^#include[ \t]*<[^>]+>       { printf("Standard Header File: %s\n", yytext); }
^#include[ \t]*\"[^\"]+\"   { printf("User-defined Header File: %s\n", yytext); }
.|\n                       { /* Ignore all other characters and lines */ }
%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    } else {
        printf("Please enter C code (Press Ctrl+D to end input):\n");
    }

    yylex();
    return 0;
}
