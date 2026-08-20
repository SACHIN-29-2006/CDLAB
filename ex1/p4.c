%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;

FILE *mail;
FILE *url;
%}

email [a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}
url   (https?:\/\/[a-zA-Z0-9.\/?=_-]+)

%%

{email} { fprintf(mail, "%s\n", yytext); }
{url}   { fprintf(url , "%s\n", yytext); }
.|\n

%%

int main(int argc, char *argv[])
{
    mail = fopen("email.txt", "w");
    url = fopen("url.txt", "w");

    if (mail == NULL || url == NULL) {
        printf("Error: Could not create output files.\n");
        return 1;
    }

    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Error: Could not open input file %s\n", argv[1]);
            fclose(mail);
            fclose(url);
            return 1;
        }
    }

    yylex();

    fclose(mail);
    fclose(url);

    return 0;
}

int yywrap()
{
    return 1;
}
