#pragma once

#include <string>
#include <iostream>

class Button
{
public:
    Button(float x, float y, float w, float h, std::string t) : m_PositionX(x), m_PositionY(y), m_Width(w), m_Height(h) {}

    bool Collide(float x, float y) const
    {
        if (x >= m_PositionX - m_Width / 2 && x <= m_PositionX + m_Width / 2 && y >= m_PositionY - m_Height / 2 && y <= m_PositionY + m_Height / 2)
        {
            return true;
        }
        return false;
    }

    void Show() const;

private:
    float m_PositionX;
    float m_PositionY;
    float m_Width;
    float m_Height;
};