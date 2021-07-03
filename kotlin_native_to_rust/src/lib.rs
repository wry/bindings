use std::ffi::CString;
use std::ffi::CStr;
use std::fs;

use sxd_document::{parser, dom};
use sxd_xpath::{Factory, Context, Value};

#[derive(Debug)]
#[derive(Default)]
pub struct Release {
    title: String,
    link: String,
    description: String,
    pub_date: String,
}

#[derive(Debug)]
#[repr(C)]
pub struct CRelease {
    title: *mut libc::c_char,
    link: *mut libc::c_char,
    description: *mut libc::c_char,
    pub_date: *mut libc::c_char,
}

impl Drop for CRelease {
    fn drop(&mut self) {
        unsafe {
            if !self.title.is_null() {
                CString::from_raw(self.title);
            }
            if !self.link.is_null() {
                CString::from_raw(self.link);
            }
            if !self.description.is_null() {
                CString::from_raw(self.description);
            }
            if !self.pub_date.is_null() {
                CString::from_raw(self.pub_date);
            }
        }
    }
}

fn rss_value_for_xpath<'d>(factory: &'d Factory, context: &'d Context, doc: &'d dom::Document, path: &'d str) -> Option<sxd_xpath::Value<'d>> {
    let xpath = match factory.build(path) {
        Ok(xpath) => {
            match xpath {
                Some(xpath) => xpath,
                _=> {
                    println!("Could not extract xpath");
                    return None;
                }
            }
        }
        _ => {
            println!("Could not compile XPath");
            return None;
        }
    };

    let item = match xpath.evaluate(&context, doc.root()) {
        Ok(item) => item,
        _ => {
            println!("XPath evaluation failed");
            return None;
        }
    };

    Some(item)
}

fn find_first_release_item(path: &str) -> Option<Release> {
    let mut release: Release = Default::default();

    let releases = match fs::read_to_string(path) {
        Ok(releases) => releases,
        Err(error) => {
            println!("Error : {:?}", error);
            return None;
        }
    };
    let dom = match parser::parse(&releases) {
        Ok(dom) => dom,
        Err(error) => {
            println!("Failed to parse XML : {:?}", error);
            return None;
        }
    };

    let doc = dom.as_document();

    let factory = Factory::new();
    let context = Context::new();

    // xpath will return a list of items containing a single element
    let items = match rss_value_for_xpath(&factory, &context, &doc, "//channel/item[description[contains(text(),\"iPadOS\")]][1]") {
        Some(items) => match items {
            Value::Nodeset(items) => items,
            _=> {
                println!("Item found but not nodeset");
                return None;
            }
        },
        None => {
            println!("Item could not be found");
            return None;
        }
    };

    let first_item = match items.document_order_first() {
        Some(item) => item,
        _ => {
            println!("Could not find first document in list of items");
            return None;
        }
    };

    for item in first_item.children() {
        let item_element = match item.element() {
            Some(item_element) => item_element,
            _ => {
                continue;
            }
        };

        match item_element.name().local_part() {
            "title" => {
                for item_element_node in item_element.children() {
                    if let Some(item_text) = item_element_node.text() {
                        release.title = String::from(item_text.text());
                    }
                }
            }
            "link" => {
                for item_element_node in item_element.children() {
                    if let Some(item_text) = item_element_node.text() {
                        release.link = String::from(item_text.text());
                    }
                }
            }
            "description" => {
                for item_element_node in item_element.children() {
                    if let Some(item_text) = item_element_node.text() {
                        release.description = String::from(item_text.text());
                    }
                }
            }
            "pubDate" => {
                for item_element_node in item_element.children() {
                    if let Some(item_text) = item_element_node.text() {
                        release.pub_date = String::from(item_text.text());
                    }
                }
            }
            _ => {}
        };
    }

    // println!("{:?}", release);

    return Some(release);
}

#[no_mangle]
pub unsafe extern "C" fn first_crelease_item(path: *const libc::c_char) -> *mut CRelease {
    if path.is_null() {
        return std::ptr::null_mut();
    }

    let path_c_str = CStr::from_ptr(path);
    let release = match find_first_release_item(path_c_str.to_str().unwrap()) {
        Some(release) => release,
        _ => {
            return std::ptr::null_mut();
        }
    };
    
    let crelease = CRelease {
        title: CString::new(release.title).unwrap().into_raw(),
        link: CString::new(release.link).unwrap().into_raw(),
        description: CString::new(release.description).unwrap().into_raw(),
        pub_date: CString::new(release.pub_date).unwrap().into_raw(),
    };

    return Box::into_raw(Box::new(crelease));
}

#[no_mangle]
pub unsafe extern "C" fn release_crelease_item(crelease_ptr: *mut CRelease) {
    if crelease_ptr.is_null() {
        return;
    }
    Box::from_raw(crelease_ptr);
}