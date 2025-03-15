#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

// Class representing a vertex
class Node {
 public:
  int distance;              // Distance from the starting vertex
  bool isVisited;            // Flag to mark if the vertex was visited
  std::vector<int> adjacent; // List of adjacent vertices

  // Constructor to initialize default values
  Node() {
    isVisited = false;
    distance = INT_MAX; // Set distance to infinity by default
  }
};

int main() {
  // Open the file
  std::fstream file("graph.txt");

  int numOfVertices, numOfEdges, startEdge;
  file >> numOfVertices >> numOfEdges;

  // Create a vector to store pointers to Node objects
  std::vector<Node *> nodes(numOfVertices);

  // Initialize each node
  for (int i = 0; i < numOfVertices; i++) {
    nodes.at(i) = new Node();
  }

  // Read and add edges from a file
  for (int i = 0; i < numOfEdges; i++) {
    int from, to;
    file >> from >> to;
    nodes.at(from)->adjacent.push_back(to);
    nodes.at(to)->adjacent.push_back(from);
  }

  // Read the starting vertex
  file >> startEdge;

  // Close the file
  file.close();

  // BFS initialization
  std::queue<Node *> queue;
  nodes.at(startEdge)->isVisited = true;
  nodes.at(startEdge)->distance = 0;
  queue.push(nodes.at(startEdge));

  // BFS loop to calculate the shortest paths
  while (!queue.empty()) {
    Node *node = queue.front();
    queue.pop();

    // Go through all adjacent vertices
    for (int adjacent : node->adjacent) {
      if (nodes.at(adjacent)->isVisited) {
        continue; // Skip already visited nodes
      } else {
        queue.push(nodes.at(adjacent));
        nodes.at(adjacent)->isVisited = true;
        nodes.at(adjacent)->distance = node->distance + 1;
      }
    }
  }

  // Output the shortest distances
  for (Node *node : nodes) {
    std::cout << node->distance << std::endl;
  }

  // Free memory
  for (int i = 0; i < numOfVertices; i++) {
    delete (nodes.at(i));
  }
  return 0;
}
