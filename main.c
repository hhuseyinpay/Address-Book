//
// Created by hhp on 28/04/2017.
//

#include "dbg.h"
#include "address_book.h"


void print_menu(int *answer);

int main()
{
    addressbook_init();
    printf("\nMy Address Book Application\n\n");

    int choice;
    while (1) {
        print_menu(&choice);

        switch (choice) {
            case 1:

                if(new_record())
                    printf("\n**Duplicate record**\n");
                else
                    printf("\nRecord has been added\n\n");
                break;
            case 2:

                if(update_record()) {

                }


                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                // exit
                return 0;
            default:
                log_info("Wrong parameter");
        }
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
