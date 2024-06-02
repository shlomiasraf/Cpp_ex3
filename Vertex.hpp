#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <string>
#include <unordered_map>

namespace ariel
{
    class Vertex
    {
    private:
        int x;
        int y;
        std::string SettelemntOwner;
        std::string CityOwner;
        std::vector<Vertex> neighborsVertex;
        std::unordered_map<int,std::string> resourcesAndCoins;
        static std::unordered_map<std::string, Vertex> vertexMap;

    public:
        Vertex();
        Vertex(int x, int y);
        int getX();
        int getY();
        std::string GetSettelemntOwner();
        std::string GetCityOwner();
        void addCity(std::string& playerName);
        void addResourceAndCoin(std::string& resource, int coinNumber);
        void addSettelemnt(std::string& playerName);
        void addNeighborVertex(Vertex neighborVertex);
        bool VertexNearRoad();
        bool nearSettelemntOrCity();
        std::unordered_map<int,std::string> getResourcesAndCoins();
        static Vertex& getVertex(int x, int y);

        bool operator==(Vertex other);
    };
}

#endif // VERTEX_HPP
