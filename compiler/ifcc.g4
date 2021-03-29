grammar ifcc;

axiom: prog;

prog: TYPE 'main' '(' ')' '{' line* '}'; //change to block

line: var_decl | var_aff | return_stmt | ifelse;

var_decl: TYPE VAR_NAME ('=' expr)? (inline_var_decl)* ';';

inline_var_decl: (',' VAR_NAME ('=' expr)?);

var_aff: VAR_NAME '=' expr ';';

return_stmt: 'return' expr ';';

expr:
	CONST							# const
	| VAR_NAME						# var
	| '(' expr ')'					# par
	| expr (OP_DIV | OP_MULT) expr	# div_or_mult
	| expr (OP_LESS | OP_ADD) expr	# less_or_add
	| expr '&' expr					# and
	| expr '|' expr					# or
	| expr '^' expr					# xor
	| '-' expr						# opp
	| '!' expr						# not;

TYPE: 'int32_t' | 'int64_t';

CONST: [0-9]+;
OP_DIV: '/';
OP_MULT: '*';
OP_LESS: '-';
OP_ADD: '+';

ifelse:
	'if(' expr ')' (line | block) (
		'else' ((line | block) | ifelse)
	)?;

block: '{' line* '}';

VAR_NAME: [a-zA-Z_][\\w]*;

COMMENT: '/*' .*? '*/' -> skip;

DIRECTIVE: '#' .*? '\n' -> skip;

WS: [ \t\r\n] -> channel(HIDDEN);