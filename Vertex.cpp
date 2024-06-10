#include "Vertex.hpp"
#include <unordered_map>
#include <stdexcept>

#include "Edge.hpp"
using namespace ariel;
std::unordered_map<std::string, Vertex> Vertex::vertexMap;
#include <iostream>

Vertex::Vertex() = default;

Vertex::Vertex(int x, int y)
{
    this->x = x;
    this->y = y;
}
Vertex &Vertex::createVertex(int x, int y)
{
    // Create a string key by concatenating x and y values
    std::string key = std::to_string(x) + "," + std::to_string(y);

    // Check if the vertex already exists in the map
    auto it = vertexMap.find(key);
    if (it != vertexMap.end())
    {
        // Vertex already exists, return the existing instance
        return it->second;
    }
    // Create a new vertex and store it in the map
    Vertex newVertex(x, y);
    vertexMap[key] = newVertex;
    return vertexMap[key];
}

Vertex& Vertex::getVertex(int x, int y)
{
    // Create a string key by concatenating x and y values
    std::string key = std::to_string(x) + "," + std::to_string(y);

    // Check if the vertex already exists in the map
    auto it = vertexMap.find(key);
    if (it != vertexMap.end())
    {
        // Vertex already exists, return the existing instance
        return it->second;
    }
    throw std::out_of_range("this vertex " +key +" isn't on the board.");
}


int Vertex::getX() 
{
    return this->x;
}

int Vertex::getY() 
{
    return this->y;
}

std::string Vertex::GetSettelemntOwner() 
{
    return this->SettelemntOwner;
}

std::string Vertex::GetCityOwner() 
{
    return this->CityOwner;
}
void Vertex::addNeighborVertex(Vertex& neighborVertex)
{
    bool contains = false;
    for(int i = 0; i < this->neighborsVertex.size(); i++)
    {
        if(neighborVertex == *this->neighborsVertex[i])
        {
            contains = true;
            break;
        }
    }
    if(!contains)
    {
        this->neighborsVertex.push_back(&neighborVertex);
    }
}
bool Vertex::VertexNearRoad()
{
    for(int i = 0; i < this->neighborsVertex.size(); i++)
    {
        Edge e1 = Edge::getEdge(*this, *neighborsVertex[i]);
        if(e1.getRoadOwner() == this->GetSettelemntOwner() || e1.getRoadOwner() == this->GetCityOwner())
        {
            return true;
        }
    }
    return false;
}
bool Vertex::nearSettelemntOrCity()
{
    for (int i = 0; i < this->neighborsVertex.size(); i++)
    {
        if(this->neighborsVertex[i]->GetSettelemntOwner() != "" || this->neighborsVertex[i]->GetCityOwner() != "")
        {
            return true;
        }
    }
    return false;
}
void Vertex::addCity(std::string playerColor)
{
    this->CityOwner = playerColor;
}

void Vertex::addResourceAndCoin(std::string resource, int coinNumber)
{
    this->resourcesAndCoins[coinNumber] = resource;
}
void Vertex::addSettelemnt(std::string playerColor)
{
    this->SettelemntOwner = playerColor;
}
std::unordered_map<int,std::string> Vertex::getResourcesAndCoins()
{
    return this->resourcesAndCoins;
}
std::vector<Vertex*> Vertex::getNeighborsVertex()
{
    return this->neighborsVertex;
}

bool Vertex::operator==(Vertex other)
{
    return this->x == other.getX() && this->y == other.getY();
}
