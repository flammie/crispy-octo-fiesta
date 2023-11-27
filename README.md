# crispy-octo-fiesta

I experiment with programming languages? The name was suggested by github.

Here's the programming languages in order of in how well I know them kind of:

1. Python
1. C
1. awk
1. PHP
1. C++
1. Rust
1. Go
1. Java
1. Ruby
1. C#
1. Basic (but no easily accessible floss parser or compiler)
1. Pascal
1. javascript (currently using nodejs for command line running)

Here's the list of experiments in order of complexity:

1. Hello world
1. Read CSV from file, print TSV to file
1. Handle command-line parametres
1. Software localisation and translation
1. Something about data structures and algorithms

Following is the description of the experiments.

## Hello world

I have written a hello world in most languages.
They are most minimal things one can write kind of. I didn't follow any specific
idea to minimise the examples systematically or use the best practices, e.g.
there's `std::endl` in C++ even though I know it is newline plus flush, the
mains return `EXIT_SUCCESS`, python has hashbang and main function and the
name main dunder blurb etc. This is also to gauge how much boilerplate each
language has in very typical setting, e.g. for python runnables you generally
always do write the blurb and also I take into account what each languages'
linters say.

## File i/o, string split and join

One of the gold standard tests I use for programming languages as a programmer
in natural language processing is, how easy it is to read in and print out comma
or tab separated values, to and from suitable data structures, an array, list or
similar. We also usually want to use files easily. If roundtripping between
comma and tab separated values and programming language data structures is slow
or really convoluted to program it's probably not a good programming language
for NLPers. (By NLP I mean here processing of the language by humans and
linguists, if you do neural NLP you probably never need to see text data or
strings.)

This test is interesting since it shows how bad some of my otherwise favorite
langauges are really quite bad indeed; string handling in C is quite pain.
The standard for splitting in C is of course based on `strtok`, which is not
very neat function to work with. `getline` or `getdelim` is a bit nicer. C++
does not have much more to help with, I went with string functions mainly,
there would be another option of using more functional approach with string
stream iterators probably, I don't find that style of programming very readable
or maintainable and usually pain to write.

## Command-line arguments

In the end of the day, most of the experimenting in NLP and probably other
sciences happens through command-line hacking, and we need tools that maybe can
handle a bit of standard-ish command-lines even though it is not so popular with
young people anymore again.

In C the `getopt_long` from GNU is the gold standard that all others should be
modelled after. It may not have ideal implementation with global state and
destructive operation on stuff but it handles permutations and such in a way we
all expect.

In Python's standard library there is `ArgumentParser` that is quite pythonic
and easy to use and works reasonably well.

For C++ there isn't anything particularly standard or popular, boost has some
stuff but boost is kind of meh for a lot of reasons. I have seen cxxopts but
barely trying to understand the parentheses hell that its normal way to declare
arguments is (that breaks all current code formatters btw)... yeah,
demonstrating this as the best c++ way would be just mean.

In rust there was couple of options to parse command-lines, they seem to slowly
converge in having only `clap` left so I've gone with that.

## Localisation

I've been localiser for a good while now, I like to know how hard it is to
localise stuff properly in the languages I learn.

In the FLOSS localisation, `gettext` is the traditional gold standard, there are
others but they do not get used that much. Linguistically gettext is quite poor,
it only supports one numeral *plural forms* thing as a linguistic concept and
everything else is 1:1 string to string translations.

## Data structures and algorithms

More basic parts of computer science curriculum, data structures are an
interesting experiment cause they really need to test the programming languages
features for handling datatypes, pointers and cyclic pointers and memory
management and stuff.
