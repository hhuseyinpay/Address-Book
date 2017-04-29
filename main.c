//
// Created by hhp on 28/04/2017.
//

#include "dbg.h"


#define MENU "Main Menu\n=====================\n1.\tAdd New Record\n2.\tUpdate A Record\n\
3.\tDelete A record\n4.\tFind A Record\n5.\tList Records\n6.\tExit\n\nEnter your choice ==> "

int main()
{
    printf("\nMy Address Book Application\n\n");

    int choice;
    while (1) {
        printf(MENU);
        fscanf(stdin, "%d", &choice);

        switch (choice) {
            case 1:
                break;
            case 2:
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