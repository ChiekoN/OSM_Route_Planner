#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : 
Model(xml) {
  int i = 0;
  for (Model::Node cur_node : this->Nodes()) {
    Node new_node = Node(i, this, cur_node);
    m_Nodes.push_back(new_node);
    i++;
  }
  CreateNodeToRoadHashmap();
}

void RouteModel::CreateNodeToRoadHashmap() {

  for(int i=0; i < Roads().size(); i++) {
    const Model::Road &road = Roads()[i];

    if(road.type != Model::Road::Type::Footway) {
      for(int n : Ways()[road.way].nodes) {
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
  
  // Search the closest node to <this> from nodes of node_indices.
  for(int n_idx : node_indices) {
    Node &node = parent_model->SNodes()[n_idx];
    if( (!node.visited) && (node.distance(*this) != 0)) {
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
    RouteModel::Node* closest_on_road = FindNeighbor(nodes_on_road);
    if (closest_on_road != nullptr) {
      this->neighbors.push_back(closest_on_road);
    }
  }
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
      for(int n_idx : Ways()[road.way].nodes) {
        float dist = SNodes()[n_idx].distance(temp_node); 
        if((closest_idx < 0) || (dist < min_dist)) {
          min_dist = dist;
          closest_idx = n_idx;
        }
      }
    }
  }
  return SNodes()[closest_idx];
}