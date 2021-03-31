grammar ifcc;

axiom: prog;

prog: def_func+;

def_func: TYPE ID '(' param_list? ')' '{' line* '}';

param_list: param (',' param)*;

param: TYPE ID;

line: var_decl | expr ';' | return_stmt;

var_decl: TYPE ID ('=' expr)? (inline_var_decl)* ';';

inline_var_decl: (',' ID ('=' expr)?);

return_stmt: 'return' expr ';';

expr:
	CONST								# const
	| ID								# var
	| '(' expr ')'						# par
	| ID '(' expr_list? ')'				# function
	| (OP_LESS | OP_UNAIRE_NOT) expr	# opp_or_not
	| expr (OP_DIV | OP_MULT) expr		# div_or_mult
	| expr (OP_LESS | OP_ADD) expr		# less_or_add
	| expr '&' expr						# and
	| expr '|' expr						# or
	| expr '^' expr						# xor
	| ID '=' expr						# var_aff
	;

expr_list: expr (',' expr)*;

TYPE: 'int32_t' | 'int64_t' | 'void';

CONST: [0-9]+;
OP_DIV: '/';
OP_MULT: '*';
OP_LESS: '-';
OP_ADD: '+';
OP_UNAIRE_NOT: '!';

ID: [_a-zA-Z][_a-zA-Z0-9]*;

COMMENT: '/*' .*? '*/' -> skip;

DIRECTIVE: '#' .*? '\n' -> skip;

WS: [ \t\r\n] -> channel(HIDDEN);