#include "matrix.h"

Matrix::Matrix()
{
    m_height = 0;
    m_width = 0;
}

int Matrix::GetHeight() const
{
    return m_height;
}

int Matrix::GetWidth() const
{
    return m_width;
}

int **Matrix::GetNumbers() const
{
    return m_array;
}

Matrix::Matrix(const Matrix & temp)
{
    m_height = temp.GetHeight();
    m_width = temp.GetWidth();
    int** tmp_arr = temp.GetNumbers();
    m_array = new int*[m_height];
    for(int i =0; i <m_height;i++)
    {
        m_array[i] = new int[m_width];
        for(int j=0;j<m_width;j++)
        {
            m_array[i][j] = tmp_arr[i][j];
        }
    }
}
