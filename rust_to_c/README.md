# rust_to_c

a simple rust example calling into libhello.a through libhellob.a (provides a C wrapper for the C++ libhello.a)

- a Makefile to create a static lib (libhellob.a) from wrap_example
- a rust example that linkes to libhellob.a and libhello.a and calls into them

make
cargo run

