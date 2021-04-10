// Generated from /home/koechslin/INSA/4IF/S2/PLD_Comp/4IF_PLD_COMP/compiler/ifcc.g4 by ANTLR 4.8
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
		T__9=10, T__10=11, TYPE=12, CONST=13, CHAR=14, OP_UNAIRE_NOT=15, OP_DIV=16, 
		OP_MULT=17, OP_LESS=18, OP_ADD=19, OP_BITWISE_AND=20, OP_BITWISE_OR=21, 
		OP_BITWISE_XOR=22, OP_EQUAL=23, OP_DOUBLE_EQUAL=24, OP_NOT_EQUAL=25, OP_GREATER_EQUAL=26, 
		OP_GREATER=27, OP_LESSER_EQUAL=28, OP_LESSER=29, OP_LOGICAL_AND=30, OP_LOGICAL_OR=31, 
		BREAK=32, CONTINUE=33, ID=34, SINGLE_COMMENT=35, MULTILINE_COMMENT=36, 
		DIRECTIVE=37, WS=38;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "TYPE", "CONST", "CHAR", "OP_UNAIRE_NOT", "OP_DIV", 
			"OP_MULT", "OP_LESS", "OP_ADD", "OP_BITWISE_AND", "OP_BITWISE_OR", "OP_BITWISE_XOR", 
			"OP_EQUAL", "OP_DOUBLE_EQUAL", "OP_NOT_EQUAL", "OP_GREATER_EQUAL", "OP_GREATER", 
			"OP_LESSER_EQUAL", "OP_LESSER", "OP_LOGICAL_AND", "OP_LOGICAL_OR", "BREAK", 
			"CONTINUE", "ID", "SINGLE_COMMENT", "MULTILINE_COMMENT", "DIRECTIVE", 
			"WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "'{'", "'}'", "';'", "','", "'return'", "'if'", "'else'", 
			"'while'", "'for'", null, null, null, "'!'", "'/'", "'*'", "'-'", "'+'", 
			"'&'", "'|'", "'^'", "'='", "'=='", "'!='", "'>='", "'>'", "'<='", "'<'", 
			"'&&'", "'||'", "'break'", "'continue'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			"TYPE", "CONST", "CHAR", "OP_UNAIRE_NOT", "OP_DIV", "OP_MULT", "OP_LESS", 
			"OP_ADD", "OP_BITWISE_AND", "OP_BITWISE_OR", "OP_BITWISE_XOR", "OP_EQUAL", 
			"OP_DOUBLE_EQUAL", "OP_NOT_EQUAL", "OP_GREATER_EQUAL", "OP_GREATER", 
			"OP_LESSER_EQUAL", "OP_LESSER", "OP_LOGICAL_AND", "OP_LOGICAL_OR", "BREAK", 
			"CONTINUE", "ID", "SINGLE_COMMENT", "MULTILINE_COMMENT", "DIRECTIVE", 
			"WS"
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2(\u0100\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\3\2\3\2\3\3\3\3\3\4\3\4\3"+
		"\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\n\3\n"+
		"\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3\f\3\f\3\f\3\f\3\r\3\r\3\r"+
		"\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3"+
		"\r\3\r\5\r\u008b\n\r\3\16\5\16\u008e\n\16\3\16\6\16\u0091\n\16\r\16\16"+
		"\16\u0092\3\17\3\17\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23"+
		"\3\24\3\24\3\25\3\25\3\26\3\26\3\27\3\27\3\30\3\30\3\31\3\31\3\31\3\32"+
		"\3\32\3\32\3\33\3\33\3\33\3\34\3\34\3\35\3\35\3\35\3\36\3\36\3\37\3\37"+
		"\3\37\3 \3 \3 \3!\3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3"+
		"#\3#\7#\u00d2\n#\f#\16#\u00d5\13#\3$\3$\3$\3$\7$\u00db\n$\f$\16$\u00de"+
		"\13$\3$\3$\3$\3$\3%\3%\3%\3%\7%\u00e8\n%\f%\16%\u00eb\13%\3%\3%\3%\3%"+
		"\3%\3&\3&\7&\u00f4\n&\f&\16&\u00f7\13&\3&\3&\3&\3&\3\'\3\'\3\'\3\'\5\u00dc"+
		"\u00e9\u00f5\2(\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31"+
		"\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65"+
		"\34\67\359\36;\37= ?!A\"C#E$G%I&K\'M(\3\2\6\3\2\62;\5\2C\\aac|\6\2\62"+
		";C\\aac|\5\2\13\f\17\17\"\"\2\u0108\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2"+
		"\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23"+
		"\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2"+
		"\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2"+
		"\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3"+
		"\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2"+
		"\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2"+
		"\3O\3\2\2\2\5Q\3\2\2\2\7S\3\2\2\2\tU\3\2\2\2\13W\3\2\2\2\rY\3\2\2\2\17"+
		"[\3\2\2\2\21b\3\2\2\2\23e\3\2\2\2\25j\3\2\2\2\27p\3\2\2\2\31\u008a\3\2"+
		"\2\2\33\u008d\3\2\2\2\35\u0094\3\2\2\2\37\u0098\3\2\2\2!\u009a\3\2\2\2"+
		"#\u009c\3\2\2\2%\u009e\3\2\2\2\'\u00a0\3\2\2\2)\u00a2\3\2\2\2+\u00a4\3"+
		"\2\2\2-\u00a6\3\2\2\2/\u00a8\3\2\2\2\61\u00aa\3\2\2\2\63\u00ad\3\2\2\2"+
		"\65\u00b0\3\2\2\2\67\u00b3\3\2\2\29\u00b5\3\2\2\2;\u00b8\3\2\2\2=\u00ba"+
		"\3\2\2\2?\u00bd\3\2\2\2A\u00c0\3\2\2\2C\u00c6\3\2\2\2E\u00cf\3\2\2\2G"+
		"\u00d6\3\2\2\2I\u00e3\3\2\2\2K\u00f1\3\2\2\2M\u00fc\3\2\2\2OP\7*\2\2P"+
		"\4\3\2\2\2QR\7+\2\2R\6\3\2\2\2ST\7}\2\2T\b\3\2\2\2UV\7\177\2\2V\n\3\2"+
		"\2\2WX\7=\2\2X\f\3\2\2\2YZ\7.\2\2Z\16\3\2\2\2[\\\7t\2\2\\]\7g\2\2]^\7"+
		"v\2\2^_\7w\2\2_`\7t\2\2`a\7p\2\2a\20\3\2\2\2bc\7k\2\2cd\7h\2\2d\22\3\2"+
		"\2\2ef\7g\2\2fg\7n\2\2gh\7u\2\2hi\7g\2\2i\24\3\2\2\2jk\7y\2\2kl\7j\2\2"+
		"lm\7k\2\2mn\7n\2\2no\7g\2\2o\26\3\2\2\2pq\7h\2\2qr\7q\2\2rs\7t\2\2s\30"+
		"\3\2\2\2tu\7k\2\2uv\7p\2\2vw\7v\2\2wx\7\65\2\2xy\7\64\2\2yz\7a\2\2z\u008b"+
		"\7v\2\2{|\7k\2\2|}\7p\2\2}~\7v\2\2~\177\78\2\2\177\u0080\7\66\2\2\u0080"+
		"\u0081\7a\2\2\u0081\u008b\7v\2\2\u0082\u0083\7e\2\2\u0083\u0084\7j\2\2"+
		"\u0084\u0085\7c\2\2\u0085\u008b\7t\2\2\u0086\u0087\7x\2\2\u0087\u0088"+
		"\7q\2\2\u0088\u0089\7k\2\2\u0089\u008b\7f\2\2\u008at\3\2\2\2\u008a{\3"+
		"\2\2\2\u008a\u0082\3\2\2\2\u008a\u0086\3\2\2\2\u008b\32\3\2\2\2\u008c"+
		"\u008e\7/\2\2\u008d\u008c\3\2\2\2\u008d\u008e\3\2\2\2\u008e\u0090\3\2"+
		"\2\2\u008f\u0091\t\2\2\2\u0090\u008f\3\2\2\2\u0091\u0092\3\2\2\2\u0092"+
		"\u0090\3\2\2\2\u0092\u0093\3\2\2\2\u0093\34\3\2\2\2\u0094\u0095\7)\2\2"+
		"\u0095\u0096\13\2\2\2\u0096\u0097\7)\2\2\u0097\36\3\2\2\2\u0098\u0099"+
		"\7#\2\2\u0099 \3\2\2\2\u009a\u009b\7\61\2\2\u009b\"\3\2\2\2\u009c\u009d"+
		"\7,\2\2\u009d$\3\2\2\2\u009e\u009f\7/\2\2\u009f&\3\2\2\2\u00a0\u00a1\7"+
		"-\2\2\u00a1(\3\2\2\2\u00a2\u00a3\7(\2\2\u00a3*\3\2\2\2\u00a4\u00a5\7~"+
		"\2\2\u00a5,\3\2\2\2\u00a6\u00a7\7`\2\2\u00a7.\3\2\2\2\u00a8\u00a9\7?\2"+
		"\2\u00a9\60\3\2\2\2\u00aa\u00ab\7?\2\2\u00ab\u00ac\7?\2\2\u00ac\62\3\2"+
		"\2\2\u00ad\u00ae\7#\2\2\u00ae\u00af\7?\2\2\u00af\64\3\2\2\2\u00b0\u00b1"+
		"\7@\2\2\u00b1\u00b2\7?\2\2\u00b2\66\3\2\2\2\u00b3\u00b4\7@\2\2\u00b48"+
		"\3\2\2\2\u00b5\u00b6\7>\2\2\u00b6\u00b7\7?\2\2\u00b7:\3\2\2\2\u00b8\u00b9"+
		"\7>\2\2\u00b9<\3\2\2\2\u00ba\u00bb\7(\2\2\u00bb\u00bc\7(\2\2\u00bc>\3"+
		"\2\2\2\u00bd\u00be\7~\2\2\u00be\u00bf\7~\2\2\u00bf@\3\2\2\2\u00c0\u00c1"+
		"\7d\2\2\u00c1\u00c2\7t\2\2\u00c2\u00c3\7g\2\2\u00c3\u00c4\7c\2\2\u00c4"+
		"\u00c5\7m\2\2\u00c5B\3\2\2\2\u00c6\u00c7\7e\2\2\u00c7\u00c8\7q\2\2\u00c8"+
		"\u00c9\7p\2\2\u00c9\u00ca\7v\2\2\u00ca\u00cb\7k\2\2\u00cb\u00cc\7p\2\2"+
		"\u00cc\u00cd\7w\2\2\u00cd\u00ce\7g\2\2\u00ceD\3\2\2\2\u00cf\u00d3\t\3"+
		"\2\2\u00d0\u00d2\t\4\2\2\u00d1\u00d0\3\2\2\2\u00d2\u00d5\3\2\2\2\u00d3"+
		"\u00d1\3\2\2\2\u00d3\u00d4\3\2\2\2\u00d4F\3\2\2\2\u00d5\u00d3\3\2\2\2"+
		"\u00d6\u00d7\7\61\2\2\u00d7\u00d8\7\61\2\2\u00d8\u00dc\3\2\2\2\u00d9\u00db"+
		"\13\2\2\2\u00da\u00d9\3\2\2\2\u00db\u00de\3\2\2\2\u00dc\u00dd\3\2\2\2"+
		"\u00dc\u00da\3\2\2\2\u00dd\u00df\3\2\2\2\u00de\u00dc\3\2\2\2\u00df\u00e0"+
		"\7\f\2\2\u00e0\u00e1\3\2\2\2\u00e1\u00e2\b$\2\2\u00e2H\3\2\2\2\u00e3\u00e4"+
		"\7\61\2\2\u00e4\u00e5\7,\2\2\u00e5\u00e9\3\2\2\2\u00e6\u00e8\13\2\2\2"+
		"\u00e7\u00e6\3\2\2\2\u00e8\u00eb\3\2\2\2\u00e9\u00ea\3\2\2\2\u00e9\u00e7"+
		"\3\2\2\2\u00ea\u00ec\3\2\2\2\u00eb\u00e9\3\2\2\2\u00ec\u00ed\7,\2\2\u00ed"+
		"\u00ee\7\61\2\2\u00ee\u00ef\3\2\2\2\u00ef\u00f0\b%\2\2\u00f0J\3\2\2\2"+
		"\u00f1\u00f5\7%\2\2\u00f2\u00f4\13\2\2\2\u00f3\u00f2\3\2\2\2\u00f4\u00f7"+
		"\3\2\2\2\u00f5\u00f6\3\2\2\2\u00f5\u00f3\3\2\2\2\u00f6\u00f8\3\2\2\2\u00f7"+
		"\u00f5\3\2\2\2\u00f8\u00f9\7\f\2\2\u00f9\u00fa\3\2\2\2\u00fa\u00fb\b&"+
		"\2\2\u00fbL\3\2\2\2\u00fc\u00fd\t\5\2\2\u00fd\u00fe\3\2\2\2\u00fe\u00ff"+
		"\b\'\3\2\u00ffN\3\2\2\2\n\2\u008a\u008d\u0092\u00d3\u00dc\u00e9\u00f5"+
		"\4\b\2\2\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}