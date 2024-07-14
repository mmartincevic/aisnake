#pragma once

#include "Vector2.h"

class Food
{
public:
    Food(Vector2 position) : m_Position(position) {}
    inline Vector2 getPosition() const { return m_Position; }

    void Show() const;
public:
    Vector2 m_Position;
    int m_Width = 20;
    int m_Height = 20;
};