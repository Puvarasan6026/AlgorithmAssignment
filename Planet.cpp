#include <iostream>
#include <math.h>
#include "Classes.h"

using namespace std;

float Planet::calc_distance(Planet p)
{
    float x_part = pow(x-p.x,2.0);
    float y_part = pow(y-p.y,2.0);
    float z_part = pow(z-p.z,2.0);

    return sqrt(x_part+y_part+z_part);
}

bool Planet::connect_to(Planet p)
{
    for (int i=0; i<connected_planets.size(); i++)
    {
        if (connected_planets[i].name.compare(p.name) == 0)
            return true;
    }
    return false;
}

void Planet::add_connected_planets(Planet p)
{
    connected_planets.push_back(p);

    bool exist = false;
    for (int i=0; i<all_edges.size(); i++)
    {
        if (all_edges[i] == calc_distance(p))
            exist = true;
    }

    if (!exist)
        all_edges.push_back(calc_distance(p));
}

void Planet::add_value(float v)
{
    value = v;
    all_values.push_back(v);
}
