#include "BasicRayCasting.h"
#include <cmath>
#include <limits>

float dotPrd(sf::Vector2f a, sf::Vector2f b) 
{
    return a.x * b.y - a.y * b.x;
}

Intersection LineIntersect(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) 
{
    sf::Vector2f r = b - a;
    sf::Vector2f s = d - c;
    float rxs = dotPrd(r, s);
    if (rxs == 0) 
    {
        return { false, sf::Vector2f(0, 0) };
    }
    sf::Vector2f cma = c - a;
    float t = dotPrd(cma, s) / rxs;
    float u = dotPrd(cma, r) / rxs;
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) 
    {
        return { true, sf::Vector2f(a.x + t * r.x, a.y + t * r.y) };
    }
    return { false, sf::Vector2f(0, 0) };
}

sf::Vector2f rayWindowIntersection(const sf::FloatRect& winBB, const sf::Vector2f& start, float angle) 
{
    sf::Vector2f dir(std::cos(angle), std::sin(angle));
    float tMin = std::numeric_limits<float>::max();
    if (dir.x != 0) 
    {
        float tx1 = (winBB.left - start.x) / dir.x;
        float tx2 = (winBB.left + winBB.width - start.x) / dir.x;
        tMin = std::min(tMin, std::max(tx1, tx2));
    }
    if (dir.y != 0) 
    {
        float ty1 = (winBB.top - start.y) / dir.y;
        float ty2 = (winBB.top + winBB.height - start.y) / dir.y;
        tMin = std::min(tMin, std::max(ty1, ty2));
    }
    return start + tMin * dir;
}

std::unordered_set<sf::Vector2f, Vector2fHash, Vector2fEqual> calculateIntersections(
    const sf::Vector2f& mousePos,
    const ShapesPos& myShapesPos,
    const sf::FloatRect& winBB,
    const std::vector<sf::Vector2f>& winEdges,
    const std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>>& shapeEdges)
{

    const float ANGLE_OFFSET = 0.00001f;
    std::unordered_set<sf::Vector2f, Vector2fHash, Vector2fEqual> uniqueIntersections;

    // rays from mouse position to all vertices +/- 0.00001f
    for (const auto& Pos : myShapesPos.VerticesPos) 
    {
        sf::Vector2f dirToVertex = Pos - mousePos;
        float angleToVertex = std::atan2(dirToVertex.y, dirToVertex.x);

        std::vector<float> rayAngles = { angleToVertex, angleToVertex - ANGLE_OFFSET, angleToVertex + ANGLE_OFFSET };

        for (float rayAngle : rayAngles) 
        {
            sf::Vector2f rayEnd = rayWindowIntersection(winBB, mousePos, rayAngle);
            float closestDist = std::numeric_limits<float>::max();
            sf::Vector2f closestIntersect = rayEnd;

            for (size_t i = 0; i < myShapesPos.convexShapes.size(); i++) 
            {
                for (const auto& Vertex : shapeEdges[i]) 
                {
                    Intersection intersect = LineIntersect(mousePos, rayEnd, Vertex.first, Vertex.second);
                    if (intersect.res) 
                    {
                        float dist = std::pow(mousePos.x - intersect.pos.x, 2) +
                            std::pow(mousePos.y - intersect.pos.y, 2);

                        if (dist < closestDist) 
                        {
                            closestDist = dist;
                            closestIntersect = intersect.pos;
                        }
                    }
                }
            }

            uniqueIntersections.insert(closestIntersect);
        }
    }

    // rays from mouse position to all window corners
    for (const auto& winEdge : winEdges) 
    {
        sf::Vector2f dirToCorner = winEdge - mousePos;
        float angleToCorner = std::atan2(dirToCorner.y, dirToCorner.x);
        sf::Vector2f rayEnd = rayWindowIntersection(winBB, mousePos, angleToCorner);
        float closestDist = std::numeric_limits<float>::max();
        sf::Vector2f closestIntersect = rayEnd;

        for (size_t i = 0; i < myShapesPos.convexShapes.size(); i++) 
        {
            for (const auto& Vertex : shapeEdges[i]) 
            {
                Intersection intersect = LineIntersect(mousePos, rayEnd, Vertex.first, Vertex.second);
                if (intersect.res) 
                {
                    float dist = std::pow(mousePos.x - intersect.pos.x, 2) +
                        std::pow(mousePos.y - intersect.pos.y, 2);

                    if (dist < closestDist) 
                    {
                        closestDist = dist;
                        closestIntersect = intersect.pos;
                    }
                }
            }
        }

        uniqueIntersections.insert(closestIntersect);
    }

    // edge cases
    if (mousePos.x == 0.0f)
    {
        if (uniqueIntersections.find(sf::Vector2f(0.0f, 0.0f)) == uniqueIntersections.end())
        {
            uniqueIntersections.insert(sf::Vector2f(0.0f, 0.0f));
        }
        if (uniqueIntersections.find(sf::Vector2f(0.0f, winBB.width)) == uniqueIntersections.end())
        {
            uniqueIntersections.insert(sf::Vector2f(0.0f, winBB.width));
        }
    }
    if (mousePos.y == 0.0f)
    {
        if (uniqueIntersections.find(sf::Vector2f(0.0f, 0.0f)) == uniqueIntersections.end())
        {
            uniqueIntersections.insert(sf::Vector2f(0.0f, 0.0f));
        }
        if (uniqueIntersections.find(sf::Vector2f(winBB.height, 0.0f)) == uniqueIntersections.end())
        {
            uniqueIntersections.insert(sf::Vector2f(winBB.height, 0.0f));
        }
    }

    return uniqueIntersections;
}
