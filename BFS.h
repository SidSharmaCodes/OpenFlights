/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>


#include "graph.h"

#include "GraphTraversal.h"

//using namespace cs225;

/**
 * A breadth-first GraphTraversal.
 * Derived from base class GraphTraversal
 */
class BFS : public GraphTraversal {
public:
  BFS( Graph * graph, const Vertex & start, double tolerance); 
  

  GraphTraversal::Iterator begin();
  GraphTraversal::Iterator end();

  void add(const Vertex & vertex);
  Vertex pop();
  Vertex peek() const;
  bool empty() const;
  bool bounds(const Vertex & vertex);
private:
  /** @todo [Part 1] */
  /** add private members here*/  
  
  std::queue<Vertex> queue; 
};
