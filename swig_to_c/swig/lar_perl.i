%module Lar

%include <stdint.i>

%{
    #include "larc.h"
%}

%include <cstring.i>
%cstring_output_allocate(char **error, free(*$1));

%include "larc.h"
