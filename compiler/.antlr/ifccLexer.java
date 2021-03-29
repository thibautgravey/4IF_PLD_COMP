// Generated from /Users/louisrob/Documents/Ecole/4IF/4IF_PLD_COMP/compiler/ifcc.g4 by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, TYPE=14, CONST=15, OP_DIV=16, OP_MULT=17, 
		OP_LESS=18, OP_ADD=19, VAR_NAME=20, COMMENT=21, DIRECTIVE=22, WS=23;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "TYPE", "CONST", "OP_DIV", "OP_MULT", 
			"OP_LESS", "OP_ADD", "VAR_NAME", "COMMENT", "DIRECTIVE", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'main'", "'('", "')'", "'{'", "'}'", "'='", "';'", "','", "'return'", 
			"'&'", "'|'", "'^'", "'!'", null, null, "'/'", "'*'", "'-'", "'+'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, "TYPE", "CONST", "OP_DIV", "OP_MULT", "OP_LESS", "OP_ADD", 
			"VAR_NAME", "COMMENT", "DIRECTIVE", "WS"
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


	public ifccLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\31\u0094\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\3\2"+
		"\3\2\3\2\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3"+
		"\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\f\3\f\3\r\3\r\3\16\3\16\3\17"+
		"\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\3\17\5\17"+
		"b\n\17\3\20\6\20e\n\20\r\20\16\20f\3\21\3\21\3\22\3\22\3\23\3\23\3\24"+
		"\3\24\3\25\3\25\7\25s\n\25\f\25\16\25v\13\25\3\26\3\26\3\26\3\26\7\26"+
		"|\n\26\f\26\16\26\177\13\26\3\26\3\26\3\26\3\26\3\26\3\27\3\27\7\27\u0088"+
		"\n\27\f\27\16\27\u008b\13\27\3\27\3\27\3\27\3\27\3\30\3\30\3\30\3\30\4"+
		"}\u0089\2\31\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16"+
		"\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\3\2\6\3\2\62;\5\2"+
		"C\\aac|\4\2^^yy\5\2\13\f\17\17\"\"\2\u0098\2\3\3\2\2\2\2\5\3\2\2\2\2\7"+
		"\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2"+
		"\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2"+
		"\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2"+
		"\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\3\61\3\2\2\2\5\66\3\2\2\2"+
		"\78\3\2\2\2\t:\3\2\2\2\13<\3\2\2\2\r>\3\2\2\2\17@\3\2\2\2\21B\3\2\2\2"+
		"\23D\3\2\2\2\25K\3\2\2\2\27M\3\2\2\2\31O\3\2\2\2\33Q\3\2\2\2\35a\3\2\2"+
		"\2\37d\3\2\2\2!h\3\2\2\2#j\3\2\2\2%l\3\2\2\2\'n\3\2\2\2)p\3\2\2\2+w\3"+
		"\2\2\2-\u0085\3\2\2\2/\u0090\3\2\2\2\61\62\7o\2\2\62\63\7c\2\2\63\64\7"+
		"k\2\2\64\65\7p\2\2\65\4\3\2\2\2\66\67\7*\2\2\67\6\3\2\2\289\7+\2\29\b"+
		"\3\2\2\2:;\7}\2\2;\n\3\2\2\2<=\7\177\2\2=\f\3\2\2\2>?\7?\2\2?\16\3\2\2"+
		"\2@A\7=\2\2A\20\3\2\2\2BC\7.\2\2C\22\3\2\2\2DE\7t\2\2EF\7g\2\2FG\7v\2"+
		"\2GH\7w\2\2HI\7t\2\2IJ\7p\2\2J\24\3\2\2\2KL\7(\2\2L\26\3\2\2\2MN\7~\2"+
		"\2N\30\3\2\2\2OP\7`\2\2P\32\3\2\2\2QR\7#\2\2R\34\3\2\2\2ST\7k\2\2TU\7"+
		"p\2\2UV\7v\2\2VW\7\65\2\2WX\7\64\2\2XY\7a\2\2Yb\7v\2\2Z[\7k\2\2[\\\7p"+
		"\2\2\\]\7v\2\2]^\78\2\2^_\7\66\2\2_`\7a\2\2`b\7v\2\2aS\3\2\2\2aZ\3\2\2"+
		"\2b\36\3\2\2\2ce\t\2\2\2dc\3\2\2\2ef\3\2\2\2fd\3\2\2\2fg\3\2\2\2g \3\2"+
		"\2\2hi\7\61\2\2i\"\3\2\2\2jk\7,\2\2k$\3\2\2\2lm\7/\2\2m&\3\2\2\2no\7-"+
		"\2\2o(\3\2\2\2pt\t\3\2\2qs\t\4\2\2rq\3\2\2\2sv\3\2\2\2tr\3\2\2\2tu\3\2"+
		"\2\2u*\3\2\2\2vt\3\2\2\2wx\7\61\2\2xy\7,\2\2y}\3\2\2\2z|\13\2\2\2{z\3"+
		"\2\2\2|\177\3\2\2\2}~\3\2\2\2}{\3\2\2\2~\u0080\3\2\2\2\177}\3\2\2\2\u0080"+
		"\u0081\7,\2\2\u0081\u0082\7\61\2\2\u0082\u0083\3\2\2\2\u0083\u0084\b\26"+
		"\2\2\u0084,\3\2\2\2\u0085\u0089\7%\2\2\u0086\u0088\13\2\2\2\u0087\u0086"+
		"\3\2\2\2\u0088\u008b\3\2\2\2\u0089\u008a\3\2\2\2\u0089\u0087\3\2\2\2\u008a"+
		"\u008c\3\2\2\2\u008b\u0089\3\2\2\2\u008c\u008d\7\f\2\2\u008d\u008e\3\2"+
		"\2\2\u008e\u008f\b\27\2\2\u008f.\3\2\2\2\u0090\u0091\t\5\2\2\u0091\u0092"+
		"\3\2\2\2\u0092\u0093\b\30\3\2\u0093\60\3\2\2\2\b\2aft}\u0089\4\b\2\2\2"+
		"\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}