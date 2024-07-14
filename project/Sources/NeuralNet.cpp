#include "NeuralNet.h"
#include <stdexcept>
#include <algorithm>
#include "functions.h"

NeuralNet::NeuralNet(int input, int hidden, int output, int hiddenLayers)
    : m_iNodes(input), m_hNodes(hidden), m_oNodes(output), m_hLayers(hiddenLayers)
{
    m_weights.resize(m_hLayers + 1);
    m_weights[0] = new Matrix(m_hNodes, m_iNodes + 1);

    for (int i = 1; i < m_hLayers; ++i)
    {
        m_weights[i] = new Matrix(m_hNodes, m_hNodes + 1);
    }
    m_weights[m_hLayers] = new Matrix(m_oNodes, m_hNodes + 1);

    for (auto& matrix : m_weights)
    {
        matrix->randomize();
    }
}

NeuralNet::~NeuralNet() = default;

void NeuralNet::mutate(float mr)
{
    std::for_each(m_weights.begin(), m_weights.end(), [mr](auto& matrix) { matrix->mutate(mr); });
}

std::vector<float> NeuralNet::output(const std::vector<float>& inputsArr)
{
    auto inputs = Matrix::singleColumnMatrixFromArray(inputsArr);
    auto curr_bias = inputs->addBias();

    for (int i = 0; i < m_hLayers; ++i)
    {
        auto hidden_ip = m_weights[i]->dot(*curr_bias);
        auto hidden_op = hidden_ip->activate();
        curr_bias = hidden_op->addBias();
    }

    auto output_ip = m_weights.back()->dot(*curr_bias);
    auto output = output_ip->activate();

    return output->toArray();
}

NeuralNet* NeuralNet::crossover(const NeuralNet& partner) const
{
    auto child = new NeuralNet(m_iNodes, m_hNodes, m_oNodes, m_hLayers);

    for (size_t i = 0; i < m_weights.size(); ++i)
    {
        child->m_weights[i] = m_weights[i]->crossover(*partner.m_weights[i]);
    }

    return child;
}

NeuralNet* NeuralNet::clone() const
{
    auto clone = new NeuralNet(m_iNodes, m_hNodes, m_oNodes, m_hLayers);

    for (size_t i = 0; i < m_weights.size(); ++i)
    {
        clone->m_weights[i] = m_weights[i]->clone();
    }

    return clone;
}

std::vector<Matrix*> NeuralNet::pull() const
{
    std::vector<Matrix*> result;
    for (const auto& weight : m_weights)
    {
       result.push_back(weight->clone());
    }
    return result;
}

void NeuralNet::load(const std::vector<Matrix*>& weight)
{
    if (weight.size() != m_weights.size())
    {
        throw std::invalid_argument("Invalid weight size");
    }
    for (size_t i = 0; i < m_weights.size(); ++i)
    {
        *m_weights[i] = *weight[i];
    }
}


void NeuralNet::show(float x, float y, float w, float h, std::vector<float> vision, std::vector<float> decision)
{
    float space = 5;
    float nSize = (h - (space * (m_iNodes - 2))) / m_iNodes;
    float nSpace = (w - (m_weights.size() * nSize)) / m_weights.size();
    float hBuff = (h - (space * (m_hNodes - 1)) - (nSize * m_hNodes)) / 2;
    float oBuff = (h - (space * (m_oNodes - 1)) - (nSize * m_oNodes)) / 2;

    int maxIndex = 0;
    for (int i = 0; i < decision.size(); ++i)
    {
        if (decision[i] > decision[maxIndex])
        {
            maxIndex = i;
        }
    }

    int lc = 0;

    for (int i = 0; i < m_iNodes; ++i)
    {
        if (vision[i] != 0)
        {
            // fill color
        }
        else
        {
            // fill color
        }

        DrawCircle(x, y + (i * (nSize + space)), nSize);
    }

    ++lc;

    for (int a = 0; a < m_hLayers; ++a)
    {
        for (int i = 0; i < m_hNodes; ++i)
        {  //DRAW HIDDEN
            DrawCircle(x + (lc * nSize) + (lc * nSpace), y + hBuff + (i * (nSize + space)), nSize);
        }
        ++lc;
    }

    for (int i = 0; i < m_oNodes; ++i)
    {  //DRAW OUTPUTS
        if (i == maxIndex)
        {
            // fill special
        }
        else
        {
            // fill special
        }
        DrawCircle(x + (lc * nSpace) + (lc * nSize), y + oBuff + (i * (nSize + space)), nSize);
    }

    lc = 1;

    for (int i = 0; i < m_weights[0]->getRows(); i++)
    {  //INPUT TO HIDDEN
        for (int j = 0; j < m_weights[0]->getCols() - 1; j++)
        {
            SDL_Color color;
            if (m_weights[0]->getMatrix()[i][j] < 0)
            {
                color = { 255, 0, 0, 255 };
            }
            else
            {
                color = { 0, 0, 255, 255 };
            }
            DrawLine(x + nSize, y + (nSize / 2) + (j * (space + nSize)), x + nSize + nSpace, y + hBuff + (nSize / 2) + (i * (space + nSize)), color);
        }
    }

    ++lc;

    for (int a = 1; a < m_hLayers; a++)
    {
        for (int i = 0; i < m_weights[a]->getRows(); i++)
        {  //HIDDEN TO HIDDEN
            for (int j = 0; j < m_weights[a]->getCols() - 1; j++)
            {
                SDL_Color color;
                if (m_weights[a]->getMatrix()[i][j] < 0)
                {
                    color = { 255, 0, 0, 255 };
                }
                else
                {
                    color = { 0, 0, 255, 255 };
                }
                DrawLine(x + (lc * nSize) + ((lc - 1) * nSpace), y + hBuff + (nSize / 2) + (j * (space + nSize)), x + (lc * nSize) + (lc * nSpace), y + hBuff + (nSize / 2) + (i * (space + nSize)), color);
            }
        }
        lc++;
    }

    for (int i = 0; i < m_weights[m_weights.size() - 1]->getRows(); i++)
    {  //HIDDEN TO OUTPUT
        for (int j = 0; j < m_weights[m_weights.size() - 1]->getCols() - 1; j++)
        {
            SDL_Color color;
            if (m_weights[m_weights.size() - 1]->getMatrix()[i][j] < 0)
            {
                color = { 255, 0, 0, 255 };
            }
            else
            {
                color = { 0, 0, 255, 255 };
            }
            DrawLine(x + (lc * nSize) + ((lc - 1) * nSpace), y + hBuff + (nSize / 2) + (j * (space + nSize)), x + (lc * nSize) + (lc * nSpace), y + oBuff + (nSize / 2) + (i * (space + nSize)));
        }
    }

}