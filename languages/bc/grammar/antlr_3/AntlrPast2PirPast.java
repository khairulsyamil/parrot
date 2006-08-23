// $ANTLR 3.0b3 grammar/antlr_3/antlr_past2pir_past.g 2006-08-23 23:51:00

  import java.util.regex.*;


import org.antlr.runtime.*;
import org.antlr.runtime.tree.*;import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

public class AntlrPast2PirPast extends TreeParser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "ARRAY", "FUNCTION", "PRINT", "PROGRAM", "STMTS", "VAR", "NEWLINE", "STRING", "LETTER", "INTEGER", "NUMBER", "MINUS", "PLUS", "MUL_OP", "ASSIGN_OP", "REL_OP", "INCR", "DECR", "Define", "Break", "Quit", "Length", "Return", "For", "If", "While", "Sqrt", "Scale", "Ibase", "Obase", "Auto", "ML_COMMENT", "WS", "';'", "'('", "')'", "'{'", "'}'", "'['", "']'", "','"
    };
    public static final int MINUS=15;
    public static final int LETTER=12;
    public static final int INCR=20;
    public static final int ARRAY=4;
    public static final int If=28;
    public static final int WS=36;
    public static final int DECR=21;
    public static final int NUMBER=14;
    public static final int Break=23;
    public static final int Sqrt=30;
    public static final int STRING=11;
    public static final int Ibase=32;
    public static final int Scale=31;
    public static final int MUL_OP=17;
    public static final int Auto=34;
    public static final int Define=22;
    public static final int Quit=24;
    public static final int STMTS=8;
    public static final int PROGRAM=7;
    public static final int NEWLINE=10;
    public static final int VAR=9;
    public static final int ASSIGN_OP=18;
    public static final int INTEGER=13;
    public static final int PRINT=6;
    public static final int FUNCTION=5;
    public static final int Obase=33;
    public static final int While=29;
    public static final int EOF=-1;
    public static final int REL_OP=19;
    public static final int PLUS=16;
    public static final int ML_COMMENT=35;
    public static final int Length=25;
    public static final int For=27;
    public static final int Return=26;

        public AntlrPast2PirPast(TreeNodeStream input) {
            super(input);
        }
        

    public String[] getTokenNames() { return tokenNames; }
    public String getGrammarFileName() { return "grammar/antlr_3/antlr_past2pir_past.g"; }


      // used for generating unique register names
      public static int reg_num = 100;



    // $ANTLR start gen_pir_past
    // grammar/antlr_3/antlr_past2pir_past.g:27:1: gen_pir_past : ^( PROGRAM ( node["stmts"] )* ) ;
    public void gen_pir_past() throws RecognitionException {   
        try {
            // grammar/antlr_3/antlr_past2pir_past.g:28:5: ( ^( PROGRAM ( node[\"stmts\"] )* ) )
            // grammar/antlr_3/antlr_past2pir_past.g:28:5: ^( PROGRAM ( node[\"stmts\"] )* )
            {

                  System.out.println( 
                      "#!/usr/bin/env parrot                                             \n"
                    + "                                                                  \n"
                    + "# Do not edit this file.                                          \n"
                    + "# This file has been generated by Bc.java.                        \n"
                    + "                                                                  \n"
                    + "# entering 'gen_pir_past'                                         \n"
                    + ".sub bc :main                                                     \n"
                    + "  load_bytecode 'languages/punie/lib/ASTGrammar.pir'              \n"
                    + "  load_bytecode 'languages/punie/lib/PunieOpLookup.pir'           \n"              
                    + "  load_bytecode 'TGE.pbc'                                         \n"
                    + "  load_bytecode 'PAST.pbc'                                        \n"
                    + "  load_bytecode 'languages/punie/lib/POST.pir'                    \n"
                    + "  load_bytecode 'languages/punie/lib/OSTGrammar.pir'              \n"
                    + "                                                                  \n"
                    + "  # initialize the 26 up named vars                               \n"
                    + "  .sym pmc stmts                                                  \n"
                    + "  stmts = new 'PAST::Stmts'                                       \n"
                    + "                                                                  \n"
                    + "  .sym pmc reg_temp                                               \n"
                    + "                                                                  \n"
                    + "  .sym pmc reg_expression_stmt                                    \n"
                    + "  .sym pmc reg_expression_topexp                                  \n"
                    + "  .sym pmc reg_print_op                                           \n"
                    + "  .sym pmc reg_if_op                                              \n"
                    + "  .sym pmc reg_expression_exp                                     \n"
                    + "                                                                  \n"
                    + "  .sym pmc reg_assign_lhs                                         \n"
                  );
                
            match(input,PROGRAM,FOLLOW_PROGRAM_in_gen_pir_past73); 

            if ( input.LA(1)==Token.DOWN ) {
                match(input, Token.DOWN, null); 
                // grammar/antlr_3/antlr_past2pir_past.g:59:15: ( node[\"stmts\"] )*
                loop1:
                do {
                    int alt1=2;
                    int LA1_0 = input.LA(1);
                    if ( ((LA1_0>=FUNCTION && LA1_0<=PRINT)||(LA1_0>=STMTS && LA1_0<=STRING)||(LA1_0>=NUMBER && LA1_0<=REL_OP)||LA1_0==If) ) {
                        alt1=1;
                    }


                    switch (alt1) {
                	case 1 :
                	    // grammar/antlr_3/antlr_past2pir_past.g:59:15: node[\"stmts\"]
                	    {
                	    pushFollow(FOLLOW_node_in_gen_pir_past75);
                	    node("stmts");
                	    _fsp--;


                	    }
                	    break;

                	default :
                	    break loop1;
                    }
                } while (true);


                match(input, Token.UP, null); 
            }

                  System.out.print( 
                      "                                                                  \n"
                    + "  # say 'AST tree dump:'                                          \n"
                    + "  # stmts.dump()                                                  \n"
                    + "                                                                  \n"
                    + "  # Compile the abstract syntax tree                              \n"
                    + "  # down to an opcode syntax tree                                 \n"
                    + "  .sym string ost_tg_src                                          \n"
                    + "  .sym pmc tge_compiler                                           \n"
                    + "  .sym pmc ost_grammar, ost_builder, ost                          \n"
                    + "  tge_compiler = new 'TGE::Compiler'                              \n"
                    + "  ost_tg_src = _slurp_file('languages/punie/lib/OSTGrammar.tg')   \n"
                    + "  ost_grammar = tge_compiler.'compile'(ost_tg_src)                \n"
                    + "  ost_builder = ost_grammar.apply(stmts)                          \n"
                    + "  ost = ost_builder.get('result')                                 \n"
                    + "  unless ost goto ERR_NO_OST                                      \n"
                    + "                                                                  \n"
                    + "  # Compile the OST down to PIR                                   \n"
                    + "  .sym string pir_tg_src                                          \n"
                    + "  .sym pmc pir_grammar, pir_builder, pir                          \n"
                    + "  pir_tg_src = _slurp_file('languages/punie/lib/PIRGrammar.tg')   \n"
                    + "  pir_grammar = tge_compiler.'compile'(pir_tg_src)                \n"
                    + "  pir_builder = pir_grammar.apply(ost)                            \n"
                    + "  pir = pir_builder.get('result')                                 \n"
                    + "  unless pir goto ERR_NO_PIR                                      \n"
                    + "                                                                  \n"
                    + "  # execute                                                       \n"
                    + "  .sym pmc pir_compiler, pir_compiled                             \n"
                    + "  pir_compiler = compreg 'PIR'                                    \n"
                    + "  pir_compiled = pir_compiler( pir )                              \n"
                    + "  pir_compiled()                                                  \n"
                    + "  say ''                                                          \n"
                    + "  goto CLEANUP                                                    \n"
                    + "                                                                  \n"
                    + "  ERR_NO_OST:                                                     \n"
                    + "    say 'Unable to construct OST.'                                \n"
                    + "    goto CLEANUP                                                  \n"
                    + "                                                                  \n"
                    + "  ERR_NO_PIR:                                                     \n"
                    + "    say 'Unable to construct PIR.'                                \n"
                    + "    goto CLEANUP                                                  \n"
                    + "                                                                  \n"
                    + "  CLEANUP:                                                        \n"
                    + ".end                                                              \n"
                    + "                                                                  \n"
                    + ".sub _slurp_file                                                  \n"
                    + "  .param string filename                                          \n"
                    + "                                                                  \n"
                    + "  .sym pmc filehandle                                             \n"
                    + "  .sym string content                                             \n"
                    + "  filehandle = open filename, '<'                                 \n"
                    + "  unless filehandle goto ERR_NO_FILE                              \n"
                    + "  content = read filehandle, 65535                                \n"
                    + "  close filehandle                                                \n"
                    + "                                                                  \n"
                    + "  .return ( content )                                             \n"
                    + "                                                                  \n"
                    + "  ERR_NO_FILE:                                                    \n"
                    + "    print 'Unable to open file: '                                 \n"
                    + "    say filename                                                  \n"
                    + "    end                                                           \n"
                    + "                                                                  \n"
                    + ".end                                                              \n"
                    + "                                                                  \n"
                    + "# leaving 'gen_pir_past'                                          \n"
                  );
                

            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return ;
    }
    // $ANTLR end gen_pir_past


    // $ANTLR start node
    // grammar/antlr_3/antlr_past2pir_past.g:130:1: node[String reg_mother] : ( ^( PRINT node["reg_expression_exp"] ) | ^( FUNCTION LETTER ) | ^( ASSIGN_OP ^( VAR LETTER ) node["reg_assign_lhs"] ) | NUMBER | ^(infix= (PLUS|MINUS|MUL_OP|REL_OP) node[reg] node[reg] ) | ^( VAR LETTER ) | NEWLINE | STRING | ^( If node["reg_if_op"] node["reg_if_op"] ) | ^( STMTS ( node[reg_stmts] )* ) );
    public void node(String reg_mother) throws RecognitionException {   
        CommonTree infix=null;
        CommonTree LETTER1=null;
        CommonTree NUMBER2=null;
        CommonTree LETTER3=null;
        CommonTree STRING4=null;

        try {
            // grammar/antlr_3/antlr_past2pir_past.g:131:5: ( ^( PRINT node[\"reg_expression_exp\"] ) | ^( FUNCTION LETTER ) | ^( ASSIGN_OP ^( VAR LETTER ) node[\"reg_assign_lhs\"] ) | NUMBER | ^(infix= (PLUS|MINUS|MUL_OP|REL_OP) node[reg] node[reg] ) | ^( VAR LETTER ) | NEWLINE | STRING | ^( If node[\"reg_if_op\"] node[\"reg_if_op\"] ) | ^( STMTS ( node[reg_stmts] )* ) )
            int alt3=10;
            switch ( input.LA(1) ) {
            case PRINT:
                alt3=1;
                break;
            case FUNCTION:
                alt3=2;
                break;
            case ASSIGN_OP:
                alt3=3;
                break;
            case NUMBER:
                alt3=4;
                break;
            case MINUS:
            case PLUS:
            case MUL_OP:
            case REL_OP:
                alt3=5;
                break;
            case VAR:
                alt3=6;
                break;
            case NEWLINE:
                alt3=7;
                break;
            case STRING:
                alt3=8;
                break;
            case If:
                alt3=9;
                break;
            case STMTS:
                alt3=10;
                break;
            default:
                NoViableAltException nvae =
                    new NoViableAltException("130:1: node[String reg_mother] : ( ^( PRINT node[\"reg_expression_exp\"] ) | ^( FUNCTION LETTER ) | ^( ASSIGN_OP ^( VAR LETTER ) node[\"reg_assign_lhs\"] ) | NUMBER | ^(infix= (PLUS|MINUS|MUL_OP|REL_OP) node[reg] node[reg] ) | ^( VAR LETTER ) | NEWLINE | STRING | ^( If node[\"reg_if_op\"] node[\"reg_if_op\"] ) | ^( STMTS ( node[reg_stmts] )* ) );", 3, 0, input);

                throw nvae;
            }

            switch (alt3) {
                case 1 :
                    // grammar/antlr_3/antlr_past2pir_past.g:131:5: ^( PRINT node[\"reg_expression_exp\"] )
                    {

                          System.out.print( 
                              "                                                                  \n"
                            + "  # entering 'PRINT node'                                         \n"
                            + "    reg_expression_stmt = new 'PAST::Stmt'                        \n"
                            + "      reg_expression_topexp = new 'PAST::Exp'                     \n"
                            + "        reg_print_op = new 'PAST::Op'                             \n"
                            + "        reg_print_op.'op'( 'print' )                              \n"
                            + "          reg_expression_exp = new 'PAST::Exp'                    \n"
                          );
                        
                    match(input,PRINT,FOLLOW_PRINT_in_node107); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_node_in_node109);
                    node("reg_expression_exp");
                    _fsp--;


                    match(input, Token.UP, null); 
                     
                          System.out.print( 
                              "                                                                   \n"
                            + "      reg_print_op.'add_child'( reg_expression_exp )               \n"
                            + "      reg_expression_topexp.'add_child'( reg_print_op      )       \n"
                            + "    reg_expression_stmt.'add_child'( reg_expression_topexp )       \n"
                            + "  " + reg_mother + ".'add_child'( reg_expression_stmt )      \n"
                            + "  # leaving 'PRINT node'                                           \n"
                          );
                        

                    }
                    break;
                case 2 :
                    // grammar/antlr_3/antlr_past2pir_past.g:154:5: ^( FUNCTION LETTER )
                    {
                    match(input,FUNCTION,FOLLOW_FUNCTION_in_node132); 

                    match(input, Token.DOWN, null); 
                    match(input,LETTER,FOLLOW_LETTER_in_node134); 

                    match(input, Token.UP, null); 

                          // do nothing for now
                        

                    }
                    break;
                case 3 :
                    // grammar/antlr_3/antlr_past2pir_past.g:159:5: ^( ASSIGN_OP ^( VAR LETTER ) node[\"reg_assign_lhs\"] )
                    {

                          System.out.print( 
                              "                                                                   \n"
                            + "  # entering 'assign'                                              \n"
                            + "    reg_assign_lhs = new 'PAST::Exp'                               \n"
                          );
                        
                    match(input,ASSIGN_OP,FOLLOW_ASSIGN_OP_in_node162); 

                    match(input, Token.DOWN, null); 
                    match(input,VAR,FOLLOW_VAR_in_node165); 

                    match(input, Token.DOWN, null); 
                    LETTER1=(CommonTree)input.LT(1);
                    match(input,LETTER,FOLLOW_LETTER_in_node167); 

                    match(input, Token.UP, null); 
                    pushFollow(FOLLOW_node_in_node170);
                    node("reg_assign_lhs");
                    _fsp--;


                    match(input, Token.UP, null); 

                          // TODO: strip String
                          System.out.print(     
                              "                                                                   \n"
                            + "    # entering 'ASSIGN_OP ^(VAR LETTER) node'                      \n"
                            + "      .sym pmc past_op                                             \n"
                            + "      past_op = new 'PAST::Op'                                     \n"
                            + "      past_op.'op'( 'infix:=' )                                    \n"
                            + "        .sym pmc past_var                                          \n"
                            + "        past_var = new 'PAST::Var'                                 \n"
                            + "        past_var.'varname'( '" + LETTER1.getText() + "' )               \n"
                            + "        past_var.'vartype'( 'scalar' )                             \n"
                            + "        past_var.'scope'( 'global' )                               \n"
                            + "      past_op.'add_child'( past_var )                              \n"
                            + "      past_op.'add_child'( reg_assign_lhs )                        \n"
                            + "    " + reg_mother + ".'add_child'( past_op )                \n"
                            + "    # leaving  'ASSIGN_OP named_expression NUMBER'                 \n"
                          );
                        

                    }
                    break;
                case 4 :
                    // grammar/antlr_3/antlr_past2pir_past.g:187:5: NUMBER
                    {
                    NUMBER2=(CommonTree)input.LT(1);
                    match(input,NUMBER,FOLLOW_NUMBER_in_node191); 

                          System.out.print(     
                              "                                                                  \n"
                            + "# entering 'NUMBER'                                               \n"
                            + "reg_temp = new 'PAST::Val'                                        \n"
                            + "reg_temp.value( " + NUMBER2.getText() + " )                            \n"
                            + "reg_temp.valtype( 'num' )                                         \n"
                            + reg_mother + ".'add_child'( reg_temp )                       \n"
                            + "null reg_temp                                                     \n"
                            + "# leaving 'NUMBER'                                                \n"
                          );
                        

                    }
                    break;
                case 5 :
                    // grammar/antlr_3/antlr_past2pir_past.g:201:5: ^(infix= (PLUS|MINUS|MUL_OP|REL_OP) node[reg] node[reg] )
                    {

                          reg_num++;
                          String reg = "reg_" + reg_num;
                          System.out.print( 
                              "                                                                   \n"
                            + "    # entering '( PLUS | MINUS | MUL_OP | REL_OP ) node node'               \n"
                            + "      .sym pmc " + reg + "                                         \n"
                            + "      " + reg + " = new 'PAST::Op'                                 \n"
                          );
                        
                    infix=(CommonTree)input.LT(1);
                    if ( (input.LA(1)>=MINUS && input.LA(1)<=MUL_OP)||input.LA(1)==REL_OP ) {
                        input.consume();
                        errorRecovery=false;
                    }
                    else {
                        MismatchedSetException mse =
                            new MismatchedSetException(null,input);
                        recoverFromMismatchedSet(input,mse,FOLLOW_set_in_node221);    throw mse;
                    }


                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_node_in_node237);
                    node(reg);
                    _fsp--;

                    pushFollow(FOLLOW_node_in_node240);
                    node(reg);
                    _fsp--;


                    match(input, Token.UP, null); 

                          System.out.print( 
                              "      " + reg + ".'op'( 'infix:" + infix.getText() + "' )              \n"
                            + "    reg_temp = new 'PAST::Exp'                                     \n"
                            + "    reg_temp.'add_child'( " + reg + " )                            \n"
                            + "      null " + reg + "                                             \n"
                            + "  " + reg_mother + ".'add_child'( reg_temp )                 \n"
                            + "    null reg_temp                                                  \n"
                            + "    # leaving '( PLUS | MINUS | MUL | DIV ) node node'             \n"
                          );
                        

                    }
                    break;
                case 6 :
                    // grammar/antlr_3/antlr_past2pir_past.g:224:5: ^( VAR LETTER )
                    {
                    match(input,VAR,FOLLOW_VAR_in_node263); 

                    match(input, Token.DOWN, null); 
                    LETTER3=(CommonTree)input.LT(1);
                    match(input,LETTER,FOLLOW_LETTER_in_node265); 

                    match(input, Token.UP, null); 

                          System.out.print( 
                              "                                                                   \n"
                            + " # entering '( VAR LETTER )                                        \n"
                            + "    reg_temp = new 'PAST::Var'                                     \n"
                            + "    reg_temp.'varname'( '" + LETTER3.getText() + "' )                   \n"
                            + "    reg_temp.'vartype'( 'scalar' )                                 \n"
                            + "    reg_temp.'scope'( 'global' )                                   \n"
                            + "  " + reg_mother + ".'add_child'( reg_temp )                 \n"
                            + "    null reg_temp                                                  \n"
                            + "  # leaving '(VAR LETTER)'                                         \n"
                          );
                        

                    }
                    break;
                case 7 :
                    // grammar/antlr_3/antlr_past2pir_past.g:239:5: NEWLINE
                    {
                    match(input,NEWLINE,FOLLOW_NEWLINE_in_node285); 
                     
                          System.out.print(     
                              "                                                                   \n"
                            + "# entering 'NEWLINE'                                               \n"
                            + "            reg_temp = new 'PAST::Val'                             \n"
                            + "            reg_temp.value( '\\n' )                                \n"
                            + "            reg_temp.valtype( 'strqq' )                            \n"
                            + "          " + reg_mother + ".'add_child'( reg_temp )         \n"
                            + "          null reg_temp                                            \n"
                            + "# leaving 'NEWLINE'                                                \n"
                          );
                        

                    }
                    break;
                case 8 :
                    // grammar/antlr_3/antlr_past2pir_past.g:253:5: STRING
                    {
                    STRING4=(CommonTree)input.LT(1);
                    match(input,STRING,FOLLOW_STRING_in_node303); 

                          // In bc backslash has on special meaning, so s!/!//!
                          // Write newlines as '\n', in to not break PIR. s!\n!\\n!
                          String escaped = STRING4.getText().replaceAll( "\\\\", "\\\\\\\\\\\\\\\\" ).replaceAll( "\\n", "\\\\\\\\n" );
                          System.out.print(     
                              "                                                                   \n"
                            + "# entering 'STRING'                                                \n"
                            + "            reg_temp = new 'PAST::Val'                             \n"
                            + "            reg_temp.value( " + escaped + " )                      \n"
                            + "            reg_temp.valtype( 'strqq' )                            \n"
                            + "          " + reg_mother + ".'add_child'( reg_temp )         \n"
                            + "          null reg_temp                                            \n"
                            + "# leaving 'STRING'                                                 \n"
                          );
                        

                    }
                    break;
                case 9 :
                    // grammar/antlr_3/antlr_past2pir_past.g:270:5: ^( If node[\"reg_if_op\"] node[\"reg_if_op\"] )
                    {

                          reg_num++;
                          String reg_exp   = "reg_expression_" + reg_num;
                          System.out.print( 
                              "  # entering 'If node node                                         \n"
                            + "      reg_if_op = new 'PAST::Op'                                   \n"
                            + "      reg_if_op.'op'( 'if' )                                       \n"
                            + "        .sym pmc " + reg_exp + "                                   \n"
                            + "        " + reg_exp + " = new 'PAST::Exp'                          \n"
                            + "                                                                   \n"
                          );
                        
                    match(input,If,FOLLOW_If_in_node329); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_node_in_node331);
                    node("reg_if_op");
                    _fsp--;

                    pushFollow(FOLLOW_node_in_node334);
                    node("reg_if_op");
                    _fsp--;


                    match(input, Token.UP, null); 

                           // Create a node for If
                          System.out.print( 
                              "  # entering 'STMTS node*'                                         \n"
                            + "  " + reg_mother + ".'add_child'( reg_if_op )                \n"
                            + "  # leaving 'If node node                                          \n"
                          );
                        

                    }
                    break;
                case 10 :
                    // grammar/antlr_3/antlr_past2pir_past.g:292:5: ^( STMTS ( node[reg_stmts] )* )
                    {

                          reg_num++;
                          String reg_stmts = "reg_stmts_" + reg_num;
                          System.out.print( 
                              "        .sym pmc " + reg_stmts + "                                 \n"
                            + "        " + reg_stmts + " = new 'PAST::Stmts'                      \n"
                          );
                        
                    match(input,STMTS,FOLLOW_STMTS_in_node363); 

                    if ( input.LA(1)==Token.DOWN ) {
                        match(input, Token.DOWN, null); 
                        // grammar/antlr_3/antlr_past2pir_past.g:300:14: ( node[reg_stmts] )*
                        loop2:
                        do {
                            int alt2=2;
                            int LA2_0 = input.LA(1);
                            if ( ((LA2_0>=FUNCTION && LA2_0<=PRINT)||(LA2_0>=STMTS && LA2_0<=STRING)||(LA2_0>=NUMBER && LA2_0<=REL_OP)||LA2_0==If) ) {
                                alt2=1;
                            }


                            switch (alt2) {
                        	case 1 :
                        	    // grammar/antlr_3/antlr_past2pir_past.g:300:14: node[reg_stmts]
                        	    {
                        	    pushFollow(FOLLOW_node_in_node365);
                        	    node(reg_stmts);
                        	    _fsp--;


                        	    }
                        	    break;

                        	default :
                        	    break loop2;
                            }
                        } while (true);


                        match(input, Token.UP, null); 
                    }

                           // Create a node for If
                          System.out.print( 
                              "  " + reg_mother + ".'add_child'( " + reg_stmts + " )        \n"
                            + "  # leaving 'STMTS node*'                                          \n"
                          );
                        

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return ;
    }
    // $ANTLR end node


 

    public static final BitSet FOLLOW_PROGRAM_in_gen_pir_past73 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_node_in_gen_pir_past75 = new BitSet(new long[]{0x00000000100FCF68L});
    public static final BitSet FOLLOW_PRINT_in_node107 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_node_in_node109 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_FUNCTION_in_node132 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_LETTER_in_node134 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_ASSIGN_OP_in_node162 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_VAR_in_node165 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_LETTER_in_node167 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_node_in_node170 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_NUMBER_in_node191 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_node221 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_node_in_node237 = new BitSet(new long[]{0x00000000100FCF60L});
    public static final BitSet FOLLOW_node_in_node240 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_VAR_in_node263 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_LETTER_in_node265 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_NEWLINE_in_node285 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_STRING_in_node303 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_If_in_node329 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_node_in_node331 = new BitSet(new long[]{0x00000000100FCF60L});
    public static final BitSet FOLLOW_node_in_node334 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_STMTS_in_node363 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_node_in_node365 = new BitSet(new long[]{0x00000000100FCF68L});

}