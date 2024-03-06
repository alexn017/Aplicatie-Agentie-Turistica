#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Class representing a station
class Station
{
private:
    string name;
    string startDate;
    string endDate;
    double price;
    int seatsAvailable;

public:
    Station(const string &n, const string &start, const string &end, double p, int seats)
        : name(n), startDate(start), endDate(end), price(p), seatsAvailable(seats) {}

    // Getter methods
    string getName() const { return name; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }
    double getPrice() const { return price; }
    int getSeatsAvailable() const { return seatsAvailable; }

    // Display station details
    void displayStation() const
    {
        cout << "Name: " << name << endl;
        cout << "Period of stay: " << startDate << " - " << endDate << endl;
        cout << "Price: $" << price << endl;
        cout << "Seats available: " << seatsAvailable << endl;
    }

    // Update the number of available seats
    void updateSeats(int numSeats)
    {
        seatsAvailable -= numSeats;
    }
};

class Customer
{
private:
    string name;
    string stationName;
    int numSeats;

public:
    Customer(const string &n, const string &station, int seats)
        : name(n), stationName(station), numSeats(seats) {}

    // Save the booking details to a file
    void saveBooking() const
    {
        ofstream file("clients.txt", ios::app);
        if (!file)
        {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        file << "Name: " << name << endl;
        file << "Station: " << stationName << endl;
        file << "Seats booked: " << numSeats << endl;
        file << "---------------------------" << endl;

        file.close();
    }
};

bool verifyPassword()
{
    char password[20], my_password[20] = "123";
    int i;
    char ch;
    system("cls");
    printf("PASSWORD: ");
    i = 0;
    do
    {
        ch = getch();
        password[i] = ch;
        if (ch != 27 && ch != 13)
            putch('*');
        else
            break;
        i++;
    } while (i < 19);
    password[i] = '\0';
    if (strcmp(password, my_password) != 0)
    {
        printf("\n\nIncorrect password !!!");
        _getch();
        return false; // if the password is incorrect it will exit the program }
    }
    printf("\n\nThe password is correct so the program is executed !");
    _getch();
    return true;
}

void help()
{
    cout << "This program allows people to book vacations to different stations.\n You can use the menu by choosing one out of the 6 options." << endl;
    system("pause");
}

// Function to write station data to file
void writeStationToFile(const vector<Station> &stations)
{
    ofstream file("stations.txt");
    if (!file)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (const Station &station : stations)
    {
        file << station.getName() << "," << station.getStartDate() << ","
             << station.getEndDate() << "," << station.getPrice() << ","
             << station.getSeatsAvailable() << endl;
    }

    file.close();
}

// Function to read station data from file
vector<Station> readStationsFromFile()
{
    vector<Station> stations;
    ifstream file("stations.txt");
    if (!file)
    {
        cerr << "Error opening file for reading." << endl;
        return stations;
    }

    string line;
    while (getline(file, line))
    {
        string name, start, end;
        double price;
        int seats;
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, start, ',');
        getline(ss, end, ',');
        ss >> price;
        ss.ignore();
        ss >> seats;
        stations.emplace_back(name, start, end, price, seats);
    }

    file.close();
    return stations;
}

// Function to display stations sorted by name
void displayStations(const vector<Station> &stations)
{
    if (stations.empty())
    {
        cout << "No stations available." << endl;
        system("cls");

        return;
    }

    vector<Station> sortedStations = stations;
    sort(sortedStations.begin(), sortedStations.end(), [](const Station &s1, const Station &s2)
         { return s1.getName() < s2.getName(); });

    for (const Station &station : sortedStations)
    {
        station.displayStation();
        cout << endl;
    }
}

// Function to add a new station
void addStation(vector<Station> &stations)
{
    string name, startDate, endDate;
    double price;
    int seats;

    cout << "Enter the name of the station: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter the start date of the period of stay: ";
    getline(cin, startDate);

    cout << "Enter the end date of the period of stay: ";
    getline(cin, endDate);

    cout << "Enter the price: $";
    cin >> price;

    cout << "Enter the number of seats available: ";
    cin >> seats;

    stations.emplace_back(name, startDate, endDate, price, seats);
    writeStationToFile(stations);
    cout << "Station added successfully." << endl;
    system("cls");
}

// Function to display available seats sorted by a specified criteria
void displayAvailableSeats(const vector<Station> &stations)
{
    if (stations.empty())
    {
        cout << "No stations available." << endl;
        return;
        system("cls");
    }

    char choice;
    cout << "Sort by:\n1. Price\n2. Seats available\nEnter your choice: ";
    cin >> choice;

    vector<Station> sortedStations = stations;

    if (choice == '1')
    {
        sort(sortedStations.begin(), sortedStations.end(), [](const Station &s1, const Station &s2)
             { return s1.getPrice() < s2.getPrice(); });
    }
    else if (choice == '2')
    {
        sort(sortedStations.begin(), sortedStations.end(), [](const Station &s1, const Station &s2)
             { return s1.getSeatsAvailable() > s2.getSeatsAvailable(); });
    }
    else
    {
        cout << "Invalid choice." << endl;
        system("pause");
        return;
    }

    for (const Station &station : sortedStations)
    {
        station.displayStation();
        cout << endl;
    }
    system("pause");
}

// Function to book a station for a customer
void bookStation(vector<Station> &stations)
{
    if (stations.empty())
    {
        cout << "No stations available." << endl;
        system("cls");
        return;
    }

    string name, startDate, endDate;
    int numSeats;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter the start date of the desired period of stay: ";
    getline(cin, startDate);

    cout << "Enter the end date of the desired period of stay: ";
    getline(cin, endDate);

    cout << "Enter the number of seats you want to book: ";
    cin >> numSeats;

    // Find a station that matches the specified period of stay and has enough available seats
    for (auto it = stations.begin(); it != stations.end(); ++it)
    {
        if (it->getStartDate() == startDate && it->getEndDate() == endDate && it->getSeatsAvailable() >= numSeats)
        {
            it->updateSeats(numSeats);
            if (it->getSeatsAvailable() == 0)
            {
                stations.erase(it);
            }
            writeStationToFile(stations);

            Customer customer(name, it->getName(), numSeats);
            customer.saveBooking();
            cout << "Booking successful!" << endl;
            system("pause");
            return;
        }
    }

    cout << "No stations available for the specified period of stay or the desired number of seats." << endl;
    system("pause");
}

// Function to display the menu
void displayMenu()
{
    cout << "MENU" << endl;
    cout << "1. Display stations" << endl;
    cout << "2. Add a new station" << endl;
    cout << "3. Display available seats" << endl;
    cout << "4. Book a station" << endl;
    cout << "5. Help" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    if (verifyPassword() == true)
    {

        vector<Station> stations = readStationsFromFile();
        char choice;

        do
        {
            system("cls");
            displayMenu();
            cin >> choice;

            switch (choice)
            {
            case '1':
                displayStations(stations);
                system("pause");
                break;
            case '2':
                addStation(stations);
                break;
            case '3':
                displayAvailableSeats(stations);
                break;
            case '4':
                bookStation(stations);
                break;
            case '5':
                help();
                break;
            case '6':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }

            cout << endl;
        } while (choice != '6');
    }
    return 0;
}