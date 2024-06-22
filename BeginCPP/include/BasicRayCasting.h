#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>
#include "GlobalStructs.h"

Intersection LineIntersect(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);

std::unordered_set<sf::Vector2f, Vector2fHash, Vector2fEqual> calculateIntersections(
    const sf::Vector2f& mousePos,
    const ShapesPos& myShapesPos,
    const sf::FloatRect& winBB,
    const std::vector<sf::Vector2f>& winEdges,
    const std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>>& shapeEdges
);

sf::Vector2f rayWindowIntersection(const sf::FloatRect& winBB, const sf::Vector2f& start, float angle);

#endif // RAYCASTING_H