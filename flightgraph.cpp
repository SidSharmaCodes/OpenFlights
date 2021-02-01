#include "flightgraph.h" 
#include <iostream> 
#include <fstream>

FlightGraph::FlightGraph() : Graph(true, true) {
    dataLoaded_ = false; 
}

FlightGraph::FlightGraph(bool dataLoaded, string airportFilename, string flightFilename) : Graph(true, true) {
    dataLoaded_ = dataLoaded; 
    if (!dataLoaded) return; 

    ofstream debugFile; 
    debugFile.open("Vertices.txt");  

    DataHelper airports(airportFilename);
    info_ = map<string, vector<string>>();
    vector<vector<string>> cols = airports.getColumns();
    // airport id, name, city, country, iata, icao, lat, lon, altitude, timezone, dst, tz, type, source
    for (int i = 0; i < (int) cols.size(); i++) {
        vector<string> cur = cols[i];  
        if(cur.size() < 5){
            cout<<cur.size()<<endl;  
            cout<<cur[0]<<endl; 
            continue;
        }
        
        string code = cur[4]; 
       
        if (code.length() == 5 ) { // all airports without code length 5 are \N and do not have a code
            code = code.substr(1, 3); 
            vector<string> toAdd;
            toAdd.push_back(cur[6]); toAdd.push_back(cur[7]); // the info map will include the latitude and longitude
            toAdd.push_back(cur[0]); // info map includes airport code
            info_[code] = toAdd;
            res_ = Graph(true, true); 
            insertVertex(code); // insert vertices into flight graph
            res_.insertVertex(code); // insert vertices into residual graph for use in ford fulkerson 

            debugFile<< code+"\n"; //place the vertices into a file
        }
    } 
    debugFile.close();
    DataHelper flights(flightFilename);
    cols.clear();
    cols = flights.getColumns();
    for (int i = 0; i < (int) cols.size(); i++) {
        vector<string> cur = cols[i];
        string source = cur[2];  
        string dest = cur[4];
        if (info_.count(source) > 0 && info_.count(dest) > 0) {
            res_.insertEdge(source, dest);
            res_.insertEdge(dest, source); 
            res_.setEdgeWeight(source, dest, 1);
            res_.setEdgeWeight(dest, source, 0);  
            insertEdge(source, dest); 
            int dist = calcDist(source, dest);
            setEdgeWeight(source, dest, dist);
        }
    }
    cols.clear(); 
}

int FlightGraph::calcDist(string source, string dest) { 
    vector<string> sll = info_.at(source);
    vector<string> dll = info_.at(dest); 
    double lat1 = stod(sll[0]) * M_PI / 180;
    double lon1 = stod(sll[1]) * M_PI / 180;
    double lat2 = stod(dll[0]) * M_PI / 180;
    double lon2 = stod(dll[1]) * M_PI / 180;
    double latd = lat1 - lat2; 
    double lond = lon1 - lon2; 
    double a = sin(latd / 2) * sin(latd / 2) + cos(lat1) * cos(lat2) * sin(lond / 2) * sin(lond / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double R = 6371; // mean distance
    return (int) (floor(c * R));
}

bool FlightGraph::findAugmentingPath(Vertex source, Vertex dest, vector<Vertex> & path, map<Vertex, bool> & visited) {
    if (visited.count(source) != 0) // if already visited return false
        return false;
    visited[source] = true;
    if (source.compare(dest) == 0) { // if at destination return true
        return true;
    }

    vector<Vertex> adjs = res_.getAdjacent(source);
    for(auto it = adjs.begin(); it != adjs.end(); it++) {
        if (visited.count(*it) == 0 && res_.getEdgeWeight(source, *it) > 0) {
            path.push_back(*it);
            if (findAugmentingPath(*it, dest, path, visited)) // recurse over all possible paths 
                return true;
            else {
                path.pop_back(); // delete addition if not an augmenting path
            }
        }
    }
    return false; 
}

bool FlightGraph::findAugmentingPath(Vertex source, Vertex dest, vector<Vertex> & path) {
    map<Vertex, bool> visited; 
    path.clear();
    path.push_back(source);
    bool result = findAugmentingPath(source, dest, path, visited); // find augmenting path
    return result; 
}

int FlightGraph::getMaxFlow(Vertex source, Vertex dest) {
    vector<Vertex> path; 
    int result = 0; 
    while (findAugmentingPath(source, dest, path)) { // while there are augmenting paths, iterate
        for (int i = 0; i < (int) path.size() - 1; i++) {
            Vertex a = path[i];
            Vertex b = path[i + 1];
            res_.setEdgeWeight(a, b, 0);
            res_.setEdgeWeight(b, a, 1);
        }
        result++; // edge weights are always 1, so max flow increases by 1 for each augmenting path
    }
    return result; 
}

int FlightGraph::getId(Vertex vertex) const{ 
    // get airport ID of vertex
    vector<string> temp = info_.at(vertex);   
    string str_index = temp[2]; 
    std::stringstream ss(str_index);
    int idx = 0; 
    ss >> idx;
    return idx;

}

// overloads to allow priority queue to compare vertices and their distances from the source
struct DistNextVert {
    string distvert;
};

class DistNextVert_Compare {
public:
    bool operator()(DistNextVert& dv1, DistNextVert& dv2)
    {
      string d1 = dv1.distvert.substr(3,dv1.distvert.size()-2);
      string d2 = dv2.distvert.substr(3,dv2.distvert.size()-2);
      int distance1 = stoi(d1);
      int distance2 = stoi(d2);
      if (distance1 > distance2) return true;
      return false;
    }
};

vector<Vertex> FlightGraph::dijkstra(Vertex source, Vertex dest) {
    // initializing necessary structures
    vector<Vertex> result; 
    priority_queue <DistNextVert, vector<DistNextVert>, DistNextVert_Compare> q;  
    map<Vertex, int> distances; 
    DistNextVert startvert = {source + "0"};
    q.push(startvert);
    distances[source] = 0;
    map<string, bool> visited; 
    map<Vertex, Vertex> prev; 
    while (q.top().distvert.substr(0, 3) != dest) { // while not at destination vertex
        DistNextVert curr = q.top();
        q.pop();
        Vertex vert1 = curr.distvert.substr(0,3); //name of vertex
        int curDist = stoi(curr.distvert.substr(3, curr.distvert.size()-2)); //distance of vertex
        if (visited.count(vert1) != 0) continue; 
        for (Vertex v : getAdjacent(vert1)) {
            if (visited.count(v) == 0) {
                int edgeWeight = getEdgeWeight(vert1, v); 
                int d = curDist + edgeWeight;
                if (distances.count(v) == 0) {
                    distances[v] = d;
                    DistNextVert toAdd = {v + std::to_string(d)};
                    q.push(toAdd); 
                    prev[v] = vert1; 
                } else if (distances[v] > curDist + edgeWeight) {
                    distances[v] = d;
                    DistNextVert toAdd = {v + std::to_string(d)};
                    q.push(toAdd); 
                    prev[v] = vert1; 
                }
            }
        }
        if (q.empty()) return result; // if stuck, no paths are possible 
    }
    // extract path 
    Vertex curr = dest; 
    while (curr != source) {
        result.push_back(curr); 
        curr = prev[curr];
    }
    result.push_back(source);
    std::reverse(result.begin(), result.end()); 
    return result;
}