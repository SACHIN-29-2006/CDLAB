%{
#include <stdio.h>
#include <string.h>

/* Flag to track if the previous token was a template type name */
int after_template_name = 0;
%}

%%

"vector"               {
                         printf("TEMPLATE NAME : %s\n", yytext);
                         after_template_name = 1; /* Turn on context flag */
                       }

"if"                   {
                         printf("KEYWORD : %s\n", yytext);
                         after_template_name = 0;
                       }

"int"                  {
                         printf("DATA TYPE : %s\n", yytext);
                         /* Do not reset the flag yet, as closing bracket '>' follows */
                       }

"<"                    {
                         if (after_template_name) {
                             printf("TEMPLATE BRACKET (left context: after template name) : <\n");
                         } else {
                             printf("RELATIONAL OP : <\n");
                         }
                       }

">"                    {
                         if (after_template_name) {
                             printf("TEMPLATE BRACKET (left context: after template name) : >\n");
                             after_template_name = 0; /* Reset flag after template structure closes */
                         } else {
                             printf("RELATIONAL OP : >\n");
                         }
                       }

"="                    {
                         printf("OPERATOR : =\n");
                         after_template_name = 0;
                       }

"("                    { printf("PUNCTUATION : (\n"); after_template_name = 0; }
")"                    { printf("PUNCTUATION : )\n"); after_template_name = 0; }
";"                    { printf("PUNCTUATION : ;\n"); after_template_name = 0; }

[0-9]+                 {
                         printf("INT CONSTANT : %s\n", yytext);
                         after_template_name = 0;
                       }

[a-zA-Z_][a-zA-Z0-9_]* {
                         printf("IDENTIFIER : %s\n", yytext);
                         after_template_name = 0; /* Standard identifier clears the template context */
                       }

[ \t\n]+               ;   /* Ignore whitespace without altering flag context */

.                      { printf("INVALID : %s\n", yytext); after_template_name = 0; }

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
