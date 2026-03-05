# Capstone-Project-Amanda-Mathison

Problem Statement:
This project is tasked with building a bus reservation system that will manage bus trips and allow users to book, cancel, delete, view, reserve, and show reports of said trips. It should also be able to save trips to files.

Design and Architecture Details:
Overall, the project is spread into four different files: main.c, reservation.c, system.h, and trip.c. Main.c contains the main menu and the user interface loop. System.c implements seat management and trip management. Reservation.c implements reservation systems such as booking and then cancelling your reservation. System.h contains all the declarations and the different variables that are used throughout the project. 

Data Structures: Three structures were used: the trip structure, the SeatMap structure, and the Reservation structure. Trip includes a unique trip id, origin and destination, date and time, and the total number of seats available. SeatMap includes manages the seat availablility for each trip. Reservation includes the reservation id, the associated trip id, passenger name, seat number, and the reservation status. 

Features: Some of the features that are inlcuded in the design are a reporting system that shows a trip id, route, number of booked seats, and total number of available seats. Overall trip management where you are able to add, view, and delete the trip. Has a reservation system where you are able to make, cancel, and view a reservation. Has a few helper functions such as find_available_seat(), reserve_seat(), free_seat(), and init_seatmap(). The system also uses text files to store data and ensures that the data is saved after the program ends and once you start it again it loads the data. The system can generate a report showing trip id, route, number of booked seats, and total available seats.

Pros:
-Saves the data to files
-Is able to generate basic reports
-Simple, easy menu to follow along with(Could maybe use a little improvement)
Cons:
-There is currently no waitlist feature implemented
-Currently, deleting a trip doesn't remove the reservation
-Use's a fixed-sized array
