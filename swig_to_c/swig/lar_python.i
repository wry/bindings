%module Lar

%include <stdint.i>

%{
    #include "larc.h"
%}

// %typemap(in) char** (char* tmp) %{
//     $1 = &tmp;
// %}

// %typemap(argout) char** (PyObject* obj) %{
//     obj = PyUnicode_FromString(*$1);
//     $result = SWIG_Python_AppendOutput($result,obj);
// %}

// %typemap(freearg) char** %{
//     if (*$1 != NULL)
//     {
//         free(*$1);
//     }
// %}

%include <cstring.i>
%cstring_output_allocate(char **error, free(*$1));

%include "larc.h"
