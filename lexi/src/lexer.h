/* 
 *  Copyright (c) 2002-2007 The TenDRA Project <http://www.tendra.org/>.
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. Neither the name of The TenDRA Project nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific, prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 *  IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 *     		 Crown Copyright (c) 1997
 *     
 *     This TenDRA(r) Computer Program is subject to Copyright
 *     owned by the United Kingdom Secretary of State for Defence
 *     acting through the Defence Evaluation and Research Agency
 *     (DERA).  It is made available to Recipients with a
 *     royalty-free licence for its use, reproduction, transfer
 *     to other parties and amendment for any purpose not excluding
 *     product development provided that any such use et cetera
 *     shall be deemed to be acceptance of the following conditions:-
 *     
 *         (1) Its Recipients shall ensure that this Notice is
 *         reproduced upon any copies or amended versions of it;
 *     
 *         (2) Any amended version of it shall be clearly marked to
 *         show both the nature of and the organisation responsible
 *         for the relevant amendment or amendments;
 *     
 *         (3) Its onward transfer from a recipient to another
 *         party shall be deemed to be that party's acceptance of
 *         these conditions;
 *     
 *         (4) DERA gives no warranty or assurance as to its
 *         quality or suitability for any purpose and DERA accepts
 *         no liability whatsoever in relation to any use to which
 *         it may be put.
 * 
 * $Id: COPYING 1703 2007-11-22 01:34:18Z kate $
 * 
 */
/*
 *  AUTOMATICALLY GENERATED BY lexi VERSION 2.0
 */

#ifndef LEXI_GENERATED_HEADER_lexi__INCLUDED
#define LEXI_GENERATED_HEADER_lexi__INCLUDED

#include <stdint.h>

#ifndef LEX_EOF
#define LEX_EOF		256
#endif

extern void lexi_push(const int c);
extern int lexi_pop(void);
extern void lexi_flush(void);
extern int lexi_readchar(void);
enum lexi_groups {
	lexi_group_white = 0x01,
	lexi_group_alpha = 0x02,
	lexi_group_digit = 0x04,
	lexi_group_alphanum = 0x08,
	lexi_group_comment_white = 0x10,
	lexi_group_line_comment_white = 0x20
};

/* true if the given character is present in the given group */
extern int lexi_group(enum lexi_groups group, int c);
extern int lexi_keyword(const char *identifier, int notfound);
/* lexer_state_definition */

typedef struct lexi_lexer_state_tag lexi_lexer_state;
extern lexi_lexer_state* lexi_current_lexer_state;
extern int lexi_read_token(lexi_lexer_state *state);
#endif
