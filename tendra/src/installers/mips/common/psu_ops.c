/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/* psu_ops.c
 *	Output various pseudo operations to assembler
 */

#include "config.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "psu_ops.h"

extern  FILE * as_file;


void
setnoreorder()
{
	if (as_file)
		fprintf (as_file, "\t.set\tnoreorder\n");
	out_value (0, iset, set_noreorder, 0);
}

void
setreorder()
{
	if (as_file)
		fprintf (as_file, "\t.set\treorder\n");
	out_value (0, iset, set_reorder, 0);
}

void
setnomove()
{
	if (as_file)
		fprintf (as_file, "\t.set\tnomove\n");
	out_value (0, iset, set_nomove, 0);
}

void
setmove()
{
	if (as_file)
		fprintf (as_file, "\t.set\tmove\n");
	out_value (0, iset, set_move, 0);
}

void
setvolatile()
{
	if (as_file)
		fprintf (as_file, "\t.set\tvolatile\n");
	out_value (0, iset, set_volatile, 0);
}

void
setnovolatile()
{
	if (as_file)
		fprintf (as_file, "\t.set\tnovolatile\n");
	out_value (0, iset, set_novolatile, 0);
}

void
setnoat()
{
	if (as_file)
		fprintf (as_file, "\t.set\tnoat\n");
	out_value (0, iset, set_noat, 0);
}

void
setat()
{
	if (as_file)
		fprintf (as_file, "\t.set\tat\n");
	out_value (0, iset, set_at, 0);
}

void
comment(char *mess)
{
	if (as_file)
		fprintf (as_file, " ## %s\n", mess);
}

void
setframe(long st)
{
	if (as_file)
		fprintf (as_file, "\t.frame\t$sp, %ld, $31\n", st);
	out_frame (0, iframe, st, 29, 31);
}

void
settext()
{
	if (as_file)
		fprintf (as_file, "\t.text\n");
	out_common (0, itext);
}

void
setmask(long mask, long disp)
{
	if (as_file)
		fprintf (as_file, "\t.mask\t0x%lx,%ld\n", mask, disp);
	out_mask (0, imask, mask, disp);
}

void
setfmask(long mask, long disp)
{
	if (as_file)
		fprintf (as_file, "\t.fmask\t0x%lx,%ld\n", mask, disp);
	out_mask (0, ifmask, mask, disp);
}