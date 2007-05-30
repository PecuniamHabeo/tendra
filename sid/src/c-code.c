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


/**** c-code.c --- SID C code ADT routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the C code ADT used to represent action definitions
 * for the C output language.
 *
 **** Change Log:
 * $Log: c-code.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/03/01  09:53:12  smf
 * c-code.c, c-out-info.c, c-out-info.h, c-output.c:
 * 	- improved unreachable code analysis;
 * 	- improved some output formatting;
 * 	- added support for comment or macro to mark unreachable code.
 *
 * Revision 1.2  1994/12/15  09:56:23  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:17  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-code.h"
#include "c-out-key.h"
#include "c-output.h"
#include "gen-errors.h"
#include "name.h"

/*--------------------------------------------------------------------------*/

static void
c_code_set_labels(CCodeP code)
{
    CCodeItemP item;

    for (item = code->head; item; item = item->next) {
	if (item->type == CCT_LABEL) {
	    NameP name = entry_get_name(item->u.ident);

	    if (!name_has_label(name)) {
		name_set_label(name, c_out_next_label());
	    }
	}
    }
}

static void
c_code_reset_labels(CCodeP code)
{
    CCodeItemP item;

    for (item = code->head; item; item = item->next) {
	if (item->type == CCT_LABEL) {
	    NameP name = entry_get_name(item->u.ident);

	    name_reset_label(name);
	}
    }
}

static EntryP
c_code_get_translation(SaveRStackP state, TypeBTransP translator, EntryP ident,
		       EntryP *type_ref, BoolT *reference_ref,
		       EntryP *entry_ref)
{
    EntryP entry = btrans_get_translation(translator, ident);
    EntryP stack_entry;

    ASSERT(entry);
    stack_entry = rstack_get_translation(state, entry, type_ref,
					 reference_ref);
    if ((stack_entry == NIL(EntryP)) && (entry_is_non_local(entry))) {
	stack_entry    = entry;
	*type_ref      = entry_get_non_local(entry);
	*reference_ref = FALSE;
    }
    ASSERT(stack_entry);
    if (entry_ref) {
	*entry_ref = entry;
    }
    return(stack_entry);
}

/*--------------------------------------------------------------------------*/

CCodeP
c_code_create(CStringP file, unsigned line)
{
    CCodeP code = ALLOCATE(CCodeT);

    code->head = NIL(CCodeItemP);
    code->tail = &(code->head);
    code->file = file;
    code->line = line;
    types_init(&(code->param));
    types_init(&(code->result));
    return(code);
}

void
c_code_append_string(CCodeP code, NStringP string)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_STRING;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_label(CCodeP code, NStringP string)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_LABEL;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_identifier(CCodeP code, NStringP string)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_IDENT;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_modifiable(CCodeP code, NStringP string)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_MOD_IDENT;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_reference(CCodeP code, NStringP string)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_REF_IDENT;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_exception(CCodeP code)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_EXCEPTION;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_advance(CCodeP code)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_ADVANCE;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_terminal(CCodeP code)
{
    CCodeItemP item = ALLOCATE(CCodeItemT);

    item->next    = NIL(CCodeItemP);
    item->type    = CCT_TERMINAL;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_check(CCodeP code, BoolT exceptions, BoolT param_op, TypeTupleP param,
	     TypeTupleP result, TableP table)
{
    CCodeItemP item;
    EntryP     entry;

    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_IDENT:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if (((param == NIL(TypeTupleP)) ||
		 (!types_contains(param, entry))) &&
		((result == NIL(TypeTupleP)) ||
		 (!types_contains(result, entry)))) {
		E_bad_id_substitution(c_code_file(code), c_code_line(code),
				      entry);
	    } else if (result) {
		name_used(entry_get_name(entry));
	    }
	    break;
	  case CCT_MOD_IDENT:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if (exceptions) {
		if ((param == NIL(TypeTupleP)) ||
		    (!types_mutated(param, entry))) {
		    E_bad_mod_id_substitution(c_code_file(code),
					      c_code_line(code), entry);
		}
	    } else {
		E_mod_id_in_assign(c_code_file(code), c_code_line(code),
				   entry);
	    }
	    break;
	  case CCT_REF_IDENT:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if (!param_op) {
		if ((param == NIL(TypeTupleP)) ||
		    (!types_contains(param, entry))) {
		    E_bad_ref_id_substitution(c_code_file(code),
					      c_code_line(code), entry);
		}
	    } else {
		E_ref_id_in_param_op(c_code_file(code), c_code_line(code),
				     entry);
	    }
	    break;
	  case CCT_LABEL:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if ((param == NIL(TypeTupleP)) && (result == NIL(TypeTupleP))) {
		E_bad_label_substitution(c_code_file(code),
					 c_code_line(code), entry);
	    }
	    break;
	  case CCT_EXCEPTION:
	    if (!exceptions) {
		E_bad_exception_substitution(c_code_file(code),
					     c_code_line(code));
	    }
	    break;
	  case CCT_ADVANCE:
	    if (!exceptions) {
		E_bad_advance_substitution(c_code_file(code),
					   c_code_line(code));
	    }
	    break;
	  case CCT_TERMINAL:
	    if (!exceptions) {
		E_bad_terminal_substitution(c_code_file(code),
					    c_code_line(code));
	    }
	    break;
	  case CCT_STRING:
	    break;
	}
    }
    if (result) {
	types_check_used(result, E_code_undefined_result, (void *)code);
	for (item = code->head; item; item = item->next) {
	    if (item->type == CCT_IDENT) {
		name_not_used(entry_get_name(item->u.ident));
	    }
	}
    }
    if (param) {
	types_assign(&(code->param), param);
    }
    if (result) {
	types_assign(&(code->result), result);
    }
}

