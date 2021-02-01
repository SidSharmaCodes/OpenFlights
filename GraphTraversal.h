/**
 * @file GraphTraversal.h
 */
#pragma once

#include <iterator> 
#include <vector> 
#include <map>
#include "graph.h"
//IN DEVELOPMENT
//using namespace cs225; 
using namespace std;
/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of vertexs on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * GraphTraversal::Iterator.
 */
class GraphTraversal {
public:
  /**
   * A forward iterator through an GraphTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
  public:
   // Iterator(); 
    //~Iterator(); 
    Iterator();
    Iterator(GraphTraversal *t, Vertex p);
    Iterator & operator++();
    Vertex operator*();
    bool operator!=(const Iterator &other);
    bool visited(Vertex vertex); 
    GraphTraversal* traversal; 
    bool tolCheck(Vertex next); 
    bool bounds(Vertex vertex);  
    void markVisited(Vertex vertex); 
    bool discovered(Vertex vertex);  
    void markDiscovered(Vertex vertex); 
    
    /** @todo [Part 1] */
    /** add member functions if neccesary*/
  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/ 
   std::vector <bool> matrix; 
   std::vector<bool> found;
   Vertex vertex; 
  }; 

  
  
  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new vertex to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Vertex & t) = 0;
  /**
   * Remove and return the next vertex of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Vertex pop() = 0;
  /**
   * Return but not remove the next vertex of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Vertex peek() const = 0;
  /**
   * To see if the traversal has no vertexs left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0; 
  int getEdgeCount();
protected:  
  unsigned long int _edges;
  Graph* _graph; 
  Vertex startVertex;  
  double delta;
private:
 // static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);   

};
