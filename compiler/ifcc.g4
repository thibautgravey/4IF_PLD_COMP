grammar ifcc;

axiom: prog;

prog: 'int' 'main' '(' ')' '{' line* '}';

line: var_decl | var_aff | return_stmt;

var_decl: TYPE VAR_NAME ('=' expr)? (inline_var_decl)* ';';

inline_var_decl: (',' VAR_NAME ('=' expr)?);

var_aff: VAR_NAME '=' expr ';';

return_stmt: 'return' expr ';';

expr:
	CONST			# const
	| VAR_NAME		# var
	| '(' expr ')'	# par
	| expr '/' expr	# div
	| expr '*' expr	# mult
	| expr '-' expr	# less
	| expr '+' expr	# add
	| expr '|' expr	# or
	| expr '&' expr	# and
	| expr '^' expr	# xor;

TYPE: 'int';

CONST: '-'? [0-9]+;

VAR_NAME: [a-zA-Z_][\\w]*;

COMMENT: '/*' .*? '*/' -> skip;

DIRECTIVE: '#' .*? '\n' -> skip;

WS: [ \t\r\n] -> channel(HIDDEN);