CStringP
c_code_file(CCodeP code)
{
    return(code->file);
}

unsigned
c_code_line(CCodeP code)
{
    return(code->line);
}

TypeTupleP
c_code_param(CCodeP code)
{
    return(&(code->param));
}

TypeTupleP
c_code_result(CCodeP code)
{
    return(&(code->result));
}

void
c_code_deallocate(CCodeP code)
{
    CCodeItemP item = code->head;

    while (item) {
	CCodeItemP next = item->next;

	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    nstring_destroy(&(item->u.string));
	    break;
	  case CCT_IDENT:
	  case CCT_MOD_IDENT:
	  case CCT_REF_IDENT:
	  case CCT_LABEL:
	  case CCT_EXCEPTION:
	  case CCT_TERMINAL:
	  case CCT_ADVANCE:
	    break;
	}
	DEALLOCATE(item);
	item = next;
    }
    types_destroy(&(code->param));
    types_destroy(&(code->result));
    DEALLOCATE(code);
}

void
c_output_c_code_action(COutputInfoP info, CCodeP code, TypeTupleP param,
		       TypeTupleP result, SaveRStackP state,
		       RuleP handler_rule)
{
    OStreamP    ostream      = c_out_info_ostream(info);
    NStringP    label_prefix = c_out_info_label_prefix(info);
    NStringP    in_prefix    = c_out_info_in_prefix(info);
    CCodeItemP  item;
    EntryP      stack_entry;
    EntryP      entry;
    EntryP      stack_type;
    BoolT       stack_reference;
    BoolT       use_cast;
    TypeBTransT translator;

    c_code_set_labels(code);
    btrans_init(&translator);
    btrans_add_translations(&translator, &(code->param), param);
    btrans_add_translations(&translator, &(code->result), result);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    stack_entry = c_code_get_translation(state, &translator,
						 item->u.ident, &stack_type,
						 &stack_reference, &entry);
	    use_cast = (types_contains(param, entry) &&
			c_out_info_get_casts(info));
	    if (use_cast) {
		write_cstring(ostream, "((");
		c_output_mapped_key(info, stack_type);
		write_cstring(ostream, ") (");
	    } else {
		write_char(ostream, '(');
	    }
	    if (stack_reference) {
		write_char(ostream, '*');
	    }
	    c_output_key(info, entry_key(stack_entry), in_prefix);
	    if (use_cast) {
		write_cstring(ostream, "))");
	    } else {
		write_char(ostream, ')');
	    }
	    break;
	  case CCT_MOD_IDENT:
	    stack_entry = c_code_get_translation(state, &translator,
						 item->u.ident, &stack_type,
						 &stack_reference,
						 NIL(EntryP *));
	    write_char(ostream, '(');
	    if (stack_reference) {
		write_char(ostream, '*');
	    }
	    c_output_key(info, entry_key(stack_entry), in_prefix);
	    write_char(ostream, ')');
	    break;
	  case CCT_REF_IDENT:
	    stack_entry = c_code_get_translation(state, &translator,
						 item->u.ident, &stack_type,
						 &stack_reference,
						 NIL(EntryP *));
	    write_char(ostream, '(');
	    if (!stack_reference) {
		write_char(ostream, '&');
	    }
	    c_output_key(info, entry_key(stack_entry), in_prefix);
	    write_char(ostream, ')');
	    break;
	  case CCT_EXCEPTION:
	    write_cstring(ostream, "goto ");
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream, rule_get_handler_label(handler_rule));
	    break;
	  case CCT_ADVANCE:
	    write_cstring(ostream, "ADVANCE_LEXER");
	    break;
	  case CCT_TERMINAL:
	    write_cstring(ostream, "CURRENT_TERMINAL");
	    break;
	}
    }
    btrans_destroy(&translator);
    c_code_reset_labels(code);
}

