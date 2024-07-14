#include "Snake.h"
#include "../../helpers/SDL/SDLManager.h"
#include "Vector2.h"
#include "definitions.h"
#include <algorithm>
#include <cmath>
#include <random>
#include "functions.h"

Snake::Snake() : m_brain(new NeuralNet(24, 16, 4, 2))
{
    m_vision.resize(VISION_SIZE);
    m_decision.resize(DECISION_SIZE);

    m_snakeBody.push_back(calculateInitialBodyPosition());

    // I could extract this into configuration so I can adjust starting length
    addBody();
    addBody();

    Vector2 pos = calculateRandomPosition();
    m_food = new Food(pos);
    spawnFood();
}

Snake::Snake(const Snake& other) : m_replay(other.m_replay), m_isAlive(other.m_isAlive),
m_fitness(other.m_fitness), m_score(other.m_score), m_moves(other.m_moves),
m_lifetime(other.m_lifetime), m_foodIterate(other.m_foodIterate),
m_foodList(other.m_foodList), m_vision(other.m_vision), m_decision(other.m_decision),
m_snakeBody(other.m_snakeBody), m_food(other.m_food ? new Food(*other.m_food) : nullptr),
m_brain(other.m_brain ? other.m_brain->clone() : nullptr)
{}

Snake& Snake::operator=(const Snake& other)
{
    if (this != &other)
    {
        m_replay = other.m_replay;
        m_isAlive = other.m_isAlive;
        m_fitness = other.m_fitness;
        m_score = other.m_score;
        m_moves = other.m_moves;
        m_lifetime = other.m_lifetime;
        m_foodIterate = other.m_foodIterate;
        m_foodList = other.m_foodList;
        m_vision = other.m_vision;
        m_decision = other.m_decision;
        m_snakeBody = other.m_snakeBody;
        m_food = other.m_food ? new Food(*other.m_food) : nullptr;
        m_brain = other.m_brain ? other.m_brain->clone() : nullptr;
    }
    return *this;
}

Snake::~Snake() = default;

Snake* Snake::clone() const
{
    return new Snake(*this);
}

bool Snake::bodyCollide(float x, float y) const
{
    return std::any_of(m_snakeBody.begin() + 1, m_snakeBody.end(),
        [x, y](const BodyPart& part) { return part.m_position.x == x && part.m_position.y == y; });
}

bool Snake::foodCollide(float x, float y) const
{
    return m_food && m_food->getPosition().x == x && m_food->getPosition().y == y;
}

bool Snake::foodCollide() const
{
    return foodCollide(m_snakeBody.front().m_position.x, m_snakeBody.front().m_position.y);
}

bool Snake::wallCollide(float x, float y) const
{
    return x < FIELD_START_X || x >= FIELD_START_X + FIELD_WIDTH ||
        y < FIELD_START_Y || y >= FIELD_START_Y + FIELD_HEIGHT;
}

bool Snake::wallCollide() const
{
    const auto& head = m_snakeBody.front().m_position;
    return wallCollide(head.x, head.y);
}

void Snake::show() const
{
    m_food->Show();

    SDL_Color color;
    if (m_replay)
    {
        color = { 255, 0, 0, 255 };
    }
    else
    {
        color = { 0, 0, 255, 255 };
    }

    // Implement visualization using your preferred graphics library
    for (const BodyPart& body : m_snakeBody)
    {
        SDL_Rect pRect;
        pRect.x = body.m_position.x;
        pRect.y = body.m_position.y;
        pRect.w = body.m_width;
        pRect.h = body.m_height;
        SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(SDLManager::Instance().Renderer(), &pRect);
    }
}

void Snake::eat()
{
    m_score++;
    m_moves += 100;
    addBody();
    spawnFood();
}

void Snake::shiftBody()
{
    for (size_t i = m_snakeBody.size() - 1; i > 0; --i)
    {
        m_snakeBody[i].m_position = m_snakeBody[i - 1].m_position;
    }
}

Snake* Snake::crossover(const Snake& parent) const
{
    auto child = new Snake();
    child->m_brain = m_brain->crossover(*parent.m_brain);
    return child;
}

void Snake::mutate(float mutationRate)
{
    m_brain->mutate(mutationRate);
}

void Snake::calculateFitness()
{
    if (m_score < 10)
    {
        m_fitness = static_cast<float>(m_lifetime * m_lifetime) * std::pow(2, m_score);
    }
    else
    {
        m_fitness = static_cast<float>(m_lifetime * m_lifetime);
        m_fitness *= std::pow(2, 10);
        m_fitness *= static_cast<float>(m_score - 9);
    }
}

void Snake::look()
{
    std::vector<Vector2> directions;
    directions.resize(8);

    directions = {
        Vector2(-CELL_DIMENSION, 0), Vector2(-CELL_DIMENSION, -CELL_DIMENSION),
        Vector2(0, -CELL_DIMENSION), Vector2(CELL_DIMENSION, -CELL_DIMENSION),
        Vector2(CELL_DIMENSION, 0), Vector2(CELL_DIMENSION, CELL_DIMENSION),
        Vector2(0, CELL_DIMENSION), Vector2(-CELL_DIMENSION, CELL_DIMENSION)
    };

    for (size_t i = 0; i < directions.size(); ++i)
    {
        auto result = lookInDirection(directions[i]);
        m_vision[i * 3] = result[0];
        m_vision[i * 3 + 1] = result[1];
        m_vision[i * 3 + 2] = result[2];
    }
}

