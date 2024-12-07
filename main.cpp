#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
using namespace std;

int main()
{
    Graph graph;
    graph.createIntersections("traffic_signals.csv");
    graph.createNetwork("road_network.csv");

    graph.visualizeNetwork();
    graph.visualizeSignals();

    return 0;
}