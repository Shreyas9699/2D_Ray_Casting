#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& window) : m_window(window)
{
    if (!m_font.loadFromFile("res/font.ttf"))
    {
        std::cerr << "Error loading font\n";
        exit(-1);
    }
    m_mouseText.setFont(m_font);
    m_mouseText.setCharacterSize(15);
    m_mouseText.setFillColor(sf::Color::Green);

    m_mouseCircle.setRadius(10);
    m_mouseCircle.setFillColor(sf::Color::Red);
    m_mouseCircle.setOrigin(m_mouseCircle.getRadius(), m_mouseCircle.getRadius());
}

void Renderer::drawShapes(const std::vector<sf::ConvexShape>& shapes)
{
    for (const auto& shape : shapes)
    {
        m_window.draw(shape);
    }
}

void Renderer::drawPolygons(const sf::Vector2f& mousePos, const std::vector<sf::Vector2f>& intersections)
{
    if (intersections.size() >= 2) {
        for (size_t i = 0; i < intersections.size(); i++)
        {
            sf::ConvexShape polygon(3);
            polygon.setPoint(0, mousePos);
            polygon.setPoint(1, intersections[i]);
            polygon.setPoint(2, intersections[(i + 1) % intersections.size()]);
            polygon.setFillColor(sf::Color(255, 0, 0, 128));
            m_window.draw(polygon);
        }
    }
}

void Renderer::drawRays(const sf::Vector2f& mousePos, const std::vector<sf::Vector2f>& intersections)
{
    for (const auto& intersection : intersections)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(mousePos, sf::Color(0, 255, 255, 128)),
            sf::Vertex(intersection, sf::Color(0, 255, 255, 128))
        };
        m_window.draw(line, 2, sf::Lines);
    }
}

void Renderer::drawMouseInfo(const sf::Vector2f& mousePos)
{
    m_mouseText.setString("Mouse Position: " + std::to_string(static_cast<int>(mousePos.x)) + ", " + std::to_string(static_cast<int>(mousePos.y)));
    m_mouseText.setPosition(10, 10);
    m_mouseCircle.setPosition(mousePos);

    m_window.draw(m_mouseText);
    m_window.draw(m_mouseCircle);
}

void Renderer::clear()
{
    m_window.clear();
}

void Renderer::display()
{
    m_window.display();
}