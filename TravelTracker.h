/*-------------------------------------------------
// CSCI 2270 Data Structures                     //
// Spring 2016                                   //
// Final Project                                 //
// Alex Thompson                                 //
-------------------------------------------------*/

/*-----------------------------------------------------------------
Header file for my Travel Tracker class. Also includes definitions of
two structures that are used for storing previous travel data that
can be accessed later.
-----------------------------------------------------------------*/
#ifndef TRAVELTRACKER_H
#define TRAVELTRACKER_H
#include "Graph.h"
#include <vector>
#include <iostream>

/*-----------------------------------------------------------------
Structure that is used to track the total number of visits someone has
traveled to/through a city while the tracker is active.
-----------------------------------------------------------------*/

struct visitedCity
{
    std::string cityName;
    int numberOfVisits;
    visitedCity(std::string initName, int initVisits)
    {
        cityName = initName;
        numberOfVisits = initVisits;
    }
};

/*-----------------------------------------------------------------
Structure that is used to keep records of entire trips the user has
logged from start to finish. It stores the path they took through
all cities as well as the total number of miles they covered.
-----------------------------------------------------------------*/
struct trip
{
    std::vector<vertex*> cities;
    int totalTravelDistance;
};

class TravelTracker
{
    public:
        TravelTracker();
        ~TravelTracker();
        void startTrip();                                       // used to start tracking a new trip from the user
        void endTrip();                                         // used to end tracking on a trip and log it in tripHistory
        void travelToCity(std::string destination);             // allows user to move to a different city using their choice of algorithms
        void findShortestRoute(std::string destination);        // calculates the shortest path to a destination based on user's choice of algorithms
        void printCurrentTrip();                                // displays data pertaining to the current trip in progress
        void printTripHistory();                                // displays all records of prior completed trips
        void getTotalTravel();                                  // displays a user's total lifetime travel miles while the tracker is active
        void getAdjCities();                                    // displays all cities within one edge of the user's current position and their distance in miles
        void getVisitedCities();                                // displays all cities user has traveled to/through and the number of times visited
        void printCities();                                     // displays all possible destinations using user's choice of algorithm
        void importGraphData(char* fileName);                   // initializes the tracker's city graph based on a properly formatted text file containing the adjacency matrix
        void initialize();                                      // takes steps to initialize the Travel Tracker object to its proper state

    private:
        bool traveling;                                         // used to determine if user is currently tracking their movement
        vertex* currentPosition;                                // current location of the user
        std::vector<vertex*> currentTrip;                       // vector containing all cities visited on the current trip
        std::vector<trip> tripHistory;                          // vector containing all past completed trips
        int tripDistance;                                       // miles traveled on the current trip
        int totalTravelDistance;                                // total miles traveled on all completed and current trips
        std::vector<visitedCity> visitedCities;                 // vector containing all visited cities and the number of times they have been visited
        void updateVisits(std::string name);                    // used to update the visitedCities vector when traveling to a new location
        bool setStartingCity(std::string location);             // only used in the initialize() function to determine where the user first starts
        Graph cityMap;                                          // data structure holding all of the cities and their weighted connections

};

#endif // TRAVELTRACKER_H
