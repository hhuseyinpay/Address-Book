//
// Created by hhp on 06/05/2017.
//

#include "dbg.h"
#include "address_book.h"


struct index_record *index_root;

int new_record()
{

    char name[NAMESIZE];
    char surname[NAMESIZE];
    char address[ADRSSIZE];
    char notes[NOTESIZE];

    struct data_record dr;

    printf("Name: ");
    scanf(" %[^\n]s", name);
    strcpy(dr.name, name);

    printf("Surname: ");
    scanf(" %[^\n]s", surname);
    strcpy(dr.surname, surname);

    printf("Address: ");
    scanf(" %[^\n]s", address);
    strcpy(dr.address, address);

    printf("Notes: ");
    scanf(" %[^\n]s", notes);
    strcpy(dr.notes, notes);


    struct index_record *ir = calloc(1, sizeof(struct index_record));

    char tmpid[2 * NAMESIZE];
    strcpy(tmpid, name);
    strcat(tmpid, surname);

    if (search_index(tmpid) != NULL) // id varsa kayıt gerçekleşmeyecek
        return 1;

    strcpy(ir->id, tmpid);
    ir->index = data_write(&dr);

    insert_index(ir);

    debug("New record: %s - %s - %s - %s", name, surname, address, notes);
    debug("New index: %s :%l ", ir->id, ir->index);

    return 0;
}

int update_record()
{
    char id[2 * NAMESIZE];
    printf("Enter Old Name and Surname (Please do not put space between): ");
    scanf(" %[^\n]s", id);
    struct index_record *ir = search_index(id);

    if (ir == NULL) // can not find
        return 1;


    char name[NAMESIZE];
    char surname[NAMESIZE];
    char address[ADRSSIZE];
    char notes[NOTESIZE];

    struct data_record dr;
    printf("New Name: ");
    scanf(" %[^\n]s", name);
    strcpy(dr.name, name);

    printf("New Surname: ");
    scanf(" %[^\n]s", surname);
    strcpy(dr.surname, surname);

    printf("New Address: ");
    scanf(" %[^\n]s", address);
    strcpy(dr.address, address);

    printf("New Notes: ");
    scanf(" %[^\n]s", notes);
    strcpy(dr.notes, notes);

    FILE *f = fopen(DATA_FILE_NAME, "ab");
    fseek(f, ir->index, SEEK_SET);
    fwrite(&dr, sizeof(struct data_record), 1, f);

    // remove index record and re add

    long i = ir->index;
    remove_index(ir);

    ir = calloc(1, sizeof(struct index_record));

    char tmpid[2 * NAMESIZE];
    strcpy(tmpid, name);
    strcat(tmpid, surname);
    strcpy(ir->id, tmpid);

    ir->index = i;

    insert_index(ir);

    return 0;
}

int addressbook_init()
{
    debug("addressbook_init()");
    index_root = calloc(1, sizeof(struct index_record));

    /* if index_read return success, initialization success*/
    if (index_read(index_root) == 0) {
        return 0;
    }

    int index = 0;
    char tmps[2 * NAMESIZE];
    struct data_record tmpd;
    struct index_record *tmpi = calloc(1, sizeof(struct index_record));

    FILE *f = fopen(DATA_FILE_NAME, "rb");

    if (f == NULL)
        return 1;

    // contuninue until eof
    while (data_read(f, &tmpd, index) == 0) {
        strcpy(tmps, tmpd.name);
        strcat(tmps, tmpd.surname);

        strcpy(tmpi->id, tmps);
        tmpi->index = index;
        insert_index(tmpi);

        index++;
    }

    fclose(f);
    debug("end of addressbook_init()");
    return 1;
}

void list_names()
{
    char c;
    printf("Please enter a character: ");
    scanf(" %[^\n]c", &c);

    struct index_record *current = index_root;
    while (current != NULL) {
        if (current->id[0] == c){
            //printf("%s %s",);
        }
        current = current->next;
    }
}
