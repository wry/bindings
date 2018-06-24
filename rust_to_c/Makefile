# creation of a theoretical 'libhellob' static lib that binds to 'libhello' (a C++ lib), to be used from a Rust project

CXX ?= g++
LD ?= ld
SWIG ?= swig

TARGET := hellob
CXXFLAGS += -std=c++11
CXXFLAGS += -I../wrap_example/src -I../lib_example/src

all: lib$(TARGET).a ../lib_example/obj/libhello.a

../lib_example/obj/libhello.a:
	$(MAKE) -C ../lib_example/

lib$(TARGET).a: $(TARGET).o
	$(AR) rcs $@ $(TARGET).o

$(TARGET).o: ../wrap_example/src/$(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET).o lib$(TARGET).a

