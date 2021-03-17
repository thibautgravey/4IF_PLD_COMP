grammar ifcc;

axiom: prog;

prog: TYPE 'main' '(' ')' '{' line* '}';

line: var_decl | var_aff | return_stmt;

var_decl: TYPE VAR_NAME ('=' expr)? (inline_var_decl)* ';';

inline_var_decl: (',' VAR_NAME ('=' expr)?);

var_aff: VAR_NAME '=' expr ';';

return_stmt: 'return' expr ';';

expr:
	CONST			# const
	| VAR_NAME		# var
	| '(' expr ')'	# par
	| expr (OP_DIV | OP_MULT) expr # div_or_mult
	| expr (OP_LESS | OP_ADD) expr	# less_or_add
	| expr '&' expr	# and
	| expr '|' expr	# or
	| expr '^' expr	# xor;

TYPE: 'int';

OP_DIV: '/';
OP_MULT: '*';
OP_LESS: '-';
OP_ADD: '+';

CONST: '-'? [0-9]+;

VAR_NAME: [a-zA-Z_][\\w]*;

COMMENT: '/*' .*? '*/' -> skip;

DIRECTIVE: '#' .*? '\n' -> skip;

WS: [ \t\r\n] -> channel(HIDDEN);