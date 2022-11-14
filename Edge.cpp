#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Classes.h"
using namespace std;

Edge :: Edge(Planet s, Planet d) {
    src = s;
    dest = d;
    weight = src.calc_distance(dest);
}
