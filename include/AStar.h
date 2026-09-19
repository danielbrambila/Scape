#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Node
{
    int x;
    int y;

    float g;
    float h;
    float f;

    Node* parent;

    Node(int x, int y);
};

class AStar
{
public:

    static std::vector<sf::Vector2i> findPath(
        const std::vector<std::vector<int>>& grid,
        sf::Vector2i start,
        sf::Vector2i goal
    );

private:

    static float heuristic(
        sf::Vector2i a,
        sf::Vector2i b
    );
};