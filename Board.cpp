//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Board.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Card.hpp"
#include "Catan.hpp"
#include "Hexagon.hpp"
#include "Player.hpp"
using namespace ariel;

Board::Board() = default;

void Board::createBoard()
{
    createHexagon(Vertex(-3,-7),"Brick",5);
    createHexagon(Vertex(-1,-7),"Grain",6);
    createHexagon(Vertex(1,-7),"Wool",11);
    createHexagon(Vertex(-4,-4),"Lumber",8);
    createHexagon(Vertex(-2,-4),"Ore",3);
    createHexagon(Vertex(0,-4),"Grain",4);
    createHexagon(Vertex(2,-4),"Wool",5);
    createHexagon(Vertex(-5,-1),"Grain",9);
    createHexagon(Vertex(-3,-1),"Lumber",11);
    createHexagon(Vertex(-1,-1),"Desert",0);
    createHexagon(Vertex(1,-1),"Lumber",3);
    createHexagon(Vertex(3,-1),"Ore",8);
    createHexagon(Vertex(-4,2),"Grain",12);
    createHexagon(Vertex(-2,2),"Brick",6);
    createHexagon(Vertex(0,2),"Wool",4);
    createHexagon(Vertex(2,2),"Brick",10);
    createHexagon(Vertex(-3,5),"Ore",10);
    createHexagon(Vertex(-1,5),"Wool",2);
    createHexagon(Vertex(1,5),"Lumber",9);

}
void Board::createHexagon(Vertex v,std::string resource, int coinNumber)
{
    // Get or create the flyweight vertex
    Vertex& v1 = Vertex::getVertex(v.getX(),v.getY());
    v1.addResourceAndCoin(resource,coinNumber);

    // Get or create the flyweight vertices for v2 to v6
    Vertex& v2 = Vertex::getVertex(v1.getX(), v1.getY() + 2);
    v2.addResourceAndCoin(resource,coinNumber);
    Vertex& v3 = Vertex::getVertex(v1.getX() + 1, v1.getY() + 3);
    v3.addResourceAndCoin(resource,coinNumber);
    Vertex& v4 = Vertex::getVertex(v1.getX() + 2, v1.getY() + 2);
    v4.addResourceAndCoin(resource,coinNumber);
    Vertex& v5 = Vertex::getVertex(v1.getX() + 2, v1.getY());
    v5.addResourceAndCoin(resource,coinNumber);
    Vertex& v6 = Vertex::getVertex(v1.getX() + 1, v1.getY() - 1);
    v6.addResourceAndCoin(resource,coinNumber);

    // Create the vector of vertices
    std::vector<Vertex> vertexs = {v1, v2, v3, v4, v5, v6};

    // Get or create the flyweight edges
    Edge& e1 = Edge::getEdge(v1, v2);
    Edge& e2 = Edge::getEdge(v2, v3);
    Edge& e3 = Edge::getEdge(v3, v4);
    Edge& e4 = Edge::getEdge(v4, v5);
    Edge& e5 = Edge::getEdge(v5, v6);
    Edge& e6 = Edge::getEdge(v6, v1);

    // Create the vector of edges
    std::vector<Edge> edges = {e1, e2, e3, e4, e5, e6};

    // Connect neighboring edges
    for(int i = 0; i < 6; i++)
    {
        edges[i].getVertex1().addNeighborVertex(edges[i].getVertex2());
        edges[i].getVertex2().addNeighborVertex(edges[i].getVertex1());
        if(i < 5)
        {
            edges[i].addNeighborEdge(edges[i+1]);
            edges[i+1].addNeighborEdge(edges[i]);
        }
        else
        {
            edges[i].addNeighborEdge(edges[0]);
            edges[0].addNeighborEdge(edges[i]);
        }
    }

    // Create the hexagon and add it to the board
    this->Hexagons.push_back(Hexagon(vertexs, edges, resource, coinNumber));
}

