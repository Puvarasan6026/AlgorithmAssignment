#include <iostream>
#include <chrono>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Classes.h"
using namespace std;

int Quicksort::partition(vector<float> &values, int left, int right,string method)
{
    int pivotIndex = left + (right - left) / 2;
    float pivotValue = values[pivotIndex];
    int i = left, j = right;
    float temp;

    while(i <= j)
    {
        if (method.compare("ascending") == 0)
        {
            while(values[i] < pivotValue)
                i++;

            while(values[j] > pivotValue)
                j--;
        }
        else
        {
            while(values[i] > pivotValue)
                i++;

            while(values[j] < pivotValue)
                j--;
        }

        if(i <= j)
        {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void Quicksort::sort(vector<float> &values, int left, int right,string method)
{
    if(left < right)
    {
        int pivotIndex = partition(values, left, right,method);
        sort(values, left, pivotIndex - 1,method);
        sort(values, pivotIndex, right,method);
    }
}

void Quicksort::print_edges(vector<float> all_edges,int planet_size,Planet planets[])
{
    cout << endl << "List of edges in ascending order of distance:" << endl;
    for (int c=0; c<all_edges.size(); c++)
    {
        bool found = false;
        for (int i=0; i<planet_size && !found; i++)
        {
            for (int j=0; j<planets[i].connected_planets.size() && !found; j++)
            {
                if (all_edges[c] == planets[i].calc_distance(planets[i].connected_planets[j]))
                {
                    found = true;
                    cout << planets[i].name << "_" << planets[i].connected_planets[j].name << ": " << planets[i].calc_distance(planets[i].connected_planets[j]) << endl;
                }
            }
        }
    }
}

void Quicksort::print_values(vector<float> all_values,int planet_size,Planet planets[])
{
    cout << endl << "List of planets in descending order of value:" << endl;
    for (int c=0; c<all_values.size(); c++)
    {
        for (int i=0; i<planet_size; i++)
        {
            if (planets[i].value == all_values[c])
                cout << planets[i].name << ": " << planets[i].value << endl;
        }
    }
}
