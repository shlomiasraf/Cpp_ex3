//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Board.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Card.hpp"
#include "Hexagon.hpp"
#include <random>
#include <iostream>

using namespace ariel;

Board::Board() = default;

void Board::createBoard()
{
    std::vector<Vertex> vertexs = {Vertex(-3,-7), Vertex(-1,-7), Vertex(1,-7), Vertex(-4,-4), Vertex(-2,-4), Vertex(0,-4), Vertex(2,-4)
    ,Vertex(-5,-1), Vertex(-3,-1), Vertex(-1,-1), Vertex(1,-1), Vertex(3,-1), Vertex(-4,2), Vertex(-2,2)
    ,Vertex(0,2), Vertex(2,2), Vertex(-3,5), Vertex(-1,5), Vertex(1,5)};
    std::vector<std::string> resources = {"Brick", "Grain", "Wool", "Lumber", "Ore", "Grain", "Wool"
    , "Grain", "Lumber", "Desert", "Lumber", "Ore", "Grain", "Brick"
    ,"Wool", "Brick", "Ore", "Wool", "Lumber"};
    std::vector<int> coins = {5, 6, 11, 8, 3, 4, 5, 9, 11, 3, 8, 12, 6, 4, 10, 10, 2, 9};
    for(int i = 0; i < vertexs.size(); i++)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, resources.size()-1);
        int randomResourceIndex = dis(gen);
        int coin;
        if(resources[randomResourceIndex] == "Desert")
        {
            coin = 0;
        }
        else
        {
            std::uniform_int_distribution<> dis2(0, coins.size()-1);
            int coinIndex = dis2(gen);
            coin = coins[coinIndex];
            coins.erase(coins.begin() + coinIndex);

        }
        createHexagon(vertexs[i],resources[randomResourceIndex],coin);
        resources.erase(resources.begin() + randomResourceIndex);

    }
}
void Board::createHexagon(Vertex v,std::string resource, int coinNumber)
{
    // Get or create the flyweight vertex
    Vertex& v1 = Vertex::createVertex(v.getX(),v.getY());
    v1.addResourceAndCoin(resource,coinNumber);

    // Get or create the flyweight vertices for v2 to v6
    Vertex& v2 = Vertex::createVertex(v1.getX(), v1.getY() + 2);
    v2.addResourceAndCoin(resource,coinNumber);
    Vertex& v3 = Vertex::createVertex(v1.getX() + 1, v1.getY() + 3);
    v3.addResourceAndCoin(resource,coinNumber);
    Vertex& v4 = Vertex::createVertex(v1.getX() + 2, v1.getY() + 2);
    v4.addResourceAndCoin(resource,coinNumber);
    Vertex& v5 = Vertex::createVertex(v1.getX() + 2, v1.getY());
    v5.addResourceAndCoin(resource,coinNumber);
    Vertex& v6 = Vertex::createVertex(v1.getX() + 1, v1.getY() - 1);
    v6.addResourceAndCoin(resource,coinNumber);

    // Create the vector of vertices
    std::vector<Vertex> vertexs = {v1, v2, v3, v4, v5, v6};

    // Get or create the flyweight edges
    Edge& e1 = Edge::createEdge(v1, v2);
    Edge& e2 = Edge::createEdge(v2, v3);
    Edge& e3 = Edge::createEdge(v3, v4);
    Edge& e4 = Edge::createEdge(v4, v5);
    Edge& e5 = Edge::createEdge(v5, v6);
    Edge& e6 = Edge::createEdge(v6, v1);

    // Create the vector of edges
    std::vector<Edge*> edges = {&e1, &e2, &e3, &e4, &e5, &e6};
    // Connect neighboring edges
    for(int i = 0; i < 6; i++)
    {
        edges[i]->getVertex1().addNeighborVertex(edges[i]->getVertex2());
        edges[i]->getVertex2().addNeighborVertex(edges[i]->getVertex1());
        if(i < 5)
        {
            edges[i]->addNeighborEdge(*edges[i+1]);
            edges[i+1]->addNeighborEdge(*edges[i]);
        }
        else
        {
            edges[i]->addNeighborEdge(*edges[0]);
            edges[0]->addNeighborEdge(*edges[i]);
        }
    }

    // Create the hexagon and add it to the board
    this->Hexagons.push_back(Hexagon(vertexs, edges, resource, coinNumber));
}
std::vector<Hexagon> Board::getHexagons()
{
    return this->Hexagons;
}
