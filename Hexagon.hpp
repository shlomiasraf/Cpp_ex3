/* ID: 207970252
    Mail: Shlomi55577@gmail.com */

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
            Hexagon(std::vector<Vertex>, std::vector<Edge*>, std::string, int);
            std::vector<Vertex> getVertexs();
            std::vector<Edge> getEdges();
    };
}
#endif //HEXAGON_HPP
