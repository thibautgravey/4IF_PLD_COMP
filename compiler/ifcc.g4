grammar ifcc;

axiom: prog;

prog: def_func+;

def_func: TYPE ID '(' param_list? ')' '{' line* '}';

line:
	var_decl ';'
	| array_decl
	| expr ';'
	| return_stmt
	| ifblock
	| whileblock
	| forblock
	| block
	| BREAK ';'
	| CONTINUE ';';

param_list: param (',' param)*;

param: TYPE ID;

var_decl: TYPE ID ('=' expr)? (inline_var_decl)*;

array_decl:
	TYPE ID '[' ']' '=' '{' expr_list '}' ';'				# array_decl_no_size
	| TYPE ID '[' CONST ']' ('=' '{' expr_list '}')? ';'	# array_decl_size;

inline_var_decl: (',' ID ('=' expr)?);

return_stmt: 'return' expr ';';

ifblock: ('if' '(' expr ')' (line | block) elseblock?);

elseblock: 'else' (line | block | ifblock);

whileblock: ('while' '(' expr ')' (line | block));

forblock: (
		'for' '(' (var_decl | expr_list)? ';' expr? ';' expr_list? ')' (
			line
			| block
		)
	);

block: '{' line* '}';

expr:
	ID '[' expr ']'						# array
	| '(' expr ')'						# par
	| ID '(' expr_list? ')'				# function
	| (OP_LESS | OP_UNAIRE_NOT)? (CONST | CHAR | ID)	# literal
	| (OP_LESS | OP_UNAIRE_NOT) expr	# opp_or_not
	| expr (OP_DIV | OP_MULT) expr		# div_or_mult
	| expr (OP_LESS | OP_ADD) expr		# less_or_add
	| expr (
		OP_GREATER_EQUAL
		| OP_GREATER
		| OP_LESSER_EQUAL
		| OP_LESSER
	) expr							# greater_equal_lesser_equal
	| expr OP_DOUBLE_EQUAL expr		# equal
	| expr OP_NOT_EQUAL expr		# notequal
	| expr OP_BITWISE_AND expr		# and
	| expr OP_BITWISE_OR expr		# or
	| expr OP_BITWISE_XOR expr		# xor
	| expr OP_LOGICAL_AND expr		# cdtand
	| expr OP_LOGICAL_OR expr		# cdtor
	| ID OP_EQUAL expr				# var_aff
	| ID OP_EQUAL '{' expr_list '}'	# array_aff
	| ID '[' expr ']' OP_EQUAL expr	# array_element_aff;

expr_list: expr (',' expr)*;

TYPE: 'int32_t' | 'int64_t' | 'char' | 'void';

CONST: [0-9]+;
CHAR: '\'' . '\'';
OP_UNAIRE_NOT: '!';
OP_DIV: '/';
OP_MULT: '*';
OP_LESS: '-';
OP_ADD: '+';
OP_BITWISE_AND: '&';
OP_BITWISE_OR: '|';
OP_BITWISE_XOR: '^';
OP_EQUAL: '=';
OP_DOUBLE_EQUAL: '==';
OP_NOT_EQUAL: '!=';
OP_GREATER_EQUAL: '>=';
OP_GREATER: '>';
OP_LESSER_EQUAL: '<=';
OP_LESSER: '<';
OP_LOGICAL_AND: '&&';
OP_LOGICAL_OR: '||';
BREAK: 'break';
CONTINUE: 'continue';

ID: [_a-zA-Z][_a-zA-Z0-9]*;

SINGLE_COMMENT: '//' .*? '\n' -> skip;

MULTILINE_COMMENT: '/*' .*? '*/' -> skip;

DIRECTIVE: '#' .*? '\n' -> skip;

WS: [ \t\r\n] -> channel(HIDDEN);