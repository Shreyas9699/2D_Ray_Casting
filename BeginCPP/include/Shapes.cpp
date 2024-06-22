#include "Shapes.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

ShapesPos createShapes(const std::string& config)
{
    std::ifstream fin(config);
    if (!fin.is_open())
    {
        std::cerr << "Error opening the file!" << "\n";
        exit(EXIT_FAILURE);
    }

    ShapesPos shapesPos;
    std::string line;
    while (std::getline(fin, line))
    {
        std::istringstream iss(line);
        std::string shapeType;
        iss >> shapeType;

        if (shapeType == "convex")
        {
            int s;
            iss >> s;
            sf::ConvexShape convex;
            convex.setPointCount(s);
            for (int i = 0; i < s; ++i)
            {
                int a, b;
                iss >> a >> b;
                shapesPos.VerticesPos.push_back(sf::Vector2f(a, b));
                convex.setPoint(i, sf::Vector2f(a, b));
            }
            convex.setFillColor(sf::Color::White);
            shapesPos.convexShapes.push_back(convex);
        }
        else 
        {
            std::cerr << "Invalid shape type\n";
            exit(-1);
        }
    }
    return shapesPos;
}

std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>> computeShapeEdges(const ShapesPos& shapesPos)
{
    std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>> shapeEdges;
    for (const auto& shape : shapesPos.convexShapes)
    {
        std::vector<std::pair<sf::Vector2f, sf::Vector2f>> edges;
        size_t vertices = shape.getPointCount();
        for (size_t j = 0; j < vertices; j++)
        {
            edges.emplace_back(shape.getPoint(j), shape.getPoint((j + 1) % vertices));
        }
        shapeEdges.push_back(std::move(edges));
    }
    return shapeEdges;
}