// Filename: parameterRemapBasicStringToString.C
// Created by:  drose (09Aug00)
// 
////////////////////////////////////////////////////////////////////

#include "parameterRemapBasicStringToString.h"
#include "wrapperBuilder.h"

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapBasicStringToString::Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
ParameterRemapBasicStringToString::
ParameterRemapBasicStringToString(CPPType *orig_type) :
  ParameterRemapToString(orig_type)
{
}

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapBasicStringToString::pass_parameter
//       Access: Public, Virtual
//  Description: Outputs an expression that converts the indicated
//               variable from the original type to the new type, for
//               passing into the actual C++ function.
////////////////////////////////////////////////////////////////////
void ParameterRemapBasicStringToString::
pass_parameter(ostream &out, const string &variable_name) {
  out << variable_name;
}

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapBasicStringToString::prepare_return_expr
//       Access: Public, Virtual
//  Description: This will be called immediately before
//               get_return_expr().  It outputs whatever lines the
//               remapper needs to the function to set up its return
//               value, e.g. to declare a temporary variable or
//               something.  It should return the modified expression.
////////////////////////////////////////////////////////////////////
string ParameterRemapBasicStringToString::
prepare_return_expr(ostream &out, int indent_level, const string &expression) {
  WrapperBuilder::indent(out, indent_level)
    << "static basic_string<char> string_holder = " << expression << ";\n";
  return "string_holder";
}

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapBasicStringToString::get_return_expr
//       Access: Public, Virtual
//  Description: Returns an expression that evalutes to the
//               appropriate value type for returning from the
//               function, given an expression of the original type.
////////////////////////////////////////////////////////////////////
string ParameterRemapBasicStringToString::
get_return_expr(const string &expression) {
  return "string_holder.c_str()";
}
