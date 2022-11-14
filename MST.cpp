#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Classes.h"
using namespace std;

bool sortByWeight(Edge &A, Edge &B){
    return (A.weight < B.weight);
}

MST :: MST (Planet* p) {
    planets = p;

    graph.clear();
    mst.clear();

    for(int i=0; i<numOfPlanets; i++) {
        for(int j=0; j<planets[i].connected_planets.size(); j++) {
            graph.push_back(Edge(planets[i], planets[i].connected_planets[j]));
        }
    }
    sort(graph.begin(), graph.end(), sortByWeight);
    kruskal();
}

MST :: ~MST() {
    delete planets;
}

int MST :: toIndex(Planet p) {
    const string allPlanets[numOfPlanets] = {"Planet_A", "Planet_B", "Planet_C", "Planet_D", "Planet_E", "Planet_F", "Planet_G", "Planet_H", "Planet_I", "Planet_J"};
    for(int i=0; i<numOfPlanets; i++) {
        if(allPlanets[i] == p.name) {
            return i;
        }
    }
    return -1;
}

Planet MST :: findSet(Planet p) {
    if(p.name == planets[toIndex(p)].name) {
        return p;
    }
    else {
        return findSet(planets[toIndex(p)]);
    }
}

void MST :: unionSet(Planet s, Planet d) {
    planets[toIndex(s)] = planets[toIndex(d)];
}

void MST :: kruskal() {
    Planet src, dest;
    for(int i=0; i<graph.size(); i++) {
        src = findSet(graph[i].src);
        dest = findSet(graph[i].dest);
        if(src.name != dest.name) {
            mst.push_back(graph[i]);
            unionSet(src, dest);
        }
    }
}

void MST :: print() {
    cout << "Minimum Spanning Tree using Kruskal's Algorithm" << endl;
    cout << endl;
    cout << setw(11) << "Edge" << setw(17) << "Weight" << endl;
    for(Edge e : mst) {
        cout << e.src.name << "_" << e.dest.name << setw(10) << e.weight << endl;
    }
}
