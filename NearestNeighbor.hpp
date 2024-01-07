#ifndef NearestNeighbor_hpp
#define NearestNeighbor_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <chrono>
#include "Node.hpp"


std::pair<Node, int> findClosestNodeAndRemove(Node sourceNode, std::list<Node>& nodeList) {
    double minDistance = std::numeric_limits<double>::max();
    Node closestNode = nodeList.front(); // Initialize with the first node
    std::list<Node>::iterator closestNodeIter = nodeList.begin();

    for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
        double dist = sourceNode.distance(*it);
        if (dist < minDistance) {
            minDistance = dist;
            closestNode = *it;
            closestNodeIter = it;
        }
    }
    
    // Remove the closest node from the list
    nodeList.erase(closestNodeIter);
    int distanceTravel = sourceNode.distance(closestNode);
    return std::make_pair(closestNode,distanceTravel);
}
std::list<Node> readTSPFile(const std::string& filename) {
    std::ifstream file(filename);
    std::list<Node> nodes;

    if (file.is_open()) {
        std::string line;
        int linesToSkip = 7; // Number of lines to skip

        while (linesToSkip > 0 && std::getline(file, line)) {
            linesToSkip--;
        }

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int nodeNumber;
            double x, y;

            // Read node number and coordinates
            if (iss >> nodeNumber >> x >> y) {
                Node node(nodeNumber, x, y);
                nodes.push_back(node);
            }
        }

        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return nodes;
}
void nearestNeighbor (std::string filename){
    //read file and store the city and location to tsp
    std::list<Node> nodes = readTSPFile(filename);
    auto startTime = std::chrono::steady_clock::now();
    //create a empty list of visted Nodes
    std::list<Node> visitedNodes;
    //create a variable of for totalDistance
    int totalDistance = 0;
    visitedNodes.push_back(nodes.front()); // Start with node 1
    nodes.pop_front(); // Remove node 1 from the unvisited nodes list

    while (!nodes.empty()) {
        Node lastVisitedNode = visitedNodes.back();
        std::pair<Node, int> closestAndDistance = findClosestNodeAndRemove(lastVisitedNode, nodes);
//        std::cout<<closestAndDistance.first.getid()<<"\n";
        visitedNodes.push_back(closestAndDistance.first);
        totalDistance+=closestAndDistance.second;
        
    }
    totalDistance+=visitedNodes.back().distance(visitedNodes.front());
    visitedNodes.push_back(visitedNodes.front());
    // Print visited nodes
    auto end = std::chrono::steady_clock::now();
    auto diff = end - startTime;
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
//    std::cout << "Visited Nodes: ";
    for (const Node& node : visitedNodes) {
        std::cout << node.id << " ";
    }
    std::cout << "\n";
        
    // Print total distance
    std::cout << "Total Distance: " << totalDistance << std::endl;

    // Print time taken
    std::cout << "Time in ms: " << duration << std::endl;
    
}
#endif /* NearestNeighbor_hpp */

