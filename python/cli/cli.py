#!/usr/bin/env python3
"""Command-line interface in python with argparse."""

from argparse import ArgumentParser


def main():
    """Main entry point."""
    a = ArgumentParser(description="Command line parsing")
    a.add_argument("-i", "--input", metavar="INFILE", type=open,
                   dest="infile", help="read input from INFILE")
    a.add_argument("-v", "--verbose", help="print verbosely while doing",
                   action="store_true")
    a.add_argument("-V", "--version", help="print version info",
                   action="version", version="CrispyOctoFiesta 0.0.0")
    options = a.parse_args()
    if options.verbose:
        print("Being verbose")
    if options.infile:
        print("Opened", options.infile.name, "for input")


if __name__ == "__main__":
    main()
