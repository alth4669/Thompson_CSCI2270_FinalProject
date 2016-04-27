/*-------------------------------------------------
// CSCI 2270 Data Structures                     //
// Spring 2016                                   //
// Final Project                                 //
// Alex Thompson                                 //
-------------------------------------------------*/

/*-----------------------------------------------------------------
Function definitions for my modified graph class.
-----------------------------------------------------------------*/

#include "Graph.h"
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

///////////////////////////////////
// Constructor and Destructor
///////////////////////////////////

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

///////////////////////////////////
// Private functions
///////////////////////////////////

/*-----------------------------------------------------------------
Basic implementation of Dijkstra's Algorithm. Returns a path to a destination
that covers the fewest number of miles.
-----------------------------------------------------------------*/
vector<vertex*> Graph::dijkstraSP(string startingCity, string endingCity)
{
    vertex* foundCity1 = findVertex(startingCity);
    vertex* foundCity2 = findVertex(endingCity);
    if ((foundCity1 == NULL) | (foundCity2 == NULL))
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else
    {
        vector <vertex*> shortestPath;
        vector <vertex*> solvedCities;
        foundCity1->distance = 0;
        foundCity1->solved = true;
        solvedCities.push_back(foundCity1);
        while (!foundCity2->solved)                                         // proceeds so long as the destination is not solved
        {
            int minDistance = INT_MAX;
            vertex* solvedV = NULL;
            vertex* parent = NULL;
            for (int i=0; i<solvedCities.size(); i++)
            {                                                               // checks each solved city and each of its non-visited
                vertex* n = solvedCities[i];                                // connections to determine which city is the next one
                for (int j=0; j<(n->adj).size(); j++)                       // to mark solved
                {
                    if (!((n->adj)[j].v)->solved)
                    {
                        int dist = n->distance + (n->adj)[j].weight;
                        if (dist < minDistance)
                        {
                            solvedV = (n->adj)[j].v;
                            minDistance = dist;
                            parent = n;
                        }
                    }
                }
            }
            solvedV->distance = minDistance;
            solvedV->parent = parent;
            solvedV->solved = true;
            solvedCities.push_back(solvedV);
        }
        vertex* temp = foundCity2;
        while (temp != foundCity1)
        {
            shortestPath.push_back(temp);
            temp = temp->parent;
        }
        shortestPath.push_back(temp);
        return shortestPath;
    }
}

/*-----------------------------------------------------------------
Basic implementation of the Bellman-Ford algorithm. Should return a path to
the destination that covers the fewest number of miles.
NOTE(4/27/16): This function does not appear to be functioning normally.
-----------------------------------------------------------------*/
vector<vertex*> Graph::bellmanFordSP(string startingCity, string endingCity)
{
    vertex* foundCity1 = findVertex(startingCity);
    vertex* foundCity2 = findVertex(endingCity);
    if ((foundCity1 == NULL) | (foundCity2 == NULL))
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else
    {
        vector<vertex*> shortestPath;
        for (int i=0; i<vertices.size(); i++)
        {
            vertices[i]->distance = INT_MAX;
        }
        foundCity1->distance = 0;
        for (int j=0; j<vertices.size(); j++)
        {
            vertex* temp = vertices[j];
            for (int k=0; k<(temp->adj).size(); k++)
            {
                if (  (temp->distance + (temp->adj)[k].weight) < ((temp->adj)[k].v)->distance  )
                {
                    ((temp->adj)[k].v)->distance = temp->distance + (temp->adj)[k].weight;
                    ((temp->adj)[k].v)->parent = temp;
                }
            }
        }

        vertex* temp = foundCity2;
        while (temp != foundCity1)
        {
            shortestPath.push_back(temp);
            temp = temp->parent;
        }
        shortestPath.push_back(temp);
        return shortestPath;
    }
}

