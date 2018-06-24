ODIR := obj

CXX ?= g++
LD ?= ld
SWIG ?= swig
JAVAC ?= javac
LANG ?= perl

INCLUDES += -I./src -I../lib_example/src
CXXFLAGS += $(INCLUDES) -std=c++11

all: $(ODIR)/hellob.o

$(ODIR)/hellob.o: src/hellob.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(ODIR)/*

