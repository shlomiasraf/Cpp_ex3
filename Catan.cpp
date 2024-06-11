/* ID: 207970252
    Mail: Shlomi55577@gmail.com */

#include "Catan.hpp"
#include <iostream>
#include <random>
#include <string>
#include <sstream>

using namespace ariel;

Catan::Catan(Player& player1, Player& player2, Player& player3)
    : p1(player1), p2(player2), p3(player3)
{
    for(int i = 0; i < 4; i++)
    {
        this->allDevelopmentCards.emplace_back("Victory Point");
        if(i < 3)
        {
            this->allDevelopmentCards.emplace_back("Knight");
        }
        if(i < 2)
        {
            this->allDevelopmentCards.emplace_back("Monopoly");
            this->allDevelopmentCards.emplace_back("Road Building");
            this->allDevelopmentCards.emplace_back("Year of Plenty");
        }
    }
}
void Catan::ChooseStartingPlayer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);
    int randomNumber = dis(gen);
    if(randomNumber == 1)
    {
        this->allPlayers.push_back(&p1);
        this->allPlayers.push_back(&p2);
        this->allPlayers.push_back(&p3);
        p1.ChangeToHisTurn(allPlayers);
        std::cout<< p1.getName() << " you start the game." << "\n";
    }
    else if (randomNumber == 2)
    {
        this->allPlayers.push_back(&p2);
        this->allPlayers.push_back(&p3);
        this->allPlayers.push_back(&p1);
        p2.ChangeToHisTurn(allPlayers);
        std::cout<< p2.getName() << " you start the game." << "\n";
    }
    else
    {
        allPlayers.push_back(&p3);
        allPlayers.push_back(&p1);
        allPlayers.push_back(&p2);
        p3.ChangeToHisTurn(allPlayers);
        std::cout<< p3.getName() << " you start the game." << "\n";
    }
}
std::vector<Player*>& Catan::getPlayers()
{
    return this->allPlayers;
}
void Catan::rollDice(Player* player1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    int cube1 = dis(gen);
    std::uniform_int_distribution<> dis2(1, 6);
    int cube2 = dis2(gen);
    int randomNumber = cube1 + cube2;
    player1->ChangeToHisTurn(allPlayers);
    for(Player* player : this->allPlayers)
    {
        if(randomNumber == 7)
        {
            if(player->getResourceCards().size() > 7)
            {
                std::string resources;
                std::vector<ResourceCard> ResourceCards;
                std::cout<< "the roll dice in " << player1->getName() << "'s turn " << "with color " << player1->getColor() <<  " is: " << randomNumber << "\n";
                std::cout<< player->getName() << " you have more than 7 resources cards what the " << player->getResourceCards().size()/2 << " cards you want to give up" << "\n";
                player->printResourcesCards();
                std::getline(std::cin, resources);
                std::istringstream iss(resources);
                std::string word;
                while (iss >> word)
                {
                    ResourceCards.emplace_back(word);
                }
                if(ResourceCards.size() != player->getResourceCards().size()/2 || !player->contains(player->getResourceCards(),ResourceCards))
                {
                    throw std::out_of_range("You didn't give what you need");
                }
            }
        }
        else
        {
            for(int j = 0; j < player->getSettlements().size(); j++)
            {
                std::unordered_map<int,std::string> HexagonOfPlayer = player->getSettlements()[j].getResourcesAndCoins();
                auto it = HexagonOfPlayer.find(randomNumber);
                if (it != HexagonOfPlayer.end())
                {
                    player->AddResourceCard(it->second);
                }
            }
            for(int j = 0; j < player->getCities().size(); j++)
            {
                std::unordered_map<int,std::string> HexagonOfPlayer = player->getCities()[j].getResourcesAndCoins();
                auto it = HexagonOfPlayer.find(randomNumber);
                if (it != HexagonOfPlayer.end())
                {
                    player->AddResourceCard(it->second);
                    player->AddResourceCard(it->second);
                }
            }
        }
    }
    std::cout<< "the roll dice in " << player1->getName() << "'s turn " << "with color " << player1->getColor() <<  " is: " << randomNumber << "\n";
}
bool Catan::gameIsEnding(Player* player)
{
    if(player->getTotalPoints() >= 10)
    {
        std::cout<< player->getName() << " with color " << player->getColor() <<  " you win the game! congratulations" <<  "\n";
        return true;
    }
    return false;
}
bool Catan::buyDevelopmentCard(Player* player)
{
    if(player->getIfHisTurn() && this->allDevelopmentCards.size() > 0)
    {
        std::vector<ResourceCard> rescurcesForDevelopment = {ResourceCard("Ore"),ResourceCard("Wool"),ResourceCard("Grain")};
        if(player->contains(player->getResourceCards(),rescurcesForDevelopment))
        {
            DevelopmentCard development_card = GetDevelopmentCard();
            player->getDevelopmentCards().push_back(development_card);
            if(development_card.name == "Victory Point")
            {
                player->addTotalPoints();
            }
            if(development_card.name == "Knight")
            {
                player->addTotalKnights();
                if(player->getTotalKnights() == 3)
                {
                    player->addTotalPoints();
                    player->addTotalPoints();
                }
            }
            return true;
        }
    }
    return false;
}
DevelopmentCard Catan::GetDevelopmentCard()
{
    if (this->allDevelopmentCards.empty())
    {
        throw std::out_of_range("No development cards available.");
    }
    DevelopmentCard card = allDevelopmentCards.back();
    allDevelopmentCards.pop_back();
    return card;
}
