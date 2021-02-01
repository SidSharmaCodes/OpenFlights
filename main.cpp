#include "datahelper.h"
//#include "random.h"
#include "graph.h"
#include "edge.h" 
#include "GraphTraversal.h"
#include "BFS.h"  
#include "flightgraph.h"
#include <string> 
#include <iostream> 
#include <fstream> 
#include <map> 
#include <vector>

using namespace std;  


// HELPER FUNCTIONS 

void printPath(vector<Vertex> path) {
  if (path.size() == 0) {
    std::cout << "No path exists" << std::endl; 
    return; 
  }
  std::cout << "Path from " + path[0] + " to " + path[path.size() - 1] + ": ";
  for (int i = 0; i < (int) path.size() - 1; i++) {
    std::cout << path[i] + " -> ";
  }
  std::cout << path[path.size() - 1] << std::endl; 
}
// END OF HELPER FUNCTIONS



int main() { 
  std::cout << std::endl; 
  // Initializing
  std::cout << "Initializing FlightGraphs..."; 
  FlightGraph fg_small(true, "sampleairports.txt", "sampleflights.txt");
  FlightGraph fg_large(true, "airportsInfo.txt", "data.txt"); 
  std::cout << "done!" << std::endl; std::cout << std::endl; 

  // TEST DIJKSTRA's ALGORITHM
  std::cout << "Testing Dijkstra's Algorithm Valid Small Graph Path: " << std::endl; 
  vector<Vertex> shortPath1 = fg_small.dijkstra("SEA", "ORD");
  printPath(shortPath1); 
  std::cout << "Testing Dijkstra's Algorithm Invalid Small Graph Path: " << std::endl; 
  vector<Vertex> shortPath2 = fg_small.dijkstra("DEN", "SEA"); 
  printPath(shortPath2); 
  std::cout << "Testing Dijkstra's Algorithm Valid Large Graph Path: " << std::endl; 
  vector<Vertex> longPath1 = fg_large.dijkstra("BOM", "CMI");
  printPath(longPath1); 
  std::cout << "Testing Dijkstra's Algorithm Invalid Large Graph Path: " << std::endl; 
  vector<Vertex> longPath2 = fg_large.dijkstra("BFI", "CMI");
  printPath(longPath2); 
  std::cout << std::endl; 

  // TEST BFS 
  cout <<"Testing BFS on Sample Data" << endl;  
  BFS t(&fg_small, "SEA", 0.2);
  unsigned count = 0;  
  cout << "Traversal Order:" <<endl;
  for (const Vertex & p : t) { 
    cout << p << endl;
    count++;
  }    
  cout << endl; cout<<"Graph:"<<endl;
  fg_small.print(); 
  
  cout<<"Number of Nodes visited: "<<count<<endl; 
  cout<<"Number of Edges visited: "<<t.getEdgeCount()<<endl; cout << endl; 

  //TEST BFS ON LARGE DATASET 

  cout<<"Testing BFS on entire data set"<<endl; 
  BFS large(&fg_large, "SEA", 0.2); 
  count =0;  

  map<Vertex, bool>  visited; 
  vector<Vertex> vertices = fg_large.getVertices(); 
  //initializing visited
  for(Vertex v : vertices){
    visited[v] = false;
  }
  //if a node is visited
  for(const Vertex & p : large){
    count++; 
    visited[p] = true;
  }  

  cout<<"Number of Nodes visited: "<<count<<endl;
  cout<<"Number of Edges visited: "<<large.getEdgeCount()<<endl; cout << endl;   
  
  /* The verfication process below takes an extremely long time! */ 

  /*
  cout<<"Using Dijkstra's Algorithm to prove no path exists to unvisited nodes..."<<endl;  
  cout<<"Warning- this verification takes a very long time"<<endl; cout<<endl;

  vector<Vertex> unvisited; 

  for(auto it : visited){

    if(!it.second){ //if a node hasn't been visited
      unvisited.push_back(it.first); //put it into the unvisited vector
    }

  } 
  bool pass = true;
  for(Vertex v : unvisited){

    vector<Vertex> path = fg_large.dijkstra("SEA", v); //calling djikstra's algorithm from Seattle to each unvisited airport 

    if(path.size() != 0){ //if a path is found, test failed
      cout<<"Test Failed: path exists from SEA to "<<v<<endl;  
      pass = false;
      break;
    }
  } 
 
  if(pass){
    cout<<"Test Passed: no paths exist from SEA to unvisited airports"<<endl; cout<<endl;
  }
  */


  // TEST FORD-FULKERSON ALGORITHM

  std::cout << "Testing Max Flow for Small Graph:" << std::endl; 
  int maxFlowSmall = fg_small.getMaxFlow("SEA", "ORD"); // this should be two, reference Sample Flights Map
  std::cout << "Max flow from SEA to ORD: " + std::to_string(maxFlowSmall) << std::endl; 

  std::cout << "Testing Max Flow for Large Graph:" << std::endl; 
  int maxFlowLarge = fg_large.getMaxFlow("SEA", "ORD"); 

  // The smaller of the following two values should be a maximum for the flow evaluated on fg_large
  // It is difficult to check whether the max flow is correct, but these values provide a cap
  std::cout << "Total outgoing flights from SEA: " + std::to_string(fg_large.getAdjacent("SEA").size()) << std::endl; 
  std::cout << "Total incoming flights to ORD: " + std::to_string(fg_large.getIncomingVertices("ORD").size()) << std::endl; 
  std::cout << "Max flow from SEA to ORD: " + std::to_string(maxFlowLarge) << std::endl; 
  std::cout << std::endl; 

} 


