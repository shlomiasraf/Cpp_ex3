#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Card.hpp"
#include <vector>

#include "Edge.hpp"
namespace ariel
{
    class Vertex;
    class Player
    {
    private:
        std::string name;
        std::string color;
        int totalPoints;
        int totalKnights;
        bool hisTurn;
        bool firstTurn;
        bool secondTurn;
        std::vector<Vertex> Settlements;
        std::vector<Vertex> Cities;
        std::vector<Edge> Roads;
        std::vector<ResourceCard> resourceCards;
        std::vector<DevelopmentCard> developmentCards;
    public:
        Player();
        Player(std::string,std::string);
        bool placeSettelemnt(Vertex&);
        bool placeRoad(Edge&);
        bool placeCity(Vertex&);
        void endTurn();
        void trade(Player*, std::vector<std::string>, std::vector<std::string>);
        void printPoints();
        bool contains(std::vector<ResourceCard>&,std::vector<ResourceCard>);
        bool getIfHisTurn();
        void ChangeToHisTurn(std::vector<Player*>);
        std::vector<Vertex>getSettlements();
        std::vector<Edge>getRoads();
        std::vector<Vertex>getCities();
        std::string getName();
        std::string getColor();
        int getTotalPoints();
        std::vector<ResourceCard>& getResourceCards();
        std::vector<DevelopmentCard>& getDevelopmentCards();
        void useDevelopmentCard(std::vector<Player*>);
        void AddResourceCard(std::string);
        void printResourcesCards();
        void placeCities();
        void placeSettelments();
        void placeRoads();
        void TradeWhatNeeded(std::vector<Player*>);
        void tradeDevelopmentCards(Player*,std::string,std::string);
        bool containsWithoutErase(std::vector<ResourceCard>&, std::vector<std::string>);
        void useMonopoly(ResourceCard, std::vector<Player*>);
        void useYearofPlenty(ResourceCard,ResourceCard);
        void RoadBuilding(Edge,Edge);
        void addTotalPoints();
        void addTotalKnights();
        int getTotalKnights();
    };
}

#endif //PLAYER_HPP
