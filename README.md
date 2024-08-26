# Train Reservation System

A console-based Train Reservation System developed in C++ to demonstrate Object-Oriented Programming (OOP) principles. This project allows users to manage train reservations by viewing and updating train details, reserving and canceling tickets, and checking reservation statuses.

## Features

- **Train Details Management**: View and update information about trains including seat availability and routes.
- **Ticket Reservation**: Reserve tickets for different classes and receive a reservation number.
- **Ticket Cancellation**: Cancel previously made reservations and update the system records.
- **Reservation Status Check**: Retrieve and display the status of a reservation using a reservation number.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- Basic understanding of C++ and Object-Oriented Programming concepts

### Compilation

1. Clone the repository:

    ```bash
    git clone https://github.com/Chandanmajhi7/TrainReservationSystem.git
    cd TrainReservationSystem
    ```

2. Compile the code using g++:

    ```bash
    g++ MyTrain.cpp -o TrainReservationSystem
    ```

3. Run the executable:

    ```bash
    ./TrainReservationSystem
    ```

### Usage

1. **View Train Details**: Choose option `1` to display current train information.
2. **Update Train Details**: Choose option `2` to input or modify train details.
3. **Reserve a Ticket**: Choose option `3` to reserve a ticket, providing necessary details.
4. **Cancel a Ticket**: Choose option `4` to cancel a reservation by entering the reservation number.
5. **Check Ticket Status**: Choose option `5` to check the status of a reservation using the reservation number.
6. **Exit**: Choose option `6` to exit the application.

## File Format

- **Train1.dat**: Stores information about trains.
- **Ticket1.dat**: Stores reservation details.



