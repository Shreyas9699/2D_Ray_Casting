#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "GlobalStructs.h"

class Renderer {
public:
    Renderer(sf::RenderWindow& window);
    void drawShapes(const std::vector<sf::ConvexShape>& shapes);
    void drawPolygons(const sf::Vector2f& mousePos, const std::vector<sf::Vector2f>& intersections);
    void drawRays(const sf::Vector2f& mousePos, const std::vector<sf::Vector2f>& intersections);
    void drawMouseInfo(const sf::Vector2f& mousePos);
    void clear();
    void display();

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_mouseText;
    sf::CircleShape m_mouseCircle;
};

#endif // RENDERER_H