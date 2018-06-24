# create a static lib that we can bind to from another language

ODIR := obj
OBJ := $(ODIR)/libhello.a

CXX ?= g++
LD ?= ld
AR ?= ar

all: $(OBJ)

$(ODIR)/libhello.a: $(ODIR)/hello.o
	$(AR) rcs $@ $<

$(ODIR)/hello.o: src/hello.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(ODIR)/*