void
c_output_c_code_basic(COutputInfoP info, CCodeP code, TypeTupleP result,
		      SaveRStackP state)
{
    OStreamP    ostream      = c_out_info_ostream(info);
    NStringP    label_prefix = c_out_info_label_prefix(info);
    NStringP    in_prefix    = c_out_info_in_prefix(info);
    CCodeItemP  item;
    EntryP      stack_entry;
    EntryP      stack_type;
    BoolT       stack_reference;
    TypeBTransT translator;

    c_code_set_labels(code);
    btrans_init(&translator);
    btrans_add_translations(&translator, &(code->result), result);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    stack_entry = c_code_get_translation(state, &translator,
						 item->u.ident, &stack_type,
						 &stack_reference,
						 NIL(EntryP *));
	    c_output_key(info, entry_key(stack_entry), in_prefix);
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_REF_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
    btrans_destroy(&translator);
    c_code_reset_labels(code);
}

void
c_output_c_code_assign(COutputInfoP info, CCodeP code, EntryP type,
		       EntryP from, EntryP to, BoolT from_reference,
		       BoolT to_reference)
{
    OStreamP   ostream      = c_out_info_ostream(info);
    NStringP   label_prefix = c_out_info_label_prefix(info);
    NStringP   in_prefix    = c_out_info_in_prefix(info);
    BoolT      is_param;
    BoolT      use_cast;
    CCodeItemP item;

    c_code_set_labels(code);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    is_param = types_contains(&(code->param), item->u.ident);
	    use_cast = (is_param && c_out_info_get_casts(info));
	    if (use_cast) {
		write_cstring(ostream, "((");
		c_output_mapped_key(info, type);
		write_cstring(ostream, ") (");
	    } else {
		write_char(ostream, '(');
	    }
	    if (is_param) {
		if (from_reference) {
		    write_char(ostream, '*');
		}
		c_output_key(info, entry_key(from), in_prefix);
	    } else {
		if (to_reference) {
		    write_char(ostream, '*');
		}
		c_output_key(info, entry_key(to), in_prefix);
	    }
	    if (use_cast) {
		write_cstring(ostream, "))");
	    } else {
		write_char(ostream, ')');
	    }
	    break;
	  case CCT_REF_IDENT:
	    write_char(ostream, '(');
	    if (!from_reference) {
		write_char(ostream, '&');
	    }
	    c_output_key(info, entry_key(from), in_prefix);
	    write_char(ostream, ')');
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
    c_code_reset_labels(code);
}

void
c_output_c_code_param_assign(COutputInfoP info, CCodeP code, EntryP type,
			     EntryP entry)
{
    OStreamP   ostream      = c_out_info_ostream(info);
    NStringP   label_prefix = c_out_info_label_prefix(info);
    NStringP   in_prefix    = c_out_info_in_prefix(info);
    NStringP   out_prefix   = c_out_info_out_prefix(info);
    CCodeItemP item;

    c_code_set_labels(code);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    if (types_contains(&(code->param), item->u.ident)) {
		BoolT use_cast = c_out_info_get_casts(info);

		if (use_cast) {
		    write_cstring(ostream, "((");
		    c_output_mapped_key(info, type);
		    write_cstring(ostream, " *) (");
		}
		c_output_key(info, entry_key(entry), out_prefix);
		if (use_cast) {
		    write_cstring(ostream, "))");
		}
	    } else {
		c_output_key(info, entry_key(entry), in_prefix);
	    }
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_REF_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
    c_code_reset_labels(code);
}

void
c_output_c_code_result_assign(COutputInfoP info, CCodeP code, EntryP type,
			      EntryP entry)
{
    OStreamP   ostream      = c_out_info_ostream(info);
    NStringP   label_prefix = c_out_info_label_prefix(info);
    NStringP   in_prefix    = c_out_info_in_prefix(info);
    NStringP   out_prefix   = c_out_info_out_prefix(info);
    CCodeItemP item;

    c_code_set_labels(code);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    if (types_contains(&(code->param), item->u.ident)) {
		BoolT use_cast = c_out_info_get_casts(info);

		if (use_cast) {
		    write_cstring(ostream, "((");
		    c_output_mapped_key(info, type);
		    write_cstring(ostream, ") (");
		}
		c_output_key(info, entry_key(entry), in_prefix);
		if (use_cast) {
		    write_cstring(ostream, "))");
		}
	    } else {
		c_output_key(info, entry_key(entry), out_prefix);
	    }
	    break;
	  case CCT_REF_IDENT:
	    write_cstring(ostream, "(&");
	    c_output_key(info, entry_key(entry), in_prefix);
	    write_char(ostream, ')');
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
    c_code_reset_labels(code);
}

void
c_output_c_code(COutputInfoP info, CCodeP code)
{
    OStreamP   ostream = c_out_info_ostream(info);
    CCodeItemP item;

    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	  case CCT_IDENT:
	  case CCT_MOD_IDENT:
	  case CCT_REF_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
