#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"
using std::vector;

//
// This header file declares RoutePlanner Class.
// RoutePlanner class have attributes and methods that are used to perform A* search.
//

class RoutePlanner {

  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    float GetDistance() { return distance; }
    void AStarSearch();
  
  private:
    RouteModel &m_Model;
    RouteModel::Node* start_node;
    RouteModel::Node* end_node;
    float distance;
    // A list of nodes that are possible next nodes to go.
    vector<RouteModel::Node*> open_list;
  
    // Construct a list of Nodes from current_node to start_node in order.
    vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node* current_node);   
    float CalculateHValue(const RouteModel::Node* current_node);
    // Find the next node to go from open_list.
    RouteModel::Node* NextNode();
    // Add neighbor nodes to current_node with setting the information.
    void AddNeighbors(RouteModel::Node* current_node);
};

#endif
