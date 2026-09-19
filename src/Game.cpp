#include "Game.h"
#include "AStar.h"

#include <fstream>
#include <iostream>
#include <sstream>

Game::Game()
    : window(
        sf::VideoMode({800u, 600u}),
        "A* Escape"
      ),
      grid(15, 20, 40)
{
    // =====================================
    // POSICIONES INICIALES
    // =====================================

    player = {1, 1};

    enemy1 = {18, 1};

    enemy2 = {1, 13};

    goal = {18, 13};

    // =====================================
    // CONFIGURACIÓN DE VENTANA
    // =====================================

    window.setFramerateLimit(60);

    // =====================================
    // CARGAR FUENTE
    // =====================================

    if (font.openFromFile("assets/consola.ttf"))
    {
        fontLoaded = true;

        std::cout
            << "Fuente cargada desde assets.\n";
    }
    else if (
        font.openFromFile(
            "C:/Windows/Fonts/consola.ttf"
        )
    )
    {
        fontLoaded = true;

        std::cout
            << "Fuente cargada desde Windows.\n";
    }
    else
    {
        fontLoaded = false;

        std::cout
            << "ERROR: No se pudo cargar consola.ttf\n";
    }

    // =====================================
    // CARGAR WIN.TXT
    // =====================================

    winAscii =
        loadTextFile(
            "assets/win.txt"
        );

    // =====================================
    // CARGAR GAMEOVER.TXT
    // =====================================

    gameOverAscii =
        loadTextFile(
            "assets/gameover.txt"
        );

    // =====================================
    // TEXTO DE RESPALDO
    // =====================================

    if (winAscii.empty())
    {
        winAscii =
            "============================\n"
            "          YOU WIN!\n"
            "============================";
    }

    if (gameOverAscii.empty())
    {
        gameOverAscii =
            "============================\n"
            "         GAME OVER\n"
            "============================";
    }

    // =====================================
    // CARGAR MÚSICA
    // =====================================

    if (!music.openFromFile(
            "assets/medieval.wav"))
    {
        std::cout
            << "ERROR: No se pudo cargar "
               "medieval.wav\n";
    }
    else
    {
        music.setLooping(true);

        music.setVolume(30.0f);

        music.play();

        std::cout
            << "Musica cargada correctamente.\n";
    }

    // =====================================
    // TÍTULO
    // =====================================

    updateWindowTitle();
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();

        update();

        render();
    }
}

void Game::processEvents()
{
    while (const auto event =
               window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void Game::movePlayer()
{
    // =====================================
    // No mover después del final
    // =====================================

    if (gameOver || won)
    {
        return;
    }

    // =====================================
    // Control de velocidad
    // =====================================

    if (
        playerClock.getElapsedTime()
        < playerMoveDelay)
    {
        return;
    }

    sf::Vector2i newPosition = player;

    // =====================================
    // W - ARRIBA
    // =====================================

    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::W))
    {
        newPosition.y--;
    }

    // =====================================
    // S - ABAJO
    // =====================================

    else if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::S))
    {
        newPosition.y++;
    }

    // =====================================
    // A - IZQUIERDA
    // =====================================

    else if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::A))
    {
        newPosition.x--;
    }

    // =====================================
    // D - DERECHA
    // =====================================

    else if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::D))
    {
        newPosition.x++;
    }

    else
    {
        return;
    }

    // =====================================
    // VERIFICAR MOVIMIENTO
    // =====================================

    if (
        grid.isWalkable(
            newPosition.x,
            newPosition.y))
    {
        player = newPosition;
    }

    playerClock.restart();
}

