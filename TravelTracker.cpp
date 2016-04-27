/*-------------------------------------------------
// CSCI 2270 Data Structures                     //
// Spring 2016                                   //
// Final Project                                 //
// Alex Thompson                                 //
-------------------------------------------------*/

/*-----------------------------------------------------------------
Function definitions for the travel tracker class.
-----------------------------------------------------------------*/
#include "TravelTracker.h"
#include "Graph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

///////////////////////////////
// Constructor and Destructor
///////////////////////////////

TravelTracker::TravelTracker()
{
    //ctor
}

TravelTracker::~TravelTracker()
{
    //dtor
}

///////////////////////////////
// Private functions
///////////////////////////////

/*-----------------------------------------------------------------
Checks to see if a city has been visited before. If it has, increments
the stored value by 1. If it hasn't been visited, a new entry is created
with an initial value of 1.
-----------------------------------------------------------------*/
void TravelTracker::updateVisits(string name)
{
    for (int i=0; i<visitedCities.size(); i++)
    {
        if (visitedCities[i].cityName == name)
        {
            visitedCities[i].numberOfVisits ++;
            return;
        }
    }
    visitedCity newVisit = visitedCity(name, 1);
    visitedCities.push_back(newVisit);
}

/*-----------------------------------------------------------------
Sets the initial starting location of the user for the initialize()
function. Returns a boolean value due to constraints of the initialize()
function.
-----------------------------------------------------------------*/
bool TravelTracker::setStartingCity(string location)
{
    vertex* test = cityMap.findVertex(location);
    if (test == NULL)
    {
        cout << "Sorry. We couldn't find that city. Please try another location." << endl;
        return false;
    }
    else
    {
        cout << "Setting your current location to: " << test->name << endl;
        currentPosition = test;
        return true;
    }
}

///////////////////////////////
// Public Functions
///////////////////////////////

/*-----------------------------------------------------------------
Changes the user's status to active traveling and resets both the
current trip distance and the current trip vector. Also updates
the visitedCities vector with the current location.
-----------------------------------------------------------------*/
void TravelTracker::startTrip()
{
    if (traveling)
    {
        cout << "You are already traveling. You have to end your current trip to start a new one." << endl;
    }
    else
    {
        traveling = true;
        tripDistance = 0;
        cout << "New trip started with " << currentPosition->name << " as the origin." << endl;
        currentTrip.clear();
        currentTrip.push_back(currentPosition);
        updateVisits(currentPosition->name);
    }
}

/*-----------------------------------------------------------------
Changes the user's status so that travel is not being tracked. It
completes a current trip if there is one active. If a current trip is
ended, it creates a trip structure and stores it in the tripHistory
vector for later access.
-----------------------------------------------------------------*/
void TravelTracker::endTrip()
{
    if (!traveling)
    {
        cout << "You are not currently traveling. Feel free to start a new trip!" << endl;
    }
    else
    {
        traveling = false;
        cout << "Current trip ended with " << currentPosition->name << " as final destination." << endl;
        trip newTrip;
        newTrip.cities = currentTrip;
        newTrip.totalTravelDistance = tripDistance;
        tripHistory.push_back(newTrip);
    }
}

