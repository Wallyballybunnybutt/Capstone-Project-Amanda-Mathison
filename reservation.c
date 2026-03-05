#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

void load_reservation() {
    FILE *file = fopen("reservation.txt", "r"); //opens and reads the file
    if (!file) {
        return;
    }
//fills the reservation with ID, trip ID, name, seat, and status
    fscanf(file, "%d\n%d\n", &reservation_count, &next_reservation_id);
    for (int i = 0; i < reservation_count; i++) {
        char line[256];
        fgets(line, sizeof(line), file);
        char *token = strtok(line, ";");
        reservations[i].reservation_id = atoi(token);

        token = strtok(NULL, ";");
        reservations[i].trip_id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(reservations[i].passenger, token);

        token = strtok(NULL, ";");
        reservations[i].seat_number = atoi(token);

        token = strtok(NULL, ";");
        strcpy(reservations[i].status, token);
    }
    fclose(file);
}
//writes the reservation to the file
//same formatt as above
void save_reservation() {
    FILE *file = fopen("reservation.txt", "w");
    if (!file) {
        return;
    }
    fprintf(file, "%d\n%d\n", reservation_count, next_reservation_id);
    for (int i = 0; i < reservation_count; i++) {
        fprintf(file, "%d;%d;%s;%d;%s\n", reservations[i].reservation_id, reservations[i].trip_id, reservations[i].passenger, reservations[i].seat_number, reservations[i].status);
    }
    fclose(file);
}
void make_reservation() {
    int trip_id;
    char passenger[100];
    view_trips();

    printf("Enter your trip ID to reserve: ");
    scanf("%d", &trip_id);
    getchar();
//finds the trip in the memory
    Trip *trip = NULL;
    int trip_index = -1;
    for (int i = 0; i < trip_count; i++) {
        if (trips[i].trip_id == trip_id) {
            trip = &trips[i];
            trip_index = i;
            break;
        }
    }
    if (!trip) {
        printf("Trip not found!\n");
        return;
    }
    //finds available seat for trip and exits if their isn't any
    int seat = find_available_seat(&seatmaps[trip_index]);
    if (seat == -1) {
        printf("Their are no seats available for this trip!\n");
        return;
    }

    printf("Passenger name: ");
    fgets(passenger, 100, stdin);
    passenger[strcspn(passenger, "\n")] = 0;
    Reservation *res = &reservations[reservation_count++];//creates a new reservation in the array
    res->reservation_id = next_reservation_id++;//
    res->trip_id = trip_id;//
    strcpy(res->passenger, passenger);//
    res->seat_number = seat; //
    strcpy(res->status, "CONFIRMED!"); //creates a new reservation in the array

    reserve_seat(&seatmaps[trip_index], seat); //marks seat as taken
    save_reservation();
    printf("Your reservation has been confirmed! ID: %d | Seat: %d\n", res->reservation_id, seat);
//confirms seat reservation to the user
}

//reads the reservation from the user then finds it in the array
//frees the seat
//replaces canceled reservation with last one confirmed
void cancel_reservation() {
    int res_id;
    printf("enter your reservation ID that you would like to cancel: ");
    scanf("%d", &res_id);
    getchar();

    for (int i = 0; i < reservation_count; i++) {
        if (reservations[i].reservation_id == res_id) {
            int trip_index = -1;
            for (int j = 0; j < trip_count; j++) {
                if (trips[j].trip_id == reservations[i].trip_id) {
                    trip_index = j;
                }
            }
            if (trip_index != -1) {
                free_seat(&seatmaps[trip_index], reservations[i].seat_number);
            }
            reservations[i] = reservations[reservation_count - 1];
            reservation_count--;
            save_reservation();
            printf("Your reservation has been sucessfully cancelled!\n");
            return;
        }
    }
    printf("No ID found!\n");
}
//prints all the reservations with ID, trip ID, passenger, seat, and status
void view_reservation() {
    if (reservation_count == 0) { //if no reservation 
        printf("No reservation found. \n");
        return;
    }
    printf("\n%-4s %-8s %-20s %-5s %-10s\n", "ID", "TripID", "Passenger", "Seat", "Status");
    printf("%-4s %-8s %-20s %-5s %-10s\n", "----", "------", "--------------------", "----", "----------");
    for (int i = 0; i < reservation_count; i++) {
        printf("%-4d %-8d %-20s %-5d %-10s\n", reservations[i].reservation_id, reservations[i].trip_id, reservations[i].passenger, reservations[i].seat_number, reservations[i].status);
    }
}
//loops through the whole trip and checks how many seats are booked
//prints summary report with trip ID, route, and occupancy
void generate_report() {
    if (trip_count == 0) {
        printf("No trips are available at the moment.\n");
        return;
    }
    printf("= Trip Report =\n");
    for (int i = 0; i < trip_count; i++) {
        int booked = 0;
        for (int j = 0; j < reservation_count; j++) {
            if (reservations[j].trip_id == trips[i].trip_id) {
                booked++;
            }
        }
        printf("Trip ID: %d | %s -> %s | Booked: %d / %d\n", trips[i].trip_id, trips[i].origin, trips[i].destination, booked, trips[i].total_seats);
    }
}