void Game::updateEnemies()
{
    if (gameOver || won)
    {
        return;
    }

    // =====================================
    // ENEMIGO 1
    // =====================================

    path1 =
        AStar::findPath(
            grid.getMap(),
            enemy1,
            player
        );

    if (
        enemy1Clock.getElapsedTime()
        >= enemy1MoveDelay)
    {
        if (path1.size() > 1)
        {
            enemy1 = path1[1];
        }

        enemy1Clock.restart();
    }

    // =====================================
    // ENEMIGO 2
    // =====================================

    path2 =
        AStar::findPath(
            grid.getMap(),
            enemy2,
            player
        );

    if (
        enemy2Clock.getElapsedTime()
        >= enemy2MoveDelay)
    {
        if (path2.size() > 1)
        {
            enemy2 = path2[1];
        }

        enemy2Clock.restart();
    }
}

void Game::checkGoal()
{
    if (gameOver || won)
    {
        return;
    }

    // =====================================
    // LLEGÓ A LA META
    // =====================================

    if (player == goal)
    {
        won = true;

        path1.clear();
        path2.clear();

        music.stop();

        updateWindowTitle();

        showWin();
    }
}

void Game::checkCollision()
{
    if (gameOver || won)
    {
        return;
    }

    // =====================================
    // PROTECCIÓN
    // =====================================

    if (
        collisionClock.getElapsedTime()
        < collisionProtectionTime)
    {
        return;
    }

    // =====================================
    // COLISIÓN ENEMIGO 1
    // =====================================

    bool hitEnemy1 =
        (player == enemy1);

    // =====================================
    // COLISIÓN ENEMIGO 2
    // =====================================

    bool hitEnemy2 =
        (player == enemy2);

    // =====================================
    // SI HUBO COLISIÓN
    // =====================================

    if (hitEnemy1 || hitEnemy2)
    {
        // Restar vida
        lives--;

        // Limpiar caminos
        path1.clear();
        path2.clear();

        // Reiniciar posiciones
        resetPositions();

        // Reiniciar protección
        collisionClock.restart();

        // Actualizar vidas
        updateWindowTitle();

        std::cout
            << "Has perdido una vida. "
            << "Vidas restantes: "
            << lives
            << "\n";

        // =================================
        // GAME OVER
        // =================================

        if (lives <= 0)
        {
            lives = 0;

            gameOver = true;

            music.stop();

            updateWindowTitle();

            showGameOver();
        }
    }
}

void Game::resetPositions()
{
    player = {1, 1};

    enemy1 = {18, 1};

    enemy2 = {1, 13};

    playerClock.restart();

    enemy1Clock.restart();

    enemy2Clock.restart();
}

void Game::updateWindowTitle()
{
    if (gameOver)
    {
        window.setTitle(
            "A* Escape - GAME OVER"
        );
    }
    else if (won)
    {
        window.setTitle(
            "A* Escape - YOU WIN"
        );
    }
    else
    {
        window.setTitle(
            "A* Escape - Vidas: "
            + std::to_string(lives)
        );
    }
}

