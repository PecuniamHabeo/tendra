/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* AUTOMATICALLY GENERATED BY make_tdf VERSION 2.0 FROM TDF 4.0 */

#include <stdio.h>

#include "consfile.h"
#include "defs.h"
#include "syntax.h"

/*
 * The table is sorted by piping it through consfile.awk:
 *
 * $ make_tdf=$TENDRA/make_tdf/obj/src/make_tdf
 * $ db=$TENDRA/tdf/db/def_4_0.db
 * $ cd $TENDRA/tpl/src
 * $ $make_tdf $db templ/consfile.c - | awk -f templ/consfile.awk > consfile.c
 *
 */

Constructs constructs [] = {
/* lines below | LC_ALL=C sort */
{ "abs", exp_t, c_abs },
{ "add_accesses", access_t, c_add_accesses },
{ "add_modes", transfer_mode_t, c_add_modes },
{ "add_to_ptr", exp_t, c_add_to_ptr },
{ "alignment", alignment_t, c_alignment },
{ "alloca_alignment", alignment_t, c_alloca_alignment },
{ "and", exp_t, c_and },
{ "assign", exp_t, c_assign },
{ "assign_with_mode", exp_t, c_assign_with_mode },
{ "bfvar_bits", bitfield_variety_t, c_bfvar_bits },
{ "bitfield", shape_t, c_bitfield },
{ "bitfield_assign", exp_t, c_bitfield_assign },
{ "bitfield_assign_with_mode", exp_t, c_bitfield_assign_with_mode },
{ "bitfield_contents", exp_t, c_bitfield_contents },
{ "bitfield_contents_with_mode", exp_t, c_bitfield_contents_with_mode },
{ "bottom", shape_t, c_bottom },
{ "callees_alignment", alignment_t, c_callees_alignment },
{ "callers_alignment", alignment_t, c_callers_alignment },
{ "change_bitfield_to_int", exp_t, c_change_bitfield_to_int },
{ "change_floating_variety", exp_t, c_change_floating_variety },
{ "change_int_to_bitfield", exp_t, c_change_int_to_bitfield },
{ "change_variety", exp_t, c_change_variety },
{ "code_alignment", alignment_t, c_code_alignment },
{ "comparable", ntest_t, c_comparable },
{ "complete", transfer_mode_t, c_complete },
{ "complex_conjugate", exp_t, c_complex_conjugate },
{ "complex_of_float", floating_variety_t, c_complex_of_float },
{ "complex_parms", floating_variety_t, c_complex_parms },
{ "component", exp_t, c_component },
{ "compound", shape_t, c_compound },
{ "computed_nat", nat_t, c_computed_nat },
{ "computed_signed_nat", signed_nat_t, c_computed_signed_nat },
{ "concat_nof", exp_t, c_concat_nof },
{ "conditional", exp_t, c_conditional },
{ "constant", access_t, c_constant },
{ "contents", exp_t, c_contents },
{ "contents_with_mode", exp_t, c_contents_with_mode },
{ "continue", error_treatment_t, c_continue },
{ "current_env", exp_t, c_current_env },
{ "div0", exp_t, c_div0 },
{ "div1", exp_t, c_div1 },
{ "div2", exp_t, c_div2 },
{ "env_offset", exp_t, c_env_offset },
{ "env_size", exp_t, c_env_size },
{ "equal", ntest_t, c_equal },
{ "error_val", nat_t, c_error_val },
{ "fail_installer", exp_t, c_fail_installer },
{ "false", bool_t, c_false },
{ "float_int", exp_t, c_float_int },
{ "float_of_complex", floating_variety_t, c_float_of_complex },
{ "floating", shape_t, c_floating },
{ "floating_abs", exp_t, c_floating_abs },
{ "floating_div", exp_t, c_floating_div },
{ "floating_maximum", exp_t, c_floating_maximum },
{ "floating_minimum", exp_t, c_floating_minimum },
{ "floating_minus", exp_t, c_floating_minus },
{ "floating_mult", exp_t, c_floating_mult },
{ "floating_negate", exp_t, c_floating_negate },
{ "floating_plus", exp_t, c_floating_plus },
{ "floating_power", exp_t, c_floating_power },
{ "floating_test", exp_t, c_floating_test },
{ "flvar_parms", floating_variety_t, c_flvar_parms },
{ "goto", exp_t, c_goto },
{ "goto_local_lv", exp_t, c_goto_local_lv },
{ "greater_than", ntest_t, c_greater_than },
{ "greater_than_or_equal", ntest_t, c_greater_than_or_equal },
{ "ignorable", exp_t, c_ignorable },
{ "imaginary_part", exp_t, c_imaginary_part },
{ "impossible", error_treatment_t, c_impossible },
{ "initial_value", exp_t, c_initial_value },
{ "integer", shape_t, c_integer },
{ "integer_test", exp_t, c_integer_test },
{ "last_local", exp_t, c_last_local },
{ "less_than", ntest_t, c_less_than },
{ "less_than_or_equal", ntest_t, c_less_than_or_equal },
{ "less_than_or_greater_than", ntest_t, c_less_than_or_greater_than },
{ "local_alloc", exp_t, c_local_alloc },
{ "local_alloc_check", exp_t, c_local_alloc_check },
{ "local_free", exp_t, c_local_free },
{ "local_free_all", exp_t, c_local_free_all },
{ "locals_alignment", alignment_t, c_locals_alignment },
{ "long_jump", exp_t, c_long_jump },
{ "long_jump_access", access_t, c_long_jump_access },
{ "make_complex", exp_t, c_make_complex },
{ "make_compound", exp_t, c_make_compound },
{ "make_local_lv", exp_t, c_make_local_lv },
{ "make_nof", exp_t, c_make_nof },
{ "make_nof_int", exp_t, c_make_nof_int },
{ "make_null_local_lv", exp_t, c_make_null_local_lv },
{ "make_null_proc", exp_t, c_make_null_proc },
{ "make_null_ptr", exp_t, c_make_null_ptr },
{ "make_signed_nat", signed_nat_t, c_make_signed_nat },
{ "make_stack_limit", exp_t, c_make_stack_limit },
{ "make_top", exp_t, c_make_top },
{ "make_value", exp_t, c_make_value },
{ "maximum", exp_t, c_maximum },
{ "minimum", exp_t, c_minimum },
{ "minus", exp_t, c_minus },
{ "move_some", exp_t, c_move_some },
{ "mult", exp_t, c_mult },
{ "n_copies", exp_t, c_n_copies },
{ "negate", exp_t, c_negate },
{ "nil_access", error_code_t, c_nil_access },
{ "no_other_read", access_t, c_no_other_read },
{ "no_other_write", access_t, c_no_other_write },
{ "nof", shape_t, c_nof },
{ "not", exp_t, c_not },
{ "not_comparable", ntest_t, c_not_comparable },
{ "not_equal", ntest_t, c_not_equal },
{ "not_greater_than", ntest_t, c_not_greater_than },
{ "not_greater_than_or_equal", ntest_t, c_not_greater_than_or_equal },
{ "not_less_than", ntest_t, c_not_less_than },
{ "not_less_than_and_not_greater_than", ntest_t, c_not_less_than_and_not_greater_than },
{ "not_less_than_or_equal", ntest_t, c_not_less_than_or_equal },
{ "offset", shape_t, c_offset },
{ "offset_add", exp_t, c_offset_add },
{ "offset_div", exp_t, c_offset_div },
{ "offset_div_by_int", exp_t, c_offset_div_by_int },
{ "offset_max", exp_t, c_offset_max },
{ "offset_mult", exp_t, c_offset_mult },
{ "offset_negate", exp_t, c_offset_negate },
{ "offset_pad", exp_t, c_offset_pad },
{ "offset_subtract", exp_t, c_offset_subtract },
{ "offset_test", exp_t, c_offset_test },
{ "offset_zero", exp_t, c_offset_zero },
{ "or", exp_t, c_or },
{ "out_par", access_t, c_out_par },
{ "overflow", error_code_t, c_overflow },
{ "overlap", transfer_mode_t, c_overlap },
{ "parameter_alignment", alignment_t, c_parameter_alignment },
{ "plus", exp_t, c_plus },
{ "pointer", shape_t, c_pointer },
{ "pointer_test", exp_t, c_pointer_test },
{ "power", exp_t, c_power },
{ "preserve", access_t, c_preserve },
{ "proc", shape_t, c_proc },
{ "proc_test", exp_t, c_proc_test },
{ "profile", exp_t, c_profile },
{ "real_part", exp_t, c_real_part },
{ "register", access_t, c_register },
{ "rem0", exp_t, c_rem0 },
{ "rem1", exp_t, c_rem1 },
{ "rem2", exp_t, c_rem2 },
{ "repeat", exp_t, c_repeat },
{ "return", exp_t, c_return },
{ "return_to_label", exp_t, c_return_to_label },
{ "rotate_left", exp_t, c_rotate_left },
{ "rotate_right", exp_t, c_rotate_right },
{ "round_as_state", rounding_mode_t, c_round_as_state },
{ "round_with_mode", exp_t, c_round_with_mode },
{ "set_stack_limit", exp_t, c_set_stack_limit },
{ "shape_offset", exp_t, c_shape_offset },
{ "shift_left", exp_t, c_shift_left },
{ "shift_right", exp_t, c_shift_right },
{ "snat_from_nat", signed_nat_t, c_snat_from_nat },
{ "stack_overflow", error_code_t, c_stack_overflow },
{ "standard_access", access_t, c_standard_access },
{ "standard_transfer_mode", transfer_mode_t, c_standard_transfer_mode },
{ "subtract_ptrs", exp_t, c_subtract_ptrs },
{ "to_nearest", rounding_mode_t, c_to_nearest },
{ "top", shape_t, c_top },
{ "toward_larger", rounding_mode_t, c_toward_larger },
{ "toward_smaller", rounding_mode_t, c_toward_smaller },
{ "toward_zero", rounding_mode_t, c_toward_zero },
{ "trap", error_treatment_t, c_trap },
{ "trap_on_nil", transfer_mode_t, c_trap_on_nil },
{ "true", bool_t, c_true },
{ "unite_alignments", alignment_t, c_unite_alignments },
{ "untidy_return", exp_t, c_untidy_return },
{ "used_as_volatile", access_t, c_used_as_volatile },
{ "var_limits", variety_t, c_var_limits },
{ "var_param_alignment", alignment_t, c_var_param_alignment },
{ "var_width", variety_t, c_var_width },
{ "visible", access_t, c_visible },
{ "volatile", transfer_mode_t, c_volatile },
{ "wrap", error_treatment_t, c_wrap },
{ "xor", exp_t, c_xor },
/* lines above | LC_ALL=C sort */
} ;
