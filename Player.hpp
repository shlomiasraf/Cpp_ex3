#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Card.hpp"
#include <vector>

#include "Catan.hpp"
#include "Edge.hpp"
namespace ariel
{
    class Vertex;
    class Player
    {
    private:
        std::string name;
        int totalPoints;
        bool hisTurn;
        bool firstTurn;
        bool secondTurn;
        std::vector<Vertex> Settlements;
        std::vector<Vertex> Cities;
        std::vector<ResourceCard> resourceCards;
        std::vector<DevelopmentCard> developmentCards;
    public:
        Player();
        Player(std::string);
        std::string PlayerGetName();
        void placeSettelemnt(Vertex&);
        void placeRoad(Edge&);
        void placeCity(Vertex&);
        void endTurn();
        void trade(Player, std::vector<ResourceCard>, std::vector<ResourceCard>);
        void buyDevelopmentCard();
        void printPoints();
        bool contains(std::vector<ResourceCard>,std::vector<ResourceCard>);
        void ChangeToHisTurn();
        std::vector<Vertex>getSettlements();
    };
}

#endif //PLAYER_HPP
