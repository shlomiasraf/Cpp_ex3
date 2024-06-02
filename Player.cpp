//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Player.hpp"
#include <iostream>
#include <random>

#include "Catan.hpp"

using namespace ariel;

Player::Player() = default;

Player::Player(std::string name)
{
    this->name = name;
    this->firstTurn = true;
    this->secondTurn = false;
    this->totalPoints = 0;
}
std::string Player::PlayerGetName()
{
    return this->name;
}
void Player::placeSettelemnt(Vertex& Vertex)
{
    if(hisTurn && Vertex.GetSettelemntOwner() == "" && Vertex.GetCityOwner() == "" && !Vertex.nearSettelemntOrCity())
    {
        std::vector<ResourceCard> rescurcesForSettelemnt = {ResourceCard("Brick"),ResourceCard("Lumber"),ResourceCard("Wool"),ResourceCard("Grain")};
        if(this->firstTurn || this->secondTurn)
        {
            Vertex.addSettelemnt(this->name);
            this->totalPoints++;
            this->Settlements.push_back(Vertex);
            if(this->secondTurn)
            {
                for (const auto& pair : Vertex.getResourcesAndCoins())
                {
                    this->resourceCards.emplace_back(pair.second);
                }
            }
        }
        else if(contains(resourceCards,rescurcesForSettelemnt) && Vertex.VertexNearRoad())
        {
            Vertex.addSettelemnt(this->name);
            this->totalPoints++;
            this->Settlements.push_back(Vertex);
        }
    }
}
void Player::placeCity(Vertex& Vertex)
{
    if(hisTurn && Vertex.GetSettelemntOwner() == this->name && Vertex.GetCityOwner() == "")
    {
        std::vector<ResourceCard> rescurcesForCity = {ResourceCard("Ore"),ResourceCard("Ore"),ResourceCard("Ore"),ResourceCard("Grain"),ResourceCard("Grain")};
        if(contains(resourceCards,rescurcesForCity))
        {
            Vertex.addCity(this->name);
            this->totalPoints++;
            this->Settlements.erase(std::remove(this->Settlements.begin(), this->Settlements.end(), Vertex), this->Settlements.end());
            this->Cities.push_back(Vertex);
        }
    }
}
void Player::placeRoad(Edge& edge)
{
    if(hisTurn && edge.getRoadOwner() == "" && (edge.EdgeNearSettelemntOrCity() || edge.nearRoad()))
    {
        std::vector<ResourceCard> rescurcesForRoad = {ResourceCard("Brick"),ResourceCard("Lumber")};
        if(this->firstTurn || this->secondTurn)
        {
            edge.addRoad(this->name);
            if(this->firstTurn)
            {
                this->firstTurn = false;
                this->secondTurn = true;
            }
            else if(this->secondTurn)
            {
                this->secondTurn = false;
            }
        }
        else if(contains(resourceCards,rescurcesForRoad))
        {
            edge.addRoad(this->name);
        }
    }
}
bool Player::contains(std::vector<ResourceCard> resourceCards, std::vector<ResourceCard> resources)
{
    int indexs[resources.size()];
    bool HaveinCards[resources.size()];
    bool haveEverything = true;
    for(int i = 0; i < resourceCards.size(); i++)
    {
        for(int j = 0; j < resources.size(); j++)
        {
            if(resourceCards[i].name == resources[j].name)
            {
                indexs[j] = i;
                HaveinCards[j] = true;
            }
            if(!HaveinCards[j])
            {
                haveEverything = false;
            }
        }
        if(haveEverything)
        {
            for(int j = 0; j < resources.size(); j++)
            {
                resourceCards.erase(resourceCards.begin() + indexs[j]);
                return true;
            }
        }
        haveEverything = true;
    }
    return false;
}
void Player::endTurn()
{
    hisTurn = false;
}
void Player::trade(Player playerToTrade, std::vector<ResourceCard> resourcesPlayer1, std::vector<ResourceCard> resourcesPlayer2)
{
    if(hisTurn)
    {
        if(contains(resourceCards,resourcesPlayer1))
        {
            if(contains(playerToTrade.resourceCards,resourcesPlayer2))
            {
                for(int i = 0; i < resourcesPlayer1.size(); i++)
                {
                    playerToTrade.resourceCards.push_back(resourcesPlayer1[i]);
                }
                for(int i = 0; i < resourcesPlayer2.size(); i++)
                {
                   resourceCards.push_back(resourcesPlayer2[i]);
                }
            }
            else
            {
                for(int i = 0; i < resourcesPlayer1.size(); i++)
                {
                   resourceCards.push_back(resourcesPlayer1[i]);
                }
            }
        }
    }
}
void Player::buyDevelopmentCard()
{
    if(hisTurn)
    {
        std::vector<ResourceCard> rescurcesForDevelopment = {ResourceCard("Ore"),ResourceCard("Wool"),ResourceCard("Grain")};
        if(contains(resourceCards,rescurcesForDevelopment))
        {
            developmentCards.push_back(DevelopmentCard("development"));
        }
    }
}

void Player::printPoints()
{
    std::cout<< "the total points of " << this->name << " is: " << this->totalPoints << "\n";
}
void Player::ChangeToHisTurn()
{
    this->hisTurn = true;
}
std::vector<Vertex> Player::getSettlements()
{
    return this->Settlements;
}






