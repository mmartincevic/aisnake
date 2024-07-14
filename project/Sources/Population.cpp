#include "Population.h"
#include "definitions.h"
#include <algorithm>
#include <random>
#include "functions.h"

Population::Population(int numberOfSnakes)
{
    m_snakes.resize(numberOfSnakes);
    std::generate(m_snakes.begin(), m_snakes.end(), []() { return new Snake(); });
    m_bestSnake = m_snakes[0]->clone();
    m_bestSnake->setReplay(true);
}

Population::~Population()
{
    clearAndDeleteSnakes();
    delete m_bestSnake;
}

bool Population::isDone() const
{
    return std::all_of(m_snakes.begin(), m_snakes.end(),
        [](const auto& snake) { return snake->isDead(); })
        && m_bestSnake->isDead();
}

void Population::update()
{
    if (!m_bestSnake->isDead())
    {
        m_bestSnake->look();
        m_bestSnake->think();
        m_bestSnake->move();
    }
    for (auto& snake : m_snakes)
    {
        if (!snake->isDead())
        {
            snake->look();
            snake->think();
            snake->move();
        }
    }
}

void Population::show() const
{
    if (REPLY_BEST)
    {
        m_bestSnake->show();
        m_bestSnake->m_brain->show(0, 0, 360, 790, m_bestSnake->getVision(), m_bestSnake->getDecision());
    }
    else
    {
        for (const auto& snake : m_snakes)
        {
            snake->show();
        }
    }
}

void Population::setBestSnake()
{
    auto bestSnakeIt = std::max_element(m_snakes.begin(), m_snakes.end(),
        [](const auto& a, const auto& b) { return a->getFitness() < b->getFitness(); });

    if ((*bestSnakeIt)->getFitness() > m_bestFitness)
    {
        m_bestFitness = (*bestSnakeIt)->getFitness();
        m_bestSnake = (*bestSnakeIt)->cloneForReplay();
        m_bestSnakeScore = (*bestSnakeIt)->getScore();
    }
    else
    {
        m_bestSnake = m_bestSnake->cloneForReplay();
    }
}

Snake* Population::selectParent() const
{
    float rand = randomFloatInRange(0, m_fitnessSum);
    float summation = 0;
    for (const auto& snake : m_snakes)
    {
        summation += snake->getFitness();
        if (summation > rand)
        {
            return snake->clone();
        }
    }
    return m_snakes[0]->clone();
}

void Population::naturalSelection()
{
    std::vector<Snake*> newSnakes;
    newSnakes.reserve(m_snakes.size());

    setBestSnake();
    calculateFitnessSum();

    newSnakes.push_back(m_bestSnake->clone());
    for (size_t i = 1; i < m_snakes.size(); ++i)
    {
        auto child = selectParent()->crossover(*selectParent());
        child->mutate(MUTATION_RATE);
        newSnakes.push_back(child);
    }

    clearAndDeleteSnakes();
    m_snakes = std::move(newSnakes);
    // Implement evolution tracking if needed
    // TODO: Evolution graph
    ++m_generation;
}

void Population::clearAndDeleteSnakes()
{
    for (Snake* snake : m_snakes)
    {
        delete snake;
    }
    m_snakes.clear();
}

void Population::mutate()
{
    for (size_t i = 1; i < m_snakes.size(); ++i)
    {
        m_snakes[i]->mutate(MUTATION_RATE);
    }
}

void Population::calculateFitness()
{
    for (auto& snake : m_snakes)
    {
        snake->calculateFitness();
    }
}

void Population::calculateFitnessSum()
{
    m_fitnessSum = 0;
    for (const auto& snake : m_snakes)
    {
        m_fitnessSum += snake->getFitness();
    }
}