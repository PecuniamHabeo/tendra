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


#include <stddef.h>

#include "list.h"
#include "utility.h"


/*
 * SPARE LISTS
 *
 * This is a list of list structures which have been freed using free_list.
 * new_list tries to allocate new list structures from this list before using
 * its internal array.
 */
static list *spare_lists = NULL;


/*
 * CREATE A NEW LIST
 *
 * This routine allocates a new list structure.
 */
static list *
new_list(void)
{
	static int no_free = 0;
	static list *free_objs = NULL;

	if (spare_lists) {
		list *p = spare_lists;
		spare_lists = p->next;

		return (p);
	}

	if (no_free == 0) {
		no_free = 1000;
		free_objs = alloc_nof(list, no_free);
	}

	return (free_objs + (--no_free));
}


/*
 * FREE A LIST
 *
 * This list returns p to free.
 */
void
free_list(list *p)
{
	spare_lists = add_list(p, spare_lists);
}


/*
 * JOIN TWO LISTS
 *
 * This routine joins two lists, p and q, and returns the result.
 */
list *
add_list(list *p, list *q)
{
	list *r;

	if (p == NULL)
		return (q);

	if (q == NULL)
		return (p);

	for (r = p; r->next != NULL; r = r->next)
		;

	r->next = q;
	return (p);
}


/*
 * ADD AN ITEM TO A LIST
 *
 * This routine adds a new item, s, to the end of the list p and returns the
 * result.
 * XXX: better name?
 */
list *
add_item(list *p, char *s)
{
	list *q;

	q = new_list();
	q->item.s = s;
	q->next = NULL;

	return (add_list(p, q));
}


/*
 * INSERT AN ITEM INTO A LIST
 *
 * This routine adds a new item, s, to the start of the list p and returns the
 * result.
 * TODO argument order inconsistent against add_item()
 * XXX: better name?
 */
list *
insert_item(char *s, list *p)
{
	list *q;

	q = new_list();
	q->item.s = s;
	q->next = NULL;

	return (add_list(q, p));
}


/*
 * Insert a command item in ascending order, based on their rank. Items with a
 * lower rank value are executed first.
 */
list*
insert_inorder(ordered_node* indata, list *inlst)
{
	list *head = inlst;
	list *curr = inlst;
	list *newlst  = new_list();
	list *prev = newlst;

	newlst->item.on = indata;
	newlst->next = NULL;

	if (inlst == NULL)
	        return (newlst);

	if (indata->rank < curr->item.on->rank) {
	        newlst->next = inlst;
	        return (newlst);
	}

	while (curr != NULL &&
	           curr->item.on->rank <= indata->rank) {
	        prev = curr;
	        curr = curr->next;
	}

	prev->next = newlst;
	newlst->next = curr;

	return (head);
}


/*
 * CONVERT A STRING TO A LIST
 *
 * This routine converts a string to a list by breaking it at all white spaces
 * (spaces and tabs).
 */
list *
make_list(char *s)
{
	list *r = NULL;
	char *p = string_copy(s);

	for (;;) {
		while (*p == ' ' || *p == '\t')
			*(p++) = '\0';

		if (*p == '\0')
			break;

		r = add_item(r, p);

		while (*p && *p != ' ' && *p != '\t')
			p++;
	}

	return (r);
}
