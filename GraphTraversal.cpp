#include <cmath>
#include <iterator>
#include <iostream>
#include <sstream>


#include "GraphTraversal.h" 
//IN DEVELOPMENT
using namespace std;


/**
 * Default iterator constructor.
 */
GraphTraversal::Iterator::Iterator() : traversal(NULL){
 

}
GraphTraversal::Iterator::Iterator(GraphTraversal* t, Vertex p) {
  
  //storing the traversal and the initial starting point
  traversal = t;  
  vertex = p; 

  vector<Vertex> vertices = t->_graph->getVertices();
  matrix.resize(14111); //will store visited nodes
  found.resize(14111); //will be used to determine if an edge is a discovery edge or a cross edge 
  for(unsigned int i = 0;  i < vertices.size(); ++i){ 
   //initialize both arrays as false
   matrix[i] = false;  
   found[i] = false;

  } 

  markDiscovered(vertex); //mark the first node as being discovered (different from visited) by the traversal
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
GraphTraversal::Iterator & GraphTraversal::Iterator::operator++() {
 
  Vertex current = this->traversal->pop(); //get the next item to be visited from the traversal

   if(!visited(current)){  

    vector<Vertex> neighbors = traversal->_graph->getAdjacent(vertex);  //get the neighbors of current

    //cout<<"# of Neighbors of node"<<vertex<<": "<<neighbors.size()<<endl;

    for(Vertex node : neighbors) //for each of the adjacent nodes
    {  
      if(discovered(node)){ //if the neighbor has already been discovered, mark the edge between the neighbor and current as a cross edge
        traversal->_graph->setEdgeLabel(vertex, node, "CROSS");
      } 
      else{
        traversal->_graph->setEdgeLabel(vertex,node, "DISCOVERY"); //else mark the edge as discovery
        markDiscovered(node); //mark that the node has been discovered
      } 

      ++(traversal->_edges);
      this->traversal->add(node); //add the neighbor to the traversal, will be processed next
    } 
    markVisited(vertex);
  }  
  //cout<<"breakpoint"<<endl; 
  //quick empty check
  if(this->traversal->empty()) {   
    this->traversal = NULL;
    return *this; 
  }

  Vertex next = this->traversal->peek(); //see whats next in the traversal


  while(visited(next)) //while next is a neighbor thats been visited
  {  

    next = this->traversal->pop();  //remove it from the traversal because it's neighbors have already been added

  //empty check 
    if(this->traversal->empty()) {  
     this->traversal = NULL;
     return *this; 
    }

   next = this->traversal->peek(); //look at the top of the traversal

  }
  
  this->vertex = next; //this element has definitely not been visited yet!
  return *this;

} 

/*returns true if a vertex has been visited*/ 
bool GraphTraversal::Iterator::visited(Vertex vertex){  
int idx = traversal->_graph->getId(vertex);
return matrix[idx];
}

//marks a node as visited
void GraphTraversal::Iterator::markVisited(Vertex vertex){ 

int idx = traversal->_graph->getId(vertex);
matrix[idx] = true;

} 

//returns true if a node has been discovered
bool GraphTraversal::Iterator::discovered(Vertex vertex){

  return found[traversal->_graph->getId(vertex)];

}  
//mark a node as discovered
void GraphTraversal::Iterator::markDiscovered(Vertex vertex){

  found[traversal->_graph->getId(vertex)] = true; 
 

}  

int GraphTraversal::getEdgeCount(){
  return _edges;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Vertex in the GraphTraversal.
 */
Vertex GraphTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->vertex;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool GraphTraversal::Iterator::operator!=(const GraphTraversal::Iterator &other) {
  /** @todo [Part 1] */ 
     bool thisEmpty = false; 
     bool otherEmpty = false;
     if (traversal == NULL) { thisEmpty = true; }
     if (other.traversal == NULL) { otherEmpty = true; }

    if (!thisEmpty)  { thisEmpty = traversal->empty(); }
    if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

    if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
    else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
    else return true; // one is empty while the other is not, return true
}
 
 /*IGNORE*/
bool GraphTraversal::Iterator::bounds(const Vertex vertex){  

//if(vertex.x < this->traversal->pic.width() && vertex.y < this->traversal->pic.height()){return true;} 
return false;
}


/*IGNORE*/
bool GraphTraversal::Iterator::tolCheck(Vertex next){  

//double tol = calculateDelta(this->traversal->pic.getPixel(this->traversal->startVertex.x, this->traversal->startVertex.y), this->traversal->pic.getPixel(next.x, next.y)); 

//if(tol < this->traversal->delta) {return true;} 
 
return false;
} 
