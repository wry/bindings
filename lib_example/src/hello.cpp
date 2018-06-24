// gcc -c -o hello.o hello.c
// ar rcs libhello.a hello.o

#include "hello.h"

std::string Hello::hello()
{
  return "hello world";
}
