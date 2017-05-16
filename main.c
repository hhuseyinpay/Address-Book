//
// Created by hhp on 28/04/2017.
//

#include "dbg.h"
#include "address_book.h"


void print_menu(int *answer);

int main()
{
    setbuf(stdout, NULL);
    addressbook_init();
    printf("\nMy Address Book Application\n\n");

    int choice;
    while (1) {
        print_menu(&choice);

        switch (choice) {
            case 1:

                if (new_record())
                    printf("\n**Duplicate record**\n");
                else
                    printf("\nRecord has been added\n\n");
                break;
            case 2:

                list_id();
                if (update_record())
                    printf("\n**Record did not found or record exist**\n");
                 else
                    printf("\nRecord has been updated\n");

                break;
            case 3:

                list_id();
                if (remove_record())
                    printf("\n**Record did not found**\n");
                else
                    printf("\nRecord has been deleted\n");

                break;
            case 4:

                list_id();
                if (find_record())
                    printf("\n**Record did not found**\n");

                break;
            case 5:
                if (list_record())
                    printf("\n**Records did not found**\n");
                break;
            case 6:
               addressbook_exit();
                return 0;
            default:
                printf("Wrong parameter\n");
        }
        printf("\n\n\n");
        fflush(stdout);
        fflush(stdin);
    }
}

void print_menu(int *answer)
{

    //print the user menu
    printf("1.\tAdd New Record \n");
    printf("2.\tUpdate A Record \n");
    printf("3.\tDelete A record \n");
    printf("4.\tFind A Record \n");
    printf("5.\tList Records \n");
    printf("-------------------------------------\n");
    printf("6. Exit \n");
    printf("Enter your choice ==> ");
    scanf("%d", answer);
    printf("\n");
}
