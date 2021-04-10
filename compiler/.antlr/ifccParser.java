// Generated from /home/tmignot/Bureau/PLD-COMP/4IF_PLD_COMP/compiler/ifcc.g4 by ANTLR 4.8
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, TYPE=13, CONST=14, CHAR=15, OP_UNAIRE_NOT=16, 
		OP_DIV=17, OP_MULT=18, OP_LESS=19, OP_ADD=20, OP_BITWISE_AND=21, OP_BITWISE_OR=22, 
		OP_BITWISE_XOR=23, OP_EQUAL=24, OP_DOUBLE_EQUAL=25, OP_NOT_EQUAL=26, OP_GREATER_EQUAL=27, 
		OP_GREATER=28, OP_LESSER_EQUAL=29, OP_LESSER=30, OP_LOGICAL_AND=31, OP_LOGICAL_OR=32, 
		ID=33, SINGLE_COMMENT=34, MULTILINE_COMMENT=35, DIRECTIVE=36, WS=37;
	public static final int
		RULE_axiom = 0, RULE_prog = 1, RULE_def_func = 2, RULE_line = 3, RULE_param_list = 4, 
		RULE_param = 5, RULE_var_decl = 6, RULE_array_decl = 7, RULE_inline_var_decl = 8, 
		RULE_return_stmt = 9, RULE_ifblock = 10, RULE_elseblock = 11, RULE_whileblock = 12, 
		RULE_block = 13, RULE_expr = 14, RULE_expr_list = 15;
	private static String[] makeRuleNames() {
		return new String[] {
			"axiom", "prog", "def_func", "line", "param_list", "param", "var_decl", 
			"array_decl", "inline_var_decl", "return_stmt", "ifblock", "elseblock", 
			"whileblock", "block", "expr", "expr_list"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "'{'", "'}'", "';'", "','", "'['", "']'", "'return'", 
			"'if'", "'else'", "'while'", null, null, null, "'!'", "'/'", "'*'", "'-'", 
			"'+'", "'&'", "'|'", "'^'", "'='", "'=='", "'!='", "'>='", "'>'", "'<='", 
			"'<'", "'&&'", "'||'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, "TYPE", "CONST", "CHAR", "OP_UNAIRE_NOT", "OP_DIV", "OP_MULT", 
			"OP_LESS", "OP_ADD", "OP_BITWISE_AND", "OP_BITWISE_OR", "OP_BITWISE_XOR", 
			"OP_EQUAL", "OP_DOUBLE_EQUAL", "OP_NOT_EQUAL", "OP_GREATER_EQUAL", "OP_GREATER", 
			"OP_LESSER_EQUAL", "OP_LESSER", "OP_LOGICAL_AND", "OP_LOGICAL_OR", "ID", 
			"SINGLE_COMMENT", "MULTILINE_COMMENT", "DIRECTIVE", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ifccParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class AxiomContext extends ParserRuleContext {
		public ProgContext prog() {
			return getRuleContext(ProgContext.class,0);
		}
		public AxiomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_axiom; }
	}

	public final AxiomContext axiom() throws RecognitionException {
		AxiomContext _localctx = new AxiomContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_axiom);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(32);
			prog();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ProgContext extends ParserRuleContext {
		public List<Def_funcContext> def_func() {
			return getRuleContexts(Def_funcContext.class);
		}
		public Def_funcContext def_func(int i) {
			return getRuleContext(Def_funcContext.class,i);
		}
		public ProgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prog; }
	}

	public final ProgContext prog() throws RecognitionException {
		ProgContext _localctx = new ProgContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_prog);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(35); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(34);
				def_func();
				}
				}
				setState(37); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==TYPE );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Def_funcContext extends ParserRuleContext {
		public TerminalNode TYPE() { return getToken(ifccParser.TYPE, 0); }
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public Param_listContext param_list() {
			return getRuleContext(Param_listContext.class,0);
		}
		public List<LineContext> line() {
			return getRuleContexts(LineContext.class);
		}
		public LineContext line(int i) {
			return getRuleContext(LineContext.class,i);
		}
		public Def_funcContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_def_func; }
	}

	public final Def_funcContext def_func() throws RecognitionException {
		Def_funcContext _localctx = new Def_funcContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_def_func);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(39);
			match(TYPE);
			setState(40);
			match(ID);
			setState(41);
			match(T__0);
			setState(43);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TYPE) {
				{
				setState(42);
				param_list();
				}
			}

			setState(45);
			match(T__1);
			setState(46);
			match(T__2);
			setState(50);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__2) | (1L << T__8) | (1L << T__9) | (1L << T__11) | (1L << TYPE) | (1L << CONST) | (1L << CHAR) | (1L << OP_UNAIRE_NOT) | (1L << OP_LESS) | (1L << ID))) != 0)) {
				{
				{
				setState(47);
				line();
				}
				}
				setState(52);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(53);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LineContext extends ParserRuleContext {
		public Var_declContext var_decl() {
			return getRuleContext(Var_declContext.class,0);
		}
		public Array_declContext array_decl() {
			return getRuleContext(Array_declContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Return_stmtContext return_stmt() {
			return getRuleContext(Return_stmtContext.class,0);
		}
		public IfblockContext ifblock() {
			return getRuleContext(IfblockContext.class,0);
		}
		public WhileblockContext whileblock() {
			return getRuleContext(WhileblockContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public LineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_line; }
	}

	public final LineContext line() throws RecognitionException {
		LineContext _localctx = new LineContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_line);
		try {
			setState(64);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(55);
				var_decl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(56);
				array_decl();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(57);
				expr(0);
				setState(58);
				match(T__4);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(60);
				return_stmt();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(61);
				ifblock();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(62);
				whileblock();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(63);
				block();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Param_listContext extends ParserRuleContext {
		public List<ParamContext> param() {
			return getRuleContexts(ParamContext.class);
		}
		public ParamContext param(int i) {
			return getRuleContext(ParamContext.class,i);
		}
		public Param_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param_list; }
	}

	public final Param_listContext param_list() throws RecognitionException {
		Param_listContext _localctx = new Param_listContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_param_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(66);
			param();
			setState(71);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__5) {
				{
				{
				setState(67);
				match(T__5);
				setState(68);
				param();
				}
				}
				setState(73);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParamContext extends ParserRuleContext {
		public TerminalNode TYPE() { return getToken(ifccParser.TYPE, 0); }
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public ParamContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param; }
	}

	public final ParamContext param() throws RecognitionException {
		ParamContext _localctx = new ParamContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_param);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(74);
			match(TYPE);
			setState(75);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Var_declContext extends ParserRuleContext {
		public TerminalNode TYPE() { return getToken(ifccParser.TYPE, 0); }
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public TerminalNode OP_EQUAL() { return getToken(ifccParser.OP_EQUAL, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public List<Inline_var_declContext> inline_var_decl() {
			return getRuleContexts(Inline_var_declContext.class);
		}
		public Inline_var_declContext inline_var_decl(int i) {
			return getRuleContext(Inline_var_declContext.class,i);
		}
		public Var_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var_decl; }
	}

	public final Var_declContext var_decl() throws RecognitionException {
		Var_declContext _localctx = new Var_declContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_var_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(77);
			match(TYPE);
			setState(78);
			match(ID);
			setState(81);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==OP_EQUAL) {
				{
				setState(79);
				match(OP_EQUAL);
				setState(80);
				expr(0);
				}
			}

			setState(86);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__5) {
				{
				{
				setState(83);
				inline_var_decl();
				}
				}
				setState(88);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(89);
			match(T__4);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Array_declContext extends ParserRuleContext {
		public Array_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_array_decl; }
	 
		public Array_declContext() { }
		public void copyFrom(Array_declContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Array_decl_sizeContext extends Array_declContext {
		public TerminalNode TYPE() { return getToken(ifccParser.TYPE, 0); }
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public TerminalNode CONST() { return getToken(ifccParser.CONST, 0); }
		public TerminalNode OP_EQUAL() { return getToken(ifccParser.OP_EQUAL, 0); }
		public Expr_listContext expr_list() {
			return getRuleContext(Expr_listContext.class,0);
		}
		public Array_decl_sizeContext(Array_declContext ctx) { copyFrom(ctx); }
	}
	public static class Array_decl_no_sizeContext extends Array_declContext {
		public TerminalNode TYPE() { return getToken(ifccParser.TYPE, 0); }
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public TerminalNode OP_EQUAL() { return getToken(ifccParser.OP_EQUAL, 0); }
		public Expr_listContext expr_list() {
			return getRuleContext(Expr_listContext.class,0);
		}
		public Array_decl_no_sizeContext(Array_declContext ctx) { copyFrom(ctx); }
	}

	public final Array_declContext array_decl() throws RecognitionException {
		Array_declContext _localctx = new Array_declContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_array_decl);
		int _la;
		try {
			setState(114);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				_localctx = new Array_decl_no_sizeContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(91);
				match(TYPE);
				setState(92);
				match(ID);
				setState(93);
				match(T__6);
				setState(94);
				match(T__7);
				setState(95);
				match(OP_EQUAL);
				setState(96);
				match(T__2);
				setState(97);
				expr_list();
				setState(98);
				match(T__3);
				setState(99);
				match(T__4);
				}
				break;
			case 2:
				_localctx = new Array_decl_sizeContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(101);
				match(TYPE);
				setState(102);
				match(ID);
				setState(103);
				match(T__6);
				setState(104);
				match(CONST);
				setState(105);
				match(T__7);
				setState(111);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==OP_EQUAL) {
					{
					setState(106);
					match(OP_EQUAL);
					setState(107);
					match(T__2);
					setState(108);
					expr_list();
					setState(109);
					match(T__3);
					}
				}

				setState(113);
				match(T__4);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Inline_var_declContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public TerminalNode OP_EQUAL() { return getToken(ifccParser.OP_EQUAL, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Inline_var_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inline_var_decl; }
	}

	public final Inline_var_declContext inline_var_decl() throws RecognitionException {
		Inline_var_declContext _localctx = new Inline_var_declContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_inline_var_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(116);
			match(T__5);
			setState(117);
			match(ID);
			setState(120);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==OP_EQUAL) {
				{
				setState(118);
				match(OP_EQUAL);
				setState(119);
				expr(0);
				}
			}

			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Return_stmtContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Return_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_return_stmt; }
	}

	public final Return_stmtContext return_stmt() throws RecognitionException {
		Return_stmtContext _localctx = new Return_stmtContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_return_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(122);
			match(T__8);
			setState(123);
			expr(0);
			setState(124);
			match(T__4);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfblockContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public LineContext line() {
			return getRuleContext(LineContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public ElseblockContext elseblock() {
			return getRuleContext(ElseblockContext.class,0);
		}
		public IfblockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifblock; }
	}

	public final IfblockContext ifblock() throws RecognitionException {
		IfblockContext _localctx = new IfblockContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_ifblock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(126);
			match(T__9);
			setState(127);
			match(T__0);
			setState(128);
			expr(0);
			setState(129);
			match(T__1);
			setState(132);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				{
				setState(130);
				line();
				}
				break;
			case 2:
				{
				setState(131);
				block();
				}
				break;
			}
			setState(135);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				{
				setState(134);
				elseblock();
				}
				break;
			}
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ElseblockContext extends ParserRuleContext {
		public LineContext line() {
			return getRuleContext(LineContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public IfblockContext ifblock() {
			return getRuleContext(IfblockContext.class,0);
		}
		public ElseblockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elseblock; }
	}

	public final ElseblockContext elseblock() throws RecognitionException {
		ElseblockContext _localctx = new ElseblockContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_elseblock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(137);
			match(T__10);
			setState(141);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				{
				setState(138);
				line();
				}
				break;
			case 2:
				{
				setState(139);
				block();
				}
				break;
			case 3:
				{
				setState(140);
				ifblock();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class WhileblockContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public LineContext line() {
			return getRuleContext(LineContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public WhileblockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_whileblock; }
	}

	public final WhileblockContext whileblock() throws RecognitionException {
		WhileblockContext _localctx = new WhileblockContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_whileblock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(143);
			match(T__11);
			setState(144);
			match(T__0);
			setState(145);
			expr(0);
			setState(146);
			match(T__1);
			setState(149);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				{
				setState(147);
				line();
				}
				break;
			case 2:
				{
				setState(148);
				block();
				}
				break;
			}
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BlockContext extends ParserRuleContext {
		public List<LineContext> line() {
			return getRuleContexts(LineContext.class);
		}
		public LineContext line(int i) {
			return getRuleContext(LineContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(151);
			match(T__2);
			setState(155);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__2) | (1L << T__8) | (1L << T__9) | (1L << T__11) | (1L << TYPE) | (1L << CONST) | (1L << CHAR) | (1L << OP_UNAIRE_NOT) | (1L << OP_LESS) | (1L << ID))) != 0)) {
				{
				{
				setState(152);
				line();
				}
				}
				setState(157);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(158);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ParContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ParContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Array_element_affContext extends ExprContext {
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_EQUAL() { return getToken(ifccParser.OP_EQUAL, 0); }
		public Array_element_affContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class OrContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_BITWISE_OR() { return getToken(ifccParser.OP_BITWISE_OR, 0); }
		public OrContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class CdtandContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_LOGICAL_AND() { return getToken(ifccParser.OP_LOGICAL_AND, 0); }
		public CdtandContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Div_or_multContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_DIV() { return getToken(ifccParser.OP_DIV, 0); }
		public TerminalNode OP_MULT() { return getToken(ifccParser.OP_MULT, 0); }
		public Div_or_multContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class NotequalContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_NOT_EQUAL() { return getToken(ifccParser.OP_NOT_EQUAL, 0); }
		public NotequalContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Less_or_addContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_LESS() { return getToken(ifccParser.OP_LESS, 0); }
		public TerminalNode OP_ADD() { return getToken(ifccParser.OP_ADD, 0); }
		public Less_or_addContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Array_affContext extends ExprContext {
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public TerminalNode OP_EQUAL() { return getToken(ifccParser.OP_EQUAL, 0); }
		public Expr_listContext expr_list() {
			return getRuleContext(Expr_listContext.class,0);
		}
		public Array_affContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Greater_equal_lesser_equalContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_GREATER_EQUAL() { return getToken(ifccParser.OP_GREATER_EQUAL, 0); }
		public TerminalNode OP_GREATER() { return getToken(ifccParser.OP_GREATER, 0); }
		public TerminalNode OP_LESSER_EQUAL() { return getToken(ifccParser.OP_LESSER_EQUAL, 0); }
		public TerminalNode OP_LESSER() { return getToken(ifccParser.OP_LESSER, 0); }
		public Greater_equal_lesser_equalContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class LiteralContext extends ExprContext {
		public TerminalNode CONST() { return getToken(ifccParser.CONST, 0); }
		public TerminalNode CHAR() { return getToken(ifccParser.CHAR, 0); }
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public LiteralContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class EqualContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_DOUBLE_EQUAL() { return getToken(ifccParser.OP_DOUBLE_EQUAL, 0); }
		public EqualContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Var_affContext extends ExprContext {
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public TerminalNode OP_EQUAL() { return getToken(ifccParser.OP_EQUAL, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Var_affContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class CdtorContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_LOGICAL_OR() { return getToken(ifccParser.OP_LOGICAL_OR, 0); }
		public CdtorContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class ArrayContext extends ExprContext {
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ArrayContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class AndContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_BITWISE_AND() { return getToken(ifccParser.OP_BITWISE_AND, 0); }
		public AndContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class FunctionContext extends ExprContext {
		public TerminalNode ID() { return getToken(ifccParser.ID, 0); }
		public Expr_listContext expr_list() {
			return getRuleContext(Expr_listContext.class,0);
		}
		public FunctionContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class XorContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OP_BITWISE_XOR() { return getToken(ifccParser.OP_BITWISE_XOR, 0); }
		public XorContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Opp_or_notContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode OP_LESS() { return getToken(ifccParser.OP_LESS, 0); }
		public TerminalNode OP_UNAIRE_NOT() { return getToken(ifccParser.OP_UNAIRE_NOT, 0); }
		public Opp_or_notContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		return expr(0);
	}

	private ExprContext expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExprContext _localctx = new ExprContext(_ctx, _parentState);
		ExprContext _prevctx = _localctx;
		int _startState = 28;
		enterRecursionRule(_localctx, 28, RULE_expr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(195);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
			case 1:
				{
				_localctx = new ArrayContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(161);
				match(ID);
				setState(162);
				match(T__6);
				setState(163);
				expr(0);
				setState(164);
				match(T__7);
				}
				break;
			case 2:
				{
				_localctx = new LiteralContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(166);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << CONST) | (1L << CHAR) | (1L << ID))) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				break;
			case 3:
				{
				_localctx = new ParContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(167);
				match(T__0);
				setState(168);
				expr(0);
				setState(169);
				match(T__1);
				}
				break;
			case 4:
				{
				_localctx = new FunctionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(171);
				match(ID);
				setState(172);
				match(T__0);
				setState(174);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << CONST) | (1L << CHAR) | (1L << OP_UNAIRE_NOT) | (1L << OP_LESS) | (1L << ID))) != 0)) {
					{
					setState(173);
					expr_list();
					}
				}

				setState(176);
				match(T__1);
				}
				break;
			case 5:
				{
				_localctx = new Opp_or_notContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(177);
				_la = _input.LA(1);
				if ( !(_la==OP_UNAIRE_NOT || _la==OP_LESS) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(178);
				expr(14);
				}
				break;
			case 6:
				{
				_localctx = new Var_affContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(179);
				match(ID);
				setState(180);
				match(OP_EQUAL);
				setState(181);
				expr(3);
				}
				break;
			case 7:
				{
				_localctx = new Array_affContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(182);
				match(ID);
				setState(183);
				match(OP_EQUAL);
				setState(184);
				match(T__2);
				setState(185);
				expr_list();
				setState(186);
				match(T__3);
				}
				break;
			case 8:
				{
				_localctx = new Array_element_affContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(188);
				match(ID);
				setState(189);
				match(T__6);
				setState(190);
				expr(0);
				setState(191);
				match(T__7);
				setState(192);
				match(OP_EQUAL);
				setState(193);
				expr(1);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(229);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(227);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,17,_ctx) ) {
					case 1:
						{
						_localctx = new Div_or_multContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(197);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(198);
						_la = _input.LA(1);
						if ( !(_la==OP_DIV || _la==OP_MULT) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(199);
						expr(14);
						}
						break;
					case 2:
						{
						_localctx = new Less_or_addContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(200);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(201);
						_la = _input.LA(1);
						if ( !(_la==OP_LESS || _la==OP_ADD) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(202);
						expr(13);
						}
						break;
					case 3:
						{
						_localctx = new Greater_equal_lesser_equalContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(203);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(204);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << OP_GREATER_EQUAL) | (1L << OP_GREATER) | (1L << OP_LESSER_EQUAL) | (1L << OP_LESSER))) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(205);
						expr(12);
						}
						break;
					case 4:
						{
						_localctx = new EqualContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(206);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(207);
						match(OP_DOUBLE_EQUAL);
						setState(208);
						expr(11);
						}
						break;
					case 5:
						{
						_localctx = new NotequalContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(209);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(210);
						match(OP_NOT_EQUAL);
						setState(211);
						expr(10);
						}
						break;
					case 6:
						{
						_localctx = new AndContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(212);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(213);
						match(OP_BITWISE_AND);
						setState(214);
						expr(9);
						}
						break;
					case 7:
						{
						_localctx = new OrContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(215);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(216);
						match(OP_BITWISE_OR);
						setState(217);
						expr(8);
						}
						break;
					case 8:
						{
						_localctx = new XorContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(218);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(219);
						match(OP_BITWISE_XOR);
						setState(220);
						expr(7);
						}
						break;
					case 9:
						{
						_localctx = new CdtandContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(221);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(222);
						match(OP_LOGICAL_AND);
						setState(223);
						expr(6);
						}
						break;
					case 10:
						{
						_localctx = new CdtorContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(224);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(225);
						match(OP_LOGICAL_OR);
						setState(226);
						expr(5);
						}
						break;
					}
					} 
				}
				setState(231);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class Expr_listContext extends ParserRuleContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public Expr_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_list; }
	}

	public final Expr_listContext expr_list() throws RecognitionException {
		Expr_listContext _localctx = new Expr_listContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_expr_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(232);
			expr(0);
			setState(237);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__5) {
				{
				{
				setState(233);
				match(T__5);
				setState(234);
				expr(0);
				}
				}
				setState(239);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 14:
			return expr_sempred((ExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expr_sempred(ExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 13);
		case 1:
			return precpred(_ctx, 12);
		case 2:
			return precpred(_ctx, 11);
		case 3:
			return precpred(_ctx, 10);
		case 4:
			return precpred(_ctx, 9);
		case 5:
			return precpred(_ctx, 8);
		case 6:
			return precpred(_ctx, 7);
		case 7:
			return precpred(_ctx, 6);
		case 8:
			return precpred(_ctx, 5);
		case 9:
			return precpred(_ctx, 4);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\'\u00f3\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\3\2\3\2\3"+
		"\3\6\3&\n\3\r\3\16\3\'\3\4\3\4\3\4\3\4\5\4.\n\4\3\4\3\4\3\4\7\4\63\n\4"+
		"\f\4\16\4\66\13\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\5\5C\n\5"+
		"\3\6\3\6\3\6\7\6H\n\6\f\6\16\6K\13\6\3\7\3\7\3\7\3\b\3\b\3\b\3\b\5\bT"+
		"\n\b\3\b\7\bW\n\b\f\b\16\bZ\13\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3"+
		"\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\5\tr\n\t\3\t\5\tu\n"+
		"\t\3\n\3\n\3\n\3\n\5\n{\n\n\3\13\3\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3"+
		"\f\5\f\u0087\n\f\3\f\5\f\u008a\n\f\3\r\3\r\3\r\3\r\5\r\u0090\n\r\3\16"+
		"\3\16\3\16\3\16\3\16\3\16\5\16\u0098\n\16\3\17\3\17\7\17\u009c\n\17\f"+
		"\17\16\17\u009f\13\17\3\17\3\17\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\5\20\u00b1\n\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\5\20\u00c6\n\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\7\20\u00e6\n\20\f\20\16\20\u00e9\13\20\3\21"+
		"\3\21\3\21\7\21\u00ee\n\21\f\21\16\21\u00f1\13\21\3\21\2\3\36\22\2\4\6"+
		"\b\n\f\16\20\22\24\26\30\32\34\36 \2\7\4\2\20\21##\4\2\22\22\25\25\3\2"+
		"\23\24\3\2\25\26\3\2\35 \2\u010a\2\"\3\2\2\2\4%\3\2\2\2\6)\3\2\2\2\bB"+
		"\3\2\2\2\nD\3\2\2\2\fL\3\2\2\2\16O\3\2\2\2\20t\3\2\2\2\22v\3\2\2\2\24"+
		"|\3\2\2\2\26\u0080\3\2\2\2\30\u008b\3\2\2\2\32\u0091\3\2\2\2\34\u0099"+
		"\3\2\2\2\36\u00c5\3\2\2\2 \u00ea\3\2\2\2\"#\5\4\3\2#\3\3\2\2\2$&\5\6\4"+
		"\2%$\3\2\2\2&\'\3\2\2\2\'%\3\2\2\2\'(\3\2\2\2(\5\3\2\2\2)*\7\17\2\2*+"+
		"\7#\2\2+-\7\3\2\2,.\5\n\6\2-,\3\2\2\2-.\3\2\2\2./\3\2\2\2/\60\7\4\2\2"+
		"\60\64\7\5\2\2\61\63\5\b\5\2\62\61\3\2\2\2\63\66\3\2\2\2\64\62\3\2\2\2"+
		"\64\65\3\2\2\2\65\67\3\2\2\2\66\64\3\2\2\2\678\7\6\2\28\7\3\2\2\29C\5"+
		"\16\b\2:C\5\20\t\2;<\5\36\20\2<=\7\7\2\2=C\3\2\2\2>C\5\24\13\2?C\5\26"+
		"\f\2@C\5\32\16\2AC\5\34\17\2B9\3\2\2\2B:\3\2\2\2B;\3\2\2\2B>\3\2\2\2B"+
		"?\3\2\2\2B@\3\2\2\2BA\3\2\2\2C\t\3\2\2\2DI\5\f\7\2EF\7\b\2\2FH\5\f\7\2"+
		"GE\3\2\2\2HK\3\2\2\2IG\3\2\2\2IJ\3\2\2\2J\13\3\2\2\2KI\3\2\2\2LM\7\17"+
		"\2\2MN\7#\2\2N\r\3\2\2\2OP\7\17\2\2PS\7#\2\2QR\7\32\2\2RT\5\36\20\2SQ"+
		"\3\2\2\2ST\3\2\2\2TX\3\2\2\2UW\5\22\n\2VU\3\2\2\2WZ\3\2\2\2XV\3\2\2\2"+
		"XY\3\2\2\2Y[\3\2\2\2ZX\3\2\2\2[\\\7\7\2\2\\\17\3\2\2\2]^\7\17\2\2^_\7"+
		"#\2\2_`\7\t\2\2`a\7\n\2\2ab\7\32\2\2bc\7\5\2\2cd\5 \21\2de\7\6\2\2ef\7"+
		"\7\2\2fu\3\2\2\2gh\7\17\2\2hi\7#\2\2ij\7\t\2\2jk\7\20\2\2kq\7\n\2\2lm"+
		"\7\32\2\2mn\7\5\2\2no\5 \21\2op\7\6\2\2pr\3\2\2\2ql\3\2\2\2qr\3\2\2\2"+
		"rs\3\2\2\2su\7\7\2\2t]\3\2\2\2tg\3\2\2\2u\21\3\2\2\2vw\7\b\2\2wz\7#\2"+
		"\2xy\7\32\2\2y{\5\36\20\2zx\3\2\2\2z{\3\2\2\2{\23\3\2\2\2|}\7\13\2\2}"+
		"~\5\36\20\2~\177\7\7\2\2\177\25\3\2\2\2\u0080\u0081\7\f\2\2\u0081\u0082"+
		"\7\3\2\2\u0082\u0083\5\36\20\2\u0083\u0086\7\4\2\2\u0084\u0087\5\b\5\2"+
		"\u0085\u0087\5\34\17\2\u0086\u0084\3\2\2\2\u0086\u0085\3\2\2\2\u0087\u0089"+
		"\3\2\2\2\u0088\u008a\5\30\r\2\u0089\u0088\3\2\2\2\u0089\u008a\3\2\2\2"+
		"\u008a\27\3\2\2\2\u008b\u008f\7\r\2\2\u008c\u0090\5\b\5\2\u008d\u0090"+
		"\5\34\17\2\u008e\u0090\5\26\f\2\u008f\u008c\3\2\2\2\u008f\u008d\3\2\2"+
		"\2\u008f\u008e\3\2\2\2\u0090\31\3\2\2\2\u0091\u0092\7\16\2\2\u0092\u0093"+
		"\7\3\2\2\u0093\u0094\5\36\20\2\u0094\u0097\7\4\2\2\u0095\u0098\5\b\5\2"+
		"\u0096\u0098\5\34\17\2\u0097\u0095\3\2\2\2\u0097\u0096\3\2\2\2\u0098\33"+
		"\3\2\2\2\u0099\u009d\7\5\2\2\u009a\u009c\5\b\5\2\u009b\u009a\3\2\2\2\u009c"+
		"\u009f\3\2\2\2\u009d\u009b\3\2\2\2\u009d\u009e\3\2\2\2\u009e\u00a0\3\2"+
		"\2\2\u009f\u009d\3\2\2\2\u00a0\u00a1\7\6\2\2\u00a1\35\3\2\2\2\u00a2\u00a3"+
		"\b\20\1\2\u00a3\u00a4\7#\2\2\u00a4\u00a5\7\t\2\2\u00a5\u00a6\5\36\20\2"+
		"\u00a6\u00a7\7\n\2\2\u00a7\u00c6\3\2\2\2\u00a8\u00c6\t\2\2\2\u00a9\u00aa"+
		"\7\3\2\2\u00aa\u00ab\5\36\20\2\u00ab\u00ac\7\4\2\2\u00ac\u00c6\3\2\2\2"+
		"\u00ad\u00ae\7#\2\2\u00ae\u00b0\7\3\2\2\u00af\u00b1\5 \21\2\u00b0\u00af"+
		"\3\2\2\2\u00b0\u00b1\3\2\2\2\u00b1\u00b2\3\2\2\2\u00b2\u00c6\7\4\2\2\u00b3"+
		"\u00b4\t\3\2\2\u00b4\u00c6\5\36\20\20\u00b5\u00b6\7#\2\2\u00b6\u00b7\7"+
		"\32\2\2\u00b7\u00c6\5\36\20\5\u00b8\u00b9\7#\2\2\u00b9\u00ba\7\32\2\2"+
		"\u00ba\u00bb\7\5\2\2\u00bb\u00bc\5 \21\2\u00bc\u00bd\7\6\2\2\u00bd\u00c6"+
		"\3\2\2\2\u00be\u00bf\7#\2\2\u00bf\u00c0\7\t\2\2\u00c0\u00c1\5\36\20\2"+
		"\u00c1\u00c2\7\n\2\2\u00c2\u00c3\7\32\2\2\u00c3\u00c4\5\36\20\3\u00c4"+
		"\u00c6\3\2\2\2\u00c5\u00a2\3\2\2\2\u00c5\u00a8\3\2\2\2\u00c5\u00a9\3\2"+
		"\2\2\u00c5\u00ad\3\2\2\2\u00c5\u00b3\3\2\2\2\u00c5\u00b5\3\2\2\2\u00c5"+
		"\u00b8\3\2\2\2\u00c5\u00be\3\2\2\2\u00c6\u00e7\3\2\2\2\u00c7\u00c8\f\17"+
		"\2\2\u00c8\u00c9\t\4\2\2\u00c9\u00e6\5\36\20\20\u00ca\u00cb\f\16\2\2\u00cb"+
		"\u00cc\t\5\2\2\u00cc\u00e6\5\36\20\17\u00cd\u00ce\f\r\2\2\u00ce\u00cf"+
		"\t\6\2\2\u00cf\u00e6\5\36\20\16\u00d0\u00d1\f\f\2\2\u00d1\u00d2\7\33\2"+
		"\2\u00d2\u00e6\5\36\20\r\u00d3\u00d4\f\13\2\2\u00d4\u00d5\7\34\2\2\u00d5"+
		"\u00e6\5\36\20\f\u00d6\u00d7\f\n\2\2\u00d7\u00d8\7\27\2\2\u00d8\u00e6"+
		"\5\36\20\13\u00d9\u00da\f\t\2\2\u00da\u00db\7\30\2\2\u00db\u00e6\5\36"+
		"\20\n\u00dc\u00dd\f\b\2\2\u00dd\u00de\7\31\2\2\u00de\u00e6\5\36\20\t\u00df"+
		"\u00e0\f\7\2\2\u00e0\u00e1\7!\2\2\u00e1\u00e6\5\36\20\b\u00e2\u00e3\f"+
		"\6\2\2\u00e3\u00e4\7\"\2\2\u00e4\u00e6\5\36\20\7\u00e5\u00c7\3\2\2\2\u00e5"+
		"\u00ca\3\2\2\2\u00e5\u00cd\3\2\2\2\u00e5\u00d0\3\2\2\2\u00e5\u00d3\3\2"+
		"\2\2\u00e5\u00d6\3\2\2\2\u00e5\u00d9\3\2\2\2\u00e5\u00dc\3\2\2\2\u00e5"+
		"\u00df\3\2\2\2\u00e5\u00e2\3\2\2\2\u00e6\u00e9\3\2\2\2\u00e7\u00e5\3\2"+
		"\2\2\u00e7\u00e8\3\2\2\2\u00e8\37\3\2\2\2\u00e9\u00e7\3\2\2\2\u00ea\u00ef"+
		"\5\36\20\2\u00eb\u00ec\7\b\2\2\u00ec\u00ee\5\36\20\2\u00ed\u00eb\3\2\2"+
		"\2\u00ee\u00f1\3\2\2\2\u00ef\u00ed\3\2\2\2\u00ef\u00f0\3\2\2\2\u00f0!"+
		"\3\2\2\2\u00f1\u00ef\3\2\2\2\26\'-\64BISXqtz\u0086\u0089\u008f\u0097\u009d"+
		"\u00b0\u00c5\u00e5\u00e7\u00ef";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}