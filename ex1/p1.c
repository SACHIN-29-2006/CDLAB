%{
#include <stdio.h>
%}

ID [a-zA-Z_][a-zA-Z]*

%%
{ID}    {printf("Valid C identifier\n");}
.*      {printf("Invalid C identifier\n");}
%%

int main(int argc,char *argv[])
{
if(argc>1)
{
FILE *fp = fopen(argv[1],"r");
yyin = fp;
}
yylex();
return 0;
}
int yywrap()
{
return 0;
}
