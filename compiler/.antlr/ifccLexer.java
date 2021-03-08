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
		T__9=10, T__10=11, T__11=12, TYPE=13, CONST=14, VAR_NAME=15, COMMENT=16, 
		DIRECTIVE=17, WS=18;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "TYPE", "CONST", "VAR_NAME", "COMMENT", "DIRECTIVE", 
			"WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'main'", "'('", "')'", "'{'", "'}'", "';'", "'return'", "'='", 
			"'+'", "'-'", "'*'", "'/'", "'int'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, "TYPE", "CONST", "VAR_NAME", "COMMENT", "DIRECTIVE", "WS"
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\24w\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7"+
		"\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\f\3\f\3\r\3\r"+
		"\3\16\3\16\3\16\3\16\3\17\5\17M\n\17\3\17\6\17P\n\17\r\17\16\17Q\3\20"+
		"\3\20\7\20V\n\20\f\20\16\20Y\13\20\3\21\3\21\3\21\3\21\7\21_\n\21\f\21"+
		"\16\21b\13\21\3\21\3\21\3\21\3\21\3\21\3\22\3\22\7\22k\n\22\f\22\16\22"+
		"n\13\22\3\22\3\22\3\22\3\22\3\23\3\23\3\23\3\23\4`l\2\24\3\3\5\4\7\5\t"+
		"\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23"+
		"%\24\3\2\6\3\2\62;\5\2C\\aac|\4\2^^yy\5\2\13\f\17\17\"\"\2{\2\3\3\2\2"+
		"\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3"+
		"\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2"+
		"\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2"+
		"\2\2\3\'\3\2\2\2\5,\3\2\2\2\7.\3\2\2\2\t\60\3\2\2\2\13\62\3\2\2\2\r\64"+
		"\3\2\2\2\17\66\3\2\2\2\21=\3\2\2\2\23?\3\2\2\2\25A\3\2\2\2\27C\3\2\2\2"+
		"\31E\3\2\2\2\33G\3\2\2\2\35L\3\2\2\2\37S\3\2\2\2!Z\3\2\2\2#h\3\2\2\2%"+
		"s\3\2\2\2\'(\7o\2\2()\7c\2\2)*\7k\2\2*+\7p\2\2+\4\3\2\2\2,-\7*\2\2-\6"+
		"\3\2\2\2./\7+\2\2/\b\3\2\2\2\60\61\7}\2\2\61\n\3\2\2\2\62\63\7\177\2\2"+
		"\63\f\3\2\2\2\64\65\7=\2\2\65\16\3\2\2\2\66\67\7t\2\2\678\7g\2\289\7v"+
		"\2\29:\7w\2\2:;\7t\2\2;<\7p\2\2<\20\3\2\2\2=>\7?\2\2>\22\3\2\2\2?@\7-"+
		"\2\2@\24\3\2\2\2AB\7/\2\2B\26\3\2\2\2CD\7,\2\2D\30\3\2\2\2EF\7\61\2\2"+
		"F\32\3\2\2\2GH\7k\2\2HI\7p\2\2IJ\7v\2\2J\34\3\2\2\2KM\7/\2\2LK\3\2\2\2"+
		"LM\3\2\2\2MO\3\2\2\2NP\t\2\2\2ON\3\2\2\2PQ\3\2\2\2QO\3\2\2\2QR\3\2\2\2"+
		"R\36\3\2\2\2SW\t\3\2\2TV\t\4\2\2UT\3\2\2\2VY\3\2\2\2WU\3\2\2\2WX\3\2\2"+
		"\2X \3\2\2\2YW\3\2\2\2Z[\7\61\2\2[\\\7,\2\2\\`\3\2\2\2]_\13\2\2\2^]\3"+
		"\2\2\2_b\3\2\2\2`a\3\2\2\2`^\3\2\2\2ac\3\2\2\2b`\3\2\2\2cd\7,\2\2de\7"+
		"\61\2\2ef\3\2\2\2fg\b\21\2\2g\"\3\2\2\2hl\7%\2\2ik\13\2\2\2ji\3\2\2\2"+
		"kn\3\2\2\2lm\3\2\2\2lj\3\2\2\2mo\3\2\2\2nl\3\2\2\2op\7\f\2\2pq\3\2\2\2"+
		"qr\b\22\2\2r$\3\2\2\2st\t\5\2\2tu\3\2\2\2uv\b\23\3\2v&\3\2\2\2\b\2LQW"+
		"`l\4\b\2\2\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}