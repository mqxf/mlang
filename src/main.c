#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/mlang.h"
#include "include/macros.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide name of input file.\n");
        return 0;
    }

    char* outfile;
    char* infile;

    if (strcmp(argv[1], "-o") == 0) {
        if (argc < 4) {
            printf("Please provide name of input file.\n");
            return 0;
        }
        outfile = calloc(strlen(argv[2]), sizeof(char));
        infile = calloc(strlen(argv[3]), sizeof(char));
        strcpy(outfile, argv[2]);
        strcpy(infile, argv[3]);
    }
    else {
        infile = calloc(strlen(argv[1]), sizeof(char));
        strcpy(infile, argv[1]);
        if (argc > 2 && strcmp(argv[2], "-o") == 0) {
            if (argc < 4) {
                printf("Invalid number of arguments. Please provide name of output file after \'-o\'.\n");
                return 0;
            }
            outfile = calloc(strlen(argv[3]), sizeof(char));
            strcpy(outfile, argv[3]);
        }
        else {
            outfile = calloc(strlen(strtok(argv[1], ".")) + 2, sizeof(char));
            strcpy(outfile, strtok(argv[1], "."));
            strcat(outfile, ".s");
        }
    }

    printf("Input: %s, Output: %s\n", infile, outfile);
    
    mlang_init(infile, outfile);

    free(outfile);
    free(infile);

    return 0;
}
