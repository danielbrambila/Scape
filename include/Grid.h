#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
private:

    int rows;
    int columns;
    int cellSize;

    std::vector<std::vector<int>> map;

public:

    Grid(int rows, int columns, int cellSize);

    void createMap();

    void draw(sf::RenderWindow& window);

    bool isWalkable(int x, int y) const;

    const std::vector<std::vector<int>>& getMap() const;

    int getRows() const;
    int getColumns() const;
    int getCellSize() const;
};