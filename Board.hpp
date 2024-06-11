/* ID: 207970252
    Mail: Shlomi55577@gmail.com */

#ifndef BOARD_HPP
#define BOARD_HPP
#include "Hexagon.hpp"

namespace ariel
{
    class Board
    {
        private:
            std::vector<Hexagon> Hexagons;
        public:
            Board();
            void createBoard();
            void createHexagon(Vertex, std::string, int);
            std::vector<Hexagon> getHexagons();
    };
}



#endif //BOARD_HPP
