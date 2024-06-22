#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "GlobalStructs.h"
#include "Shapes.h"
#include "BasicRayCasting.h"
#include "Renderer.h"

class Game {
public:
    Game(int winWidth, int winHeight, const std::string& config);
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow m_window;
    ShapesPos m_shapesPos;
    std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>> m_shapeEdges;
    std::vector<sf::Vector2f> m_rayIntersections;
    sf::Vector2f m_lastMousePosF;
    sf::FloatRect m_winBB;
    std::vector<sf::Vector2f> m_winEdges;
    Renderer m_renderer;
};

#endif // GAME_H