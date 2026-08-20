%{
#include <stdio.h>
#include <stdlib.h> // Required for exit()
%}

%x FORHEADER INIT COND UPDATE

%%

[ \t\n]+ ;

"for" {
    printf("KEYWORD : for\n");
    BEGIN(FORHEADER);
}

<FORHEADER>"(" {
    printf("PUNCTUATION : (\n");
    BEGIN(INIT);
}

<INIT>[ \t]+ ;

<INIT>[^;]+ {
    printf("INITIALIZATION : %s", yytext);
}

<INIT>";" {
    printf("\nPUNCTUATION : ;\n");
    BEGIN(COND);
}

<COND>[ \t]+ ;

<COND>[^;]+ {
    printf("CONDITION : %s", yytext);
}

<COND>";" {
    printf("\nPUNCTUATION : ;\n");
    BEGIN(UPDATE);
}

<UPDATE>[ \t]+ ;

<UPDATE>[^)]+ {
    printf("UPDATE : %s", yytext);
}

<UPDATE>")" {
    printf("\nPUNCTUATION : )\n");
    BEGIN(INITIAL);
}

"{" {
    printf("PUNCTUATION : {\n");
}

"}" {
    printf("PUNCTUATION : }\n");
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("IDENTIFIER : %s\n", yytext);
}

"+="|"-="|"*="|"/="|"%=" {
    printf("COMPOUND OP : %s\n", yytext);
}

";" {
    printf("PUNCTUATION : ;\n");
}

%%

int main(int argc, char *argv[])
{
    // Check if a file name was passed as an argument
    if (argc > 1)
    {
        FILE *file = fopen(argv[1], "r");
        if (!file)
        {
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            exit(1);
        }
        // Redirect standard Lex input to the opened file
        yyin = file;
    }
    else
    {
        printf("No file provided. Reading from standard input (Ctrl+D to exit):\n");
    }

    yylex();

    // Close file if it was opened
    if (argc > 1)
    {
        fclose(yyin);
    }

    return 0;
}

int yywrap()
{
    return 1;
}