/*-----------------------------------------------------------------
Basic breath-first algorithm for finding an unweighted shortest path.
This returns a path that will have the fewest stops in cities, even if
that means covering more miles. However, the distances are still updated
with the appropriate mileages for tracking purposes.
-----------------------------------------------------------------*/
vector<vertex*> Graph::breadthFirstSP(string startingCity, string endingCity)
{
    vertex* foundCity1 = findVertex(startingCity);
    vertex* foundCity2 = findVertex(endingCity);
    if ((foundCity1 == NULL) | (foundCity2 == NULL))
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else
    {
        queue <vertex*> visitedCities;
        vector <vertex*> shortestPath;
        foundCity1->visited = true;
        visitedCities.push(foundCity1);
        while (!visitedCities.empty())
        {
            vertex* n = visitedCities.front();
            for (int i=0; i<(n->adj).size(); i++)
            {
                if (!((n->adj)[i].v)->visited)
                {
                    ((n->adj)[i].v)->visited = true;
                    ((n->adj)[i].v)->distance = (n->distance)+(n->adj)[i].weight;
                    ((n->adj)[i].v)->parent = n;
                    if (((n->adj)[i].v)->name == endingCity)
                    {
                        vertex* temp = (n->adj)[i].v;
                        while (temp->name != startingCity)
                        {
                            shortestPath.push_back(temp);
                            temp = temp->parent;
                        }
                        shortestPath.push_back(temp);
                        return shortestPath;
                    }
                    visitedCities.push((n->adj)[i].v);
                }
            }
            visitedCities.pop();
        }
    }
}

/*-----------------------------------------------------------------
Basic depth-first algorithm for finding an unweighted shortest path.
This returns a path that will have the fewest stops in cities, even if
that means covering more miles. However, the distances are still updated
with the appropriate mileages for tracking purposes.
-----------------------------------------------------------------*/
vector<vertex*> Graph::depthFirstSP(string startingCity, string endingCity)
{
    vertex* foundCity1 = findVertex(startingCity);
    vertex* foundCity2 = findVertex(endingCity);
    if ((foundCity1 == NULL) | (foundCity2 == NULL))
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else
    {
        stack <vertex*> visitedCities;
        vector <vertex*> shortestPath;
        foundCity1->visited = true;
        visitedCities.push(foundCity1);
        while (!visitedCities.empty())
        {
            vertex* n = visitedCities.top();
            for (int i=0; i<(n->adj).size(); i++)
            {
                if (!((n->adj)[i].v)->visited)
                {
                    ((n->adj)[i].v)->visited = true;
                    ((n->adj)[i].v)->distance = (n->distance)+(n->adj)[i].weight;
                    ((n->adj)[i].v)->parent = n;
                    if (((n->adj)[i].v)->name == endingCity)
                    {
                        vertex* temp = (n->adj)[i].v;
                        while (temp->name != startingCity)
                        {
                            shortestPath.push_back(temp);
                            temp = temp->parent;
                        }
                        shortestPath.push_back(temp);
                        return shortestPath;
                    }
                    visitedCities.push((n->adj)[i].v);
                }
            }
            visitedCities.pop();
        }
    }
}

///////////////////////////////
// Public Functions
///////////////////////////////

/*-----------------------------------------------------------------
Function to add edges to the graph when they are read in from a properly
formatted text file.
-----------------------------------------------------------------*/
void Graph::addEdge(string v1, string v2, int weight)
{
    vertex* foundCity1 = findVertex(v1);
    if (foundCity1 == NULL)
    {
        cout << "First city entry was not found. Try a different city." << endl;
        return;
    }
    else
    {
        vertex* foundCity2 = findVertex(v2);
        if (foundCity2 == NULL)
        {
            cout << "Second city entry was not found. Try a different city." << endl;
            return;
        }
        adjVertex newAdj;
        newAdj.v = foundCity2;
        newAdj.weight = weight;
        (foundCity1->adj).push_back(newAdj);
    }
}

/*-----------------------------------------------------------------
Adds a vertex to the list of vertices in the graph.
-----------------------------------------------------------------*/
void Graph::addVertex(string newName)
{
    vertex* newVertex = new vertex();
    newVertex->name = newName;
    newVertex->visited = false;
    newVertex->solved = false;
    newVertex->distance = 0;

    vertices.push_back(newVertex);
}

