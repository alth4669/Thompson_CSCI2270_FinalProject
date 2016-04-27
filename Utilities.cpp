#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Utilities.h"
#include "Graph.h"

using namespace std;

void displayMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Start tracking a new trip" << endl;
    cout << "2. Complete/stop tracking your current trip" << endl;
    cout << "3. Travel to a city" << endl;
    cout << "4. Find shortest route to a city" << endl;
    cout << "5. Print details of your current trip" << endl;
    cout << "6. Print your lifetime history of all trips taken" << endl;
    cout << "7. Find out your lifetime amount of miles traveled" << endl;
    cout << "8. Find adjacent cities that are a single stop away" << endl;
    cout << "9. See how many times you've visited each city" << endl;
    cout << "10. Display all possible cities to travel to" << endl;
    cout << "11. Quit" << endl;
}

