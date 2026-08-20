%{
#include <stdio.h>
#include <string.h>

int pal_count = 0;

int pal_check(char str[], int length) {
    int i = 0;
    int j = length - 1;

    while (i < j) {
        if (str[i] != str[j]) {
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}
%}

%%

[ab]+ {
         if (pal_check(yytext, yyleng))
         {
            pal_count++;
            if (yyout) {
                fprintf(yyout, "%s\n", yytext);
            }
         }
      }

.|\n  { ; }

%%

int main(int argc, char *argv[])
{
    FILE *fp = NULL;

    if(argc > 1)
    {
        fp = fopen(argv[1], "r");
        if(fp) {
            yyin = fp;
        } else {
            printf("Error opening input file.\n");
            return 1;
        }
    }

    yyout = fopen("output.txt", "w");
    if(!yyout) {
        printf("Error creating output.txt\n");
        if(fp) fclose(fp);
        return 1;
    }

    yylex();

    printf("\nNo. of Palindromes : %d\n", pal_count);

    if(fp) fclose(fp);
    fclose(yyout);

    return 0;
}

int yywrap() {
    return 1;
}
