%module hellob

%include <std_string.i>
%include <stdint.i>

%{
/* Includes the header in the wrapper code */
#include "hellob.h"
%}

/* Parse the header file to generate wrappers */
%include "hellob.h"
