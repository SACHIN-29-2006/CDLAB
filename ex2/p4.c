%{
#include <stdio.h>
%}

%start AFTER_OPERAND

%%

[a-zA-Z_][a-zA-Z0-9_]*    { printf("IDENTIFIER : %s\n", yytext); BEGIN(AFTER_OPERAND); }
[0-9]+                    { printf("INT CONSTANT : %s\n", yytext); BEGIN(AFTER_OPERAND); }

<AFTER_OPERAND>"-"        { printf("BINARY SUBTRACTION : -\n"); BEGIN(INITIAL); }
"-"                       { printf("UNARY MINUS : -\n"); }
"="                       { printf("OPERATOR : =\n"); BEGIN(INITIAL); }
"("                       { printf("PUNCTUATION : (\n"); BEGIN(INITIAL); }
")"                       { printf("PUNCTUATION : )\n"); BEGIN(AFTER_OPERAND); }
";"                       { printf("PUNCTUATION : ;\n"); BEGIN(INITIAL); }

[ \t\n]+                  ; /* Spaces do not reset the state */
.                         { printf("INVALID : %s\n", yytext); }

%%

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        FILE *fp = fopen(argv[1], "r");

        if(fp)
            yyin = fp;
        else
            printf("Cannot open file.\n");
    }

    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
