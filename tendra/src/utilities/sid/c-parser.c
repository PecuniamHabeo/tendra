/*
 * Automatically generated from the files:
 *	./c-parser.sid
 * and
 *	./c-parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


/*
 * Copyright (c) 2003-2004, The Tendra Project <http://www.ten15.org/>
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
 *  		 Crown Copyright (c) 1997
 *
 *  This TenDRA(r) Computer Program is subject to Copyright
 *  owned by the United Kingdom Secretary of State for Defence
 *  acting through the Defence Evaluation and Research Agency
 *  (DERA).  It is made available to Recipients with a
 *  royalty-free licence for its use, reproduction, transfer
 *  to other parties and amendment for any purpose not excluding
 *  product development provided that any such use et cetera
 *  shall be deemed to be acceptance of the following conditions:-
 *
 *      (1) Its Recipients shall ensure that this Notice is
 *      reproduced upon any copies or amended versions of it;
 *
 *      (2) Any amended version of it shall be clearly marked to
 *      show both the nature of and the organisation responsible
 *      for the relevant amendment or amendments;
 *
 *      (3) Its onward transfer from a recipient to another
 *      party shall be deemed to be that party's acceptance of
 *      these conditions;
 *
 *      (4) DERA gives no warranty or assurance as to its
 *      quality or suitability for any purpose and DERA accepts
 *      no liability whatsoever in relation to any use to which
 *      it may be put.
 *
 * $TenDRA$
 */


#include "c-parser.h"
#include "action.h"
#include "c-code.h"
#include "c-out-info.h"
#include "basic.h"
#include "entry.h"
#include "msgcat.h"
#include "type.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

#define CURRENT_TERMINAL c_lexer_get_terminal (c_current_stream)
#define ADVANCE_LEXER c_lexer_next_token (c_current_stream)
#define SAVE_LEXER(x) (c_lexer_save_terminal (c_current_stream, (CTokenT) (x)))
#define RESTORE_LEXER (c_lexer_restore_terminal (c_current_stream))

/*--------------------------------------------------------------------------*/

static NStringT		c_prefix_names [CPFX_NUM_PREFIXES];
static BoolT		c_inited_prefix_names = FALSE;
static CPrefixT		c_current_prefix;
static EntryP		c_current_entry;
static TypeTupleT	c_saved_type;
static TypeTupleT	c_current_type;
static BoolT		c_propagating_error = FALSE;

/*--------------------------------------------------------------------------*/

CLexerStreamP		c_current_stream;
COutputInfoP		c_current_out_info;
TableP			c_current_table;

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR84 (void);
static void ZR132 (void);
static void ZR110 (void);
static void ZR139 (void);
static void ZR112 (void);
static void ZR134 (void);
static void ZR101 (void);
static void ZR141 (void);
static void ZR172 (void);
static void ZR146 (void);
static void ZR82 (void);
extern void c_parse_grammar (void);
static void ZR92 (void);
static void ZR119 (void);
static void ZR148 (void);
static void ZR107 (void);
static void ZR90 (void);
static void ZR99 (void);
static void ZR117 (void);
static void ZR116 (void);
static void ZR125 (void);
static void ZR121 (void);
static void ZR127 (void);
static void ZR124 (void);

/* BEGINNING OF STATIC VARIABLES */

