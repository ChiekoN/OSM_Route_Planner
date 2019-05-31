#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>
using std::vector;
using std::unordered_map;

//
// This is a header file for RouteModel class.
// RouteModel inherits Model class from IO2D example code.
// Add attributes and methods which are used to perform A* search to find a shortest path.
//

class RouteModel : public Model {

  public:

    // Define Node class which has some new attributes and methods for A* search. 
    class Node : public Model::Node {

      public:

        Node* parent = nullptr; // Set the previous node in the path
      	float h_value = std::numeric_limits<float>::max();
      	float g_value = 0.0;
      	bool visited = false;
      	vector<Node *> neighbors;

        Node(){}
        Node(int idx, RouteModel* search_model, Model::Node node) : 
			Model::Node(node), parent_model(search_model), index(idx) {}
        
      	float distance(Node to_node) const; // Get a distance from this node to to_node.
        void FindNeighbors(); // Find candidates of the nearest neighbor.

      
      private:

        int index; // arbitrary index for a node.
        RouteModel* parent_model = nullptr; // The model this node belongs to.
        // Find the closest neighbor from node_indices.
        RouteModel::Node* FindNeighbor(vector<int> node_indices);
    };
    
    vector<Node> path; // This variable will eventually store the path that is found by the A* search.

    RouteModel(const vector<std::byte> &xml);  

    // Return Model::m_Nodes which stores all nodes in the Model.
    vector<Node> &SNodes() { return m_Nodes; }
    unordered_map <int, vector<const Model::Road*>> &GetNodeToRoadMap() { return node_to_road; }
    // Return the closest node from the coordinates (x,y).
    Node &FindClosestNode(float x, float y);

  private:

    vector<Node> m_Nodes;
    // node_to_road stores a dictionary where each node refers to the list of road it belongs to.
    unordered_map <int, vector<const Model::Road*>> node_to_road;
    void CreateNodeToRoadHashmap();
};

#endif
