/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/getopt.h>
#include <shared/error.h>

#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/readglob.h>

#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/exp.h>

#include <flpt/flpt.h>

#include <symtab/cross_config.h>
#include <symtab/symtab.h>
#include <symtab/symconst.h>
#include <symtab/new_symbol.h>

#include <main/driver.h>
#include <main/flags.h>

#include "make_code.h"
#include "inst_fmt.h"

#define VERSION_STR "2.4.11"

static bool produce_binasm = false;

long currentfile = -1;
long mainfile=0;
int majorno = 3;
int minorno = 11;

static void
init(void)
{
	endian    = ENDIAN_LITTLE;
	assembler = ASM_GAS;
	format    = FORMAT_ELF;
	diag      = DIAG_NONE;
	cconv     = CCONV_ALPHA;
	abi       = ABI_OSF1;

	target_dbl_maxexp = 308;
	redo_structfns    = true;
	promote_pars      = false;
	do_alloca         = false;
#if DO_NEW_DIVISION
	use_umulh_for_div = 1;
#else
	use_umulh_for_div = 0;
#endif

	local_prefix = "$$";
	name_prefix  = "";
}

static int
option(char c, const char *optarg)
{
	switch (c) {
	case 'u': use_umulh_for_div = 1; break;
	case 's': produce_binasm = true; break;
	case 'd':
		/* handle IEEE denormals */
		treat_denorm_specially = true;

		switch (atoi(optarg)) {
		case 0:
			/* replace denormal const with 0.0 (don't do this) */
			error(ERR_WARN, "Unsupported denormal switch");
			fail_with_denormal_constant = false;
			break;

		case 1:
			/* error if denormal const is encountered */
			fail_with_denormal_constant = true;
			break;

		case 2:
			/*
			 * Handle denormals properly (and slowly), by stopping the
			 * interleaving of floating point operations and using the
			 * OS exception handler
			 */
			treat_denorm_specially = false;
			trap_all_fops = true;
			break;

		default:
			return -1;
		}
	}

	return 0;
}

static void
unhas(void)
{
	/* Things trans.alpha does not "has" */
	has &= ~HAS_BYTEOPS;
	has &= ~HAS_BYTEREGS;
	has &= ~HAS_NEGSHIFT;
	has &= ~HAS_ROTATE;
	has &= ~HAS_MAXMIN;
	has &= ~HAS_CONDASSIGN;
	has &= ~HAS_DIV0;
	has &= ~HAS_SETCC;
	has &= ~HAS_COMPLEX;

	/* This does not work on the alpha */
	optim &= ~OPTIM_CASE;

	if (PIC_code) {
		error(ERR_FATAL, "no PIC code available");
	}
}

static void
symtab(void)
{
	output_symtab(st_file);
}

static void
binasm(void)
{
	/* handled during translation */
}

static void
cleanup(void)
{
}

struct driver driver = {
	VERSION_STR,

	init,
	unhas,
	symtab,
	binasm,
	cleanup,

	"sud:",
	option,
	NULL,

	local_translate_capsule,

	ABI_OSF1,
	CCONV_ALPHA,
	ENDIAN_BIG | ENDIAN_LITTLE,
	FORMAT_ELF,
	DIAG_NONE | DIAG_STABS,
	ASM_OSF1 | ASM_GAS
};

