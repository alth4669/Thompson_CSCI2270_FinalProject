ReadMe file for the final project in CSCI 2270 Data Structures at CU Boulder.

Most recent update: 4/17/2016

Students working on this project: Alex Thompson

Project Description:

For the final project in this course, I will be working alone to implement a program that simulates a travel tracker in the United States.
This project will implement a graph data structure to store the capital cities of all 50 states in the U.S. and the edges connecting them.
While this program is running, the user will be able to pick a starting location and begin to travel through the US. This graph will
use weighted edges. As a user travels from city to city, the program will keep track of how far they have traveled and possibly by
what means (have not decided if this will be implemented yet). The program will optimize travel between cities using shortest distance
algorithms such as Dijkstra's algorithm. Will possibly implement further optimization functionality surrounding mode of travel. I will
be designing this program to track travel in the US, but the code will be written such that any text file that is formatted properly
and has the correct information can be used to generate a different graph with the same functionality, such as cities in Europe. The
text file needs to be formatted such that the first line of text begins with the word "cities" followed by a comma, then all city
names that are to be included in the graph separated by commas. Each subsequent line will have the name of a city followed by the
connections to all other cities in the graph, separated by commas. A value of -1 will indicate there is no connection between those
two cities. 0 indicates the city is connected to itself. All other positive values indicate a link between those cities and the value
is the distance between them. A sample file "US_cities.txt" will be included in this repository as an example of how the file needs
to be formatted.
