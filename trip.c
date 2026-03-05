#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

Trip trips[MAX_TRIPS];
int trip_count = 0; //tracks ids used
int next_trip_id = 1; //ids
Reservation reservations[MAX_RESERVATIONS];
int reservation_count = 0; //tracks ids used
int next_reservation_id = 1; //ids
SeatMap seatmaps[MAX_TRIPS];

void load_trips() {
    FILE *file = fopen("trips.txt", "r"); //loads trip from file
    if (!file) {
        return;
    }

    fscanf(file, "%d\n%d\n", &trip_count, &next_trip_id);
    
    for (int i = 0; i < trip_count; i++) { //fills trip struct with each item
        char line[256];
        fgets(line, sizeof(line), file);

        char *token = strtok(line, ";");
        trips[i].trip_id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(trips[i].origin, token);

        token = strtok(NULL, ";");
        strcpy(trips[i].destination, token);

        token = strtok(NULL, ";");
        strcpy(trips[i].date, token);

        token = strtok(NULL, ";");
        strcpy(trips[i].time, token);

        token = strtok(NULL, ";");
        trips[i].total_seats = atoi(token);
        init_seatmap(&seatmaps[i], trips[i].total_seats);
    }
    fclose(file);
}

void save_trip() {
    FILE *file = fopen("trips.txt", "w");
    if (!file) {
        return;
    }
    fprintf(file, "%d\n%d\n", trip_count, next_trip_id);
    for (int i = 0; i < trip_count; i++) { //saves each trip into the trip format
        fprintf(file, "%d;%s;%s;%s;%s;%d\n", trips[i].trip_id, trips[i].origin, trips[i].destination, trips[i].date, trips[i].time, trips[i].total_seats);
    }
    fclose(file);
}
//adds new trip
//prompts the user for all detail such as origin, destination, etc
//initializes seats for the trip
void add_trip() { 
    if (trip_count >= MAX_TRIPS) { //checks if full
        printf("MAXIMUM TRIPS REACHED!\n");
    }

    Trip *trip = &trips[trip_count];
    trip->trip_id = next_trip_id++;

    printf("Origin: ");
    fgets(trip->origin, 100, stdin);
    trip->origin[strcspn(trip->origin,"\n")] = 0;

    printf("Destination: ");
    fgets(trip->destination, 100, stdin);
    trip->destination[strcspn(trip->destination,"\n")] = 0;

    printf("Date(Y-M-D): ");
    fgets(trip->date, 100, stdin);
    trip->date[strcspn(trip->date,"\n")] = 0;

    printf("Time(H:M): ");
    fgets(trip->time, 100, stdin);
    trip->time[strcspn(trip->time,"\n")] = 0;

    printf("Total Seats (max %d): ", MAX_SEATS);
    scanf("%d", &trip->total_seats);
    getchar();

    init_seatmap(&seatmaps[trip_count], trip->total_seats);

    trip_count++;
    save_trip();
    printf("Your trip was added! Your ID is: %d\n", trip->trip_id);

}
//loops through the trips and then prints a summary with date, 
//time, and total seats
void view_trips() {
    for (int i = 0; i < trip_count; i++) {
        printf("ID:%d | %s -> %s | %s %s | Seats:%d\n", trips[i].trip_id, trips[i].origin, trips[i].destination, trips[i].date, trips[i].time, trips[i].total_seats);
    }
}
//deletes a trip by the id
//replaces deleted trip with last one
//decreases trip count
//saves the updated file
void delete_trip() {
    int id;
    printf("Enter your trip ID: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < trip_count; i++) {
        if (trips[i].trip_id == id) {
            trips[i] = trips[trip_count - 1];
            trip_count--;
            save_trip();
            printf("Your trip has been deleted.\n");
            return;
        }
    }
    printf("Trip is not found.\n");
}
//loops through the sears and finds the first free seat
int find_available_seat(SeatMap *map) {
    for (int i = 0; i < map->total_seats; i++) {
        if (map->seats[i] == 0) {
            return i + 1;
        }
    }
    return -1;
}
//marks the seat as taken
void reserve_seat(SeatMap *map, int seat) {
    if (seat > 0 && seat <= map->total_seats) {
        map->seats[seat - 1] = 1;
    }
}
//marks the seat as free
void free_seat(SeatMap *map, int seat) {
    if (seat > 0 && seat <= map->total_seats) {
        map->seats[seat - 1] = 0;
    }
}
//all the free seats
//sets the total seats for the trip
void init_seatmap(SeatMap *map, int total) {
    map->total_seats = total;
    for (int i = 0; i < MAX_SEATS; i++) {
        map->seats[i] = 0;
    }
}