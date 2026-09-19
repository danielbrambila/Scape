#include "AStar.h"

#include <algorithm>
#include <cmath>
#include <limits>

Node::Node(int x, int y)
{
    this->x = x;
    this->y = y;

    g = std::numeric_limits<float>::infinity();
    h = 0;
    f = 0;

    parent = nullptr;
}

float AStar::heuristic(
    sf::Vector2i a,
    sf::Vector2i b)
{
    return std::abs(a.x - b.x)
         + std::abs(a.y - b.y);
}

std::vector<sf::Vector2i> AStar::findPath(
    const std::vector<std::vector<int>>& grid,
    sf::Vector2i start,
    sf::Vector2i goal)
{
    int rows = static_cast<int>(grid.size());

    if (rows == 0)
        return {};

    int columns =
        static_cast<int>(grid[0].size());

    std::vector<std::vector<Node>> nodes;

    nodes.reserve(rows);

    for (int y = 0; y < rows; y++)
    {
        std::vector<Node> row;

        for (int x = 0; x < columns; x++)
        {
            row.emplace_back(x, y);
        }

        nodes.push_back(std::move(row));
    }

    std::vector<Node*> openList;

    std::vector<std::vector<bool>> closedList(
        rows,
        std::vector<bool>(columns, false)
    );

    Node* startNode =
        &nodes[start.y][start.x];

    Node* goalNode =
        &nodes[goal.y][goal.x];

    startNode->g = 0;

    startNode->h =
        heuristic(start, goal);

    startNode->f =
        startNode->g + startNode->h;

    openList.push_back(startNode);

    const int directions[4][2] =
    {
        { 1,  0 },
        {-1,  0 },
        { 0,  1 },
        { 0, -1 }
    };

    while (!openList.empty())
    {
        auto currentIterator =
            std::min_element(
                openList.begin(),
                openList.end(),
                [](Node* a, Node* b)
                {
                    return a->f < b->f;
                }
            );

        Node* current =
            *currentIterator;

        openList.erase(currentIterator);

        closedList[current->y][current->x] =
            true;

        if (current == goalNode)
        {
            std::vector<sf::Vector2i> path;

            Node* node = current;

            while (node != nullptr)
            {
                path.emplace_back(
                    node->x,
                    node->y
                );

                node = node->parent;
            }

            std::reverse(
                path.begin(),
                path.end()
            );

            return path;
        }

        for (const auto& direction : directions)
        {
            int nx =
                current->x + direction[0];

            int ny =
                current->y + direction[1];

            if (nx < 0 ||
                nx >= columns ||
                ny < 0 ||
                ny >= rows)
            {
                continue;
            }

            if (grid[ny][nx] == 1)
                continue;

            if (closedList[ny][nx])
                continue;

            Node* neighbor =
                &nodes[ny][nx];

            float newG =
                current->g + 1.0f;

            bool inOpenList =
                std::find(
                    openList.begin(),
                    openList.end(),
                    neighbor
                ) != openList.end();

            if (!inOpenList ||
                newG < neighbor->g)
            {
                neighbor->parent = current;

                neighbor->g = newG;

                neighbor->h =
                    heuristic(
                        { nx, ny },
                        goal
                    );

                neighbor->f =
                    neighbor->g +
                    neighbor->h;

                if (!inOpenList)
                    openList.push_back(neighbor);
            }
        }
    }

    return {};
}