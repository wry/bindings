fn main() {
    println!("cargo:rustc-link-search=.");
    println!("cargo:rustc-link-search=../lib_example/obj");
    println!("cargo:rustc-link-lib=static=hellob");
    println!("cargo:rustc-link-lib=static=hello");
    println!("cargo:rustc-link-lib=dylib=c++");
}
