#ifndef SHAPES_H
#define SHAPES_H

#include <SFML/Graphics.hpp>
#include "GlobalStructs.h"

ShapesPos createShapes(const std::string& config);
std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>> computeShapeEdges(const ShapesPos& shapesPos);

#endif // SHAPES_H