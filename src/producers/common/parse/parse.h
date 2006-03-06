/*
    		 Crown Copyright (c) 1997, 1998
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef PARSE_INCLUDED
#define PARSE_INCLUDED


/*
    TYPE REPRESENTING A PARSER STATE

    This type is used to represent the information to be saved before the
    separate compilation of any saved preprocessing tokens and restored
    afterwards.
*/

typedef struct pstate_tag {
    LOCATION loc ;
    OPTIONS *opts ;
    int flag [10] ;
    DECL_SPEC dspec [2] ;
    NAMESPACE nspace [2] ;
    STACK ( NAMESPACE ) nstack [3] ;
} PARSE_STATE ;


/*
    TOKEN EXPANSION STATES

    These values are used as arguments to expand_token to indicate the
    current parsing state.
*/

#define EXPAND_NORMAL			0
#define EXPAND_AHEAD			1
#define EXPAND_RESCAN			2
#define EXPAND_TEMPLATE			3
#define EXPAND_IDENTIFIER		4
#define EXPAND_COLON_COLON		5
#define EXPAND_CHECK_COLON		6
#define EXPAND_DESTRUCTOR		7
#define EXPAND_STRING			8


/*
    TOKEN PARSER DECLARATIONS

    The routines in this module are concerned with reading the next lexical
    token from the input file.  They include expand_token which is the top
    level lexical analysis and preprocessing routine.
*/

extern void init_parser PROTO_S ( ( PPTOKEN * ) ) ;
extern int expand_token PROTO_S ( ( int ) ) ;
extern int expand_preproc PROTO_S ( ( int ) ) ;
extern void rescan_template PROTO_S ( ( NAMESPACE ) ) ;
extern PPTOKEN *patch_tokens PROTO_S ( ( int ) ) ;
extern PPTOKEN *restore_parser PROTO_S ( ( void ) ) ;
extern PPTOKEN *read_loc_tokens PROTO_S ( ( PPTOKEN * ) ) ;
extern void snip_tokens PROTO_S ( ( PPTOKEN *, PPTOKEN * ) ) ;
extern void save_state PROTO_S ( ( PARSE_STATE *, int ) ) ;
extern void restore_state PROTO_S ( ( PARSE_STATE * ) ) ;
extern int crt_state_depth ;


/*
    CURRENT TOKEN INFORMATION

    These variables are used to store information about the current lexical
    token as read by expand_token.  crt_lex_token gives the current token
    number, with any additional information being stored in crt_token.
    last_lex_token gives the previous value of crt_lex_token.  Finally
    saved_lex_token is used as a temporary store in exception handling.
*/

extern PPTOKEN *crt_token ;
extern NAMESPACE crt_lookup ;
extern int crt_lex_token ;
extern int saved_lex_token ;
extern int last_lex_token ;
extern int have_syntax_error ;


/*
    PARSER MACROS

    These macros are used by the SID parser to access the output of the
    lexical analysis and preprocessing routines.  CURRENT_TERMINAL gives
    the value of the current lexical token.  ADVANCE_LEXER reads the next
    lexical token.  RESCAN_LEXER rescans the current token.  SAVE_LEXER
    and RESTORE_LEXER are used in exception handling.
*/

#define CURRENT_TERMINAL	crt_lex_token
#define RESTORE_LEXER		crt_lex_token = saved_lex_token ;
#define next_token()		expand_token ( EXPAND_AHEAD )
#define RESCAN_LEXER		crt_lex_token = expand_token ( EXPAND_RESCAN )

#define ADVANCE_LEXER\
    {\
	last_lex_token = crt_lex_token ;\
	crt_lex_token = expand_token ( EXPAND_NORMAL ) ;\
    }


#define SAVE_LEXER( T )\
    {\
	saved_lex_token = crt_lex_token ;\
	crt_lex_token = ( T ) ;\
    }


#endif