#include "Game.h"
#include <algorithm>

Game::Game(int winWidth, int winHeight, const std::string& config)
    : m_window(sf::VideoMode(winWidth, winHeight), "Ray Casting", sf::Style::Default, sf::ContextSettings(8)),
    m_shapesPos(createShapes(config)),
    m_shapeEdges(computeShapeEdges(m_shapesPos)),
    m_lastMousePosF(winWidth / 2.0f, winHeight / 2.0f),
    m_winBB(0, 0, winWidth, winHeight),
    m_winEdges({ sf::Vector2f(0, 0), sf::Vector2f(0, winHeight), sf::Vector2f(winWidth, 0), sf::Vector2f(winWidth, winHeight) }),
    m_renderer(m_window)
{
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::update()
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(m_window));
    m_lastMousePosF.x = std::max(0.0f, std::min(mousePos.x, static_cast<float>(m_window.getSize().x)));
    m_lastMousePosF.y = std::max(0.0f, std::min(mousePos.y, static_cast<float>(m_window.getSize().y)));

    std::unordered_set<sf::Vector2f, Vector2fHash, Vector2fEqual> uniqueIntersections =
        calculateIntersections(m_lastMousePosF, m_shapesPos, m_winBB, m_winEdges, m_shapeEdges);

    m_rayIntersections.clear();
    m_rayIntersections.insert(m_rayIntersections.end(), uniqueIntersections.begin(), uniqueIntersections.end());

    Vector2fAngleComparator comparator{ m_lastMousePosF };
    std::sort(m_rayIntersections.begin(), m_rayIntersections.end(), comparator);
}

void Game::render()
{
    m_renderer.clear();

    m_renderer.drawShapes(m_shapesPos.convexShapes);

    // uncomment/comment out below if you want/dont want to see the rays as well
    m_renderer.drawRays(m_lastMousePosF, m_rayIntersections);
    
    // uncomment/comment out below if you want/dont want to see visibility
    m_renderer.drawPolygons(m_lastMousePosF, m_rayIntersections);
    m_renderer.drawMouseInfo(m_lastMousePosF);

    m_renderer.display();
}