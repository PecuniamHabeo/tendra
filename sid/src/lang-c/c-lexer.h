/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

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


/*
 * c-lexer.h --- SID C lexical analyser.
 *
 * See the file "c-lexer.c" for details.
 */

#ifndef H_C_LEXER
#define H_C_LEXER

#include "c-code.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include <exds/istream.h>
#include "c-lexi_lexer.h"


struct c_lexi_state c_lexer_current_state ;

/*
 * Note:
 *
 * It is important that any changes to this enumerated type declaration are
 * reflected in the "c-parser.sid" file.
 */
typedef enum {
    C_TOK_BLT_HPREFIXES,
    C_TOK_BLT_HMAPS,
    C_TOK_BLT_HPERSISTENTS,
    C_TOK_BLT_HASSIGNMENTS,
    C_TOK_BLT_HTERMINALS,
    C_TOK_BLT_HHEADER,
    C_TOK_BLT_HACTIONS,
    C_TOK_BLT_HTRAILER,
    C_TOK_BLT_HRESULT_HASSIGN,
    C_TOK_SID_HIDENTIFIER,
    C_TOK_C_HIDENTIFIER,
    C_TOK_SEPARATOR,
    C_TOK_TYPEMARK,
    C_TOK_TERMINATOR,
    C_TOK_BEGIN_HACTION,
    C_TOK_DEFINE,
    C_TOK_END_HACTION,
    C_TOK_CODE,
    C_TOK_ARROW,
    C_TOK_OPEN_HTUPLE,
    C_TOK_CLOSE_HTUPLE,
    C_TOK_BLT_HPARAM_HASSIGN,
    C_TOK_REFERENCE,
    C_TOK_EOF,

	/* Action code block tokens */
	C_TOK_ACT_HAT,
	C_TOK_ACT_HEXCEPTION,
	C_TOK_ACT_HTERMINAL,
	C_TOK_ACT_HADVANCE,
	C_TOK_ACT_HBASIC,
	C_TOK_ACT_HLABEL,
	C_TOK_ACT_HREFERENCE,
	C_TOK_ACT_HIDENTIFIER,
	C_TOK_ACT_HMODIFIABLE,
	C_TOK_ACT_HCODESTRING,
	C_TOK_ACT_HEOF,
	C_TOK_ACT_HCODESTART,
	C_TOK_ACT_HCODEEND,

	C_TOK_ERROR
} CTokenT;

typedef struct CLexT {
    CTokenT			t;
    union {
	NStringT		string;
	CCodeT *			code;
    } u;
} CLexT;

typedef struct CLexerStreamT {
    IStreamT			istream;
    CLexT			token;
    CTokenT			saved_terminal;
} CLexerStreamT;

/* XXX Remove once lexi provides identifier support */
int c_lexer_support_read_id(int c, int rettok, enum c_lexi_groups bodygroup);
int c_lexer_read_builtin(int c0, int c1);
int c_lexer_act_read_string(int c);
int c_lexer_unknown_token(int c);

/* Lexi interface support */
int c_lexi_getchar(void);

void		c_lexer_init(CLexerStreamT *, IStreamT *);
void		c_lexer_close(CLexerStreamT *);
char *		c_lexer_stream_name(CLexerStreamT *);
unsigned		c_lexer_stream_line(CLexerStreamT *);
CTokenT		c_lexer_get_terminal(CLexerStreamT *);
void		c_lexer_next_token(CLexerStreamT *);
NStringT *		c_lexer_string_value(CLexerStreamT *);
CCodeT *		c_lexer_code_value(CLexerStreamT *);
void		c_lexer_save_terminal(CLexerStreamT *, CTokenT);
void		c_lexer_restore_terminal(CLexerStreamT *);

/* XXX remove once lexi provides opaque pointers */
CLexerStreamT *c_lexer_stream;

#endif /* !defined (H_C_LEXER) */
