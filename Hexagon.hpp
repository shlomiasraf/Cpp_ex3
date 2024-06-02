//
// Created by Shlomi Asraf on 28/05/2024.
//

#ifndef HEXAGON_HPP
#define HEXAGON_HPP
#include "Vertex.hpp"
#include "Edge.hpp"
#include <string>
#include <vector>

namespace ariel
{
    class Board;
    class Hexagon
    {
        private:
            std::vector<Vertex> Vertexs;
            std::vector<Edge> edges;
            std::string resource;
            int coinNumber;
        public:
            Hexagon();
            Hexagon(std::vector<Vertex>, std::vector<Edge>, std::string, int);
    };
}
#endif //HEXAGON_HPP
