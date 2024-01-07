//
//  GreedyTSP.hpp
//  Project 3
//
//  Created by Riyuan Liu on 12/20/23.
//

#ifndef GreedyTSP_hpp
#define GreedyTSP_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <queue>
#include <chrono>
#include <algorithm>
#include "Node.hpp" // Assuming Node struct is defined



struct Edge {
    double weight;
    Node node1;
    Node node2;

    Edge(Node n1, Node n2) : node1(n1), node2(n2) {
        weight = n1.distance(n2);
    }
};
struct less_than_key{
    inline bool operator() (const Edge& struct1, const Edge& struct2)
    {
        return (struct1.weight < struct2.weight);
    }
};


std::list<Node> readTSPFile1(const std::string& filename) {
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


std::list<Edge> createEdgeList(const std::list<Node>& nodes) {
    std::vector<Edge> edges;
    for (auto it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != nodes.end(); ++it2) {
            Edge edge(*it1,*it2);
            edges.push_back(edge);
        }
    }

    std::sort(edges.begin(),edges.end());
    

    return edges;
}
void greedyTSP(const std::string& filename) {
    //read file and store the city and location to tsp
    std::list<Node> nodes = readTSPFile(filename);
    auto startTime = std::chrono::steady_clock::now();
    //create a empty list of visted Nodes
    std::list<Node> visitedNodes;
    //create a variable of for totalDistance
    int totalDistance = 0;
    visitedNodes.push_back(nodes.front()); // Start with node 1
    nodes.pop_front(); // Remove node 1 from the unvisited nodes list
    std::list<Edge> edges =createEdgeList(nodes);
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Print visited nodes
    std::cout << "Visited Nodes: ";
    for (const Node& node : visitedNodes) {
        std::cout << node.id << " ";
    }

    // Print total distance
    std::cout << "Total Distance: " << totalDistance << std::endl;

    // Print time taken
    std::cout << "Time in ms: " << elapsedTime.count() << std::endl;
}

#endif /* GreedyTSP_hpp */
