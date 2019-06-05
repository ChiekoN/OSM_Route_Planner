#include "route_model.h"
#include <iostream>

//
// This file defines RouteModel class which inherits Model class 
// from IO2D example code.
//

RouteModel::RouteModel(const std::vector<std::byte> &xml) : 
Model(xml) {
  int i = 0;
  // Create RouteModel::Node objects that correspond to the nodes in the model.
  for (Model::Node cur_node : this->Nodes()) {
    Node new_node = Node(i, this, cur_node);
    m_Nodes.push_back(new_node);
    i++;
  }
  CreateNodeToRoadHashmap();
}

float RouteModel::Node::distance(Node to_node) const {
  // Return the euclidean distance given by sqrt( (x1 - x2)^2 + (y1 - y2)^2 ).
  return sqrt(pow(this->x - to_node.x, 2) + pow(this->y - to_node.y, 2));
}

void RouteModel::CreateNodeToRoadHashmap() {

  for(int i=0; i < Roads().size(); i++) {
    const Model::Road &road = Roads()[i];

    if(road.type != Model::Road::Type::Footway) {

      // Add every node in the current road(=way) to node_to_road.
      for(int n : Ways()[road.way].nodes) {

        // If this is the first time to find this node, set the empty vector of Road
        //   with respect to this node in node_to_road.
        if(node_to_road.find(n) == node_to_road.end()) {
          node_to_road[n] = vector<const Model::Road*> {};
        }
        node_to_road[n].push_back(&road);
      }
    }
  }
}

RouteModel::Node* RouteModel::Node::FindNeighbor(vector<int> node_indices) {
  
  RouteModel::Node* closest_node = nullptr;
  
  // DEBUG
  std::cout << " FindNeighbor ! node_indices.size() = " << node_indices.size() << "\n";
  
  // Search the closest node to <this> from nodes of node_indices.
  for(int n_idx : node_indices) {
    Node &node = parent_model->SNodes()[n_idx];

    // Find the closest node that hasn't been visited and that isn't itself.
    if( (!node.visited) && (node.distance(*this) != 0)) {

      // DEBUG
      // std::cout << " >>> FindNeighbor : node = " << node.index << "\n";
      if((closest_node == nullptr) ||
         (closest_node->distance(*this) > node.distance(*this))) {
        closest_node = &node;
      }
    }
  }
  return closest_node;
}

void RouteModel::Node::FindNeighbors() {
  
  vector<const Model::Road*> roads = parent_model->node_to_road[this->index];
  this->neighbors = vector<Node *> {};
  
  // Get the closest node on each road and store them in this->neighbors.
  for(const Model::Road* road : roads) {
    vector<int> nodes_on_road = parent_model->Ways()[road->way].nodes;

    // Get the current node in the road and set the previous node 
    //  and next node as neighbors.
    for(int i = 0; i < nodes_on_road.size(); i++) {
      RouteModel::Node &node = parent_model->SNodes()[nodes_on_road[i]];
      if(node.index == this->index) {

        // Push back the previous node to neighbors if it hasn't been visited. 
        if(i > 0 && parent_model->SNodes()[nodes_on_road[i-1]].visited == false) {
          this->neighbors.push_back(&parent_model->SNodes()[nodes_on_road[i-1]]);

        // Push back the next node to neighbors if it hasn't been visited.
        } else if((i < nodes_on_road.size() - 1) &&
                parent_model->SNodes()[nodes_on_road[i+1]].visited == false) {
            this->neighbors.push_back(&parent_model->SNodes()[nodes_on_road[i+1]]);
        }
        break;
      }
    }
   
    // RouteModel::Node* closest_on_road = FindNeighbor(nodes_on_road);

    // if (closest_on_road != nullptr) {
    //   this->neighbors.push_back(closest_on_road);
    //}
  }
  // DEBUG
  std::cout << " >>> FindNeighbors : size of neighbors = " << this->neighbors.size() << "\n" ;
}

RouteModel::Node &RouteModel::FindClosestNode(float x, float y) {

  RouteModel::Node temp_node;
  temp_node.x = x;
  temp_node.y = y;
  float min_dist = std::numeric_limits<float>::max();
  int closest_idx = -1;

  // Check the distance to every node in each road, and save the closest node.
  for(Model::Road road : Roads()) {
    if(road.type != Model::Road::Type::Footway) {
      // Search only roads for vehicles.

      // Loop over the node in the road and calculate the distance to (x,y).
      for(int n_idx : Ways()[road.way].nodes) {
        float dist = SNodes()[n_idx].distance(temp_node); 
        // Save the closest node.
        if((closest_idx < 0) || (dist < min_dist)) {
          min_dist = dist;
          closest_idx = n_idx;
        }
      }
    }
  }
  return SNodes()[closest_idx];
}
