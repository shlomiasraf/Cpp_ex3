//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Edge.hpp"

using namespace ariel;

std::unordered_map<std::string, Edge> Edge::allEdges;
Edge::Edge(Vertex& V1, Vertex& V2)
: Vertex1(V1), Vertex2(V2)
{
}
Edge& Edge::createEdge(Vertex& v1, Vertex& v2)
{
    std::string edgeKey1 = std::to_string(v1.getX()) + "," + std::to_string(v1.getY()) +  "," + std::to_string(v2.getX()) + "," + std::to_string(v2.getY());
    std::string edgeKey2 = std::to_string(v2.getX()) + "," + std::to_string(v2.getY()) +  "," + std::to_string(v1.getX()) + "," + std::to_string(v1.getY());

    auto it = allEdges.find(edgeKey1);
    if (it != allEdges.end())
    {
        return it->second;
    }
    it = allEdges.find(edgeKey2);
    if (it != allEdges.end())
    {
        return it->second;
    }
    // Create a new edge if it doesn't exist
    Edge newEdge(v1, v2);
    auto result = allEdges.emplace(edgeKey1, newEdge);
    return result.first->second;
}
Edge& Edge::getEdge(Vertex& v1, Vertex& v2)
{
    std::string edgeKey1 = std::to_string(v1.getX()) + "," + std::to_string(v1.getY()) +  "," + std::to_string(v2.getX()) + "," + std::to_string(v2.getY());
    std::string edgeKey2 = std::to_string(v2.getX()) + "," + std::to_string(v2.getY()) +  "," + std::to_string(v1.getX()) + "," + std::to_string(v1.getY());

    auto it = allEdges.find(edgeKey1);
    if (it != allEdges.end())
    {
        return it->second;
    }
    it = allEdges.find(edgeKey2);
    if (it != allEdges.end())
    {
        return it->second;
    }
    throw std::out_of_range("this edge " + edgeKey1 + " isn't on the board.");

}
std::string Edge::getRoadOwner()
{
    return this->RoadOwner;
}
void Edge::addNeighborEdge(Edge& neighborEdge)
{
    bool contains = false;
    for(int i = 0; i < this->neighborsEdge.size(); i++)
    {
        if(neighborEdge == *this->neighborsEdge[i])
        {
            contains = true;
            break;
        }
    }
    if(!contains)
    {
        this->neighborsEdge.push_back(&neighborEdge);
    }
}
void Edge::addRoad(std::string playerColor)
{
    this->RoadOwner = playerColor;
}
bool Edge::nearRoad()
{
    for (int i = 0; i < this->neighborsEdge.size(); i++)
    {
        if(this->neighborsEdge[i]->getRoadOwner() == this->RoadOwner)
        {
            return true;
        }
    }
    return false;
}
bool Edge::EdgeNearSettelemntOrCity()
{
    if(this->getRoadOwner() == this->Vertex1.GetSettelemntOwner() || this->getRoadOwner() == this->Vertex2.GetSettelemntOwner() || this->getRoadOwner() == this->Vertex1.GetCityOwner() || this->getRoadOwner() == this->Vertex2.GetCityOwner())
    {
        return true;
    }
    return false;
}
Vertex& Edge::getVertex1()
{
    return this->Vertex1;
}
Vertex& Edge::getVertex2()
{
    return this->Vertex2;
}
bool Edge::operator==(Edge other)
{
    return (this->Vertex1 == other.getVertex1() && this->Vertex2 == other.getVertex2()) || (this->Vertex1 == other.getVertex2() && this->Vertex2 == other.getVertex1());
}
std::vector<Edge*> Edge::getNeighborsEdge()
{
    return this->neighborsEdge;
}

