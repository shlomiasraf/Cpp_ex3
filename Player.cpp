//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Player.hpp"
#include <iostream>
#include <random>
#include <algorithm> 
#include "Catan.hpp"

using namespace ariel;

Player::Player() = default;

Player::Player(std::string name,std::string color)
{
    this->name = name;
    this->color = color;
    this->firstTurn = true;
    this->secondTurn = false;
    this->totalPoints = 0;
    this->totalKnights = 0;
}
std::string Player::getColor()
{
    return this->color;
}
bool Player::placeSettelemnt(Vertex& Vertex)
{
    if(this->hisTurn && Vertex.GetSettelemntOwner() == "" && Vertex.GetCityOwner() == "" && !Vertex.nearSettelemntOrCity())
    {
        std::vector<ResourceCard> resourcesForSettelemnt = {ResourceCard("Brick"),ResourceCard("Lumber"),ResourceCard("Wool"),ResourceCard("Grain")};
        if(this->firstTurn || this->secondTurn)
        {
            Vertex.addSettelemnt(this->color);
            this->totalPoints++;
            this->Settlements.push_back(Vertex);
            if(this->secondTurn)
            {
                for (const auto& pair : Vertex.getResourcesAndCoins())
                {
                    this->resourceCards.emplace_back(pair.second);
                }
            }
            return true;
        }
        if(contains(this->resourceCards,resourcesForSettelemnt) && Vertex.VertexNearRoad())
        {
            Vertex.addSettelemnt(this->color);
            this->totalPoints++;
            this->Settlements.push_back(Vertex);
            return true;
        }
    }
    return false;
}
bool Player::placeCity(Vertex& Vertex)
{
    if(this->hisTurn && Vertex.GetSettelemntOwner() == this->color && Vertex.GetCityOwner() == "")
    {
        std::vector<ResourceCard> resourcesForCity = {ResourceCard("Ore"),ResourceCard("Ore"),ResourceCard("Ore"),ResourceCard("Grain"),ResourceCard("Grain")};
        if(contains(this->resourceCards,resourcesForCity))
        {
            Vertex.addCity(this->color);
            this->totalPoints++;
            Vertex.addSettelemnt("");
            this->Cities.push_back(Vertex);
            for (int i = 0; i < this->Settlements.size(); i++)
            {
                if (this->Settlements[i] == Vertex)
                {
                    this->Settlements.erase(this->Settlements.begin() + i);
                    break;
                }
            }
            return true;
        }
    }
    return false;
}
bool Player::placeRoad(Edge& edge)
{
    if(this->hisTurn && edge.getRoadOwner() == "" && (edge.EdgeNearSettelemntOrCity() || edge.nearRoad()))
    {
        std::vector<ResourceCard> resourceForRoad = {ResourceCard("Brick"),ResourceCard("Lumber")};
        if(this->firstTurn || this->secondTurn)
        {
            edge.addRoad(this->color);
            this->Roads.push_back(edge);
            if(this->firstTurn)
            {
                this->firstTurn = false;
                this->secondTurn = true;
            }
            else if(this->secondTurn)
            {
                this->secondTurn = false;
            }
            return true;
        }
        if(contains(this->resourceCards,resourceForRoad))
        {
            edge.addRoad(this->color);
            this->Roads.push_back(edge);
            return true;
        }
    }
    return false;
}
bool Player::contains(std::vector<ResourceCard>& resourceCards, std::vector<ResourceCard> resources)
{
    std::vector<int> indexes;
    bool haveEverything = true;
    if(resourceCards.size() < resources.size())
    {
        return false;
    }
    for (int j = 0; j < resources.size(); j++)
    {
        bool found = false;
        bool haveIndexI = false;
        for (int i = 0; i < resourceCards.size(); i++)
        {
            if (resourceCards[i].name == resources[j].name)
            {
                for(int index : indexes)
                {
                    if(index == i)
                    {
                        haveIndexI = true;
                        break;
                    }
                }
                if(!haveIndexI)
                {
                    indexes.push_back(i);
                    found = true;
                    break;
                }
            }
            haveIndexI = false;
        }
        if (!found)
        {
            haveEverything = false;
            break;
        }
    }
    if (haveEverything)
    {
        std::sort(indexes.begin(), indexes.end(), std::greater<int>());
        for (int index : indexes)
        {
            resourceCards.erase(resourceCards.begin() + index);
        }
        return true;
    }
    return false;
}
bool Player::containsWithoutErase(std::vector<ResourceCard>& resourceCards, std::vector<std::string> resources)
{
    std::vector<int> indexes;
    bool haveEverything = true;
    if(resourceCards.size() < resources.size())
    {
        return false;
    }
    for (int j = 0; j < resources.size(); j++)
    {
        bool found = false;
        bool haveIndexI = false;
        for (int i = 0; i < resourceCards.size(); i++)
        {
            if (resourceCards[i].name == resources[j])
            {
                for(int index : indexes)
                {
                    if(index == i)
                    {
                        haveIndexI = true;
                        break;
                    }
                }
                if(!haveIndexI)
                {
                    indexes.push_back(i);
                    found = true;
                    break;
                }
            }
            haveIndexI = false;
        }
        if (!found)
        {
            haveEverything = false;
            break;
        }
    }
    if (haveEverything)
    {
        return true;
    }
    return false;
}
void Player::endTurn()
{
    hisTurn = false;
}
void Player::trade(Player* playerToTrade, std::vector<std::string> resourcesPlayer1, std::vector<std::string> resourcesPlayer2)
{
    if(this->hisTurn)
    {
        if(containsWithoutErase(this->resourceCards,resourcesPlayer1))
        {
            if(containsWithoutErase(playerToTrade->resourceCards,resourcesPlayer2))
            {
                std::vector<ResourceCard> resourcesPlayer1ToRemove;
                std::vector<ResourceCard> resourcesPlayer2ToRemove;
                for(int i = 0; i < resourcesPlayer1.size(); i++)
                {
                    resourcesPlayer1ToRemove.emplace_back(resourcesPlayer1[i]);
                }
                for(int i = 0; i < resourcesPlayer2.size(); i++)
                {
                    resourcesPlayer2ToRemove.emplace_back(resourcesPlayer2[i]);
                }
                contains(this->resourceCards,resourcesPlayer1ToRemove);
                contains(playerToTrade->resourceCards,resourcesPlayer2ToRemove);
                for(int i = 0; i < resourcesPlayer1ToRemove.size(); i++)
                {
                    playerToTrade->resourceCards.push_back(resourcesPlayer1ToRemove[i]);
                }
                for(int i = 0; i < resourcesPlayer2ToRemove.size(); i++)
                {
                   this->resourceCards.emplace_back(resourcesPlayer2ToRemove[i]);
                }
            }
        }
    }
}
void Player::tradeDevelopmentCards(Player* playerToTrade, std::string developmentPlayer1, std::string developmentPlayer2)
{
    int indexDevelopmentPlayer1 = -1;
    int indexDevelopmentPlayer2 = -1;
    if(this->hisTurn)
    {
        for (int i = 0; i < this->developmentCards.size(); i++)
        {
            if(developmentPlayer1 == this->developmentCards[i].name)
            {
                indexDevelopmentPlayer1 = i;
                break;
            }
        }
        for (int i = 0; i < playerToTrade->developmentCards.size(); i++)
        {
            if(developmentPlayer2 == playerToTrade->developmentCards[i].name)
            {
                indexDevelopmentPlayer2 = i;
                break;
            }
        }
        if(indexDevelopmentPlayer1 != -1 && indexDevelopmentPlayer2 != -1)
        {
            this->developmentCards.erase(this->developmentCards.begin() + indexDevelopmentPlayer1);
            playerToTrade->developmentCards.erase(playerToTrade->developmentCards.begin() + indexDevelopmentPlayer2);
            this->developmentCards.emplace_back(developmentPlayer2);
            playerToTrade->developmentCards.emplace_back(developmentPlayer1);
            if(developmentPlayer1 == "Knight" && developmentPlayer2 != "Knight")
            {
                if(developmentPlayer2 == "Victory Point")
                {
                    this->totalPoints++;
                    playerToTrade->totalPoints--;
                }
                this->totalKnights--;
                if(this->totalKnights == 2)
                {
                    this->totalPoints -= 2;
                }
                playerToTrade->totalKnights++;
                if(playerToTrade->totalKnights == 3)
                {
                    playerToTrade->totalPoints += 2;
                }
            }
            if(developmentPlayer2 == "Knight" && developmentPlayer1 != "Knight")
            {
                if(developmentPlayer1 == "Victory Point")
                {
                    this->totalPoints--;
                    playerToTrade->totalPoints++;
                }
                playerToTrade->totalKnights--;
                if(playerToTrade->totalKnights == 2)
                {
                    playerToTrade->totalPoints -= 2;
                }
                this->totalKnights++;
                if(this->totalKnights == 3)
                {
                    this->totalPoints += 2;
                }
            }
        }
    }

}
void Player::printPoints()
{
    std::cout<< "the total points of " << this->name << " with color " << this->color << " is: " << this->totalPoints << "\n";
}
void Player::ChangeToHisTurn(std::vector<Player*> allPlayers)
{
    for(int i = 0; i < allPlayers.size(); i++)
    {
        if(allPlayers[i]->color != this->color)
        {
            allPlayers[i]->endTurn();
        }
    }
    this->hisTurn = true;

}
std::vector<Vertex> Player::getSettlements()
{
    return this->Settlements;
}
std::vector<Vertex> Player::getCities()
{
    return this->Cities;
}
std::string Player::getName()
{
    return this->name;
}
std::vector<ResourceCard>& Player::getResourceCards()
{
    return this->resourceCards;
}
void Player::AddResourceCard(std::string resource)
{
    this->resourceCards.emplace_back(resource);
}
int Player::getTotalPoints()
{
    return this->totalPoints;
}
std::vector<Edge> Player::getRoads()
{
    return this->Roads;
}
void Player::printResourcesCards()
{
    for(int i = 0; i < this->resourceCards.size(); i++)
    {
        std::cout<<resourceCards[i].name<<" ";
    }
    std::cout<<"\n";
}
void Player::placeCities()
{
    std::vector<std::string> resourcesForCity = {("Ore"),("Ore"),("Ore"),("Grain"),("Grain")};
    bool canBuild = true;
    while(containsWithoutErase(this->resourceCards,resourcesForCity) && canBuild && this->Settlements.size() > 0)
    {
        for(int i = 0; i < this->Settlements.size(); i++)
        {
            if(this->placeCity(this->Settlements[i]))
            {
                break;
            }
            if(i == this->Settlements.size()-1)
            {
                canBuild = false;
            }
        }
    }
}
void Player::placeSettelments()
{
    std::vector<std::string> resourcesForSettelment = {("Brick"),("Lumber"),("Wool"),("Grain")};
    bool canBuild = true;
    while(containsWithoutErase(this->resourceCards,resourcesForSettelment) && canBuild)
    {
        for(int i = 0; i < this->Roads.size(); i++)
        {
            if(this->placeSettelemnt(this->Roads[i].getVertex1()) || this->placeSettelemnt(this->Roads[i].getVertex2()))
            {
                break;
            }
            if(i == this->Roads.size()-1)
            {
                canBuild = false;
            }
        }
    }
}
void Player::placeRoads()
{
    std::vector<std::string> resourcesForRoad = {("Brick"),("Lumber")};
    bool canBuild = true;
    while(containsWithoutErase(this->resourceCards,resourcesForRoad) && canBuild)
    {
        bool buildAlready = false;
        for(int i = 0; i < this->Roads.size(); i++)
        {
            for(int j = 0; j < this->Roads[i].getNeighborsEdge().size(); j++)
            {
                if(this->placeRoad(*this->Roads[i].getNeighborsEdge()[j]))
                {
                    buildAlready = true;
                    break;
                }
            }
            if (buildAlready)
            {
                break;
            }
            if(i == this->Roads.size()-1)
            {
                canBuild = false;
            }
        }
    }
}
void Player::useMonopoly(ResourceCard resource, std::vector<Player*> allPlayers)
{
    bool haveMonopoly = false;
    for(int i = 0; i < this->developmentCards.size(); i++)
    {
        if(this->developmentCards[i].name == "Monopoly")
        {
            haveMonopoly = true;
            this->developmentCards.erase(this->developmentCards.begin() + i);
            break;
        }
    }
    if(haveMonopoly)
    {
        for(int i = 0; i < allPlayers.size(); i++)
        {
            if (allPlayers[i]->color != this->color)
            {
                for(int j = 0; j < allPlayers[i]->resourceCards.size(); j++)
                {
                    if(allPlayers[i]->resourceCards[j].name == resource.name)
                    {
                        this->resourceCards.push_back(resource);
                        allPlayers[i]->resourceCards.erase(allPlayers[i]->resourceCards.begin() + j);
                    }
                }
            }
        }
        this->hisTurn = false;
    }
}
void Player::RoadBuilding(Edge Road1, Edge Road2)
{
    bool haveRoadBuilding = false;
    for(int i = 0; i < this->developmentCards.size(); i++)
    {
        if(this->developmentCards[i].name == "Road Building")
        {
            haveRoadBuilding = true;
            this->developmentCards.erase(this->developmentCards.begin() + i);
            break;
        }
    }
    if(haveRoadBuilding)
    {
        for(int i = 0; i < 2; i++)
        {
            this->resourceCards.emplace_back("Brick");
            this->resourceCards.emplace_back("Lumber");
        }
        placeRoad(Road1);
        placeRoad(Road2);
        this->hisTurn = false;

    }
}
void Player::useYearofPlenty(ResourceCard ResourceCard1, ResourceCard ResourceCard2)
{
    bool haveYearofPlenty = false;
    for(int i = 0; i < this->developmentCards.size(); i++)
    {
        if(this->developmentCards[i].name == "Year of Plenty")
        {
            haveYearofPlenty = true;
            this->developmentCards.erase(this->developmentCards.begin() + i);
            break;
        }
    }
    if(haveYearofPlenty)
    {
        this->resourceCards.push_back(ResourceCard1);
        this->resourceCards.push_back(ResourceCard2);
        this->hisTurn = false;
    }
}
void Player::useDevelopmentCard(std::vector<Player*> allPlayers)
{
    if(this->developmentCards.size() > 0)
    {
        DevelopmentCard card = this->developmentCards.back();
        if(card.name == "Road Building")
        {
            this->developmentCards.pop_back();
            for(int i = 0; i < 2; i++)
            {
                this->resourceCards.emplace_back("Brick");
                this->resourceCards.emplace_back("Lumber");
            }
            placeRoads();
        }
        if(card.name == "Year of Plenty")
        {
            this->developmentCards.pop_back();
            int resourcesToTake = 0;
            std::vector<std::string> resources = {("Brick"),("Lumber"),("Wool"),("Grain"),("Ore")};
            for(int j = 0; j < resources.size(); j++)
            {
                std::vector<std::string> resource = {resources[j]};
                if(!containsWithoutErase(this->resourceCards, resource))
                {
                    resourcesToTake++;
                    this->resourceCards.emplace_back(resources[j]);
                }
                if(resourcesToTake == 2)
                {
                    break;
                }
            }
            while(resourcesToTake < 2)
            {
                resourcesToTake++;
                this->resourceCards.emplace_back(resources[resourcesToTake]);
            }
        }
        if(card.name == "Monopoly")
        {
            std::vector<std::string> resources = {("Brick"),("Lumber"),("Wool"),("Grain"),("Ore")};
            bool useInMonopoly = false;
            for(int j = 0; j < resources.size(); j++)
            {
                std::vector<std::string> resource = {resources[j]};
                if(!containsWithoutErase(this->resourceCards, resource))
                {
                    useMonopoly(resources[j],allPlayers);
                    useInMonopoly = true;
                    break;
                }
            }
            if(!useInMonopoly)
            {
                useMonopoly(resources[0],allPlayers);
            }
        }
        this->hisTurn = false;
    }
}
void Player::TradeWhatNeeded(std::vector<Player*> all_players)
{
    if(this->developmentCards.size() > 2 && this->totalKnights == 2)
    {
        bool tradeKnight = false;
        for(int i = 0; i < all_players.size(); i++)
        {
            if(all_players[i]->color != this->color && all_players[i]->totalKnights > 0)
            {
                for(int j = 0; j < this->developmentCards.size(); j++)
                {
                    if(this->developmentCards[j].name != "Knight")
                    {
                        tradeDevelopmentCards(all_players[i],this->developmentCards[j].name,"Knight");
                        tradeKnight = true;
                        break;
                    }
                }
                if(tradeKnight)
                {
                    break;
                }
            }
        }
    }
    std::vector<std::string> resources = {("Brick"),("Lumber"),("Wool"),("Grain"),("Ore")};
    for(int j = 0; j < resources.size(); j++)
    {
        std::vector<std::string> resource = {resources[j]};
        if(this->resourceCards.size() > 7 && !containsWithoutErase(this->resourceCards, resource))
        {
            for(int i = 0; i < all_players.size(); i++)
            {
                if(all_players[i]->color != this->color)
                {
                    if(all_players[i]->containsWithoutErase(all_players[i]->resourceCards, resource))
                    {
                        std::vector<std::string> resourcesPlayer1 = {this->resourceCards[0].name, this->resourceCards[1].name};
                        this->trade(all_players[i], resourcesPlayer1,resource);
                        break;
                    }
                }
            }
        }
    }
}
bool Player::getIfHisTurn()
{
    return this->hisTurn;
}
std::vector<DevelopmentCard>& Player::getDevelopmentCards()
{
    return this->developmentCards;
}
void Player::addTotalPoints()
{
    this->totalPoints++;
}
void Player::addTotalKnights()
{
    this->totalKnights++;
}
int Player::getTotalKnights()
{
    return this->totalKnights;
}









