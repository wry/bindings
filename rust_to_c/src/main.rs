extern crate libc;
use libc::{int64_t, size_t};

#[link(name = "hello")]
extern "C" {
    // the function in our static C lib
    fn hello(num: int64_t, outStr: *mut u8, outLen: *mut size_t) -> *mut u8;
}

pub fn hello_cmd(num: i64) -> Vec<u8> {
    unsafe {
        // length of our pre-allocated char vec (note: strlen will be max dstlen-1)
        let mut dstlen = 1024;
        let mut dst = Vec::with_capacity(dstlen as usize);
        let pdst = dst.as_mut_ptr();

        hello(num, pdst, &mut dstlen);
        dst.set_len(dstlen as usize);
        dst
    }
}

fn main() {
    let cmd = hello_cmd(42);
    let s = String::from_utf8(cmd).expect("Found invalid UTF-8");
    println!("{}", s);
}
