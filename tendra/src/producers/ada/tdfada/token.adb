with Asis;

with States;
with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;
with XASIS.Classes;

package body Token is

   Error : exception;

   ---------------------
   -- Close_Token_Def --
   ---------------------

   procedure Close_Token_Def
     (State : access States.State;
      D     : in out TenDRA.Streams.Memory_Stream;
      Tok   : in     TenDRA.Small)
   is
      use States;
      use TenDRA;
      use TenDRA.Types;
      T     : TenDRA.Streams.Memory_Stream renames State.Units (TOKDEF).all;
   begin
      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Tok);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Close_Token_Def;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize
     (Stream : in out TenDRA.Streams.Memory_Stream;
      Kind   : in     States.Support_Kinds)
   is
      use States;
      use TenDRA;
      use TenDRA.Types;
   begin
      case Kind is
         when Compare_Integer_Value | Compare_Float_Value =>
            Streams.Expect (Stream, Dummy,
                            ((NTEST_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
         when Boolean_Jump =>
            Streams.Expect (Stream, Dummy,
                            ((NAT_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (LABEL_SORT, Singular, False)));
         when Constraint_Error_If =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (LABEL_SORT, Singular, False)));
         when Enum_Succ_Pred_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False),
                             (NAT_SORT, Singular, False)));
         when Signed_Succ_Pred_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False),
                             (NAT_SORT, Singular, False)));
         when Enum_Val_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Signed_Val_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Signed_Base_Lower | Signed_Base_Upper =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Mod_Plus | Mod_Minus | Mod_Multiply
           | Mod_Or | Mod_Xor | Mod_And =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Mod_Power =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Mod_Not | Mod_Negative =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Test_Range_Jump | Float_Test_Range_Jump =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (NAT_SORT, Singular, False),
                             (LABEL_SORT, Singular, False)));
         when Make_Float_Id
           | Make_Small_Attribute =>
            Streams.Expect (Stream, Dummy,
                            (1 => (EXP_SORT, Singular, False)));
         when Make_Float_Range_Id =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
         when Rep_Fv | Rep_Fv_Max_Val
           | Make_Float_Attr =>
            Streams.Expect (Stream, Dummy,
                            (1 => (NAT_SORT, Singular, False)));
         when Make_Float_Attr_1 =>
            Streams.Expect (Stream, Dummy,
                            ((NAT_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
         when Make_Float_Attr_2 =>
            Streams.Expect (Stream, Dummy,
                            ((NAT_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
         when Fixed_Divide | Fixed_Multiply =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),        -- Left
                             (EXP_SORT, Singular, False),        -- Right
                             (VARIETY_SORT, Singular, False),    -- Result
                             (EXP_SORT, Singular, False),        -- L Upper
                             (EXP_SORT, Singular, False),        -- R Upper
                             (EXP_SORT, Singular, False),        -- L Small
                             (EXP_SORT, Singular, False),        -- R Small
                             (EXP_SORT, Singular, False),        -- Small
                             (ERROR_TREATMENT_SORT, Singular, False)));
         when Fixed_To_Float =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),        -- Left
                             (EXP_SORT, Singular, False),        -- L Small
                             (VARIETY_SORT, Singular, False),  -- L Type
                             (FLOATING_VARIETY_SORT, Singular, False),  --  Res
                             (ERROR_TREATMENT_SORT, Singular, False)));
         when Fixed_To_Int | Int_To_Fixed =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),      -- Left
                             (EXP_SORT, Singular, False),      -- L Small
                             (VARIETY_SORT, Singular, False),  -- L Type
                             (VARIETY_SORT, Singular, False),  -- Result
                             (ERROR_TREATMENT_SORT, Singular, False)));
         when Float_To_Fixed =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),      -- Left
                             (EXP_SORT, Singular, False),      -- L Small
                             (FLOATING_VARIETY_SORT, Singular, False),  -- L Tp
                             (VARIETY_SORT, Singular, False),  -- Result
                             (ERROR_TREATMENT_SORT, Singular, False)));
         when Fixed_To_Fixed =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),      -- Left
                             (EXP_SORT, Singular, False),      -- L Small
                             (EXP_SORT, Singular, False),      -- Small
                             (VARIETY_SORT, Singular, False),  -- L Type
                             (VARIETY_SORT, Singular, False),  -- Result
                             (ERROR_TREATMENT_SORT, Singular, False)));
         when In_Bounds | Float_In_Bounds =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
      end case;
   end Initialize;

   ---------------
   -- New_Token --
   ---------------

   procedure New_Token
     (State : access States.State;
      Link  : in     States.Linkage_Access)
   is
      use States;
      use TenDRA;
      use TenDRA.Types;

      Decl : Linkage_Access;
      O    : Streams.Memory_Stream renames State.Units (TOKDEC).all;
   begin
      Link.Usage := Link.Usage or Declared;

      Decl := Find (State, Link.all, TOKDEC);
      Output.TDF (O, c_make_tokdec);
      Output.TDFINT (O, Decl.Unit_Code (TOKDEC));
      Output.No_Option (O);
      Inc (State.Length (TOKDEC));

      case Link.Kind is
         when Shape_Token =>
            Output.TDF (O, c_shape);

         when Variety_Token =>
            if XASIS.Classes.Is_Scalar (Link.Tipe) then
               if XASIS.Classes.Is_Real (Link.Tipe)
                 and not XASIS.Classes.Is_Fixed_Point (Link.Tipe)
               then
                  Output.TDF (O, c_floating_variety);
               else
                  Output.TDF (O, c_variety);
               end if;
            else
               raise Error;
            end if;

         when Name_Token | Value_Token =>
            Output.TDF (O, c_exp);

         when Type_Param_Token =>
            case Link.Param is
               when Float_Id =>
                  Output.TDF (O, c_nat);
               when Lower | Upper | Base_Lower | Base_Upper =>
                  Output.TDF (O, c_exp);
            end case;

         when Support_Token =>
            case Link.Support is
               when Compare_Integer_Value | Compare_Float_Value =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_ntest);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);

               when Boolean_Jump =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_label);

               when Constraint_Error_If =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_label);

               when Enum_Succ_Pred_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 4);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_nat);

               when Signed_Succ_Pred_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_nat);

               when Enum_Val_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 4);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Signed_Val_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Signed_Base_Lower | Signed_Base_Upper =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Mod_Plus | Mod_Minus | Mod_Multiply
                 | Mod_Or | Mod_Xor | Mod_And =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 4);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Mod_Power =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 5);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_variety);

               when Mod_Not | Mod_Negative =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Test_Range_Jump | Float_Test_Range_Jump =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 5);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_label);

               when Make_Float_Id =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_nat);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_exp);

               when Make_Float_Range_Id =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_nat);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);

               when Rep_Fv =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_floating_variety);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_nat);

               when Rep_Fv_Max_Val | Make_Float_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_nat);

               when Make_Float_Attr_1 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_exp);

               when Make_Float_Attr_2 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);

               when Make_Small_Attribute =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_exp);

               when Fixed_Divide | Fixed_Multiply =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 9);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_error_treatment);
               when Fixed_To_Float =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 5);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_floating_variety);
                  Output.TDF (O, c_error_treatment);
               when Fixed_To_Int | Int_To_Fixed =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 5);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_error_treatment);
               when Float_To_Fixed =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 5);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_floating_variety);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_error_treatment);
               when Fixed_To_Fixed =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 6);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_error_treatment);
               when In_Bounds | Float_In_Bounds =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
            end case;

         when Subtype_Attribute_Token =>
            case Link.Attribute is
               when Asis.A_First_Attribute
                 | Asis.A_Last_Attribute
                 | Asis.A_Succ_Attribute
                 | Asis.A_Pred_Attribute
                 | Asis.A_Pos_Attribute
                 | Asis.A_Val_Attribute
                 | Asis.A_Ceiling_Attribute
                 | Asis.A_Floor_Attribute
                 | Asis.A_Rounding_Attribute
                 | Asis.A_Truncation_Attribute
                 | Asis.An_Unbiased_Rounding_Attribute
                 | Asis.An_Exponent_Attribute
                 | Asis.A_Fraction_Attribute
                 | Asis.A_Machine_Attribute
                 | Asis.A_Model_Attribute
                 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_exp);
               when Asis.A_Min_Attribute
                 | Asis.A_Max_Attribute
                 | Asis.An_Adjacent_Attribute
                 | Asis.A_Copy_Sign_Attribute
                 | Asis.A_Remainder_Attribute
                 | Asis.A_Leading_Part_Attribute
                 | Asis.A_Compose_Attribute
                 | Asis.A_Scaling_Attribute
                 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
               when Asis.A_Modulus_Attribute
                 | Asis.A_Delta_Attribute
                 | Asis.A_Denorm_Attribute
                 | Asis.A_Machine_Emax_Attribute
                 | Asis.A_Machine_Emin_Attribute
                 | Asis.A_Machine_Mantissa_Attribute
                 | Asis.A_Machine_Overflows_Attribute
                 | Asis.A_Machine_Radix_Attribute
                 | Asis.A_Machine_Rounds_Attribute
                 | Asis.A_Max_Size_In_Storage_Elements_Attribute
                 | Asis.A_Model_Emin_Attribute
                 | Asis.A_Model_Epsilon_Attribute
                 | Asis.A_Model_Mantissa_Attribute
                 | Asis.A_Model_Small_Attribute
                 | Asis.A_Safe_First_Attribute
                 | Asis.A_Safe_Last_Attribute
                 | Asis.A_Signed_Zeros_Attribute
                 | Asis.A_Small_Attribute
                 =>
                  Output.TDF (O, c_exp);
               when others =>
                  raise States.Error;
            end case;
         when Tag | Proc_Tag | Subtype_Attribute_Tag =>
            null;
      end case;
   end New_Token;

   --------------------
   -- Open_Token_Def --
   --------------------

   procedure Open_Token_Def
     (State  : access States.State;
      D      : in out TenDRA.Streams.Memory_Stream;
      Result : in     TenDRA.Types.Construct := TenDRA.Types.c_exp)
   is
      Args  : Arg_List (1 .. 0);
      Types : Arg_Types (1 .. 0);
   begin
      Open_Token_Def (State, D, Args, Types, Result);
   end Open_Token_Def;

   --------------------
   -- Open_Token_Def --
   --------------------

   procedure Open_Token_Def
     (State  : access States.State;
      D      : in out TenDRA.Streams.Memory_Stream;
      Args   :    out Arg_List;
      Types  : in     Arg_Types;
      Result : in     TenDRA.Types.Construct := TenDRA.Types.c_exp)
   is
      use States;
      use TenDRA;
      use TenDRA.Types;

      function To_Sort (C : Construct) return Sort_Kind is
      begin
         case C is
            when c_exp =>
               return EXP_SORT;
            when c_floating_variety =>
               return FLOATING_VARIETY_SORT;
            when c_variety =>
               return VARIETY_SORT;
            when c_nat =>
               return NAT_SORT;
            when c_shape =>
               return SHAPE_SORT;
            when others =>
               raise States.Error;
         end case;
      end To_Sort;

      Kind : constant Sort_Kind := To_Sort (Result);
   begin
      for J in Args'Range loop
         Args (J) := State.Unit_Total (TOKDEF, States.Token);
         Inc (State.Unit_Total (TOKDEF, States.Token));
      end loop;

      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (Kind, Singular, False)));

      Output.TDF (D, c_token_definition);
      Output.TDF (D, Result);
      Output.List_Count (D, Args'Length);

      for J in Args'Range loop
         Output.TDF (D, c_make_tokformals);
         Output.TDF (D, Types (J));
         Output.TDFINT (D, Args (J));
      end loop;
   end Open_Token_Def;

end Token;


------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------