/*-----------------------------------------------------------------
Returns a vector containing the shortest path to a destination determined
by the user's choice of algorithm. There are four potential algorithms to use.
NOTE (4/27/16): Bellman-Ford Algorithm does not appear to be functioning properly.
-----------------------------------------------------------------*/
vector<vertex*> Graph::shortestPath(string startingCity, string endingCity)
{
    vector <vertex*> shortestPath;
    char selection;
    cout << "Which algorithm would you like to use to travel?" << endl;
    cout << "1. Dijkstra's Algorithm (fewest miles)" << endl;
    cout << "2. Bellman-Ford Algorithm (fewest miles)" << endl;
    cout << "3. Basic Breadth-First Algorithm (fewest stops in cities)" << endl;
    cout << "4. Basic Depth Search Algorithm (fewest stops in cities)" << endl;
    cin >> selection;
    switch(selection)
    {
        case '1':
            shortestPath = dijkstraSP(startingCity,endingCity);
            break;
        case '2':
            shortestPath = bellmanFordSP(startingCity,endingCity);
            break;
        case '3':
            shortestPath = breadthFirstSP(startingCity,endingCity);
            break;
        case '4':
            shortestPath = depthFirstSP(startingCity,endingCity);
            break;
        default:
            cout << "Please enter an integer value from 1 to 4." << endl;
    }
    return shortestPath;
}

/*-----------------------------------------------------------------
Traverses the tree using a breadth-first approach and outputs the nodes
as it visits them.
-----------------------------------------------------------------*/
void Graph::BFTraversal(string startingCity)
{
    vertex* foundCity = findVertex(startingCity);
    if (foundCity == NULL)
    {
        cout << "Starting city was not found. Try a different city." << endl;
    }
    else
    {
        queue <vertex*> visitedCities;
        foundCity->visited = true;
        visitedCities.push(foundCity);
        while (!visitedCities.empty())
        {
            vertex* n = visitedCities.front();
            cout << n->name << endl;
            for (int i=0; i<(n->adj).size(); i++)
            {
                if (!((n->adj)[i].v)->visited)
                {
                    ((n->adj)[i].v)->visited = true;
                    visitedCities.push((n->adj)[i].v);
                }
            }
            visitedCities.pop();
        }
    }
    resetVertexStatus();
}

/*-----------------------------------------------------------------
Traverses the tree using a depth-first approach and outputs the nodes
as it visits them.
-----------------------------------------------------------------*/
void Graph::DFTraversal(string startingCity)
{
    vertex* foundCity = findVertex(startingCity);
    if (foundCity == NULL)
    {
        cout << "Starting city was not found. Try a different city." << endl;
    }
    else
    {
        stack <vertex*> visitedCities;
        foundCity->visited = true;
        visitedCities.push(foundCity);
        while (!visitedCities.empty())
        {
            vertex* n = visitedCities.top();
            cout << n->name << endl;
            visitedCities.pop();
            for (int i=0; i<(n->adj).size(); i++)
            {
                if (!((n->adj)[i].v)->visited)
                {
                    ((n->adj)[i].v)->visited = true;
                    visitedCities.push((n->adj)[i].v);
                }
            }
        }
    }
    resetVertexStatus();
}

/*-----------------------------------------------------------------
Outputs each vertex in the graph and each node that it is connected to.
-----------------------------------------------------------------*/
void Graph::printVertices()
{
    for (int i=0; i<vertices.size(); i++)
    {
        vertex* temp = vertices[i];
        cout << temp->name << " connects to: " << ((temp->adj)[0].v)->name;
        for (int j=1; j<(temp->adj).size(); j++)
        {
            cout << ", " << ((temp->adj)[j].v)->name;
        }
        cout << endl;
    }
}

/*-----------------------------------------------------------------
Resets each node in the graph to a state where it can be re-used for
subsequent searches/traversals and distance calculations.
-----------------------------------------------------------------*/
void Graph::resetVertexStatus()
{
    for (int i=0; i<vertices.size(); i++)
    {
        vertices[i]->visited = false;
        vertices[i]->solved = false;
        vertices[i]->parent = NULL;
        vertices[i]->distance = 0;
    }
}

/*-----------------------------------------------------------------
Determines if there is a node for a user specified city name in the graph.
-----------------------------------------------------------------*/
vertex* Graph::findVertex(string searchName)
{
    for (int i=0; i<vertices.size(); i++)
    {
        if (vertices[i]->name == searchName)
        {
            return vertices[i];
        }
    }
    return NULL;
}
