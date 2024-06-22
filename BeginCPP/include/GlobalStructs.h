#ifndef SHAPESPOS_H
#define SHAPESPOS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

struct ShapesPos 
{
    std::vector<sf::ConvexShape> convexShapes;
    std::vector<sf::Vector2f> VerticesPos;
};

struct Intersection 
{
    bool res;
    sf::Vector2f pos;
};

struct Vector2fHash 
{
    std::size_t operator()(const sf::Vector2f& v) const 
    {
        std::hash<float> hasher;
        return hasher(v.x) ^ (hasher(v.y) << 1);
    }
};

struct Vector2fEqual 
{
    bool operator()(const sf::Vector2f& lhs, const sf::Vector2f& rhs) const 
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

struct Vector2fAngleComparator 
{
    sf::Vector2f referencePoint;

    bool operator()(const sf::Vector2f& lhs, const sf::Vector2f& rhs) const
    {
        return atan2(lhs.y - referencePoint.y, lhs.x - referencePoint.x) <
            atan2(rhs.y - referencePoint.y, rhs.x - referencePoint.x);
    }
};


#endif // SHAPESPOS_H