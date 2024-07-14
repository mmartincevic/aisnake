#pragma once
#include <vector>

class Matrix
{
public:
    Matrix(int rows, int cols);
    Matrix(const std::vector<std::vector<float>>& m);
    Matrix(std::vector<std::vector<float>>& m);

    Matrix* dot(const Matrix& n) const;
    Matrix* addBias() const;
    Matrix* activate() const;
    Matrix* clone() const;
    static Matrix* singleColumnMatrixFromArray(const std::vector<float>& arr);
    Matrix* crossover(const Matrix& partner) const;

    std::vector<float> toArray() const;
    void randomize();
    void mutate(float mutationRate);
    void output() const;

    inline int getRows() const { return m_rows; }
    inline int getCols() const { return m_cols; }

    inline std::vector<std::vector<float>> getMatrix() { return m_matrix; }

private:
    int m_rows;
    int m_cols;
    std::vector<std::vector<float>> m_matrix;

    float relu(float x) const;
};