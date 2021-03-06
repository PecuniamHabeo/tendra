/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* dynamic_init.c does all the dynamic initialisation code */

#include <string.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/string.h>

#include <construct/exp.h>
#include <construct/installglob.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "code_here.h"
#include "geninst.h"
#include "translate.h"
#include "make_code.h"
#include "proc.h"
#include "stack.h"
#include "parameter.h"
#include "dynamic_init.h"
#include "locate.h"

int do_dynamic_init;

void do__main_extern(void)
{
  asm_printop(".extern __main");
  asm_printop(".extern .__main");
}

void call__main(void)
{
  asm_printop("bl .__main");
  asm_printop("cror 15,15,15");
}
int proc_is_main(exp e)
{
  baseoff b;
  char *ext;
  b = boff(father(e));
  ext = main_globals[(-b.base)-1]->name;
  if (streq(ext,"main"))
  {
    return 1;
  }
  return 0;
}
