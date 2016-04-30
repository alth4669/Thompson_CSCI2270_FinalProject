/*-------------------------------------------------
// CSCI 2270 Data Structures                     //
// Spring 2016                                   //
// Final Project                                 //
// Alex Thompson                                 //
-------------------------------------------------*/

/*-----------------------------------------------------------------
For the final project of this course, I designed a Travel Tracker program
that is capable of recording travel through a pre-determined set of locations.
It can keep track of your current travel in real time and stores data
regarding previous trips for reference.
-----------------------------------------------------------------*/

#include <iostream>
#include "Graph.h"
#include "TravelTracker.h"
#include "Utilities.h"
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    TravelTracker testTracker;
    testTracker.importGraphData(argv[1]);         // imports the necessary data from a properly formatted text file
    testTracker.initialize();                     // takes steps to initialize the Travel Tracker object to its proper state
                                                  // and gives a brief introduction to the user
    int selection;
    string destination;
    while (true)
    {
        displayMenu();
        cin >> selection;
        switch (selection)
        {
            case 1:
                testTracker.startTrip();
                break;
            case 2:
                testTracker.endTrip();
                break;
            case 3:
                cout << "Enter a destination:" << endl;
                cin.ignore();
                getline(cin,destination);
                testTracker.travelToCity(destination);
                break;
            case 4:
                cout << "Enter a destination:" << endl;
                cin.ignore();
                getline(cin,destination);
                testTracker.findShortestRoute(destination);
                break;
            case 5:
                testTracker.printCurrentTrip();
                break;
            case 6:
                testTracker.printTripHistory();
                break;
            case 7:
                testTracker.getTotalTravel();
                break;
            case 8:
                testTracker.getAdjCities();
                break;
            case 9:
                testTracker.getVisitedCities();
                break;
            case 10:
                testTracker.printCities();
                break;
            case 11:
                cout << "So long and safe travels!" << endl;
                return 0;
            default:
                cout << "Please enter an integer value from 1 to 11." << endl;
        }

    }
    return 0;
}
