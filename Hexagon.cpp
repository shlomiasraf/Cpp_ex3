//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Hexagon.hpp"
#include <string>

using namespace ariel;

Hexagon::Hexagon() = default;

Hexagon::Hexagon(std::vector<Vertex> Vertexs, std::vector<Edge*> edges, std::string resource, int coinNumber)
{
    for(int i = 0; i < 6; i++)
    {
        this->Vertexs.push_back(Vertexs[i]);
        this->edges.push_back(*edges[i]); // Assuming this->edges is a vector of pointers to Edge
    }
    this->resource = resource;
    this->coinNumber = coinNumber;
}
std::vector<Edge> Hexagon::getEdges()
{
    return this->edges;
}
std::vector<Vertex> Hexagon::getVertexs()
{
    return this->Vertexs;
}
