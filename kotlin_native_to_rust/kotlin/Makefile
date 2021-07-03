TARGET := ktr_test_kotlin.kexe
OBJECTS := ktr.h ktr.klib
KOTLINC := $(HOME)/dev/kotlin-native-1.5.20/bin/kotlinc-native
CBINDGEN := cbindgen
CINTEROP := cinterop
KLIB := klib
KTC := kotlinc-native
CARGO := cargo

# klib info ktr
# klib contents ktr

all: $(TARGET)

$(TARGET): main.kt $(OBJECTS) 
	$(KOTLINC) $< -o $@ -l ktr

ktr.h: cbindgen.toml ../target/debug/libktr.a
	$(CBINDGEN) --config cbindgen.toml --crate ktr --output $@ --lang c ..

ktr.klib: ktr.def
	$(CINTEROP) -def $< -compiler-options -I. -libraryPath ../target/debug -staticLibrary libktr.a -o $@
	$(KLIB) install ktr

../target/debug/libktr.a: ../src/lib.rs
	$(CARGO) build

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJECTS)
	rm -rf ktr_test_kotlin.kexe.dSYM ktr.klib-build

