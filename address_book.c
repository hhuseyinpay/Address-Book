//
// Created by hhp on 06/05/2017.
//

#include "dbg.h"
#include "address_book.h"


struct index_record *index_root;
size_t ir_size = sizeof(struct index_record);
size_t dr_size = sizeof(struct data_record);

struct index_record *getid();

void print_record(struct data_record *dr);

int new_record()
{

    char name[NAMESIZE];
    char surname[NAMESIZE];
    char address[ADRSSIZE];
    char notes[NOTESIZE];

    struct data_record *dr = calloc(1, dr_size);

    printf("Name: ");
    scanf(" %[^\n]s", name);
    strcpy(dr->name, name);

    printf("Surname: ");
    scanf(" %[^\n]s", surname);
    strcpy(dr->surname, surname);

    printf("Address: ");
    scanf(" %[^\n]s", address);
    strcpy(dr->address, address);

    printf("Notes: ");
    scanf(" %[^\n]s", notes);
    strcpy(dr->notes, notes);


    char tmpid[2 * NAMESIZE + 1];
    strcpy(tmpid, name);
    strcat(tmpid, "-");
    strcat(tmpid, surname);

    if (search_index(tmpid) != NULL) {  // id varsa kayıt gerçekleşmeyecek
        free(dr);
        return 1;
    }

    struct index_record *ir = calloc(1, ir_size);

    strcpy(ir->id, tmpid);
    ir->index = data_write(dr);

    insert_index(ir);
    free(dr);
    return 0;
}

int update_record()
{

    struct index_record *ir = getid();

    if (ir == NULL) // can not find
        return 1;


    char name[NAMESIZE];
    char surname[NAMESIZE];
    char address[ADRSSIZE];
    char notes[NOTESIZE];

    struct data_record *dr = calloc(1, dr_size);
    printf("New Name: ");
    scanf(" %[^\n]s", name);
    strcpy(dr->name, name);

    printf("New Surname: ");
    scanf(" %[^\n]s", surname);
    strcpy(dr->surname, surname);

    printf("New Address: ");
    scanf(" %[^\n]s", address);
    strcpy(dr->address, address);

    printf("New Notes: ");
    scanf(" %[^\n]s", notes);
    strcpy(dr->notes, notes);

    // remove index record and re add
    char tmpid[2 * NAMESIZE + 1];
    strcpy(tmpid, name);
    strcat(tmpid, "-");
    strcat(tmpid, surname);

    if (search_index(tmpid) != NULL)
        return 1;

    FILE *f = fopen(DATA_FILE_NAME, "rb+");
    fseek(f, ir->index, SEEK_SET);
    fwrite(dr, sizeof(struct data_record), 1, f);

    long idx = ir->index;
    remove_index(ir);

    ir = calloc(1, ir_size);
    strcpy(ir->id, tmpid);

    ir->index = idx;

    insert_index(ir);
    fclose(f);
    free(dr);
    return 0;
}

int addressbook_init()
{
    debug("addressbook_init()");

    /* if index_read return success, initialization success*/
    if (index_read() == 0) {
        debug("index_read() başarılı");
        return 0;
    }

    FILE *f = fopen(DATA_FILE_NAME, "rb");

    /* Data file is not exist */
    if (f == NULL)
        return 1;

    int index = 0;
    char tmps[2 * NAMESIZE + 1];
    struct data_record *tmpd = calloc(1, dr_size);
    struct index_record *tmpi;

    // contuninue until eof
    while (fread(tmpd, dr_size, 1, f) == 1) { // başında soru işareti varsa silinmiştir
        if (tmpd->name[0] != '?') {
            tmpi = calloc(1, ir_size);
            memset(tmps, 0, 2 * NAMESIZE + 1);

            strcpy(tmps, tmpd->name);
            strcat(tmps, "-");
            strcat(tmps, tmpd->surname);

            strcpy(tmpi->id, tmps);

            tmpi->index = index;
            insert_index(tmpi);
        }

        index += dr_size;
    }

    fclose(f);
    debug("end of addressbook_init()");
    free(tmpd);
    return 0;
}

void list_id()
{
    char c;
    printf("Please enter a character: ");
    scanf(" %[^\n]c", &c);

    struct index_record *current = index_root;
    while (current != NULL) {
        if (current->id[0] == c) {
            printf("%s\n", current->id);
        }
        current = current->next;
    }
}

int remove_record()
{

    struct index_record *ir = getid();

    if (ir == NULL) // can not find
        return 1;

    FILE *f = fopen(DATA_FILE_NAME, "rb+");
    fseek(f, ir->index, SEEK_SET);
    fwrite("?", 1, 1, f);
    fclose(f);

    remove_index(ir);

    return 0;
}


int find_record()
{
    struct index_record *ir = getid();

    if (ir == NULL) // can not find
        return 1;

    FILE *f = fopen(DATA_FILE_NAME, "rb");
    if (f == NULL)
        return 1;
    struct data_record dr;
    fseek(f, ir->index, SEEK_SET);
    fread(&dr, sizeof(struct data_record), 1, f);

    print_record(&dr);
    fclose(f);
    return 0;
}

int list_record()
{
    if (index_root == NULL)
        return 1;

    FILE *f = fopen(DATA_FILE_NAME, "rb");
    if (f == NULL)
        return 1;

    struct data_record dr;
    struct index_record *current = index_root;

    while (current != NULL) {
        fseek(f, current->index, SEEK_SET);
        fread(&dr, dr_size, 1, f);

        current = current->next;
        if (dr.name[0] != '?') {
            print_record(&dr);
        }
    }
    fclose(f);
    return 0;
}

void addressbook_exit()
{
    index_write();
}

struct index_record *getid()
{
    char id[2 * NAMESIZE + 1];
    printf("Enter Name-Surname (Please put hyphen between): ");
    scanf(" %[^\n]s", id);

    return search_index(id);
}


void print_record(struct data_record *dr)
{
    printf("\n-------\n");
    printf("Name: %s\n", dr->name);
    printf("Surname: %s\n", dr->surname);
    printf("Address: %s\n", dr->address);
    printf("Notes: %s\n", dr->notes);
    printf("-------\n\n");
}