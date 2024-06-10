//
// Created by Shlomi Asraf on 28/05/2024.
//

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
