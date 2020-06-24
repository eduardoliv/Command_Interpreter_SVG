%{ 
   #include <stdio.h>
   #include "commands.h"
   #include "grammar.tab.h"
   int yylex();
   int yyerror(char*);
%}

%union {
   int inteiro;
   command *comandos;
   Value *value;
   char *str;
}

%token FD RT RPT MAKE
%token<str> VAR_NAME VAR_VALUE
%token<inteiro> INT

%type<comandos> command commandList
%type<value> value
%%

program : commandList { Draw($1); };

commandList 
  : command              { $$ = $1; }
  | command commandList  { $1->next = $2; $$ = $1; }
  ;

command  
  : FD value   { $$ = insert_Forward( NULL, $2 ); }
  | RT value   { $$ = insert_RotateRight (NULL, $2); }
  | RPT value '[' commandList ']' { $$ = insert_Repeat(NULL ,$2, $4 ); }
  | MAKE VAR_NAME value { $$ = insert_Make(NULL, $2, $3); } 
  ;

value: INT       { $$ = new_int_value($1); }
     | VAR_VALUE { $$ = new_var_value($1); }
     ; 

%%

int yyerror(char* msg) {
  printf("ERROR: %s\n", msg);
  return 0;
}