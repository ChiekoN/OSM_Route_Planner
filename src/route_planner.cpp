#include "route_planner.h"
#include <algorithm>
using std::vector;
using std::sort;

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
  // Rescale coordinates between 0 and 1.
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;
  
  // Get the closest node for the coordinates being input.
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}

vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node* current_node) {
  
  vector<RouteModel::Node> path_found {};
  distance = 0.0;
  
  // Trace nodes back to the starting node with storing them in path_found. 
  while(current_node->parent != nullptr) {
    path_found.push_back(*current_node);
    distance += current_node->distance(*(current_node->parent));
    current_node = current_node->parent;
  }
  path_found.push_back(*current_node);
  distance *= m_Model.MetricScale();
  return path_found;
}

void RoutePlanner::AStarSearch() {

  start_node->visited = true;
  open_list.push_back(start_node);
  RouteModel::Node* current_node = nullptr;
  
  while(open_list.size() > 0) {
    current_node = NextNode();
    if(current_node->distance(*end_node) == 0) {
      // When getting to the end node, set path and return.
      m_Model.path = ConstructFinalPath(current_node);
      return;
    } 
    else {
      // Add neighbors to open_list.
      AddNeighbors(current_node);
    }
  }
}
  
float RoutePlanner::CalculateHValue(const RouteModel::Node* current_node) {
  return current_node->distance(*end_node) ;
}

// Comparison function used in RoutePlanner::NextNode().
bool comp_fvalue(RouteModel::Node* n1, RouteModel::Node* n2) {
  float n1_f = n1->h_value + n1->g_value;
  float n2_f = n2->h_value + n2->g_value;
  return ( n1_f < n2_f );
}

RouteModel::Node* RoutePlanner::NextNode() {
  // Sort open_list vector by f-value(= g-value + h-value).
  sort(open_list.begin(), open_list.end(), comp_fvalue);
  // Save the pointer to the node with the lowest f-value.
  RouteModel::Node* lowest = open_list[0];
  // Delete the first element from open_list.
  open_list.erase(open_list.begin());
  
  return lowest;
}

void RoutePlanner::AddNeighbors(RouteModel::Node* current_node){
  // Set neighbors in current_node->neighbors.
  current_node->FindNeighbors() ;
  
  // Set neighbors' status (parent, g-value, h-value, status as visited).
  // Also add the neighbors to open_list.
  for(RouteModel::Node* neighbor : current_node->neighbors) {
    neighbor->parent = current_node;
    neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
    neighbor->h_value = CalculateHValue(neighbor);
    open_list.push_back(neighbor);
    neighbor->visited = true;
  }
}