static BoolT ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR84 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	NStringT ZI85;

	{
	    switch (CURRENT_TERMINAL) {
	      case CP_c_Hidentifier:
		{
		    {

    nstring_assign (&ZI85, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case CP_sid_Hidentifier:
		{
		    {

    nstring_assign (&ZI85, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    int prefix;

    if (!c_inited_prefix_names) {
	nstring_copy_cstring (&(c_prefix_names [CPFX_TYPE]), "type");
	nstring_copy_cstring (&(c_prefix_names [CPFX_FN]), "function");
	nstring_copy_cstring (&(c_prefix_names [CPFX_IN]), "input");
	nstring_copy_cstring (&(c_prefix_names [CPFX_OUT]), "output");
	nstring_copy_cstring (&(c_prefix_names [CPFX_LABEL]), "label");
	nstring_copy_cstring (&(c_prefix_names [CPFX_TERMINAL]), "terminal");
	c_inited_prefix_names = TRUE;
    }
    for (prefix = 0; prefix < CPFX_NUM_PREFIXES; prefix ++) {
	if (nstring_ci_equal ((&ZI85), &(c_prefix_names [prefix]))) {
	    break;
	}
    }
    if ((c_current_prefix = (CPrefixT) prefix) == CPFX_NUM_PREFIXES) {
	MSG_c_unknown_prefix ((&ZI85));
    }
    nstring_destroy (&(ZI85));
	}
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI88;

		switch (CURRENT_TERMINAL) {
		  case CP_c_Hidentifier:
		    {

    nstring_assign (&ZI88, c_lexer_string_value (c_current_stream));
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_prefix == CPFX_NUM_PREFIXES) {
	nstring_destroy (&(ZI88));
    } else {
	NStringP prefix = c_out_info_prefix (c_current_out_info,
					     c_current_prefix);

	nstring_destroy (prefix);
	nstring_assign (prefix, &(ZI88));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_c_identifier ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_MAPS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ASSIGNMENTS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR132 (void)
{
  ZL2_132:;
    switch (CURRENT_TERMINAL) {
      case CP_sid_Hidentifier: case CP_c_Hidentifier:
	{
	    ZR134 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_132;
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR110 (void)
{
    switch (CURRENT_TERMINAL) {
      case CP_c_Hidentifier:
	{
	    ZR107 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR139 (void)
{
  ZL2_139:;
    switch (CURRENT_TERMINAL) {
      case CP_sid_Hidentifier: case CP_c_Hidentifier:
	{
	    ZR141 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_139;
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR112 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	{

    types_init (&c_current_type);
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case CP_open_Htuple:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_open_tuple ();
    }
		}
	    }
	  ZL2:;
	}
	ZR110 ();
	if ((CURRENT_TERMINAL) == 23) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    c_propagating_error = FALSE;
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case CP_close_Htuple:
		    break;
		  default:
		    goto ZL5;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL4;
	  ZL5:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_close_tuple ();
    }
		}
	    }
	  ZL4:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR134 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	NStringT ZI79;

	{
	    switch (CURRENT_TERMINAL) {
	      case CP_c_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case CP_sid_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_type (c_current_table, (&ZI79))) ==
	NIL (EntryP)) {
	MSG_c_unknown_result_assign ((&ZI79));
    } else if (type_get_result_assign_code (entry_get_type (c_current_entry))) {
	MSG_c_result_assign_mult_def ((&ZI79));
	c_current_entry = NIL (EntryP);
    }
    nstring_destroy (&(ZI79));
	}
	ZR99 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI123;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI123 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_entry) {
	BoolT      errored = FALSE;
	KeyP       key     = entry_key (c_current_entry);
	TypeTupleT tmp;

	types_init (&tmp);
	types_add_type_entry (&tmp, c_current_entry, FALSE);
	if (!types_disjoint_names (&c_saved_type)) {
	    MSG_c_result_assign_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, &tmp)) {
	    MSG_c_res_assign_param_mismatch (key, &tmp, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    MSG_c_result_assign_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, &tmp)) {
	    MSG_c_res_assign_result_mismatch (key, &tmp, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    MSG_c_result_assign_formal_clash (key, &c_saved_type,
					    &c_current_type);
	    errored = TRUE;
	}
	types_destroy (&tmp);
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI123));
	    c_current_entry = NIL (EntryP);
	} else {
	    TypeP type = entry_get_type (c_current_entry);

	    c_code_check ((ZI123), FALSE, FALSE, &c_saved_type, &c_current_type,
			  c_current_table);
	    type_set_result_assign_code (type, (void *) (ZI123));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI123));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR101 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	NStringT ZI88;

	switch (CURRENT_TERMINAL) {
	  case CP_c_Hidentifier:
	    {

    nstring_assign (&ZI88, c_lexer_string_value (c_current_stream));
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case CP_typemark:
		{
		    ADVANCE_LEXER;
		    {
			{
			    NStringT ZI105;

			    {
				switch (CURRENT_TERMINAL) {
				  case CP_c_Hidentifier:
				    {
					{

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
					}
					ADVANCE_LEXER;
				    }
				    break;
				  case CP_sid_Hidentifier:
				    {
					{

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
					}
					ADVANCE_LEXER;
				    }
				    break;
				  default:
				    goto ZL4;
				}
			    }
			    {
				switch (CURRENT_TERMINAL) {
				  case CP_reference:
				    {
					ADVANCE_LEXER;
					{

    if (!types_add_typed_name (&c_current_type, c_current_table, &(ZI88),
			       (&ZI105), TRUE)) {
	MSG_c_unknown_type ((&ZI105));
    }
    nstring_destroy (&(ZI105));
					}
				    }
				    break;
				  default:
				    {
					{

    if (!types_add_typed_name (&c_current_type, c_current_table, &(ZI88),
			       (&ZI105), FALSE)) {
	MSG_c_unknown_type ((&ZI105));
    }
    nstring_destroy (&(ZI105));
					}
				    }
				    break;
				}
			    }
			}
			goto ZL3;
		      ZL4:;
			{
			    {

    if (!c_propagating_error) {
	MSG_c_expected_identifier ();
    }
			    }
			    {

    nstring_destroy (&(ZI88));
			    }
			    {

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_DEFINE) &&
	   (CURRENT_TERMINAL != C_TOK_CODE) &&
	   (CURRENT_TERMINAL != C_TOK_SEPARATOR) &&
	   (CURRENT_TERMINAL != C_TOK_CLOSE_TUPLE) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
			    }
			}
		      ZL3:;
		    }
		}
		break;
	      default:
		{
		    {

    types_add_name (&c_current_type, c_current_table, &(ZI88), FALSE);
		    }
		}
		break;
	    }
	}
    }
    return;
  ZL1:;
    {
	{

    if (!c_propagating_error) {
	MSG_c_expected_identifier ();
    }
	}
	{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_DEFINE) &&
	   (CURRENT_TERMINAL != C_TOK_CODE) &&
	   (CURRENT_TERMINAL != C_TOK_SEPARATOR) &&
	   (CURRENT_TERMINAL != C_TOK_CLOSE_TUPLE) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
	}
    }
}

static void
ZR141 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	NStringT ZI79;

	{
	    switch (CURRENT_TERMINAL) {
	      case CP_c_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case CP_sid_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_basic (c_current_table, (&ZI79))) ==
	NIL (EntryP)) {
	MSG_c_unknown_basic ((&ZI79));
    } else {
	BasicP basic = entry_get_basic (c_current_entry);

	if (basic_get_result_code (basic)) {
	    MSG_c_basic_mult_def ((&ZI79));
	    c_current_entry = NIL (EntryP);
	} else if (types_equal_zero_tuple (basic_result (basic))) {
	    MSG_c_basic_has_no_result ((&ZI79));
	    c_current_entry = NIL (EntryP);
	}
    }
    nstring_destroy (&(ZI79));
	}
	ZR99 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI123;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI123 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_entry) {
	BasicP     basic   = entry_get_basic (c_current_entry);
	TypeTupleP result  = basic_result (basic);
	BoolT      errored = FALSE;
	KeyP       key     = entry_key (c_current_entry);

	if (!types_disjoint_names (&c_saved_type)) {
	    MSG_c_basic_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_equal_zero_tuple (&c_saved_type)) {
	    MSG_c_basic_param_mismatch (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    MSG_c_basic_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, result)) {
	    MSG_c_basic_result_mismatch (key, result, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    MSG_c_basic_formal_clash (key, &c_saved_type, &c_current_type);
	    errored = TRUE;
	}
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI123));
	    c_current_entry = NIL (EntryP);
	} else {
	    types_destroy (&c_saved_type);
	    c_code_check ((ZI123), FALSE, FALSE, NIL (TypeTupleP),
			  &c_current_type, c_current_table);
	    basic_set_result_code (basic, (void *) (ZI123));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI123));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR172 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case CP_separator:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!c_propagating_error) {
	MSG_c_expected_separator ();
    }
	}
    }
}

