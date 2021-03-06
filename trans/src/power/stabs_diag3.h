/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DIAGOUT_H
#define DIAGOUT_H	1

#include <reader/exp.h>

#include <construct/installtypes.h>

extern void init_diag(void);
extern void fixup_name(exp , dec * , dec *);
extern void stab_bs(char *);
extern void stab_es(char *);
extern void stab_endproc(exp , char *, bool);
extern void output_diag_tags(void);
extern void stab_end_file(void);

#endif				/* DIAGOUT_H */
