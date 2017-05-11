//
// Created by hhp on 29/04/2017.
//

#ifndef RECORDS_H
#define RECORDS_H

#endif //ADDRESS_BOOK_RECORDS_H

#define NAMESIZE 32
#define NOTESIZE 100
#define ADRSSIZE 100


#define INDEX_FILE_NAME "index.bin"
#define DATA_FILE_NAME "data.bin"


struct data_record {
    char name[NAMESIZE];
    char surname[NAMESIZE];
    char address[ADRSSIZE];
    char notes[NOTESIZE];
};

struct index_record {
    char id[2 * NAMESIZE];
    long index;
    struct index_record *next;
};

extern struct index_record *index_root;

int data_read(FILE *f, struct data_record *dr, int index);

long data_write(struct data_record *dr);

int insert_index(struct index_record *newrc);

int index_read(struct index_record *root);

void index_write(struct index_record **root);

struct index_record *search_index(char *id);

int remove_index(struct index_record *ir);