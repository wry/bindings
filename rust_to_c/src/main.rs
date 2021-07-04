extern crate libc;

use libc::{free};
use std::ffi::CString;
use std::ffi::CStr;
use std::ptr;

#[repr(C)]
pub struct Lar {
    _private: [u8; 0], // empty on purpose to mark type 'Opaque'
}

#[repr(C)]
pub struct Release {
    _private: [u8; 0],
}

#[repr(C)]
pub struct CRelease {
    title: *mut i8,
    link: *mut i8,
    description: *mut i8,
    pub_date: *mut i8,
}

#[link(name = "larc")]
#[link(name = "lar")]
extern "C" {
    fn Lar_new() -> *mut Lar;
    fn Lar_delete(lar: *mut Lar);

    fn Lar_first_release_item(lar: *mut Lar, path: *const u8, error: *mut *mut u8) -> *const Release;

    fn Release_copy_into(release: *const Release, crelease: *mut CRelease);
    fn Release_delete(release: *const Release);
}

fn main() {
    unsafe {
        let lar = Lar_new();

        let mut error: *mut u8 = ptr::null_mut();
        let c_path = CString::new("/tmp/releases.rss").unwrap();
        let release = match Lar_first_release_item(lar, c_path.as_ptr() as *const u8, &mut error).as_ref() {
            Some(release) => release,
            _ => {
                println!("Error : {}", CStr::from_ptr(error as *const i8).to_str().unwrap());
                free(error as *mut libc::c_void);
                return
            }
        };

        let mut crelease: CRelease = CRelease {
            title: ptr::null_mut(),
            link: ptr::null_mut(),
            description: ptr::null_mut(),
            pub_date: ptr::null_mut(),
        };
        Release_copy_into(release, &mut crelease);

        let title = match CStr::from_ptr(crelease.title as *const i8).to_str() {
            Ok(title) => title,
            _ => ""
        };
        let link = match CStr::from_ptr(crelease.link as *const i8).to_str() {
            Ok(link) => link,
            _ => ""
        };
        let description = match CStr::from_ptr(crelease.description as *const i8).to_str() {
            Ok(description) => description,
            _ => ""
        };
        let pub_date = match CStr::from_ptr(crelease.pub_date as *const i8).to_str() {
            Ok(pub_date) => pub_date,
            _ => ""
        };

        println!("{}, {}, {}, {}\n", title, link, description, pub_date);

        Release_delete(release);
        
        Lar_delete(lar);
    }
}
