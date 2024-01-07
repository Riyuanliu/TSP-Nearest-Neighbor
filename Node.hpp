//
//  Node.hpp
//  Project 3
//
//  Created by Riyuan Liu on 12/20/23.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <math.h>

class Node {
public:
    int id;
    double x, y; // Node coordinates
    Node():id(0),x(0),y(0){}
    Node(int id, double x, double y) : id(id), x(x), y(y) {}
    const int getid(){
        return id;
    }
    // Calculate distance between nodes
    double distance(const Node& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
};
#endif /* Node_hpp */