std::string Game::loadTextFile(
    const std::string& filename)
{
    // =====================================
    // Abrir archivo
    // =====================================

    std::ifstream file(
        filename,
        std::ios::binary
    );

    if (!file.is_open())
    {
        std::cout
            << "No se pudo abrir: "
            << filename
            << "\n";

        return "";
    }

    // =====================================
    // Leer archivo completo
    // =====================================

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

void Game::showWin()
{
    std::cout
        << "\n"
        << "==============================\n"
        << "          YOU WIN!\n"
        << "==============================\n"
        << "\n";
}

void Game::showGameOver()
{
    std::cout
        << "\n"
        << "==============================\n"
        << "         GAME OVER\n"
        << "==============================\n"
        << "\n";
}

void Game::drawEndScreen(
    const std::string& message)
{
    // =====================================
    // Fondo oscuro
    // =====================================

    sf::RectangleShape overlay;

    overlay.setSize({
        800.0f,
        600.0f
    });

    overlay.setPosition({
        0.0f,
        0.0f
    });

    overlay.setFillColor(
        sf::Color(0, 0, 0, 235)
    );

    window.draw(overlay);

    // =====================================
    // Comprobar fuente
    // =====================================

    if (!fontLoaded)
    {
        return;
    }

    // =====================================
    // Crear texto
    // =====================================

    sf::Text endText(
        font,
        message,
        18
    );

    endText.setFillColor(
        sf::Color::White
    );

    // =====================================
    // Obtener tamaño del texto
    // =====================================

    sf::FloatRect bounds =
        endText.getLocalBounds();

    float textWidth =
        bounds.size.x;

    float textHeight =
        bounds.size.y;

    // =====================================
    // Centrar ASCII
    // =====================================

    endText.setPosition({
        (800.0f - textWidth) / 2.0f,
        (600.0f - textHeight) / 2.0f
    });

    // =====================================
    // Dibujar
    // =====================================

    window.draw(endText);
}

void Game::update()
{
    if (gameOver || won)
    {
        return;
    }

    // =====================================
    // JUGADOR
    // =====================================

    movePlayer();

    // =====================================
    // META
    // =====================================

    checkGoal();

    if (won)
    {
        return;
    }

    // =====================================
    // COLISIÓN
    // =====================================

    checkCollision();

    if (gameOver)
    {
        return;
    }

    // =====================================
    // ENEMIGOS
    // =====================================

    updateEnemies();

    // =====================================
    // COLISIÓN
    // =====================================

    checkCollision();

    if (gameOver)
    {
        return;
    }

    // =====================================
    // META
    // =====================================

    checkGoal();
}

void Game::drawEntity(
    sf::Vector2i position,
    sf::Color color)
{
    sf::RectangleShape entity;

    entity.setSize({
        38.0f,
        38.0f
    });

    entity.setPosition({
        static_cast<float>(
            position.x * 40 + 1
        ),

        static_cast<float>(
            position.y * 40 + 1
        )
    });

    entity.setFillColor(color);

    window.draw(entity);
}

void Game::render()
{
    // =====================================
    // FONDO
    // =====================================

    window.clear(
        sf::Color(30, 30, 30)
    );

    // =====================================
    // LABERINTO
    // =====================================

    grid.draw(window);

    // =====================================
    // CAMINO DEL ENEMIGO 1
    // =====================================

    for (const auto& position : path1)
    {
        sf::CircleShape point(5.0f);

        point.setPosition({
            static_cast<float>(
                position.x * 40 + 15
            ),

            static_cast<float>(
                position.y * 40 + 15
            )
        });

        point.setFillColor(
            sf::Color(100, 180, 255)
        );

        window.draw(point);
    }

    // =====================================
    // CAMINO DEL ENEMIGO 2
    // =====================================

    for (const auto& position : path2)
    {
        sf::CircleShape point(4.0f);

        point.setPosition({
            static_cast<float>(
                position.x * 40 + 16
            ),

            static_cast<float>(
                position.y * 40 + 16
            )
        });

        point.setFillColor(
            sf::Color(170, 120, 255)
        );

        window.draw(point);
    }

    // =====================================
    // META
    // =====================================

    drawEntity(
        goal,
        sf::Color(50, 200, 100)
    );

    // =====================================
    // JUGADOR
    // =====================================

    drawEntity(
        player,
        sf::Color(50, 100, 255)
    );

    // =====================================
    // ENEMIGO 1
    // =====================================

    drawEntity(
        enemy1,
        sf::Color(230, 40, 40)
    );

    // =====================================
    // ENEMIGO 2
    // =====================================

    drawEntity(
        enemy2,
        sf::Color(180, 30, 30)
    );

    // =====================================
    // PANTALLA WIN
    // =====================================

    if (won)
    {
        drawEndScreen(
            winAscii
        );
    }

    // =====================================
    // PANTALLA GAME OVER
    // =====================================

    if (gameOver)
    {
        drawEndScreen(
            gameOverAscii
        );
    }

    // =====================================
    // MOSTRAR
    // =====================================

    window.display();
}