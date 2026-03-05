#include <stdio.h>
#include <stdlib.h>
#include "system.h"

int main() {
    int choice;
    load_trips();
    load_reservation();

    while (1) {
        printf("\n= Bus Reservation System =\n");
        printf("1. Add Trip\n");
        printf("2. View Trips\n");
        printf("3. Delete Trip\n");
        printf("4. Make a Reservation\n");
        printf("5. Cancel your Reservation\n");
        printf("6. View your Reservation\n");
        printf("7. Reports\n");
        printf("8. Exit\n");
        printf("Choice: \n");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: 
                add_trip();
                break;
            case 2:
                view_trips();
                break;
            case 3:
                delete_trip();
                break;
            case 4:
                make_reservation();
                break;
            case 5:
                cancel_reservation();
                break;
            case 6:
                view_reservation();
                break;
            case 7:
                generate_report();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice!\n");                        
        }
    }
}