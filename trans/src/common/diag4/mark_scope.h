/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef mark_scope_key
#define mark_scope_key 1

extern void mark_scope(exp e);
extern bool doing_mark_scope;
extern void correct_mark_scope(exp e);
extern void mark_scope2(exp e);

#endif