/*-----------------------------------------------------------------
Allows the user to move to a new location. If they are not actively logging
travel in a current trip, they are simply moved to the new location.
If they are currently tracking their travel, they are given a choice of
algorithms to determine how they get to their destination.
-----------------------------------------------------------------*/
void TravelTracker::travelToCity(string destination)
{
    if (!traveling)
    {
        vertex* newLocation = cityMap.findVertex(destination);
        if (newLocation == NULL)
        {
            cout << "That city was not found in the list of possible cities." << endl;
            return;
        }
        else
        {
            cout << "Setting current location to " << destination << endl;
            currentPosition = newLocation;
        }
        cout << "You are not currently traveling. Start a trip to begin tracking!" << endl;
        return;
    }
    else
    {
        vector <vertex*> shortestPath = cityMap.shortestPath(currentPosition->name, destination);  // vector to store the path they took to get to destination
        shortestPath.pop_back();                                                                   // the back of this vector will always be the starting point.
                                                                                                   // the starting point is always logged prior and can be ignored.
        int totalStops = shortestPath.size();
        for (int i=0; i<totalStops; i++)
        {
            currentTrip.push_back(shortestPath.back());
            cout << "Traveling to: " << (shortestPath.back())->name << endl;
            updateVisits((shortestPath.back())->name);
            if (i == (totalStops-1))
            {
                tripDistance = tripDistance + (shortestPath.back())->distance;                     // updates distances once there is only one entry left in the
                totalTravelDistance = totalTravelDistance + (shortestPath.back())->distance;       // vector. It will always be the destination which contains the
                cout << "Arriving at: " << (shortestPath.back())->name << endl;                    // accurate distance information for the trip. Also resets the
                currentPosition = shortestPath.back();                                             // user's current location.
            }
            shortestPath.pop_back();
        }
        cout << "Miles traveled on current trip: " << tripDistance <<  " miles" <<endl;
        cout << "Total lifetime miles traveled: " << totalTravelDistance << " miles" << endl;
        cityMap.resetVertexStatus();
    }

}

/*-----------------------------------------------------------------
Will display the shorted route a destination from the user's current position.
They will have their choice of algorithm to decide how the path is calculated.
Displays the path once determined.
-----------------------------------------------------------------*/
void TravelTracker::findShortestRoute(string destination)
{
    vector <vertex*> shortestPath = cityMap.shortestPath(currentPosition->name, destination);
    if (!shortestPath.empty())
    {
        cout << "The shortest path is: " << (shortestPath.back())->name;
        shortestPath.pop_back();
        int totalStops = shortestPath.size();
        for (int i=0; i<totalStops; i++)
        {
            cout << "->" << (shortestPath.back())->name;
            shortestPath.pop_back();
        }
        cout << endl;
    }
    cityMap.resetVertexStatus();
}


/*-----------------------------------------------------------------
Displays information relevant to the current trip if the user is traveling.
Will display all cities traveled to and the total miles logged on the trip.
-----------------------------------------------------------------*/
void TravelTracker::printCurrentTrip()
{
    if (!traveling)
    {
        cout << "You are not currently traveling. Start a trip to begin tracking!" << endl;
        return;
    }
    else
    {
        cout << "======CURRENT TRIP DATA=======" << endl;
        cout << "Route traveled: " << currentTrip[0]->name;
        for (int i=1; i<currentTrip.size(); i++)
        {
            cout << "->" << currentTrip[i]->name;
        }
        cout << "\nMiles traveled: " << tripDistance << endl;
    }
}

/*-----------------------------------------------------------------
Displays information regarding all previously logged trips. Trips are
stored/displayed in the order in which they were logged. They will show
the paths taken from start to finish and the total miles logged for each
one.
-----------------------------------------------------------------*/
void TravelTracker::printTripHistory()
{
    cout << "======TOTAL LIFETIME TRAVEL HISTORY======" << endl;
    if (tripHistory.empty())
    {
        cout << "You currently have no logged completed trips. Go traveling!" << endl;
        return;
    }
    else
    {
        for (int i=0; i<tripHistory.size(); i++)
        {
            cout << "Trip " << i+1 << ": " << ((tripHistory[i].cities)[0])->name;
            for (int j=1; j<(tripHistory[i].cities).size(); j++)
            {
                cout << "->" << ((tripHistory[i].cities)[j])->name;
            }
            cout << "\nMiles traveled: " << tripHistory[i].totalTravelDistance << endl;;
        }
    }
}

/*-----------------------------------------------------------------
Outputs the user's total lifetime miles traveled.
-----------------------------------------------------------------*/
void TravelTracker::getTotalTravel()
{
    cout << "Your current lifetime travel is: " << totalTravelDistance << " miles" << endl;
}

/*-----------------------------------------------------------------
Will display all cities within one edge of the user's current position.
It does this by looking at the adjacency list for the current location.
-----------------------------------------------------------------*/
void TravelTracker::getAdjCities()
{
    cout << "Cities within one stop of " << currentPosition->name << ":" << endl;
    for (int i=0; i<(currentPosition->adj).size(); i++)
    {
        cout << ((currentPosition->adj)[i].v)->name << ", " << (currentPosition->adj)[i].weight << " miles away" << endl;
    }
}