static void
ZR146 (void)
{
  ZL2_146:;
    switch (CURRENT_TERMINAL) {
      case CP_begin_Haction:
	{
	    ZR148 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_146;
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR82 (void)
{
  ZL2_82:;
    switch (CURRENT_TERMINAL) {
      case CP_sid_Hidentifier: case CP_c_Hidentifier:
	{
	    ZR84 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_82;
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

void
c_parse_grammar (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	{
	    switch (CURRENT_TERMINAL) {
	      case CP_blt_Hprefixes:
		{
		    ADVANCE_LEXER;
		    ZR82 ();
		    if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case CP_blt_Hmaps:
		{
		    ADVANCE_LEXER;
		    ZR90 ();
		    if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case CP_blt_Hheader:
		    break;
		  default:
		    goto ZL5;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL4;
	  ZL5:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_blt_header ();
    }
		}
	    }
	  ZL4:;
	}
	{
	    {
		CCodeP ZI159;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI159 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL7;
		}
		ADVANCE_LEXER;
		{

    c_code_check ((ZI159), FALSE, FALSE, NIL (TypeTupleP), NIL (TypeTupleP),
		  c_current_table);
    c_out_info_set_header1 (c_current_out_info, (ZI159));
		}
	    }
	    goto ZL6;
	  ZL7:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
	    }
	  ZL6:;
	}
	ZR172 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI162;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI162 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL9;
		}
		ADVANCE_LEXER;
		{

    c_code_check ((ZI162), FALSE, FALSE, NIL (TypeTupleP), NIL (TypeTupleP),
		  c_current_table);
    c_out_info_set_header2 (c_current_out_info, (ZI162));
		}
	    }
	    goto ZL8;
	  ZL9:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
	    }
	  ZL8:;
	}
	ZR124 ();
	{
	    switch (CURRENT_TERMINAL) {
	      case CP_blt_Hassignments:
		{
		    ADVANCE_LEXER;
		    ZR117 ();
		    if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 23:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case CP_blt_Hparam_Hassign:
		{
		    ADVANCE_LEXER;
		    ZR125 ();
		    if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case CP_blt_Hresult_Hassign:
		{
		    ADVANCE_LEXER;
		    ZR132 ();
		    if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case CP_blt_Hterminals:
		    break;
		  default:
		    goto ZL14;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL13;
	  ZL14:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_blt_terminals ();
    }
		}
	    }
	  ZL13:;
	}
	ZR139 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case CP_blt_Hactions:
		    break;
		  default:
		    goto ZL16;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL15;
	  ZL16:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_blt_actions ();
    }
		}
	    }
	  ZL15:;
	}
	ZR146 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case CP_blt_Htrailer:
		    break;
		  default:
		    goto ZL18;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL17;
	  ZL18:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_blt_trailer ();
    }
		}
	    }
	  ZL17:;
	}
	{
	    {
		CCodeP ZI171;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI171 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL20;
		}
		ADVANCE_LEXER;
		{

    c_code_check ((ZI171), FALSE, FALSE, NIL (TypeTupleP), NIL (TypeTupleP),
		  c_current_table);
    c_out_info_set_trailer1 (c_current_out_info, (ZI171));
		}
	    }
	    goto ZL19;
	  ZL20:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
	    }
	  ZL19:;
	}
	ZR172 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI174;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI174 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL22;
		}
		ADVANCE_LEXER;
		{

    c_code_check ((ZI174), FALSE, FALSE, NIL (TypeTupleP), NIL (TypeTupleP),
		  c_current_table);
    c_out_info_set_trailer2 (c_current_out_info, (ZI174));
		}
	    }
	    goto ZL21;
	  ZL22:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
	    }
	  ZL21:;
	}
	ZR124 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case CP_eof:
		    break;
		  default:
		    goto ZL24;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL23;
	  ZL24:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_eof ();
    }
		}
	    }
	  ZL23:;
	}
    }
    return;
  ZL1:;
    {
	{

    UNREACHED;
	}
    }
}

