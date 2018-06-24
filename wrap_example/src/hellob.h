#ifndef __Hellob__h__
#define __Hellob__h__

#include <string>
#include <cstdint>

/* for bindings to c++ */

/* a call that wraps the 'hello' call from libhello, returns an std::string
  @param num number to append to hello() call
  @ret concatenated string from libhello's hello() and num
*/
std::string hello(int64_t num);

/* for bindings to c */

#ifdef __cplusplus
extern "C" {
#endif

/* a call that wraps the 'hello' call from libhello usable for C binding
  @param num number to append to hello() call
  @param outStr in : pre-allocated char ptr, out : null terminated string
  @param outLen in : size of pre-allocated char ptr, out : size of string after allocation (w/o \0 at the end)
  @ret same as outStr out
*/
char * hello(int64_t num, char * outStr, size_t * outLen);

#ifdef __cplusplus
}
#endif

#endif /* defined(__Hellob__h__) */
