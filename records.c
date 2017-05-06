//
// Created by hhp on 29/04/2017.
//

#include <stdio.h>
#include "records.h"


void rread(const char *filename, struct record *rcrd, int index)
{
    FILE *f = fopen(filename, 'r');
    fseek(f, index, SEEK_SET);
    fread(rcrd, sizeof(struct record), 1, f);
    fclose(f);
}

void rwrite(const char *filename, struct record *rcrd)
{
    FILE *f = fopen(filename, 'a');
    fwrite(rcrd, sizeof(struct record), 1, f);
    fclose(f);
}