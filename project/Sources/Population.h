#pragma once
#include <vector>
#include <memory>
#include "Snake.h"

class Population
{
public:
    Population(int numberOfSnakes);
    ~Population();

    bool isDone() const;
    void update();
    void show() const;
    void naturalSelection();
    void mutate();
    void calculateFitness();

    inline Snake* bestSnake() { return m_bestSnake; }
    inline int getGeneration() { return m_generation; }

private:
    void setBestSnake();
    void calculateFitnessSum();
    void clearAndDeleteSnakes();
    Snake* selectParent() const;

    std::vector<Snake*> m_snakes;
    Snake* m_bestSnake;

    int m_bestSnakeScore = 0;
    int m_generation = 0;
    float m_bestFitness = 0;
    float m_fitnessSum = 0;
    bool m_replayBest = true;  // Add this if you want to implement replay functionality
};