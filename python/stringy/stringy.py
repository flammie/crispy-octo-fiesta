#!/usr/bin/env python3
"""Read and write CSV and TSV."""
import sys


def main():
    """Main CLI function."""
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} INFILE OUTFILE")
        sys.exit(1)
    with open(sys.argv[1], "r", encoding="utf-8") as inf, \
         open(sys.argv[2], "w", encoding="utf-8") as outf:
        for line in inf:
            fields = line.rstrip("\n").split(",")
            print("\t".join(fields), file=outf)


if __name__ == "__main__":
    main()
