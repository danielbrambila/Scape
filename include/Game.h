#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "Grid.h"

class Game
{
private:

    // =====================================
    // Ventana
    // =====================================
    sf::RenderWindow window;

    // =====================================
    // Mapa
    // =====================================
    Grid grid;

    // =====================================
    // Jugador
    // =====================================
    sf::Vector2i player;

    // =====================================
    // Enemigos
    // =====================================
    sf::Vector2i enemy1;
    sf::Vector2i enemy2;

    // =====================================
    // Meta
    // =====================================
    sf::Vector2i goal;

    // =====================================
    // Caminos A*
    // =====================================
    std::vector<sf::Vector2i> path1;
    std::vector<sf::Vector2i> path2;

    // =====================================
    // Relojes
    // =====================================
    sf::Clock enemy1Clock;
    sf::Clock enemy2Clock;
    sf::Clock playerClock;
    sf::Clock collisionClock;

    // =====================================
    // Música
    // =====================================
    sf::Music music;

    // =====================================
    // Fuente
    // =====================================
    sf::Font font;
    bool fontLoaded = false;

    // =====================================
    // ASCII
    // =====================================
    std::string winAscii;
    std::string gameOverAscii;

    // =====================================
    // Velocidad jugador
    // =====================================
    sf::Time playerMoveDelay =
        sf::milliseconds(120);

    // =====================================
    // Velocidad enemigos
    // =====================================
    sf::Time enemy1MoveDelay =
        sf::milliseconds(250);

    sf::Time enemy2MoveDelay =
        sf::milliseconds(320);

    // =====================================
    // Protección después de una colisión
    // =====================================
    sf::Time collisionProtectionTime =
        sf::seconds(1.0f);

    // =====================================
    // Vidas
    // =====================================
    int lives = 3;

    // =====================================
    // Estados
    // =====================================
    bool gameOver = false;
    bool won = false;

    // =====================================
    // Funciones
    // =====================================
    void processEvents();
    void update();
    void render();

    void movePlayer();
    void updateEnemies();

    void checkCollision();
    void checkGoal();

    void resetPositions();

    void updateWindowTitle();

    void showGameOver();
    void showWin();

    void drawEndScreen(
        const std::string& message
    );

    std::string loadTextFile(
        const std::string& filename
    );

    void drawEntity(
        sf::Vector2i position,
        sf::Color color
    );

public:

    Game();

    void run();
};