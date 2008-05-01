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
 * bitvec.c - Bit vector manipulation.
 *
 * This file implements the bit vector manipulation routines specified in
 * "bitvec.h".  See that file for more details.
 */

#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>
#include <exds/bitvec.h>
#include <exds/dalloc.h>

/*
 * XXX These need to move into some ctx struct
 */
static unsigned		bitvec_size;
static unsigned		bitvec_valid_bits;
static uint8_t		bitvec_mask;

#define NUM_BITS ((unsigned) CHAR_BIT)

void
bitvec_set_size(unsigned size)
{
	bitvec_valid_bits = size;
	bitvec_size       = (size + NUM_BITS - (unsigned) 1) / NUM_BITS;
	bitvec_mask       = 0;

	if (size % NUM_BITS) {
		unsigned i;
		unsigned mask = 0;

		for (i = (NUM_BITS - (size % NUM_BITS)); i; i--) {
			mask >>= 1;
			mask  |= (unsigned) 1 << (NUM_BITS - (unsigned) 1);
		}
		bitvec_mask = (uint8_t) mask;
	}
	bitvec_mask = ~bitvec_mask;
}

void
bitvec_init(BitVecT *bitvec)
{
	bitvec->bits = ALLOCATE_VECTOR(uint8_t, bitvec_size);
}

void
bitvec_copy(BitVecT *to, BitVecT *from)
{
	to->bits = ALLOCATE_VECTOR(uint8_t, bitvec_size);
	(void) memcpy(to->bits, from->bits, (size_t) bitvec_size);
}

void
bitvec_replace(BitVecT *to, BitVecT *from)
{
	(void) memcpy(to->bits, from->bits, (size_t) bitvec_size);
}

void
bitvec_empty(BitVecT *bitvec)
{
	(void) memset(bitvec->bits, 0, (size_t) bitvec_size);
}

BoolT
bitvec_is_empty(BitVecT *bitvec)
{
	uint8_t *bitvec_bits = bitvec->bits;
	unsigned bytes       = bitvec_size;

	while (bytes--) {
		if (*bitvec_bits++) {
			return FALSE;
		}
	}

	return TRUE;
}

BoolT
bitvec_is_full(BitVecT *bitvec)
{
	uint8_t *bitvec_bits = bitvec->bits;
	unsigned bytes       = bitvec_size;

	while (bytes--) {
		uint8_t byte = *bitvec_bits++;

		if (bytes == 0) {
			byte |= (uint8_t) ~bitvec_mask;
		}
		byte = ~byte;
		if (byte) {
			return FALSE;
		}
	}

	return TRUE;
}

void
bitvec_set(BitVecT *bitvec, unsigned bit)
{
	assert(bit < bitvec_valid_bits);
	bitvec->bits[bit / NUM_BITS] |= (uint8_t) (1 << (bit % NUM_BITS));
}

BoolT
bitvec_is_set(BitVecT *bitvec, unsigned bit)
{
    assert(bit < bitvec_valid_bits);
	/* XXX check cast and parenthesis wrt bitvec_set() */
    return bitvec->bits[bit / NUM_BITS] & ((uint8_t) 1 << (bit % NUM_BITS));
}

void
bitvec_or(BitVecT *to, BitVecT *from)
{
	uint8_t *to_bits   = to->bits;
	uint8_t *from_bits = from->bits;
	unsigned bytes     = bitvec_size;

	while (bytes--) {
		*to_bits++ |= *from_bits++;
	}
}

void
bitvec_and(BitVecT *to, BitVecT *from)
{
	uint8_t *to_bits   = to->bits;
	uint8_t *from_bits = from->bits;
	unsigned bytes     = bitvec_size;

	while (bytes--) {
		*to_bits++ &= *from_bits++;
	}
}

void
bitvec_not(BitVecT *to)
{
	uint8_t *to_bits = to->bits;
	unsigned bytes   = bitvec_size;

	while (bytes--) {
		*to_bits = ~(*to_bits);
		to_bits++;
	}
	to->bits[bitvec_size - 1] &= bitvec_mask;
}

BoolT
bitvec_equal(BitVecT *bitvec1, BitVecT *bitvec2)
{
	uint8_t *bitvec1_bits = bitvec1->bits;
	uint8_t *bitvec2_bits = bitvec2->bits;
	unsigned bytes        = bitvec_size;

	while (bytes--) {
		if (*bitvec1_bits++ != *bitvec2_bits++) {
			return FALSE;
		}
	}

	return TRUE;
}

BoolT
bitvec_intersects(BitVecT *bitvec1, BitVecT *bitvec2)
{
	uint8_t *bitvec1_bits = bitvec1->bits;
	uint8_t *bitvec2_bits = bitvec2->bits;
	unsigned bytes        = bitvec_size;

	while (bytes--) {
		if (*bitvec1_bits++ & *bitvec2_bits++) {
			return TRUE;
		}
	}

	return FALSE;
}

unsigned
bitvec_num_bits(BitVecT *bitvec)
{
	unsigned i;
	unsigned num_bits = 0;

	/*
	 * There's a much niftier way to find the next bit set, if this ever needs
	 * optimising.
	 */
	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			num_bits++;
		}
	}

	return num_bits;
}

unsigned
bitvec_first_bit(BitVecT *bitvec)
{
	unsigned i;

	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			return i;
		}
	}

	return bitvec_valid_bits;
}

BoolT
bitvec_next_bit(BitVecT *bitvec, unsigned *next_ref)
{
	unsigned i;

	for (i = *next_ref + 1; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			*next_ref = i;
			return TRUE;
		}
	}

	return FALSE;
}

void
bitvec_destroy(BitVecT *bitvec)
{
	DEALLOCATE(bitvec->bits);
}

void
write_bitvec_indices(OStreamT *ostream, BitVecT *bitvec)
{
	unsigned num_bits_set = 0;
	unsigned i;

	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			num_bits_set++;
		}
	}

	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			write_unsigned(ostream, i);
			num_bits_set--;
			if (num_bits_set == 1) {
				write_cstring(ostream, " & ");
			} else if (num_bits_set != 0) {
				write_cstring(ostream, ", ");
			}
		}
	}
}