/*-----------------------------------------------------------------
Will display all cities visited/passed through by the user and the total
number of times the user has been there.
-----------------------------------------------------------------*/
void TravelTracker::getVisitedCities()
{
    cout << "======TOTAL NUMBER OF VISITS TO CITIES======" << endl;
    if (visitedCities.empty())
    {
        cout << "You currently have no logged visits to any cities. Go traveling!" << endl;
        return;
    }
    else
    {
        for (int i=0; i<visitedCities.size(); i++)
        {
            cout << visitedCities[i].cityName << ": visited " << visitedCities[i].numberOfVisits << " times" << endl;
        }
    }
}

/*-----------------------------------------------------------------
Will display all possible destinations that the user is capable of visiting.
User has choice of 3 different methods to display them using either
the vertices list of the graph or using a traversal method to go through
all nodes in the graph in a particular order based on a starting point.
-----------------------------------------------------------------*/
void TravelTracker::printCities()
{
    char selection;
    string startingCity;
    cout << "How would you like the cities to be displayed?" << endl;
    cout << "1. Display nodes and their connections using the vertices list" << endl;
    cout << "2. Display nodes as they are traversed using a Breadth-First traversal" << endl;
    cout << "3. Display nodes as they are traversed using a Depth-First traversal" << endl;
    cin >> selection;
    switch(selection)
    {
        case '1':
            cityMap.printVertices();
            break;
        case '2':
            cout << "Enter a city to start the traversal:" << endl;
            cin.ignore();
            getline(cin,startingCity);
            cityMap.BFTraversal(startingCity);
            break;
        case '3':
            cout << "Enter a city to start the traversal:" << endl;
            cin.ignore();
            getline(cin,startingCity);
            cityMap.DFTraversal(startingCity);
            break;
        default:
            cout << "Please enter an integer value from 1 to 3." << endl;
    }
}

/*-----------------------------------------------------------------
Given a file name, this function will attempt to construct a graph with
the appropriate data and connections. For this function to work properly,
the file has to be formatted in a particular way. See "USCities.txt" as
an example of how the file needs to be formatted.
-----------------------------------------------------------------*/
void TravelTracker::importGraphData(char* fileName)
{
    ifstream readFile(fileName);
    string currentLine, currentElement;
    vector <string> cities;
    while (getline(readFile, currentLine))
    {
        vector <string> elements;
        stringstream ss(currentLine);
        while (getline(ss, currentElement, ','))
        {
            elements.push_back(currentElement);
        }
        if (elements[0] == "cities")
        {
            for (int i=1; i<elements.size(); i++)
            {
                cityMap.addVertex(elements[i]);      // adds a vertex for each city name in the first row of the file
                cities.push_back(elements[i]);
            }
        }
        else
        {
            for (int i=1; i<elements.size(); i++)
            {
                if (stoi(elements[i]) >=1)          // adds an edge to the graph with the appropriate data if the text file indicates an edge is present (weight >=1)
                {
                    cityMap.addEdge(elements[0], cities[i-1], stoi(elements[i]));
                }
            }
        }
    }
}

/*-----------------------------------------------------------------
Initializes variables in the tracker to their proper initial states.
Gives a brief introduction to the user and prompts them for a city to use
as their starting location.
-----------------------------------------------------------------*/
void TravelTracker::initialize()
{
    string startingLocation;
    cout << "Welcome to TravelTracker! This program will allow you to travel between a specified" << endl;
    cout << "set of cities. You can start new trips and track your progress as you go. You can" << endl;
    cout << "also get useful information about your current position and your lifetime travel" << endl;
    cout << "history." << endl << endl;
    cout << "Before getting started you have to pick a valid starting location from the" << endl;
    cout << "available cities. Please enter what city you would like to start at:" << endl;
    while (true)
    {
        getline(cin,startingLocation);
        if (setStartingCity(startingLocation) == true)
        {
            break;
        }
    }
    tripDistance = 0;
    totalTravelDistance = 0;
    traveling = false;
}
