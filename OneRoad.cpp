//
// Created by Shlomi Asraf on 10/06/2024.
//

/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
using namespace std;
using namespace ariel;

int main()
{
    Player p1("Amit","red");
    Player p2("Yossi","blue");
    Player p3("Dana","yellow");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    vector<Player*> allPlayers = catan.getPlayers();
    Board board;// get the board of the game.
    board.createBoard();
    allPlayers[0]->placeSettelemnt(Vertex::getVertex(-3,-1));
    allPlayers[0]->placeRoad(Edge::getEdge(Vertex::getVertex(-3,-1),Vertex::getVertex(-3,1)));

    allPlayers[1]->ChangeToHisTurn(allPlayers);
    allPlayers[1]->placeSettelemnt(Vertex::getVertex(1,-5));
    allPlayers[1]->placeRoad(Edge::getEdge(Vertex::getVertex(1,-5),Vertex::getVertex(0,-4)));

    allPlayers[2]->ChangeToHisTurn(allPlayers);
    allPlayers[2]->placeSettelemnt(Vertex::getVertex(3,1));
    allPlayers[2]->placeRoad(Edge::getEdge(Vertex::getVertex(3,1),Vertex::getVertex(4,2)));

    allPlayers[2]->placeSettelemnt(Vertex::getVertex(2,-2));
    allPlayers[2]->placeRoad(Edge::getEdge(Vertex::getVertex(2,-2),Vertex::getVertex(3,-1)));

    allPlayers[1]->ChangeToHisTurn(allPlayers);
    allPlayers[1]->placeSettelemnt(Vertex::getVertex(-2,4));
    allPlayers[1]->placeRoad(Edge::getEdge(Vertex::getVertex(-2,4),Vertex::getVertex(-3,5)));

    allPlayers[0]->ChangeToHisTurn(allPlayers);
    allPlayers[0]->placeSettelemnt(Vertex::getVertex(0,4));
    allPlayers[0]->placeRoad(Edge::getEdge(Vertex::getVertex(0,4),Vertex::getVertex(-1,5)));

    for(int i = 0; i < allPlayers.size(); i++)
    {
        catan.rollDice(allPlayers[i]);
        allPlayers[i]->TradeWhatNeeded(allPlayers);
        allPlayers[i]->placeCities();
        allPlayers[i]->placeSettelments();
        if(catan.buyDevelopmentCard(allPlayers[i]))
        {
            allPlayers[i]->useDevelopmentCard(allPlayers);
        }
        allPlayers[i]->placeRoads();
    }
}

