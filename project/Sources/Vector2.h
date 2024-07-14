#pragma once

enum Direction
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

struct Vector2
{
    float x;
    float y;

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    void Add(float nX, float nY)
    {
        x += nX;
        y += nY;
    }

    void Add(const Vector2& dir)
    {
        x += dir.x;
        y += dir.y;
    }
};

struct BodyPart
{
    Vector2 m_position;
    Direction m_direction;
    int m_width;
    int m_height;

    BodyPart() : m_position(Vector2(0, 0)), m_direction(Direction::LEFT), m_width(20), m_height(20) {}
    BodyPart(Vector2 pos, Direction dir) : m_position(pos), m_direction(dir), m_width(20), m_height(20) {}
};