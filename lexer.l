   #include "commands.h"
   #include "grammar.tab.h"
   
%%

\"[a-z]+    { yylval.str = strdup(yytext + 1); return VAR_NAME; } 

:[a-z]+     { yylval.str = strdup(yytext + 1); return VAR_VALUE; }

make        { return MAKE; }

forward|fd  { return FD; }

right|rt    { return RT; }

repeat      { return RPT; }

[0-9]+      { yylval.inteiro = atoi(yytext); return INT; }

[ \n\r\t]   { /* ignore */ }

.           { return yytext[0]; }

%%

int yywrap() { return 1; }
