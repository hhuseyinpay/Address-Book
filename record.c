//
// Created by hhp on 29/04/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "address_book.h"


int data_read(FILE *f, struct data_record *dr, int index)
{
    fseek(f, index * sizeof(struct data_record), SEEK_SET);
    return (int) fread(dr, sizeof(struct data_record), 1, f);
}

long data_write(struct data_record *dr)
{
    FILE *f = fopen(DATA_FILE_NAME, "ab");
    fwrite(dr, sizeof(struct data_record), 1, f);
    fclose(f);
    return ftell(f);
}


int insert_index(struct index_record *newrc)
{
    if (index_root == NULL)
        index_root = newrc;

    struct index_record *current = index_root;
    while (current->next != NULL && strcmp(current->next->id, newrc->id) < 0) {
        current = current->next;
    }

    newrc->next = current->next;
    current->next = newrc;
    return 0;
}

int index_read(struct index_record *root)
{
    debug("index_read()");
    size_t size = sizeof(struct index_record);
    char cntrl = 1;

    FILE *f = fopen(INDEX_FILE_NAME, "rb+");
    if (f != NULL) {
        fread(&cntrl, sizeof(char), 1, f);

        if (cntrl != '0') {
            debug("dirty flag is not 0");
            fclose(f);
            debug("end of index_read()");
            return 1;
        }
    } else {
        return 0;
    }
    fseek(f, 0, SEEK_SET);
    fwrite("0", 1, 1, f); // dirty bit
    struct index_record *tmp = calloc(1, size);

    while (fread(tmp, size, 1, f) == 1) {

        tmp = calloc(1, size);
        insert_index(tmp);
        memset(tmp, 0, size);
        printf("a: %s\n", tmp->id);
    }
    free(tmp);
    debug("end of index_read()");
    return 0;
}

void index_write(struct index_record **root)
{
    errno = 0;
    size_t size = sizeof(struct index_record);

    FILE *f = fopen(INDEX_FILE_NAME, "wb");
    fwrite("0", 1, 1, f); //dirty bit

    struct index_record *tmp = *root;
    while (tmp != NULL) {
        fwrite(tmp, size, 1, f);
        tmp = tmp->next;
    }
    fclose(f);
}

struct index_record *search_index(char *id)
{
    struct index_record *current = index_root;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

int remove_index(struct index_record *ir)
{
    // root silinecekse
    if (index_root == ir) {
        // rootun nexti root olur ve eski root free olur.
        if (index_root->next != NULL) {
            struct index_record *tmp = index_root;
            index_root = index_root->next;
            free(tmp);
        }
        // rootun nexti yoksa, root NULL olur
        free(index_root);
        index_root = NULL;
    }

    struct index_record *current = index_root;
    while (current->next != NULL && current->next != ir) {
        current = current->next;
    }

    if (current->next == NULL)
        return 0; // index record yoktur.

    // currentın nexti silinecektir. tmp, free yapabilmek amacıyla tutuldu.
    struct index_record *tmp = current->next;
    current->next = current->next->next;
    free(tmp);
    return 0;
}