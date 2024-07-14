#pragma once
#include "Vector2.h"
#include <vector>
#include <memory>
#include "Food.h"
#include "NeuralNet.h"

class Snake
{
public:
    Snake();
    Snake(const Snake& other);
    Snake& operator=(const Snake& other);
    virtual ~Snake();

    virtual Snake* clone() const;
    virtual Snake* cloneForReplay();

    bool bodyCollide(float x, float y) const;
    bool foodCollide(float x, float y) const;
    bool foodCollide() const;
    bool wallCollide(float x, float y) const;
    bool wallCollide() const;

    void show() const;
    void eat();
    void shiftBody();

    Snake* crossover(const Snake& parent) const;

    void mutate(float mutationRate);

    void calculateFitness();

    void look();
    void think();

    void move();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void addBody();
    Vector2 calculatePosition(const Vector2& currentPosition, Direction direction) const;
    Vector2 calculateRandomPosition() const;
    BodyPart Snake::calculateInitialBodyPosition() const;

    void spawnFood();

    void update();

    // Getters
    bool isReplay() const { return m_replay; }
    bool isAlive() const { return m_isAlive; }
    bool isDead() const { return !m_isAlive; }
    float getFitness() const { return m_fitness; }
    int getScore() const { return m_score; }

    // Setters
    void setReplay(bool replay) { m_replay = replay; }

    std::vector<Vector2> m_foodList;

    inline int getMoves() const { return m_moves; }
    inline int getLifetime() const { return m_moves; }

    inline std::vector<float> getVision() { return m_vision; }
    inline std::vector<float> getDecision() { return m_decision; }

public:
    NeuralNet* m_brain;

private:
    std::vector<float> lookInDirection(const Vector2& direction) const;

    bool m_replay = false;
    bool m_isAlive = true;

    float m_fitness = 0;
    int m_score = 1;

    int m_moves = 200;
    int m_lifetime = 0;
    int m_foodIterate = 0;

    std::vector<float> m_vision;
    std::vector<float> m_decision;
    std::vector<BodyPart> m_snakeBody;

    Food* m_food;
};