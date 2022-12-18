use std::*;
/*use std::{
    cmp, env,
    error::{self, Error},
    fmt,
    fs::{self, File},
    hash,
    iter::{self, Peekable},
    result,
    str::{self, FromStr},
    vec,
};*/

trait Peek: Iterator {
    fn peek(&mut self) -> Option<&<Self as Iterator>::Item>;
    fn peek_mut(&mut self) -> Option<&mut <Self as Iterator>::Item>;
    fn next_if(
        &mut self,
        func: impl FnOnce(&<Self as Iterator>::Item) -> bool,
    ) -> Option<<Self as Iterator>::Item> {
        if func(self.peek()?) {
            self.next()
        } else {
            None
        }
    }
    fn next_if_eq<T>(&mut self, expected: &T) -> Option<<Self as Iterator>::Item>
    where
        T: ?Sized,
        <Self as Iterator>::Item: PartialEq<T>,
    {
        self.next_if(|x| x == expected)
    }
}

impl<I: Iterator> Peek for Peekable<I> {
    fn peek(&mut self) -> Option<&Self::Item> {
        self.peek()
    }
    fn peek_mut(&mut self) -> Option<&mut Self::Item> {
        self.peek_mut()
    }
    fn next_if(
        &mut self,
        func: impl FnOnce(&Self::Item) -> bool,
    ) -> Option<<Self as Iterator>::Item> {
        self.next_if(func)
    }
    fn next_if_eq<T>(&mut self, expected: &T) -> Option<Self::Item>
    where
        T: ?Sized,
        <Self as Iterator>::Item: PartialEq<T>,
    {
        self.next_if_eq(expected)
    }
}

#[derive(Clone, Copy, Debug, Default, Eq, Hash, PartialEq)]
enum FloatFmt {
    #[default]
    Default,
    Fixed,
    Scientific,
    Hex,
}

struct IStream<R: BufRead> {
    source: R,

    width: Option<num::NonZeroUsize>,
    prec: usize,
    float: FloatFmt,
}

impl<R: BufRead> IStream<R> {
    pub fn get(&mut self, buf: &mut [u8]) -> Option<&mut Self> {
		
	}
    fn peek(&mut self, byte: &mut u8) -> Option<&mut Self>;
    fn ignore(&mut self, n: Option<usize>, val: Option<u8>) -> Option<&mut Self>;
}

/*

// Similar to a subset of C++'s I/O Stream interface.
mod ios {
    use std::*;
    fn result_panic_if<T, E: error::Error>(res: &Result<T, E>, func: impl FnOnce(&E) -> bool) {
        if let Err(e) = res {
            if func(e) {
                res.as_ref().unwrap();
            }
        }
    }

    // Formatting State (TODO add more items from https://en.cppreference.com/w/cpp/io/manip)
    // See also https://en.cppreference.com/w/cpp/io/ios_base/fmtflags
    #[derive(Clone, Copy, Debug, Default, Eq, Hash, PartialEq)]
    enum Float {
        #[default]
        Default,
        Fixed,
        Scientific,
        Hex,
    }

    #[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
    struct State {
        fill: u8,
        prec: usize,
        width: Option<num::NonZeroUsize>,
        float: Float,
    }
    impl Default for Flags {
        fn default() -> Self {
            State {
                fill: ' ',
                prec: 6,
                width: None,
                float: default(),
            }
        }
    }

    trait Stream {

    }

    trait IStream {
        fn get(&mut self, buf: &mut [u8]) -> Option<&mut Self>;
        fn peek(&mut self, byte: &mut u8) -> Option<&mut Self>;
        fn ignore(&mut self, n: Option<usize>, val: Option<u8>) -> Option<&mut Self>;

        //fn prec(&mut self, prec: Option<usize>)
        //fn set_prec(&mut self, )
    }

    trait IStreamBase {}
}*/

fn main() {}
