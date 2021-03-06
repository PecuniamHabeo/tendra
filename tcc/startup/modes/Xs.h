/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * STARTUP FILE FOR COMPILATION MODE XS
 *
 * Xs represents ANSI compliance plus strict extra checks.
 * Your code is going to have to be pretty good to get through this!
 */

#pragma TenDRA declaration block Xs__startup begin
#pragma TenDRA begin

#pragma TenDRA complete struct/union analysis warning
#pragma TenDRA conversion analysis (int-int implicit) warning
#pragma TenDRA conversion analysis (int-pointer explicit) warning
#pragma TenDRA conversion analysis (pointer-pointer explicit) warning
#pragma TenDRA discard analysis warning
#pragma TenDRA fall into case warning
#pragma TenDRA function pointer as pointer disallow
#pragma TenDRA implicit function declaration off
#pragma TenDRA implicit int type for function return disallow
#pragma TenDRA incompatible interface declaration disallow
#pragma TenDRA incompatible void return warning
#pragma TenDRA unreachable code warning
#pragma TenDRA variable analysis warning
#pragma TenDRA weak prototype analysis on

#pragma TenDRA linkage resolution : (internal) warning

#pragma TenDRA no external declaration disallow
#pragma TenDRA unknown pragma warning

#pragma TenDRA indented # directive warning

#pragma TenDRA unmatched quote warning
#pragma TenDRA incompatible linkage warning
#pragma TenDRA writeable string literal warning

/* Additional checks set to warn */

#pragma TenDRA assignment as bool warning
#pragma TenDRA const conditional warning
#pragma TenDRA directive as macro argument warning
#pragma TenDRA enum switch analysis warning
#pragma TenDRA extra ; after conditional warning
#pragma TenDRA integer operator analysis warning
#pragma TenDRA integer overflow analysis warning
#pragma TenDRA nested comment analysis warning
#pragma TenDRA operator precedence analysis warning
#pragma TenDRA unify incompatible string literal warning
#pragma TenDRA variable hiding analysis warning

#pragma TenDRA declaration block end

