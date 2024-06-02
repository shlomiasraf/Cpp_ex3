//
// Created by Shlomi Asraf on 28/05/2024.
//

#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"
#include <vector>
#include <string>
#include <map>

namespace ariel
{
    class Edge
    {
    private:
        Vertex& Vertex1;
        Vertex& Vertex2;
        std::vector<Edge> neighborsEdge;
        std::string RoadOwner;
        static std::unordered_map<std::string, Edge> allEdges;
    public:
        Edge();
        Edge(Vertex&, Vertex&);
        static Edge& getEdge(Vertex&, Vertex&);
        std::string getRoadOwner();
        bool EdgeNearSettelemntOrCity();
        bool nearRoad();
        void addRoad(std::string player);
        void addNeighborEdge(Edge);
        Vertex& getVertex1();
        Vertex& getVertex2();
        bool operator==(Edge other);

    };
}

#endif //EDGE_HPP
