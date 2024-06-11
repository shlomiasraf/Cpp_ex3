
#include "doctest.h"
#include "Board.hpp"
#include <sstream>
#include <iostream>

#include <string>
#include "Catan.hpp"
#include "Player.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Test all the game")
{
    Player p1("Amit","red");
    Player p2("Yossi","blue");
    Player p3("Dana","yellow");
    Catan catan(p1, p2, p3);
    catan.ChooseStartingPlayer();
    vector<Player*> allPlayers = catan.getPlayers();

    Board board;// get the board of the game.
    board.createBoard();

    //test the board.
    CHECK(board.getHexagons()[0].getVertexs().size() == 6);
    CHECK(board.getHexagons()[0].getEdges().size() == 6);

    //test building Settelemnts.
    allPlayers[0]->placeSettelemnt(Vertex::getVertex(-3,-1));
    allPlayers[0]->placeRoad(Edge::getEdge(Vertex::getVertex(-3,-1),Vertex::getVertex(-3,1)));

    //test building Settelemnts near Settelemnt.
    allPlayers[0]->placeSettelemnt(Vertex::getVertex(-3,1));
    CHECK(Vertex::getVertex(-3,1).GetSettelemntOwner() == "");

    //test building Settelemnts.
    allPlayers[0]->placeSettelemnt(Vertex::getVertex(0,4));
    allPlayers[0]->placeRoad(Edge::getEdge(Vertex::getVertex(0,4),Vertex::getVertex(-1,5)));
    allPlayers[0]->contains(allPlayers[0]->getResourceCards(),allPlayers[0]->getResourceCards());

    CHECK(Vertex::getVertex(-3,-1).GetSettelemntOwner() == allPlayers[0]->getColor());
    CHECK(Vertex::getVertex(0,4).GetSettelemntOwner() == allPlayers[0]->getColor());

    //test building Settelemnts without resources.
    allPlayers[0]->placeSettelemnt(Vertex::getVertex(-3,5));
    CHECK(Vertex::getVertex(-3,5).GetSettelemntOwner() == "");

    //test building Settelemnts in place not on the borad.
    CHECK_THROWS(allPlayers[0]->placeSettelemnt(Vertex::getVertex(-12,-12)));

    //test building Roads
    CHECK(Edge::getEdge(Vertex::getVertex(0,4),Vertex::getVertex(-1,5)).getRoadOwner() == allPlayers[0]->getColor());
    CHECK(Edge::getEdge(Vertex::getVertex(-3,-1),Vertex::getVertex(-3,1)).getRoadOwner() == allPlayers[0]->getColor());

    //test building City without resources.
    allPlayers[0]->placeCity(Vertex::getVertex(-3,-1));
    CHECK(Vertex::getVertex(-3,-1).GetCityOwner() == "");

    allPlayers[0]->AddResourceCard("Ore");
    allPlayers[0]->AddResourceCard("Ore");
    allPlayers[0]->AddResourceCard("Ore");
    allPlayers[0]->AddResourceCard("Grain");
    allPlayers[0]->AddResourceCard("Grain");

    //test building City.
    allPlayers[0]->placeCity(Vertex::getVertex(-3,-1));
    CHECK(Vertex::getVertex(-3,-1).GetCityOwner() == allPlayers[0]->getColor());

    //test building City not on Settelemnt.
    allPlayers[0]->placeCity(Vertex::getVertex(-3,5));
    CHECK(Vertex::getVertex(-3,5).GetCityOwner() == "");

    //test buy development card without resources.
    catan.buyDevelopmentCard(allPlayers[0]);
    CHECK(allPlayers[0]->getDevelopmentCards().size() == 0);

    //test buy development card.
    allPlayers[0]->AddResourceCard("Ore");
    allPlayers[0]->AddResourceCard("Wool");
    allPlayers[0]->AddResourceCard("Grain");
    catan.buyDevelopmentCard(allPlayers[0]);
    CHECK(allPlayers[0]->getDevelopmentCards().size() == 1);

    //test trade between 2 players.
    vector<std::string> ResourceToTrade1 = {"Ore"};
    vector<std::string> ResourceToTrade2 = {"Wool"};
    allPlayers[0]->AddResourceCard("Ore");
    allPlayers[1]->AddResourceCard("Wool");
    allPlayers[0]->trade(allPlayers[1],ResourceToTrade1,ResourceToTrade2);
    CHECK(allPlayers[0]->getResourceCards()[0].name == "Wool");
    CHECK(allPlayers[1]->getResourceCards()[0].name == "Ore");

    //test trade without resources.
    allPlayers[0]->trade(allPlayers[1],ResourceToTrade1,ResourceToTrade2);
    CHECK(allPlayers[0]->getResourceCards()[0].name == "Wool");
    CHECK(allPlayers[1]->getResourceCards()[0].name == "Ore");

    //test trade development cards
    allPlayers[1]->AddResourceCard("Ore");
    allPlayers[1]->AddResourceCard("Wool");
    allPlayers[1]->AddResourceCard("Grain");
    allPlayers[1]->ChangeToHisTurn(allPlayers);
    catan.buyDevelopmentCard(allPlayers[1]);
    std::string developmentCard1 = allPlayers[0]->getDevelopmentCards()[0].name;
    std::string developmentCard2 = allPlayers[1]->getDevelopmentCards()[0].name;

    allPlayers[0]->ChangeToHisTurn(allPlayers);
    allPlayers[0]->tradeDevelopmentCards(allPlayers[1],developmentCard1,developmentCard2);
    CHECK(allPlayers[0]->getDevelopmentCards()[0].name == developmentCard2);
    CHECK(allPlayers[1]->getDevelopmentCards()[0].name == developmentCard1);

    //check if game ending.
    CHECK(catan.gameIsEnding(allPlayers[0]) == false);

}
