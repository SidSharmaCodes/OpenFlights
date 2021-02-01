#pragma once

#include <vector>
#include <string>
#include <queue>
#include <math.h>
#include <map>
#include <iostream>
#include "graph.h"
#include "datahelper.h"

using namespace std;

class FlightGraph : public Graph {
    public:
        FlightGraph();
        FlightGraph(bool dataLoaded, string airportFilename, string flightFilename);
        int calcDist(string source, string dest);
        bool findAugmentingPath(Vertex source, Vertex dest, vector<Vertex> & path, map<Vertex, bool> & visited); 
        bool findAugmentingPath(Vertex source, Vertex dest, vector<Vertex> & path); 
        int getMaxFlow(Vertex source, Vertex dest); 
        map<string, vector<string>> info_; 
        bool dataLoaded_; // whether or not data is loaded into the graph
        int getId(Vertex vertex) const;
        vector<Vertex> dijkstra(Vertex source, Vertex dest); 
    private:
        Graph res_; 
};