#ifndef SYSTEM_H
#define SYSTEM_H
#define MAX_TRIPS 100
#define MAX_RESERVATIONS 500
#define MAX_SEATS 50

typedef struct {
    int trip_id; //each trip
    char origin[100]; //start
    char destination[100]; //ending point
    char date[20]; //day
    char time[20]; //time of trip
    int total_seats; //total seats for the trip
} Trip;

typedef struct {
    int total_seats; //number of seats for trip
    int seats[MAX_SEATS]; //array for seat status
} SeatMap;

typedef struct {
    int reservation_id; //unique id for booking
    int trip_id; //which trip reservation is for
    char passenger[100]; //name of passenger
    int seat_number; //assigned seat
    char status[20]; //confirmed or cancelled
} Reservation;


extern Trip trips[MAX_TRIPS]; //stores all trips
extern int trip_count; //tracks number of trips
extern int next_trip_id; //unqie id for trip
extern Reservation reservations[MAX_RESERVATIONS]; //stores all reservations
extern int reservation_count; //number of reservations
extern int next_reservation_id;//gives unique ids
extern SeatMap seatmaps[MAX_TRIPS]; //stores seats for each trip

void load_trips(); //loads trips from the files
void save_trip(); //saves trips to the file
void add_trip(); //adds a new trip
void view_trips(); //shows list of trips
void delete_trip(); //deletes trip
void init_seatmap(SeatMap *map, int total); //initializes seat for trip
int find_available_seat(SeatMap *map); //searches for a free seat
void reserve_seat(SeatMap *map, int seat); //marks the seat as taken
void free_seat(SeatMap *map, int seat); //checks if a seat is taken


void load_reservation(); //reads reservation from file
void save_reservation(); //saves reservation to the file
void make_reservation(); //creates a new reservation
void cancel_reservation(); //cancels a booking
void view_reservation(); //displays the reservation
void generate_report(); //creates the report


#endif