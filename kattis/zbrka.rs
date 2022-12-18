use std::{
    cmp, env,
    error::{self, Error},
    fmt,
    fs::{self, File},
    hash,
    io::{self, prelude::*, stdin, stdout, BufRead, BufReader, BufWriter, Read, Write},
    iter::{self, Peekable},
    result,
    str::{self, FromStr},
    vec,
};
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

fn result_panic_if<T, E>(res: &Result<T, E>, func: impl FnOnce(&E) -> bool) {
    if let Err(e) = res {
        if func(e) {
            res.unwrap();
        }
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

// Similar to a subset of C++'s iostream interface; ignores errors (except for parsing errors)
struct IStream<R: BufRead> {
    source: R,
}

impl<R: BufRead> IStream<R> {
    pub fn get(&mut self, buf: &mut [u8]) -> Option<&mut Self>{
        let res = self.read_buf(buf);
        match res {
            Ok(()) => Some(self),
            Err(E) => match E.kind() {
                io::ErrorKind::UnexpectedEof => None,
                e => res.unwrap(),
            },
        }
	}
    pub fn peek(&mut self, byte: &mut u8) -> Option<&mut Self> {
		unimplemented!()
	}
    pub fn ignore(&mut self, n: Option<usize>, val: Option<u8>) -> &mut Self {
		unimplemented!()
	}
}

/*impl From<File> for IStream<R> {
    fn from(file: File) -> Self {
        IStream::new(File::op)
    }
}*/

impl<T: IStream> Iterator for T {
    type Item = u8;
}

impl<T: IStream> Peek for T {}

trait OStream {}

trait Readable {
    type Err: error::Error;
    fn read_to(&mut self, strm: &mut impl IStream) -> Result<(), Self::Err>;
}

trait Writable {
    type Err: error::Error;
    fn write_from(&mut self, strm: &mut impl OStream) -> Result<(), Self::Err>;
}

fn main() {
    println!("Hi!");
}

//type Result<T> = result::Result<T, Box<dyn Error>>;

/*
struct Scanner<I: Iterator<io::Result<u8>>> {
    it: Peekable<I>
}

impl<I: Read> Scanner<I> {
    pub fn
    pub fn eof(&mut self) -> bool {

    }
    pub fn peek_byte(&mut self) -> io::Result<u8> {
        it.peek();
    }
    pub fn peek_byte(&mut self, res : &mut u8) -> io::Result<()> {

        Ok(())
    }
}*/

/*
trait Scannable {
    fn scan<I: Iterator<char>>(&mut self, it: &mut I) -> Result<()>;
    fn scan<I: Iterator<char>>(it: &mut I) -> Result<Self>;
}

impl Scannable for String {
    fn scan<I: Iterator<char>>(&mut self, it: &mut I) -> Result<()> {
        it.peekable()
    }
    fn scan<I: Iterator<char>>(it: &mut I) -> Result<Self>;
}

struct Go<R: Read, W: Write> {
    input: BufReader<R>,
    output: BufWriter<W>,
    buffer: Vec<String>,
}*/
/*
impl<R: Read, W: Write> Go<R, W> {
    fn new(input: R, output: W) -> Go<R, W> {
        Go {
            input: BufReader::new(input),
            output: BufWriter::new(output),
            buffer: Vec::new(),
        }
    }
    fn next<String>(&mut self, t: &mut String) -> Result<()> {
        *t = String::from("f");
        Ok(());
    }
    fn next<T: FromStr>(&mut self, t: &mut T) -> Result<()>
    where
        <T as FromStr>::Err: Error,
    {
        *t = "f".parse()?;
        Ok(())
    }
    /*
    fn next<T : FromStr>(&mut self) -> T where
        <F as FromStr
    {
        loop {
            match self.buffer.pop() {
                Some(tok) => break tok.parse(),
                None => {
                    let mut str = String::new();
                    self.input.read
                    self.input.read_line(&mut str)?;
                    self.buffer = str.split_whitespace().rev().map(String::from).collect();
                }
            }
        }
        .unwrap()
    }*/
}*/

/*
fn main() -> Result<()> {
    let args: Vec<String> = env::args().collect();
    if args.len() >= 2 {
        Go::new(File::open(&args[1])?, File::open(&args[2])?).go()
    } else {
        Go::new(stdin(), stdout()).go()
    }
}*/

/*
const MOD: u64 = 1000000007;

impl<R: Read, W: Write> Go<R, W> {
    fn go(mut self) -> Result<()> {
        let n: usize = self.next()?;
        let c: usize = self.next()?;

        let mut dp: Vec<u64> = vec![0; c + 1];
        dp[0] = 1;

        for i in 0..n {
            dbg!(dp.len());
            dp = dp
                .clone()
                .into_iter()
                .enumerate()
                .scan(0u64, |s, (j, f)| {
                    let sub = { dp.get(j.checked_sub(i)?).cloned() }.unwrap_or_default();
                    *s = (MOD + *s + f - sub) % MOD;
                    dbg!(i, j, &s);
                    Some(*s)
                })
                .collect();
        }

        writeln!(self.output, "{}", dp.last().unwrap())?;

        Ok(())
    }
}
*/
