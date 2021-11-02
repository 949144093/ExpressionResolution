%module ExpressionResolution
%include<windows.i>
%include "std_string.i"
%include "std_vector.i"
namespace std {
   %template(VectorString) vector<string>;
   %template(VectorDouble) vector<double>;
};
%{
#include "CallFunction.h"
#include "FunctionParaSettings.h"
%}

%include "CallFunction.h"
%include "FunctionParaSettings.h"
