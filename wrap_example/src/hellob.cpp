#include "hellob.h"
#include <hello.h>

#include <cstring>

std::string hello(int64_t num)
{
  return Hello::hello() + " " + std::to_string(num);
}

char * hello(int64_t num, char * outStr, size_t * outLen)
{
  memset(outStr, 0, sizeof(char) * (*outLen));
  const std::string ret = hello(num);
  const size_t retlen = ret.size()+1;
  const size_t maxlen = retlen > *outLen ? *outLen : retlen;
  *outLen = maxlen-1;
  return strncpy(outStr, ret.c_str(), (*outLen));
}

