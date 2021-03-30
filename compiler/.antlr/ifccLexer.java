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
		T__9=10, T__10=11, TYPE=12, CONST=13, OP_DIV=14, OP_MULT=15, OP_LESS=16, 
		OP_ADD=17, OP_UNAIRE_NOT=18, ID=19, COMMENT=20, DIRECTIVE=21, WS=22;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "TYPE", "CONST", "OP_DIV", "OP_MULT", "OP_LESS", "OP_ADD", 
			"OP_UNAIRE_NOT", "ID", "COMMENT", "DIRECTIVE", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "'{'", "'}'", "','", "';'", "'='", "'return'", "'&'", 
			"'|'", "'^'", null, null, "'/'", "'*'", "'-'", "'+'", "'!'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			"TYPE", "CONST", "OP_DIV", "OP_MULT", "OP_LESS", "OP_ADD", "OP_UNAIRE_NOT", 
			"ID", "COMMENT", "DIRECTIVE", "WS"
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\30\u0086\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\3\2\3\2\3\3\3"+
		"\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t"+
		"\3\n\3\n\3\13\3\13\3\f\3\f\3\r\3\r\3\r\3\r\3\r\3\r\3\r\5\rR\n\r\3\16\6"+
		"\16U\n\16\r\16\16\16V\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23"+
		"\3\24\3\24\7\24e\n\24\f\24\16\24h\13\24\3\25\3\25\3\25\3\25\7\25n\n\25"+
		"\f\25\16\25q\13\25\3\25\3\25\3\25\3\25\3\25\3\26\3\26\7\26z\n\26\f\26"+
		"\16\26}\13\26\3\26\3\26\3\26\3\26\3\27\3\27\3\27\3\27\4o{\2\30\3\3\5\4"+
		"\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22"+
		"#\23%\24\'\25)\26+\27-\30\3\2\6\3\2\62;\5\2C\\aac|\6\2\62;C\\aac|\5\2"+
		"\13\f\17\17\"\"\2\u008a\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2"+
		"\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25"+
		"\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2"+
		"\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2"+
		"\2\2-\3\2\2\2\3/\3\2\2\2\5\61\3\2\2\2\7\63\3\2\2\2\t\65\3\2\2\2\13\67"+
		"\3\2\2\2\r9\3\2\2\2\17;\3\2\2\2\21=\3\2\2\2\23D\3\2\2\2\25F\3\2\2\2\27"+
		"H\3\2\2\2\31Q\3\2\2\2\33T\3\2\2\2\35X\3\2\2\2\37Z\3\2\2\2!\\\3\2\2\2#"+
		"^\3\2\2\2%`\3\2\2\2\'b\3\2\2\2)i\3\2\2\2+w\3\2\2\2-\u0082\3\2\2\2/\60"+
		"\7*\2\2\60\4\3\2\2\2\61\62\7+\2\2\62\6\3\2\2\2\63\64\7}\2\2\64\b\3\2\2"+
		"\2\65\66\7\177\2\2\66\n\3\2\2\2\678\7.\2\28\f\3\2\2\29:\7=\2\2:\16\3\2"+
		"\2\2;<\7?\2\2<\20\3\2\2\2=>\7t\2\2>?\7g\2\2?@\7v\2\2@A\7w\2\2AB\7t\2\2"+
		"BC\7p\2\2C\22\3\2\2\2DE\7(\2\2E\24\3\2\2\2FG\7~\2\2G\26\3\2\2\2HI\7`\2"+
		"\2I\30\3\2\2\2JK\7k\2\2KL\7p\2\2LR\7v\2\2MN\7x\2\2NO\7q\2\2OP\7k\2\2P"+
		"R\7f\2\2QJ\3\2\2\2QM\3\2\2\2R\32\3\2\2\2SU\t\2\2\2TS\3\2\2\2UV\3\2\2\2"+
		"VT\3\2\2\2VW\3\2\2\2W\34\3\2\2\2XY\7\61\2\2Y\36\3\2\2\2Z[\7,\2\2[ \3\2"+
		"\2\2\\]\7/\2\2]\"\3\2\2\2^_\7-\2\2_$\3\2\2\2`a\7#\2\2a&\3\2\2\2bf\t\3"+
		"\2\2ce\t\4\2\2dc\3\2\2\2eh\3\2\2\2fd\3\2\2\2fg\3\2\2\2g(\3\2\2\2hf\3\2"+
		"\2\2ij\7\61\2\2jk\7,\2\2ko\3\2\2\2ln\13\2\2\2ml\3\2\2\2nq\3\2\2\2op\3"+
		"\2\2\2om\3\2\2\2pr\3\2\2\2qo\3\2\2\2rs\7,\2\2st\7\61\2\2tu\3\2\2\2uv\b"+
		"\25\2\2v*\3\2\2\2w{\7%\2\2xz\13\2\2\2yx\3\2\2\2z}\3\2\2\2{|\3\2\2\2{y"+
		"\3\2\2\2|~\3\2\2\2}{\3\2\2\2~\177\7\f\2\2\177\u0080\3\2\2\2\u0080\u0081"+
		"\b\26\2\2\u0081,\3\2\2\2\u0082\u0083\t\5\2\2\u0083\u0084\3\2\2\2\u0084"+
		"\u0085\b\27\3\2\u0085.\3\2\2\2\b\2QVfo{\4\b\2\2\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}