#include <iostream>
#include <algorithm>
#include <iomanip>
#include "Classes.h"
using namespace std;

DP :: DP(Planet* p) {
    for(int i=0; i<numOfPlanets; i++) {
        planets.push_back(p[i]);
        profit[i] = p[i].profit;
        weight[i] = p[i].weight;
    }
    knapsack();
    findPlanets();
}

void DP :: knapsack() {
    for(int i=0; i<=numOfPlanets; i++) {
        for(int j=0; j<=capacity; j++) {
            if(i == 0 || j ==0) {
                table[i][j] = 0;
            }
            else if(weight[i-1] <= j) {
                table[i][j] = max(profit[i-1] + table[i-1][j-weight[i-1]], table[i-1][j]);
            }
            else {
                table[i][j] = table[i-1][j];
            }
        }
    }
    maxProfit = table[numOfPlanets][capacity];
}

void DP :: findPlanets() {
    int temp = maxProfit;
    int cap = capacity;
    for(int i=numOfPlanets; i>0 && temp > 0; i--) {
        if(temp == table[i-1][cap]) {
            continue;
        }
        else {
            visitedPlanets.push_back(planets[i-1]);
            temp = temp - profit[i-1];
            cap = cap - weight[i-1];
        }
    }
}

void DP :: print() {
    cout << "0/1 Knapsack using Dynamic Programming" << "\n" << endl;

    for(int i=0; i<=numOfPlanets; i++) {
        cout << "Row " << i << ": ";
        for(int j=0; j<=capacity; j++) {
            cout << table[i][j] << " ";
        }
        cout << "\n" << endl;
    }

    cout << "Maximum profit is " << maxProfit << " from:" << endl;

    cout << "           " << "Weight" << setw(8) << "Profit" << setw(7) << endl;
    for(Planet p : visitedPlanets) {
        cout << p.name << setw(7) << p.weight << setw(8) << p.profit << setw(4) << endl;
    }
}