/* ID: 207970252
    Mail: Shlomi55577@gmail.com */

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
        std::vector<Player*>& getPlayers();
        void rollDice(Player*);
        bool buyDevelopmentCard(Player*);
        bool gameIsEnding(Player*);
        DevelopmentCard GetDevelopmentCard();
    };
}

#endif //CATAN_HPP
