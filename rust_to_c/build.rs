fn main() {
    println!("cargo:rustc-link-search=.");
    println!("cargo:rustc-link-search=../c_to_cpp/build");
    println!("cargo:rustc-link-search=../liblar_cpp/build");
    println!("cargo:rustc-link-lib=static=larc");
    println!("cargo:rustc-link-lib=static=lar");
    println!("cargo:rustc-link-lib=dylib=c++");
}
