#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s INFILE OUTFILE\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE* inf = fopen(argv[1], "r");
    if (inf == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    FILE* outf = fopen(argv[2], "w");
    if (outf == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, inf) != -1) {
        size_t nfields = 1;
        for (char* c = line; *c != '\0'; c++) {
            if (*c == ',') {
                nfields++;
            }
        }
        char** fields = malloc(sizeof(char*)*nfields);
        char* field = strtok(line, ",");
        size_t n = 0;
        while (field != NULL) {
            fields[n] = strdup(field);
            field = strtok(NULL, ",");
            n++;
        }
        for (size_t i = 0; i < n; i++) {
            if (i > 0) {
                fprintf(outf, "\t");
            }
            fprintf(outf, "%s", fields[i]);
        }
    }
    fclose(outf);
    fclose(inf);
}

