#include<vector>
#ifndef ALLCLASS_H
#define ALLCLASS_H

class Planet
{
    public:
        std::string name;
        int x,y,z;  // coordinates
        float weight,profit,value;
        static std::vector<float> all_edges;
        static std::vector<float> all_values;
        std::vector<Planet> connected_planets;
        float calc_distance(Planet p);
        bool connect_to(Planet p);
        void add_connected_planets(Planet p);
        void add_value(float v);
};

class Quicksort
{
    public:
        int partition(std::vector<float> &values, int left, int right,std::string method);
        void sort(std::vector<float> &values, int left, int right,std::string method);
        void print_edges(std::vector<float> all_edges,int planet_size,Planet planets[]);
        void print_values(std::vector<float> all_values,int planet_size,Planet planets[]);
};

class Edge {
    public:
        Planet src;
        Planet dest;
        float weight;
        Edge(Planet s, Planet d);
};

class MST {
    private:
        std::vector<Edge> graph;
        std::vector<Edge> mst;
        const int numOfPlanets = 10;
        Planet* planets;

    public:
        MST(Planet* p);
        ~MST();
        int toIndex(Planet p);
        Planet findSet(Planet p);
        void unionSet(Planet s, Planet d);
        void kruskal();
        void print();
};

class DP {
    private:
        const int capacity = 80;
        const int numOfPlanets = 10;
        std::vector<Planet> planets;
        int table[10 + 1][80+1];
        int weight[10];
        int profit[80];
        int maxProfit;
        std::vector<Planet> visitedPlanets;
    public:
        DP(Planet* p);
        void knapsack();
        void print();
        void findPlanets();
};

#endif
