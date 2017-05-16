//
// Created by hhp on 29/04/2017.
//



#include "dbg.h"
#include "address_book.h"

long data_write(struct data_record *dr)
{
    FILE *f = fopen(DATA_FILE_NAME, "ab");
    long i = ftell(f);
    fwrite(dr, dr_size, 1, f);
    fclose(f);
    return i;
}


int insert_index(struct index_record *newrc)
{
    if (index_root == NULL) {
        index_root = newrc;
        return 0;
    }

    struct index_record *current = index_root;

    if (strcmp(current->id, newrc->id) > 0) {
        newrc->next = current;
        index_root = newrc;
        return 0;
    }

    while (current->next != NULL && strcmp(current->next->id, newrc->id) < 0) {
        current = current->next;
    }

    newrc->next = current->next;
    current->next = newrc;
    return 0;
}

int index_read()
{
    char cntrl = 1;

    FILE *f = fopen(INDEX_FILE_NAME, "rb+");
    if (f == NULL) // if no such a file, there is a error
        return 1;

    fread(&cntrl, sizeof(char), 1, f);
    fseek(f, 0, SEEK_SET);
    fwrite("1", 1, 1, f); //dirty bit

    if (cntrl != '0') {
        debug("dirty bit is not zero");
        fclose(f);
        return 1;
    }




    struct index_record *tmp = calloc(1, ir_size);

    while (fread(tmp, ir_size, 1, f) == 1) {
        tmp->next = NULL;
        insert_index(tmp);
        tmp = calloc(1, ir_size);
    }

    fclose(f);
    free(tmp);
    debug("end of index_read()");
    return 0;
}

void index_write()
{
    FILE *f = fopen(INDEX_FILE_NAME, "wb");
    fwrite("0", 1, 1, f); //dirty bit

    struct index_record *tmp = index_root;
    while (tmp != NULL) {
        fwrite(tmp, ir_size, 1, f);
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
        } else {
            // rootun nexti yoksa, root NULL olur
            free(index_root);
            index_root = NULL;
        }
        return 0;
    }

    struct index_record *current = index_root;
    while (current->next != NULL && current->next != ir) {
        current = current->next;
    }

    if (current->next == NULL)
        return 1; // index_record yoktur.

    // currentın nexti silinecektir. tmp, free yapabilmek amacıyla tutuldu.
    struct index_record *tmp = current->next;
    current->next = current->next->next;
    free(tmp);

    return 0;
}
