//
// Created by hhp on 29/04/2017.
//

#ifndef RECORDS_H
#define RECORDS_H

#endif //ADDRESS_BOOK_RECORDS_H

#define NMSZ 50
#define NTSZ 100
#define ADRSSZ 100

struct record {
    char name[NMSZ];
    char surname[NMSZ];
    char notes[NTSZ];
    char address[ADRSSZ];
};