#pragma once
#include <cmath>
#include <iostream>
#include <SDL.h>

int randomIntInRange(int min, int max);

float randomFloatInRange(float min, float max);

float randomGaussian(float mean = 0.0f, float stddev = 1.0f);

void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);

void DrawPoint(int32_t centreX, int32_t centreY);

void DrawLine(int32_t fromX, int32_t fromY, int32_t toX, int32_t toY, SDL_Color color = { 0, 255, 0, 255 });