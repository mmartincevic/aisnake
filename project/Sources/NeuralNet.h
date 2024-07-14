#pragma once
#include "Matrix.h"
#include <vector>
#include <memory>

class NeuralNet
{
public:
    NeuralNet(int input, int hidden, int output, int hiddenLayers);
    ~NeuralNet();

    void mutate(float mr);
    void load(const std::vector<Matrix*>& weight);
    std::vector<float> output(const std::vector<float>& inputsArr);
    std::vector<Matrix*> pull() const;
    NeuralNet* crossover(const NeuralNet& partner) const;
    NeuralNet* clone() const;


    void show(float x, float y, float w, float h, std::vector<float> vision, std::vector<float> decision);

public:
    std::vector<Matrix*> m_weights;

private:
    int m_iNodes;
    int m_hNodes;
    int m_oNodes;
    int m_hLayers;
};