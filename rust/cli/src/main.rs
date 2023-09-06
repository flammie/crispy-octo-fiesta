use std::path::PathBuf;

use clap::Parser;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    #[arg(short, long, value_name = "FILE")]
    input: Option<PathBuf>,

    /// Turn debugging information on
    #[arg(short, long, action = clap::ArgAction::Count)]
    verbose: u8,

}

fn main() {
    let cli = Cli::parse();

    if cli.verbose > 0 {
        println!("Printing {} verbosely", cli.verbose);
    }
    if let Some(inpath) = cli.input.as_deref() {
        if cli.verbose > 0 {
            println!("Opened {} for input", inpath.display());
        }
    }
    else {
        println!("No input files given!");
    }

}
