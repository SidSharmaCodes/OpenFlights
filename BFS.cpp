#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>
/*
#include "../cs225/PNG.h"
#include "../Vertex.h"
*/
#include "GraphTraversal.h"
#include "BFS.h"

//using namespace cs225;

/**
 * Initializes a breadth-first GraphTraversal on a given `png` graph,
 * starting at `start`, and with a given `tolerance`.
 * @param graph The graph this BFS is going to traverse
 * @param start The start vertex of this BFS
 * @param tolerance If the current vertex is too different (difference larger than tolerance) with the start vertex,
 * it will not be included in this BFS
 */
BFS::BFS(Graph * graph, const Vertex & start, double tolerance) {  
 
  _graph = graph; 
  startVertex = start;  
  queue.push(startVertex); 
  delta = tolerance; 
  _edges =0;
} 


/**
 * Returns an iterator for the traversal starting at the first vertex.
 */
GraphTraversal::Iterator BFS::begin() {

  return GraphTraversal::Iterator(this, startVertex); //create a GraphTraversal iterator with a certain starting point
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
GraphTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return GraphTraversal::Iterator();
}

/**
 * Adds a Vertex for the traversal to visit at some vertex in the future.
 */
void BFS::add(const Vertex & vertex) { 
    

queue.push(vertex); //since this is a BFS search, the vertex is added to a queue
} 
/*
bool BFS::bounds(const Vertex & vertex){ 
if(vertex.x < pic.width() && vertex.y < pic.height()){return true;} 
else{return false;}
} 
*/

/**
 * Removes and returns the current Vertex in the traversal.
 */
Vertex BFS::pop() {
  
  Vertex temp = queue.front(); 
  queue.pop(); 
  return temp;
}

/**
 * Returns the current Vertex in the traversal.
 */
Vertex BFS::peek() const {

  return queue.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {

  return queue.empty();
}
