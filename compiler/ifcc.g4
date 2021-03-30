grammar ifcc;

axiom: prog;

prog: TYPE 'main' '(' ')' '{' line* '}';

line: var_decl | var_aff | return_stmt | ifblock;

var_decl: TYPE VAR_NAME ('=' expr)? (inline_var_decl)* ';';

inline_var_decl: (',' VAR_NAME ('=' expr)?);

var_aff: VAR_NAME '=' expr ';';

return_stmt: 'return' expr ';';

ifblock: ('if' '(' condition ')' (line | block) elseblock?);
elseblock: 'else' (line | block | ifblock);

condition:
	boolcdt '&&' condition		# cdtand
	| boolcdt '||' condition	# cdtor
	| boolcdt					# cdtbool;

boolcdt:
	expr '==' expr		# equal
	| expr '!=' expr	# notequal
	| expr '>=' expr	# greaterequal
	| expr '>' expr		# greater
	| expr '<=' expr	# lessequal
	| expr '<' expr		# less
	| expr				# expression;

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

block: '{' line* '}';

VAR_NAME: [a-zA-Z_][\\w]*;

COMMENT: '/*' .*? '*/' -> skip;

DIRECTIVE: '#' .*? '\n' -> skip;

WS: [ \t\r\n] -> channel(HIDDEN);