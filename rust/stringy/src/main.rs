use std::fs::File;
use std::io::{BufReader, BufRead, Write};

fn main() {
    let infilename = std::env::args().nth(1);
    let outfilename  = std::env::args().nth(2);
    let infile = match infilename {
        Some(filename) => match File::open(filename) {
            Ok(f) => f,
            Err(e) => panic!("Couldn't open file: {}", e),
        }
        None => panic!("Needs two more arguments"),
    };
    let mut outfile = match outfilename {
        Some(filename) => match File::create(filename) {
            Ok(f) => f,
            Err(e) => panic!("Couldn't create file: {}", e),
        }
        None => panic!("Needs one more argument"),
    };
    if let Some(s) = std::env::args().nth(3) {
        panic!("Extra unknown arguments here: {}...", s);
    }
    let lines = BufReader::new(infile).lines();
    for line in lines {
        if let Ok(s) = line {
            let fields: Vec<&str> = s.split(",").collect();
            write!(outfile, "{}\n", fields.join("\t"))
                .expect("Could not write to file");
        }
    }
}
