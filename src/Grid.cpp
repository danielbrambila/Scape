#include "Grid.h"

Grid::Grid(
    int rows,
    int columns,
    int cellSize)
{
    this->rows = rows;
    this->columns = columns;
    this->cellSize = cellSize;

    createMap();
}

void Grid::createMap()
{
    map =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1},

        {1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1},

        {1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,1},

        {1,0,1,1,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1,1},

        {1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1},

        {1,0,1,0,1,1,0,0,1,0,1,0,0,1,1,0,1,0,1,1},

        {1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1},

        {1,0,1,0,1,0,1,1,1,0,0,1,1,0,1,0,1,0,1,1},

        {1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,1},

        {1,0,0,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1},

        {1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,1},

        {1,0,0,1,1,0,0,1,1,1,1,1,1,0,1,0,0,0,1,1},

        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1},

        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
}

bool Grid::isWalkable(
    int x,
    int y) const
{
    if (
        x < 0 ||
        x >= columns ||
        y < 0 ||
        y >= rows)
    {
        return false;
    }

    return map[y][x] == 0;
}

const std::vector<std::vector<int>>&
Grid::getMap() const
{
    return map;
}

int Grid::getRows() const
{
    return rows;
}

int Grid::getColumns() const
{
    return columns;
}

int Grid::getCellSize() const
{
    return cellSize;
}

void Grid::draw(
    sf::RenderWindow& window)
{
    sf::RectangleShape cell;

    cell.setSize(
        sf::Vector2f(
            static_cast<float>(
                cellSize - 1
            ),

            static_cast<float>(
                cellSize - 1
            )
        )
    );

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            cell.setPosition({
                static_cast<float>(
                    x * cellSize
                ),

                static_cast<float>(
                    y * cellSize
                )
            });

            if (map[y][x] == 1)
            {
                cell.setFillColor(
                    sf::Color(50, 50, 50)
                );
            }
            else
            {
                cell.setFillColor(
                    sf::Color(220, 220, 220)
                );
            }

            window.draw(cell);
        }
    }
}