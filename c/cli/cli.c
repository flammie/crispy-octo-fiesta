#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_version() {
    printf("Crispy Octo Fiesta v.0.0.0\n");
}

void print_help(const char* argv0) {
    printf("Usage: %s [-vVhi]\n", argv0);
    printf("\n");
    printf("  -h, --help           print this help\n");
    printf("  -i, --input=INFILE   read input from INFILE\n");
    printf("  -v, --verbose        print verbosely while doing stuff\n");
    printf("  -V, --version        print version info\n");
}

int main(int argc, char** argv) {
    int c;
    bool verbose = false;
    while (true) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help", no_argument, 0, 0},
            {"input", required_argument, 0, 0},
            {"verbose", no_argument, 0, 0},
            {"version", no_argument, 0, 0},
            {0, 0, 0, 0}
        };
        c = getopt_long(argc, argv, "hi:vV", long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
          case 0:
            printf("option %s", long_options[option_index].name);
            if (optarg) {
                printf(" with arg %s", optarg);
            }
            printf("\n");
            break;
          case 'h':
            print_help(argv[0]);
            exit(EXIT_SUCCESS);
            break;
          case 'i':
            printf("Would have opened %s for reading\n", optarg);
            break;
          case 'v':
            verbose = true;
            printf("being verbose\n");
            break;
          case 'V':
            print_version();
            exit(EXIT_SUCCESS);
            break;
          case '?':
            printf("\n");
            print_help(argv[0]);
            exit(EXIT_FAILURE);
          default:
            fprintf(stderr, "Unrecognised switch -%c?\n", c);
            print_help(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (optind < argc) {
        fprintf(stderr, "Unrecognised trailing arguments: ");
        while (optind < argc) {
            fprintf(stderr, "%s ", argv[optind++]);
        }
        fprintf(stderr, "\n");
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    if (verbose) {
        printf("still verbose\n");
    }
}