void Snake::think()
{
    m_decision = m_brain->output(std::vector<float>(m_vision.begin(), m_vision.end()));
    auto maxElement = std::max_element(m_decision.begin(), m_decision.end());
    int maxIndex = std::distance(m_decision.begin(), maxElement);

    switch (maxIndex)
    {
    case 0: moveUp(); break;
    case 1: moveDown(); break;
    case 2: moveLeft(); break;
    case 3: moveRight(); break;
    }
}

void Snake::move()
{
    if (!m_isAlive) return;

    m_moves--;
    m_lifetime++;

    shiftBody();
    auto& head = m_snakeBody.front();
    switch (head.m_direction)
    {
    case Direction::UP: head.m_position.y -= CELL_DIMENSION; break;
    case Direction::DOWN: head.m_position.y += CELL_DIMENSION; break;
    case Direction::LEFT: head.m_position.x -= CELL_DIMENSION; break;
    case Direction::RIGHT: head.m_position.x += CELL_DIMENSION; break;
    }

    if (foodCollide())
    {
        eat();
    }

    if (wallCollide() || bodyCollide(head.m_position.x, head.m_position.y))
    {
        m_isAlive = false;
    }

    if (m_moves <= 0)
    {
        m_isAlive = false;
    }
}

void Snake::moveUp()
{
    if (m_snakeBody.front().m_direction != Direction::DOWN)
    {
        m_snakeBody.front().m_direction = Direction::UP;
    }
}

void Snake::moveDown()
{
    if (m_snakeBody.front().m_direction != Direction::UP)
    {
        m_snakeBody.front().m_direction = Direction::DOWN;
    }
}

void Snake::moveLeft()
{
    if (m_snakeBody.front().m_direction != Direction::RIGHT)
    {
        m_snakeBody.front().m_direction = Direction::LEFT;
    }
}

void Snake::moveRight()
{
    if (m_snakeBody.front().m_direction != Direction::LEFT)
    {
        m_snakeBody.front().m_direction = Direction::RIGHT;
    }
}

void Snake::addBody()
{
    const auto& tail = m_snakeBody.back();
    m_snakeBody.push_back(BodyPart(calculatePosition(tail.m_position, tail.m_direction), tail.m_direction));
}

Vector2 Snake::calculatePosition(const Vector2& currentPosition, Direction direction) const
{
    Vector2 newPosition = currentPosition;
    switch (direction)
    {
    case Direction::UP: newPosition.y -= CELL_DIMENSION; break;
    case Direction::DOWN: newPosition.y += CELL_DIMENSION; break;
    case Direction::LEFT: newPosition.x -= CELL_DIMENSION; break;
    case Direction::RIGHT: newPosition.x += CELL_DIMENSION; break;
    }
    return newPosition;
}

Vector2 Snake::calculateRandomPosition() const
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randX = FIELD_START_X + (std::rand() % (FIELD_WIDTH / CELL_DIMENSION)) * CELL_DIMENSION;
    int randY = FIELD_START_Y + (std::rand() % (FIELD_HEIGHT / CELL_DIMENSION)) * CELL_DIMENSION;
    return Vector2(randX, randY);
}

void Snake::spawnFood()
{
    do
    {
        Vector2 pos = calculateRandomPosition();
        m_food = new Food(pos);
    } while (bodyCollide(m_food->getPosition().x, m_food->getPosition().y));

    if (!m_replay)
    {
        m_foodList.push_back(m_food->getPosition());
    }
}

void Snake::update()
{
    if (!m_isAlive) return;

    look();
    think();
    move();
}

std::vector<float> Snake::lookInDirection(const Vector2& direction) const
{
    std::vector<float> look(3, 0.0f);
    Vector2 pos = m_snakeBody.front().m_position;
    float distance = 0;
    bool foodFound = false;
    bool bodyFound = false;
    pos.Add(direction);

    while (!wallCollide(pos.x, pos.y))
    {
        if (look[0] == 0 && foodCollide(pos.x, pos.y))
        {
            foodFound = true;
            look[0] = 1;
        }
        if (look[1] == 0 && bodyCollide(pos.x, pos.y))
        {
            bodyFound = true;
            look[1] = 1;
        }

        if (SEE_VISION)
        {
            DrawPoint(pos.x, pos.y);

            if (foodFound || bodyFound)
            {
                DrawCircle(pos.x, pos.y, 5);
            }
        }

        pos.Add(direction);
        distance += 1;
    }


    if (SEE_VISION)
    {
        DrawCircle(pos.x, pos.y, 5);
    }

    look[2] = 1.0f / distance;
    return look;
}

Snake* Snake::cloneForReplay()
{
    Snake* clone = new Snake();
    clone->m_brain = m_brain->clone();
    clone->m_foodList = m_foodList;
    return clone;
}

BodyPart Snake::calculateInitialBodyPosition() const
{
    int centerX = FIELD_START_X + (FIELD_WIDTH / 2);
    int centerY = FIELD_START_Y + (FIELD_HEIGHT / 2);

    int nearestCellX = centerX - (centerX % CELL_DIMENSION) + (CELL_DIMENSION / 2);
    int nearestCellY = centerY - (centerY % CELL_DIMENSION) + (CELL_DIMENSION / 2);

    BodyPart initialPosition;
    initialPosition.m_position = Vector2(nearestCellX, nearestCellY);
    initialPosition.m_width = CELL_DIMENSION;
    initialPosition.m_height = CELL_DIMENSION;
    return initialPosition;
}