static void
ZR92 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	NStringT ZI94;

	{
	    switch (CURRENT_TERMINAL) {
	      case CP_c_Hidentifier:
		{
		    {

    nstring_assign (&ZI94, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case CP_sid_Hidentifier:
		{
		    {

    nstring_assign (&ZI94, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_entry (c_current_table, (&ZI94))) ==
	NIL (EntryP)) {
	MSG_c_unknown_identifier ((&ZI94));
    } else if (entry_get_mapping (c_current_entry)) {
	MSG_c_remapped_identifier ((&ZI94));
	c_current_entry = NIL (EntryP);
    } else {
	switch (entry_type (c_current_entry)) EXHAUSTIVE {
	  case ET_NAME:
	  case ET_ACTION:
	  case ET_NON_LOCAL:
	    MSG_c_illegal_map ((&ZI94));
	    c_current_entry = NIL (EntryP);
	    break;
	  case ET_RENAME:
	  case ET_PREDICATE:
	    /* UNREACHED */
	    break;
	  case ET_TYPE:
	  case ET_RULE:
	  case ET_BASIC:
	    break;
	}
    }
    nstring_destroy (&(ZI94));
	}
	ZR116 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI97;

		switch (CURRENT_TERMINAL) {
		  case CP_c_Hidentifier:
		    {

    nstring_assign (&ZI97, c_lexer_string_value (c_current_stream));
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_entry) {
	entry_set_mapping (c_current_entry, &(ZI97));
    } else {
	nstring_destroy (&(ZI97));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_c_identifier ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ASSIGNMENTS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR119 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	NStringT ZI79;

	{
	    switch (CURRENT_TERMINAL) {
	      case CP_c_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case CP_sid_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_type (c_current_table, (&ZI79))) ==
	NIL (EntryP)) {
	MSG_c_unknown_assign ((&ZI79));
    } else if (type_get_assign_code (entry_get_type (c_current_entry))) {
	MSG_c_assign_mult_def ((&ZI79));
	c_current_entry = NIL (EntryP);
    }
    nstring_destroy (&(ZI79));
	}
	ZR99 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI123;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI123 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_entry) {
	BoolT      errored = FALSE;
	KeyP       key     = entry_key (c_current_entry);
	TypeTupleT tmp;

	types_init (&tmp);
	types_add_type_entry (&tmp, c_current_entry, FALSE);
	if (!types_disjoint_names (&c_saved_type)) {
	    MSG_c_assign_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, &tmp)) {
	    MSG_c_assign_param_mismatch (key, &tmp, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    MSG_c_assign_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, &tmp)) {
	    MSG_c_assign_result_mismatch (key, &tmp, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    MSG_c_assign_formal_clash (key, &c_saved_type, &c_current_type);
	    errored = TRUE;
	}
	types_destroy (&tmp);
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI123));
	    c_current_entry = NIL (EntryP);
	} else {
	    TypeP type = entry_get_type (c_current_entry);

	    c_code_check ((ZI123), FALSE, FALSE, &c_saved_type, &c_current_type,
			  c_current_table);
	    type_set_assign_code (type, (void *) (ZI123));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI123));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR148 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case CP_begin_Haction:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    {
		NStringT ZI79;

		{
		    switch (CURRENT_TERMINAL) {
		      case CP_c_Hidentifier:
			{
			    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
			    }
			    ADVANCE_LEXER;
			}
			break;
		      case CP_sid_Hidentifier:
			{
			    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
			    }
			    ADVANCE_LEXER;
			}
			break;
		      default:
			goto ZL3;
		    }
		}
		{

    if ((c_current_entry = table_get_action (c_current_table, (&ZI79))) ==
	NIL (EntryP)) {
	MSG_c_unknown_action ((&ZI79));
    } else {
	ActionP action = entry_get_action (c_current_entry);

	if (action_get_code (action)) {
	    MSG_c_action_mult_def ((&ZI79));
	    c_current_entry = NIL (EntryP);
	}
    }
    nstring_destroy (&(ZI79));
		}
		{
		    {
			switch (CURRENT_TERMINAL) {
			  case CP_end_Haction:
			    break;
			  default:
			    goto ZL6;
			}
			ADVANCE_LEXER;
		    }
		    goto ZL5;
		  ZL6:;
		    {
			{

    if (!c_propagating_error) {
	MSG_c_expected_end_action ();
    }
			}
		    }
		  ZL5:;
		}
		ZR99 ();
		ZR121 ();
		{
		    if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    {
			CCodeP ZI123;

			switch (CURRENT_TERMINAL) {
			  case CP_code:
			    {

    ZI123 = c_lexer_code_value (c_current_stream);
			    }
			    break;
			  default:
			    goto ZL8;
			}
			ADVANCE_LEXER;
			{

    if (c_current_entry) {
	ActionP    action  = entry_get_action (c_current_entry);
	TypeTupleP param   = action_param (action);
	TypeTupleP result  = action_result (action);
	BoolT      errored = FALSE;
	KeyP       key     = entry_key (c_current_entry);

	if (!types_disjoint_names (&c_saved_type)) {
	    MSG_c_action_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, param)) {
	    MSG_c_action_param_mismatch (key, param, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    MSG_c_action_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, result)) {
	    MSG_c_action_result_mismatch (key, result, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    MSG_c_action_formal_clash (key, &c_saved_type, &c_current_type);
	    errored = TRUE;
	}
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI123));
	    c_current_entry = NIL (EntryP);
	} else {
	    c_code_check ((ZI123), TRUE, FALSE, &c_saved_type, &c_current_type,
			  c_current_table);
	    types_propogate_mutations (param, &c_saved_type);
	    action_set_code (action, (void *) (ZI123));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI123));
    }
			}
			ZR124 ();
			if ((CURRENT_TERMINAL) == 23) {
			    RESTORE_LEXER;
			    goto ZL8;
			}
		    }
		    goto ZL7;
		  ZL8:;
		    {
			{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
			}
			{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
			}
		    }
		  ZL7:;
		}
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_identifier ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL2:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR107 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
  ZL2_107:;
    {
	ZR101 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

    (ZI0) = ((CURRENT_TERMINAL == C_TOK_CLOSE_TUPLE) ||
		  (CURRENT_TERMINAL == C_TOK_EOF) ||
		  (c_propagating_error));
		}
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case CP_separator:
		{
		    ADVANCE_LEXER;
		    goto ZL2_107;
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_separator ();
    }
		}
		goto ZL2_107;
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR90 (void)
{
  ZL2_90:;
    switch (CURRENT_TERMINAL) {
      case CP_sid_Hidentifier: case CP_c_Hidentifier:
	{
	    ZR92 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_90;
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR99 (void)
{
    switch (CURRENT_TERMINAL) {
      case CP_typemark:
	{
	    ADVANCE_LEXER;
	    ZR112 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    types_assign (&c_saved_type, &c_current_type);
	    }
	    ZR116 ();
	    ZR112 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    types_init (&c_saved_type);
    types_init (&c_current_type);
	    }
	}
	break;
      case 23:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR117 (void)
{
  ZL2_117:;
    switch (CURRENT_TERMINAL) {
      case CP_sid_Hidentifier: case CP_c_Hidentifier:
	{
	    ZR119 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_117;
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR116 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case CP_arrow:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!c_propagating_error) {
	MSG_c_expected_arrow ();
    }
	}
    }
}

static void
ZR125 (void)
{
  ZL2_125:;
    switch (CURRENT_TERMINAL) {
      case CP_sid_Hidentifier: case CP_c_Hidentifier:
	{
	    ZR127 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_125;
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR121 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case CP_define:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!c_propagating_error) {
	MSG_c_expected_define ();
    }
	}
    }
}

static void
ZR127 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	NStringT ZI79;

	{
	    switch (CURRENT_TERMINAL) {
	      case CP_c_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case CP_sid_Hidentifier:
		{
		    {

    nstring_assign (&ZI79, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_type (c_current_table, (&ZI79))) ==
	NIL (EntryP)) {
	MSG_c_unknown_param_assign ((&ZI79));
    } else if (type_get_param_assign_code (entry_get_type (c_current_entry))) {
	MSG_c_param_assign_mult_def ((&ZI79));
	c_current_entry = NIL (EntryP);
    }
    nstring_destroy (&(ZI79));
	}
	ZR99 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI123;

		switch (CURRENT_TERMINAL) {
		  case CP_code:
		    {

    ZI123 = c_lexer_code_value (c_current_stream);
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_entry) {
	BoolT      errored = FALSE;
	KeyP       key     = entry_key (c_current_entry);
	TypeTupleT tmp;

	types_init (&tmp);
	types_add_type_entry (&tmp, c_current_entry, FALSE);
	if (!types_disjoint_names (&c_saved_type)) {
	    MSG_c_param_assign_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, &tmp)) {
	    MSG_c_param_assign_param_mismatch (key, &tmp, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    MSG_c_param_assign_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, &tmp)) {
	    MSG_c_param_assign_res_mismatch (key, &tmp, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    MSG_c_param_assign_formal_clash (key, &c_saved_type,
					    &c_current_type);
	    errored = TRUE;
	}
	types_destroy (&tmp);
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI123));
	    c_current_entry = NIL (EntryP);
	} else {
	    TypeP type = entry_get_type (c_current_entry);

	    c_code_check ((ZI123), FALSE, TRUE, &c_saved_type, &c_current_type,
			  c_current_table);
	    type_set_param_assign_code (type, (void *) (ZI123));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI123));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	MSG_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR124 (void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case CP_terminator:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!c_propagating_error) {
	MSG_c_expected_terminator ();
    }
	}
    }
}

/* BEGINNING OF TRAILER */



/* END OF FILE */