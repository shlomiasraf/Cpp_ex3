//
// Created by Shlomi Asraf on 28/05/2024.
//

#ifndef CATAN_HPP
#define CATAN_HPP
#include "Player.hpp"
#include "Board.hpp"

namespace ariel
{
    class Catan
    {
    private:
        Player& p1;
        Player& p2;
        Player& p3;
        std::vector<Player*> allPlayers;
        std::vector<DevelopmentCard> allDevelopmentCards;
    public:
        Catan(Player&, Player&, Player&);
        void ChooseStartingPlayer();
        Board getBoard();
        std::vector<Player*>& getPlayers();
        void rollDice(Player*);
        bool buyDevelopmentCard(Player*);
        bool gameIsEnding();
        DevelopmentCard GetDevelopmentCard();
    };
}

#endif //CATAN_HPP
