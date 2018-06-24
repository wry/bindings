# creation of the 'hellob' module that binds to 'libhello' (a static lib written in C++) and uses a wrapper

# note:
# - by default the Perl module gets compiled, use `make LANG=<perl|python|java>` to specify target lang
# - libs may end up with the same name, so compiling for multiple langs at the same time isn't a good idea
# - most of the defs are OSX specific
# - modulepaths are handled differently for each platform, look into the src files of each to test

ODIR := obj
MODULE := hellob

CXX ?= g++
LD ?= ld
SWIG ?= swig
JAVAC ?= javac
LANG ?= perl

INCLUDES += -I../lib_example/src -I../wrap_example/src
CXXFLAGS += $(INCLUDES)
LDFLAGS += -L../lib_example/obj -L../wrap_example/obj
SWIGFLAGS := -c++ $(INCLUDES)

# python
ifeq ($(LANG),python)
TARGET := $(ODIR)/_$(MODULE).so
RUNCMD := PYTHONPATH=obj ./python/hellob_test.py
CXXFLAGS += -I/usr/include/python2.7
LDFLAGS += -dylib -lhello -lpython -lc++ -lc
SWIGFLAGS += -python
# java
else ifeq ($(LANG),java)
TARGET := $(ODIR)/lib$(MODULE).dylib $(ODIR)/Main.class
RUNCMD := java -cp obj -Djava.library.path=./obj/ Main
CXXFLAGS += -I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers/
LDFLAGS += -dylib -lhello -lc++ -lc
SWIGFLAGS += -java
# perl
else
TARGET := $(ODIR)/lib$(MODULE).dylib
RUNCMD := ./perl/hellob_test.pl
CXXFLAGS += -I/System/Library/Perl/5.18/darwin-thread-multi-2level/CORE/
LDFLAGS += -L/System/Library/Perl/5.18/darwin-thread-multi-2level/CORE/
LDFLAGS += -dylib -lhello -lperl -lc++ -lc
SWIGFLAGS += -perl5
endif

all: $(TARGET)

run: $(TARGET)
	$(RUNCMD)

../wrap_example/obj/hellob.o: ../wrap_example/src/hellob.cpp ../wrap_example/src/hellob.h
	$(MAKE) -C ../wrap_example

../lib_example/obj/libhello.a: ../lib_example/src/hello.cpp ../lib_example/src/hello.h
	$(MAKE) -C ../lib_example

$(ODIR)/_$(MODULE).so: ../lib_example/obj/libhello.a ../wrap_example/obj/hellob.o $(ODIR)/$(MODULE)_$(LANG)_swing.o
	$(LD) $(ODIR)/$(MODULE)_$(LANG)_swing.o ../wrap_example/obj/hellob.o -o $@ $(LDFLAGS)

$(ODIR)/lib$(MODULE).dylib: ../lib_example/obj/libhello.a ../wrap_example/obj/hellob.o $(ODIR)/$(MODULE)_$(LANG)_swing.o
	$(LD) $(ODIR)/$(MODULE)_$(LANG)_swing.o ../wrap_example/obj/hellob.o -o $@ $(LDFLAGS)

$(ODIR)/$(MODULE)_$(LANG)_swing.o: $(ODIR)/$(MODULE)_$(LANG)_swing.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/$(MODULE)_$(LANG)_swing.cxx: swig/$(MODULE).i
	$(SWIG) $(SWIGFLAGS) -o $@ $<

$(ODIR)/$(MODULE).class: $(ODIR)/hellob.java
	$(JAVAC) -d $(ODIR) $<
	
$(ODIR)/$(MODULE)JNI.class: $(ODIR)/hellobJNI.java
	$(JAVAC) -d $(ODIR) $<

$(ODIR)/Main.class: java/Main.java
	$(JAVAC) -cp $(ODIR) -d $(ODIR) $<


.PHONY: clean
clean:
	$(RM) $(ODIR)/*

