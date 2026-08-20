%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
%}

%%
"//".*                      { }
"/*"([^*]|\*+[^*/])*\*+"/"  { }
[ \t]+                      { printf(" "); }
\n+                         { printf("\n"); }
.                           { printf("%s", yytext); }
%%

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            return 1;
        }
    }

    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
