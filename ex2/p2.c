%{
#include <stdio.h>
#include <string.h>

/* Temporary buffers to hold extracted expressions safely */
char init_expr[100];
char cond_expr[100];
char upd_expr[100];
%}

/* Define Exclusive Start Conditions for capturing expressions sequentially */
%x INIT_STATE COND_STATE UPD_STATE

%%

"for"                  { printf("KEYWORD : %s\n", yytext); }

    /* Match the opening parenthesis of the for loop and jump to capturing initialization */
"for"[ \t\n]*"("       {
                         printf("KEYWORD : for\n");
                         printf("PUNCTUATION : (\n");
                         init_expr[0] = '\0';
                         BEGIN(INIT_STATE);
                       }

    /* 1. INITIALIZATION STATE */
<INIT_STATE>";"        {
                         printf("INITIALIZATION : %s\n", init_expr);
                         printf("PUNCTUATION : ;\n");
                         cond_expr[0] = '\0';
                         BEGIN(COND_STATE);
                       }
<INIT_STATE>[^;]+      { strcat(init_expr, yytext); }

    /* 2. CONDITION STATE */
<COND_STATE>";"        {
                         printf("CONDITION : %s\n", cond_expr);
                         printf("PUNCTUATION : ;\n");
                         upd_expr[0] = '\0';
                         BEGIN(UPD_STATE);
                       }
<COND_STATE>[^;]+      { strcat(cond_expr, yytext); }

    /* 3. UPDATE STATE */
<UPD_STATE>")"         {
                         printf("UPDATE : %s\n", upd_expr);
                         printf("PUNCTUATION : )\n");
                         BEGIN(INITIAL); /* Return to default matching state */
                       }
<UPD_STATE>[^)]+       { strcat(upd_expr, yytext); }


    /* Default State Token Matchers matching your template style */
"{"                    { printf("PUNCTUATION : {\n"); }
"}"                    { printf("PUNCTUATION : }\n"); }
";"                    { printf("PUNCTUATION : ;\n"); }
"("                    { printf("PUNCTUATION : (\n"); }
")"                    { printf("PUNCTUATION : )\n"); }

"+="                   { printf("COMPOUND OP : +=\n"); }
"-="                   { printf("COMPOUND OP : -=\n"); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER : %s\n", yytext); }
[0-9]+                 { printf("NUMBER : %s\n", yytext); }

[ \t\n]+               ;   /* Ignore whitespace */

.                      { printf("INVALID : %s\n", yytext); }

%%

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        FILE *fp = fopen(argv[1], "r");

        if(fp)
            yyin = fp;
        else
        {
            printf("Cannot open file.\n");
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
