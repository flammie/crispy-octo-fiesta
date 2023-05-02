# crispy-octo-fiesta

I experiment with programming languages? The name was suggested by github.

Order of in how well I know them kind of:

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

## Command-line arguments

In the end of the day, most of the experimenting in NLP and probably other
sciences happens through command-line hacking, and we need tools that maybe can
handle a bit of standard-ish command-lines even though it is not so popular with
young people anymore again.

## Localisation

I've been localiser for a good while now, I like to know how hard it is to
localise stuff properly in the languages I learn.
