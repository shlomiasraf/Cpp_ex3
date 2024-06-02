//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Catan.hpp"
#include <iostream>
#include <random>

using namespace ariel;

Catan::Catan(Player& player1, Player& player2, Player& player3)
    : p1(player1), p2(player2), p3(player3)

{
}
void Catan::ChooseStartingPlayer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);
    int randomNumber = dis(gen);
    if(randomNumber == 1)
    {
        p1.ChangeToHisTurn();
        std::cout<< p1.PlayerGetName() << " you start the game." << "\n";
    }
    else if (randomNumber == 2)
    {
        p2.ChangeToHisTurn();
        std::cout<< p2.PlayerGetName() << " you start the game." << "\n";
    }
    else
    {
        p3.ChangeToHisTurn();
        std::cout<< p3.PlayerGetName() << " you start the game." << "\n";
    }
}
Board Catan::getBoard()
{
}
void Catan::printWinner()
{

}
std::vector<Player> Catan::getPlayers()
{
    this->allPlayers.push_back(p1);
    this->allPlayers.push_back(p2);
    this->allPlayers.push_back(p3);
    return this->allPlayers;
}
void Catan::rollDice()
{
    if(allPlayers.size() == 0)
    {
        allPlayers.push_back(p1);
        allPlayers.push_back(p2);
        allPlayers.push_back(p3);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 12);
    int randomNumber = dis(gen);
    for(int i = 0; i < this->allPlayers.size(); i++)
    {
        Player player = this->allPlayers[i];
        for(int j = 0; j < player.getSettlements().size(); i++)
        {
            std::unordered_map<int,std::string> HexagonOfPlayer = player.getSettlements()[i].getResourcesAndCoins();
            auto it = HexagonOfPlayer.find(randomNumber);
            if (it != HexagonOfPlayer.end())
            {
                player.resourceCards.emplace_back(it->second);
            }
        }
    }
    std::cout<< "the roll dice in " << this->name << "'s turn is: " << randomNumber << "\n";
}
