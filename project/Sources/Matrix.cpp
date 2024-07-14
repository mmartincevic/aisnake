#include "Matrix.h"
#include <random>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "functions.h"

Matrix::Matrix(int rows, int cols) : m_rows(rows), m_cols(cols)
{
    m_matrix.resize(rows, std::vector<float>(cols, 0.0f));
}

Matrix::Matrix(const std::vector<std::vector<float>>& m) : m_rows(m.size()), m_cols(m[0].size()), m_matrix(m) {}
Matrix::Matrix(std::vector<std::vector<float>>& m) : m_rows(m.size()), m_cols(m[0].size()), m_matrix(m) {}

Matrix* Matrix::dot(const Matrix& n) const
{
    if (m_cols != n.m_rows)
    {
        throw std::invalid_argument("Matrix dimensions don't match for dot product");
    }

    auto result = new Matrix(m_rows, n.m_cols);
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < n.m_cols; ++j)
        {
            float sum = 0;
            for (int k = 0; k < m_cols; ++k)
            {
                sum += m_matrix[i][k] * n.m_matrix[k][j];
            }
            result->m_matrix[i][j] = sum;
        }
    }
    return result;
}

void Matrix::randomize()
{
    for (auto& row : m_matrix)
    {
        for (auto& elem : row)
        {
            elem = randomFloatInRange(-1, 1);
        }
    }
}

Matrix* Matrix::singleColumnMatrixFromArray(const std::vector<float>& arr)
{
    auto newMatrix = new Matrix(arr.size(), 1);
    for (size_t i = 0; i < arr.size(); ++i)
    {
        newMatrix->m_matrix[i][0] = arr[i];
    }
    return newMatrix;
}

std::vector<float> Matrix::toArray() const
{
    std::vector<float> arr;
    arr.reserve(m_rows * m_cols);
    for (const auto& row : m_matrix)
    {
        arr.insert(arr.end(), row.begin(), row.end());
    }
    return arr;
}

Matrix* Matrix::addBias() const
{
    auto newMatrix = new Matrix(m_rows + 1, 1);
    for (int i = 0; i < m_rows; ++i)
    {
        newMatrix->m_matrix[i][0] = m_matrix[i][0];
    }
    newMatrix->m_matrix[m_rows][0] = 1;
    return newMatrix;
}

Matrix* Matrix::activate() const
{
    auto newMatrix = new Matrix(m_rows, m_cols);
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_cols; ++j)
        {
            newMatrix->m_matrix[i][j] = relu(m_matrix[i][j]);
        }
    }
    return newMatrix;
}

float Matrix::relu(float x) const
{
    return std::max(0.0f, x);
}

void Matrix::mutate(float mutationRate)
{
    for (auto& row : m_matrix)
    {
        for (auto& elem : row)
        {
            if (randomFloatInRange(0, 1) < mutationRate)
            {
                elem += randomGaussian(0, 0.2f);
                elem = std::clamp(elem, -1.0f, 1.0f);
            }
        }
    }
}

Matrix* Matrix::crossover(const Matrix& partner) const
{
    auto child = new Matrix(m_rows, m_cols);
    int randC = randomIntInRange(0, m_cols - 1);
    int randR = randomIntInRange(0, m_rows - 1);

    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_cols; ++j)
        {
            if ((i < randR) || (i == randR && j <= randC))
            {
                child->m_matrix[i][j] = m_matrix[i][j];
            }
            else
            {
                child->m_matrix[i][j] = partner.m_matrix[i][j];
            }
        }
    }
    return child;
}

Matrix* Matrix::clone() const
{
    return new Matrix(m_matrix);
}

void Matrix::output() const
{
    for (const auto& row : m_matrix)
    {
        for (float val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}