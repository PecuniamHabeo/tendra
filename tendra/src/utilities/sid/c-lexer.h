/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*** c-lexer.h --- SID C lexical analyser.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-lexer.c" for details.
 */

#ifndef H_C_LEXER
#define H_C_LEXER

#include "config.h"
#include "c-code.h"
#include "dstring.h"
#include "istream.h"

/**** Note:
 *
 * It is important that any changes to this enumerated type declaration are
 * reflected in the "c-parser.sid" file.
 **/

typedef enum {
	C_TOK_BLT_PREFIXES,
	C_TOK_BLT_MAPS,
	C_TOK_BLT_ASSIGNMENTS,
	C_TOK_BLT_TERMINALS,
	C_TOK_BLT_HEADER,
	C_TOK_BLT_ACTIONS,
	C_TOK_BLT_TRAILER,
	C_TOK_BLT_RESULT_ASSIGN,
	C_TOK_SID_IDENTIFIER,
	C_TOK_C_IDENTIFIER,
	C_TOK_SEPARATOR,
	C_TOK_TYPEMARK,
	C_TOK_TERMINATOR,
	C_TOK_BEGIN_ACTION,
	C_TOK_DEFINE,
	C_TOK_END_ACTION,
	C_TOK_CODE,
	C_TOK_ARROW,
	C_TOK_OPEN_TUPLE,
	C_TOK_CLOSE_TUPLE,
	C_TOK_BLT_PARAM_ASSIGN,
	C_TOK_REFERENCE,
	C_TOK_EOF,
	C_TOK_ERROR
} CTokenT, *CTokenP;

typedef struct CLexT {
	CTokenT			t;
	union {
		NStringT		string;
		CCodeP			code;
	} u;
} CLexT, *CLexP;

typedef struct CLexerStreamT {
	IStreamT			istream;
	CLexT			token;
	CTokenT			saved_terminal;
} CLexerStreamT, *CLexerStreamP;

/*--------------------------------------------------------------------------*/

void	c_lexer_init(CLexerStreamP, IStreamP);
void	c_lexer_close(CLexerStreamP);
char *	c_lexer_stream_name(CLexerStreamP);
unsigned c_lexer_stream_line(CLexerStreamP);
CTokenT	c_lexer_get_terminal(CLexerStreamP);
void	c_lexer_next_token(CLexerStreamP);
NStringP c_lexer_string_value(CLexerStreamP);
CCodeP	c_lexer_code_value(CLexerStreamP);
void	c_lexer_save_terminal(CLexerStreamP, CTokenT);
void	c_lexer_restore_terminal(CLexerStreamP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define c_lexer_close(s) (istream_close (&((s)->istream)))
#define c_lexer_stream_name(s) (istream_name (&((s)->istream)))
#define c_lexer_stream_line(s) (istream_line (&((s)->istream)))
#define c_lexer_get_terminal(s) ((s)->token.t)
#define c_lexer_string_value(s) (&((s)->token.u.string))
#define c_lexer_code_value(s) ((s)->token.u.code)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_C_LEXER) */