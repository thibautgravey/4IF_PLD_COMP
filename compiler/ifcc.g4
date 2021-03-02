grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' line* '}' ;

line: (var_decl | var_aff | RETURN expr) ';' ;

var_decl: TYPE VAR_NAME ('=' expr)? ;

var_aff: VAR_NAME '=' expr ;

expr: CONST | VAR_NAME ;

RETURN : 'return' ;

TYPE : 'int' ;

CONST : [0-9]+ ;

VAR_NAME : [a-zA-Z_][\\w]*  ;

COMMENT : '/*' .*? '*/' -> skip ;

DIRECTIVE : '#' .*? '\n' -> skip ;

WS : [ \t\r\n] -> channel(HIDDEN);
