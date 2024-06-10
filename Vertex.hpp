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
        std::vector<Vertex*> neighborsVertex;
        std::unordered_map<int,std::string> resourcesAndCoins;
        static std::unordered_map<std::string, Vertex> vertexMap;

    public:
        Vertex();
        Vertex(int,int);
        int getX();
        int getY();
        std::string GetSettelemntOwner();
        std::string GetCityOwner();
        void addCity(std::string);
        void addResourceAndCoin(std::string,int);
        void addSettelemnt(std::string);
        void addNeighborVertex(Vertex&);
        bool VertexNearRoad();
        bool nearSettelemntOrCity();
        std::unordered_map<int,std::string> getResourcesAndCoins();
        static Vertex& createVertex(int,int);
        static Vertex& getVertex(int,int);
        std::vector<Vertex*> getNeighborsVertex();
        bool operator==(Vertex);
    };
}

#endif // VERTEX_HPP
