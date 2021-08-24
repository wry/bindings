%module Lar

%include <stdint.i>

%{
    #include "larc.h"
%}

%inline %{
    struct Result
    {
        Release * result;
        char * error;
    };

    Result Lar_first_release_item_ex(Lar * lar, const char * path)
    {
        Result result = {};
        char *error = NULL;
        result.result = Lar_first_release_item(lar, path, &error);
        result.error = error;
        return result;
    }
%}

// %typemap(in) char**error (char* tmp) %{
//     $1 = &tmp;
// %}

// %typemap(argout) char**error (PyObject* obj) %{
//     obj = PyUnicode_FromString(*$1);
//     $result = SWIG_Python_AppendOutput($result,obj);
// %}

// %typemap(freearg) char *error %{
//     if (*$1 != NULL)
//     {
//         free(*$1);
//     }
// %}

%include "larc.h"
