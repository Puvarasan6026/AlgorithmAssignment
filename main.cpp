#include <iostream>
#include <chrono>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Classes.h"

#define V 10

using namespace std;

class Node;
class Edge2;
vector<Node*> nodes;
vector<Edge2*> edges;

class Node
{
    public:
        Node(char id)
        : id(id), previous(NULL), distanceFromStart(INT_MAX) {
        nodes.push_back(this);
        }
        char id;
        Node* previous;
        double distanceFromStart;
};

class Edge2
{
    public:
        Edge2(Node* node1, Node* node2, double distance)
        : node1(node1), node2(node2), distance(distance) {
        edges.push_back(this);
        }
        bool connects(Node* node1, Node* node2)
        {
            return (
                (node1 == this->node1 &&
                node2 == this->node2) ||
                (node1 == this->node2 &&
                node2 == this->node1));
        }
        Node* node1;
        Node* node2;
        double distance;
};

double minDistance(double dist[], bool sptSet[])
{
    double min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

Node* extractSmallest(vector<Node*>& nodes)
{
  double size = nodes.size();
  if (size == 0) return NULL;
  double smallestPosition = 0;
  Node* smallest = nodes.at(0);
  for (int i = 1; i < size; ++i) {
    Node* current = nodes.at(i);
    if (current->distanceFromStart <
      smallest->distanceFromStart) {
      smallest = current;
      smallestPosition = i;
    }
  }
  nodes.erase(nodes.begin() + smallestPosition);
  return smallest;
}

bool contains(vector<Node*>& nodes, Node* node)
{
  const double size = nodes.size();
  for (int i = 0; i < size; ++i) {
    if (node == nodes.at(i)) {
      return true;
    }
  }
  return false;
}

vector<Node*>* adjacentRemainingNodes(Node* node)
{
  vector<Node*>* adjacentNodes = new vector<Node*>();
  const double size = edges.size();
  for (int i = 0; i < size; ++i) {
    Edge2* edge = edges.at(i);
    Node* adjacent = NULL;
    if (edge->node1 == node) {
      adjacent = edge->node2;
    } else if (edge->node2 == node) {
      adjacent = edge->node1;
    }
    if (adjacent && contains(nodes, adjacent)) {
      adjacentNodes->push_back(adjacent);
    }
  }
  return adjacentNodes;
}

double distance(Node* node1, Node* node2)
{
  const double size = edges.size();
  for (int i = 0; i < size; ++i) {
    Edge2* edge = edges.at(i);
    if (edge->connects(node1, node2)) {
      return edge->distance;
    }
  }
  return -1;
}

void printShortestRouteTo(Node* destination)
{
    Node* previous = destination;
    cout << "Distance from Planet_A: " << destination->distanceFromStart << endl;
    while (previous)
    {
        cout << "Planet_" << previous->id << " ";
        previous = previous->previous;
    }
    cout << endl;
}

void clone(Planet* p1, Planet* p2)
{
    for(int i=0; i<10; i++) {
        p1[i] = p2[i];
    }
}

void program1(Planet planets[],int planet_size)
{
    cout << "Program 1" << endl << endl << "Adjacency List:" << endl;

    //adjacency list
    for (int i=0; i<planet_size; i++)
    {
        cout << planets[i].name;
        for (int j=0; j<planets[i].connected_planets.size(); j++)
            cout << " -> " << planets[i].connected_planets[j].name << "|" << planets[i].calc_distance(planets[i].connected_planets[j]);
        cout << endl;
    }

    //adjacency matrix
    cout << endl << "Adjacency Matrix:" << endl;

    //line
    for (int i=0; i<planet_size+1; i++)
        cout << "+----------";
    cout << "+" << endl;

    //header
    cout << "|          ";
    for (int i=0; i<planet_size; i++)
        cout << "| " << planets[i].name << " ";
    cout << "|" << endl;

    //line
    for (int i=0; i<planet_size+1; i++)
        cout << "+----------";
    cout << "+" << endl;

    for (int i=0; i<planet_size; i++)
    {
        cout << "| " << planets[i].name << " ";

        for (int j=0; j<planet_size; j++)
        {
            float distance = 0;
            if (planets[i].connect_to(planets[j]))
                distance = planets[i].calc_distance(planets[j]);

            cout << "|" << setw(10) << distance;
        }
        cout << "|" << endl;
    }

    //line
    for (int i=0; i<planet_size+1; i++)
        cout << "+----------";
    cout << "+" << endl;

    //List of edges in ascending order of distance
    Quicksort qs;
    qs.sort(Planet::all_edges,0,Planet::all_edges.size()-1,"ascending");
    qs.print_edges(Planet::all_edges,planet_size,planets);

    //List of planets in descending order of value
    qs.sort(Planet::all_values,0,Planet::all_values.size()-1,"descending");
    qs.print_values(Planet::all_values,planet_size,planets);
}

void program2(Planet planets[],int planet_size)
{
    cout << endl << "Program 2" << endl << endl;

    Node* a = new Node('Planet_A');
    Node* b = new Node('Planet_B');
    Node* c = new Node('Planet_C');
    Node* d = new Node('Planet_D');
    Node* e = new Node('Planet_E');
    Node* f = new Node('Planet_F');
    Node* g = new Node('Planet_G');
    Node* h = new Node('Planet_H');
    Node* i = new Node('Planet_I');
    Node* j = new Node('Planet_J');

    Edge2* e1 = new Edge2(a, d, 12.1244);
    Edge2* e2 = new Edge2(a, j, 308.22);
    Edge2* e3 = new Edge2(a, h, 1041.07);
    Edge2* e4 = new Edge2(a, f, 158.486);
    Edge2* e5 = new Edge2(d, b, 105.655);
    Edge2* e6 = new Edge2(d, j, 317.495);
    Edge2* e7 = new Edge2(j, h, 929.672);
    Edge2* e8 = new Edge2(j, g, 157.948);
    Edge2* e9 = new Edge2(h, f, 1196.45);
    Edge2* e10 = new Edge2(h, i, 345.673);
    Edge2* e11 = new Edge2(f, c, 1186.07);
    Edge2* e12 = new Edge2(b, e, 119.537);
    Edge2* e13 = new Edge2(b, g, 268.494);
    Edge2* e14 = new Edge2(g, i, 617.761);
    Edge2* e15 = new Edge2(g, e, 354.274);
    Edge2* e16 = new Edge2(i, e, 728.759);
    Edge2* e17 = new Edge2(i, c, 470.106);
    Edge2* e18 = new Edge2(c, e, 1054.82);

    a->distanceFromStart = 0;  // set start node

    while (nodes.size() > 0)
    {
        Node* smallest = extractSmallest(nodes);
        vector<Node*>* adjacentNodes =
        adjacentRemainingNodes(smallest);

        const double size = adjacentNodes->size();
        for (int i = 0; i < size; ++i)
        {
            Node* adjacent = adjacentNodes->at(i);
            double distance2 = distance(smallest, adjacent) + smallest->distanceFromStart;

            if (distance2 < adjacent->distanceFromStart)
            {
                adjacent->distanceFromStart = distance2;
                adjacent->previous = smallest;
            }
        }
        delete adjacentNodes;
    }

    cout<<"The shortest distance to each Planet is as follows :: \n";
    printShortestRouteTo(d);
    printShortestRouteTo(j);
    printShortestRouteTo(h);
    printShortestRouteTo(f);
    printShortestRouteTo(b);
    printShortestRouteTo(g);
    printShortestRouteTo(i);
    printShortestRouteTo(c);
    printShortestRouteTo(e);

    double graph[V][V] = { { 0, 0, 0, 12.1244, 0, 158.468, 0, 1041.07, 0, 308.72},
                        { 0, 0, 0, 105.655, 119.537, 0, 268.494, 0, 0,0 },
                        { 0, 0, 0, 0, 1054.82, 1186.07, 0, 0, 470.106,0 },
                        { 12.1244, 105.655, 0, 0, 0, 0, 0, 0, 0, 317.495},
                        { 0, 119.537, 1054.82, 0, 0, 0, 354.274, 0, 728.759,0 },
                        { 158.468, 0, 1186.07, 0, 0, 0, 0, 1196.45, 0,0 },
                        { 0, 268.494, 0, 0, 354.274, 0, 0, 0, 617.761, 154.948},
                        { 1041.07, 0, 0, 0, 0, 1196.45, 0, 0, 345.673, 929.672},
                        { 0, 0, 470.106, 0, 728.759, 0, 617.761, 345.673, 0,0 },
                        { 308.72, 0, 0, 317.495,0, 0, 154.948, 929.672, 0,0 } };

    double dist[V];

    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    cout << endl <<"Vertex \t\t Distance from Source\n";
    for (int i = 0; i < planet_size; i++)
    	 cout<< planets[i].name << "\t\t"<< dist[i] <<endl;
}

void program34 (Planet planets[],int planet_size)
{
    cout << endl << "Program 3" << endl << endl;
    Planet temp [planet_size];
    for(int i=0; i<planet_size; i++)
        temp[i] = planets[i];

    MST mst(temp);
    mst.print();

    cout << endl << "Program 4" << endl << endl;

    clone(temp, planets);
    DP dp(temp);
    dp.print();
}

vector<float> Planet::all_edges;
vector<float> Planet::all_values;

int main () {
    const int PLANET_COUNT = 10;

    //read information from the text file
    ifstream file("A2planets.txt");
    string str;
    vector<string> planets_info;
    while (getline(file, str))
      planets_info.push_back(str);

    //place information into Planet class
    Planet planets[PLANET_COUNT];
    for (int i=0; i<planets_info.size(); i++)
    {
        vector<string> new_vector;
        stringstream data(planets_info[i]);
        string line;
        while(std::getline(data,line,' '))
            new_vector.push_back(line);

        planets[i].name = new_vector[0];
        planets[i].x = stoi(new_vector[1]);
        planets[i].y = stoi(new_vector[2]);
        planets[i].z = stoi(new_vector[3]);
        planets[i].weight = stoi(new_vector[4]);
        planets[i].profit = stoi(new_vector[5]);
        if (planets[i].weight == 0)
            planets[i].add_value(0);
        else
            planets[i].add_value(planets[i].profit/planets[i].weight);
    }

    //connect planets
    planets[0].add_connected_planets(planets[3]);
    planets[0].add_connected_planets(planets[5]);
    planets[0].add_connected_planets(planets[7]);
    planets[0].add_connected_planets(planets[9]);

    planets[1].add_connected_planets(planets[3]);
    planets[1].add_connected_planets(planets[4]);
    planets[1].add_connected_planets(planets[6]);

    planets[2].add_connected_planets(planets[4]);
    planets[2].add_connected_planets(planets[5]);
    planets[2].add_connected_planets(planets[8]);

    planets[3].add_connected_planets(planets[0]);
    planets[3].add_connected_planets(planets[1]);
    planets[3].add_connected_planets(planets[9]);

    planets[4].add_connected_planets(planets[1]);
    planets[4].add_connected_planets(planets[2]);
    planets[4].add_connected_planets(planets[6]);
    planets[4].add_connected_planets(planets[8]);

    planets[5].add_connected_planets(planets[0]);
    planets[5].add_connected_planets(planets[2]);
    planets[5].add_connected_planets(planets[7]);

    planets[6].add_connected_planets(planets[1]);
    planets[6].add_connected_planets(planets[4]);
    planets[6].add_connected_planets(planets[8]);
    planets[6].add_connected_planets(planets[9]);

    planets[7].add_connected_planets(planets[0]);
    planets[7].add_connected_planets(planets[5]);
    planets[7].add_connected_planets(planets[8]);
    planets[7].add_connected_planets(planets[9]);

    planets[8].add_connected_planets(planets[2]);
    planets[8].add_connected_planets(planets[4]);
    planets[8].add_connected_planets(planets[6]);
    planets[8].add_connected_planets(planets[7]);

    planets[9].add_connected_planets(planets[0]);
    planets[9].add_connected_planets(planets[3]);
    planets[9].add_connected_planets(planets[6]);
    planets[9].add_connected_planets(planets[7]);

    program1(planets,PLANET_COUNT);
    program2(planets,PLANET_COUNT);
    program34(planets,PLANET_COUNT);

    return 0;
}
