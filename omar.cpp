#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

// Function to generate a unique ticket ID
std::string generateTicketID() {
    static int id = 1;  // Simple counter-based ID generator
    std::ostringstream oss;
    oss << "TID" << id++;
    return oss.str();
}

// Base class
class Flight {
public:
    virtual void book() = 0;  // Pure virtual function
    virtual ~Flight() {}
};

// Derived class for Round Trip
class RoundTrip : public Flight {
    std::string from;
    std::string to;
    std::string returnDate;
    std::string name;
    int age;
    std::string gender;
    std::string passportNumber;
    std::string birthDate;
    std::string ticketID;

public:
    void book() override {
        std::cout << "Enter departure location: ";
        std::cin >> from;
        std::cout << "Enter destination: ";
        std::cin >> to;
        std::cout << "Enter return date (DD/MM/YYYY): ";
        std::cin >> returnDate;
        getPassengerInfo();
        ticketID = generateTicketID();
        std::cout << "Round trip booked from " << from << " to " << to << " with return on " << returnDate << std::endl;
        std::cout << "Your Ticket ID: " << ticketID << std::endl;
        // Save the ticket information
        saveTicket("RoundTrip", from, to, returnDate);
    }

    void getPassengerInfo() {
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your age: ";
        std::cin >> age;
        std::cout << "Enter your gender: ";
        std::cin >> gender;
        std::cout << "Enter your passport number: ";
        std::cin >> passportNumber;
        std::cout << "Enter your birth date (DD/MM/YYYY): ";
        std::cin >> birthDate;
    }

    void saveTicket(const std::string& type, const std::string& from, const std::string& to, const std::string& returnDate) {
        std::ofstream file("tickets.txt", std::ios::app);
        file << ticketID << "," << type << "," << from << "," << to << "," << returnDate << "," << name << "," << age << "," << gender << "," << passportNumber << "," << birthDate << "\n";
        file.close();
    }
};

// Derived class for One Way
class OneWay : public Flight {
    std::string from;
    std::string to;
    std::string name;
    int age;
    std::string gender;
    std::string passportNumber;
    std::string birthDate;
    std::string ticketID;

public:
    void book() override {
        std::cout << "Enter departure location: ";
        std::cin >> from;
        std::cout << "Enter destination: ";
        std::cin >> to;
        getPassengerInfo();
        ticketID = generateTicketID();
        std::cout << "One way trip booked from " << from << " to " << to << std::endl;
        std::cout << "Your Ticket ID: " << ticketID << std::endl;
        // Save the ticket information
        saveTicket("OneWay", from, to);
    }

    void getPassengerInfo() {
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your age: ";
        std::cin >> age;
        std::cout << "Enter your gender: ";
        std::cin >> gender;
        std::cout << "Enter your passport number: ";
        std::cin >> passportNumber;
        std::cout << "Enter your birth date (DD/MM/YYYY): ";
        std::cin >> birthDate;
    }

    void saveTicket(const std::string& type, const std::string& from, const std::string& to) {
        std::ofstream file("tickets.txt", std::ios::app);
        file << ticketID << "," << type << "," << from << "," << to << "," << name << "," << age << "," << gender << "," << passportNumber << "," << birthDate << "\n";
        file.close();
    }
};

// Class for handling tickets
class Ticket {
public:

void displayTicket(const std::string& ticketId, const std::string& passengerName) {
    std::ifstream file("tickets.txt");
    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 7 && tokens[0] == ticketId && tokens[4] == passengerName) {
                std::cout << "Ticket Found: \n";
                std::cout << "Ticket ID: " << tokens[0] << "\n";
                std::cout << "Type: " << tokens[1] << "\n";
                std::cout << "From: " << tokens[2] << "\n";
                std::cout << "To: " << tokens[3] << "\n";
                std::cout << "Return Date: " << tokens[4] << "\n";
                std::cout << "Name: " << tokens[5] << "\n";
                std::cout << "Age: " << tokens[6] << "\n";
                std::cout << "Gender: " << tokens[7] << "\n";
                std::cout << "Passport Number: " << tokens[8] << "\n";
                std::cout << "Birth Date: " << tokens[9] << "\n";
                found = true;
                break;
            }
        }
        file.close();
        if (!found) {
            std::cout << "Ticket not found.\n";
        }
    }
};

// Function to display the main menu
void mainMenu() {
    int choice;
    while (true) {
        std::cout << "WELCOME TO WAVE AIRLINES\n";
        std::cout << "Choose your flight type\n";
        std::cout << "1. Round Trip\n";
        std::cout << "2. One Way\n";
        std::cout << "3. Check In\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        Flight* flight = nullptr;
        switch (choice) {
            case 1:
                flight = new RoundTrip();
                flight->book();
                delete flight;
                break;
            case 2:
                flight = new OneWay();
                flight->book();
                delete flight;
                break;
            case 3:
                {
                    std::string ticketId, passengerName;
                    std::cout << "Enter Ticket ID: ";
                    std::cin >> ticketId;
                    std::cout << "Enter Passenger Name: ";
                    std::cin >> passengerName;
                    Ticket ticket;
                    ticket.displayTicket(ticketId, passengerName);
                }
                break;
            case 4:
                std::cout << "Exiting the program.\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

// Main function
int main() {
    mainMenu();
    return 0;
}
