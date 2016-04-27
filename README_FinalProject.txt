ReadMe file for the final project in CSCI 2270 Data Structures at CU Boulder.

Most recent update: 4/27/2016

Group Members: Alex Thompson

Project Description:

For the final project in this course, I will be working alone to implement a program that simulates a travel tracker in the United States.
This project will implement a graph data structure to store various US cities and the edges connecting them.
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
is the distance between them. A sample file "USCities.txt" will be included in this repository as an example of how the file needs
to be formatted.

How to Run:

This program is run using command line arguments. The second command line argument must be the file name of a .txt file containing the
adjacency matrix for the desired graph. If this text file is not formatted properly, the program will be unable to read the data properly
into the graph, most likely causing a crash. Additionally, make sure the executable is from "FinalProject.cpp". The text file needs to be formatted in the following ways:
    -the first line of the file must start with the word "cities"followed by a comma. Each city name will follow the comma and have a comma
    listed after it as well
    -each subsequent line of the file starts by listing the name of one of the cities in the graph. The row will contain integers corresponding
    to connections to cities given in the order in the first line. A value of -1 implies no connection, a value of 0 implies a connection to itself,
    and a value greater than or equal to 1 indicates a connection whose weight is the specified value.
    -the integers regarding the connections must be separated by commas with no spaces
There is a file in this repository called "USCities.txt" that can be used as an example to run the program. It provides the formatting
necessary for the graph to be created successfully.
When the program launches successfully, the user will be prompted by a welcome message and asked to input a starting location. It is important
to note that you cannot progress any further than this prompt unless you enter a valid city. Valid cities will be the city names listed in
the text file. Once you have successfully specified a starting location, you will be prompted with a very intuitive menu interface with multiple
options available. Simple input the integer value of the option you want to select.

Dependencies:

The only dependency that I know of so far is that you compile these files using C++11. Certain functions will not operate properly unless your
compiler is doing this. All operating systems should run this program normally and no extra software is needed. The necessary libraries have
all been included in the header files.

Contributors:

While I largely worked alone on this project, I would like to thank Holden Sheftel for providing advice/input during the design process.
In particular, he was very helpful in designing the shortest path algorithms.

Open Issues/Bugs:

So far as I know, the only portion of this code that is not working properly is the Bellman-Ford shortest path algorithm. If you select to travel to
a new location using this algorithm, you will likely encounter the following error:

terminate called after throwing an instance of 'std::bad_alloc'
what(): std::bad_alloc

and the program will crash. As of right now, I don't know what is causing this and any contributions to make it work would be greatly appreciated.
All of the other shortest path/traversal algorithms appear to be working normally. It is also possible there are other bugs I'm not aware of and keeping
an eye out for them would also be appreciated.

Enhancement Requests:

When I was initially coming up with this idea, I thought it would be interesting to implement a type of graph where multiple modes of travel (car,bus,plane,ect.)
could be utilized for travel. I thought there could be multiple edges between two vertices so long as the edges were all of different types or modes.
This could open the door for further methods of optimizing/tracking travel. You could track the individual distances logged by each mode of transportation
and take the costs of various modes into effect as well. Unfortunately, I was not able to implement this in time.
