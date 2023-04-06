#include "matrix.h"



Matrix::Matrix()
{
    m_height = 0;
    m_width = 0;
}

Matrix::Matrix(const Matrix & temp)
{
    m_height = temp.GetHeight();
    m_width = temp.GetWidth();
    float** tmp_arr = temp.GetNumbers();
    m_array = new float*[m_height];
    for(int i =0; i <m_height;i++)
    {
        m_array[i] = new float[m_width];
        for(int j=0;j<m_width;j++)
        {
            m_array[i][j] = tmp_arr[i][j];
        }
    }
}

Matrix::Matrix(int height, int width, float numbers[])
{
    m_height = height;
    m_width = width;
    m_array = new float*[m_height];
    for(int i=0;i<m_height;i++)
    {
        m_array[i] = new float[m_width];
        for(int j=0;j<m_width;j++)
        {
            m_array[i][j] = numbers[i*m_width+j];
        }
    }

}


//Getters
int Matrix::GetHeight() const
{
    return m_height;
}

int Matrix::GetWidth() const
{
    return m_width;
}

float **Matrix::GetNumbers() const
{
    return m_array;
}


//main functions
bool Matrix::Add(const Matrix & temp)
{
    if (m_height== temp.GetHeight() && m_width==temp.GetWidth())
    {
        float** tmp_array = temp.GetNumbers();
        for(int i=0;i<m_height;i++)
        {
            for(int j=0;j<m_width;j++)
            {
               m_array[i][j]+=tmp_array[i][j];
            }
        }
        return true;
    }
    return false;
}

bool Matrix::Substr(const Matrix& temp)
{
    if (m_height== temp.GetHeight() && m_width==temp.GetWidth())
    {
        float** tmp_array = temp.GetNumbers();
        for(int i=0;i<m_height;i++)
        {
            for(int j=0;j<m_width;j++)
            {
               m_array[i][j]-=tmp_array[i][j];
            }
        }
        return true;
    }
    return false;
}

bool Matrix::Multiply(const Matrix& temp)
{
    if (m_width == temp.GetHeight())
    {
       float** tmp_arr = temp.GetNumbers();
       float** new_matrix= new float*[m_height];
       for(int i=0;i<m_height;i++)
       {
           new_matrix[i]=new float[temp.GetWidth()];
           for(int j=0;j<temp.GetWidth();j++)
           {
               new_matrix[i][j]=0;
               for (int k = 0; k < m_width; k++)
               {
                new_matrix[i][j] += m_array[i][k] * tmp_arr[k][j];
               }
           }
       }
       m_width = temp.GetWidth();
       m_array = new_matrix;
       return true;
    }
    return false;
}

Matrix &Matrix::operator+=(const Matrix &temp)
{
    this->Add(temp);
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &temp)
{
    this->Substr(temp);
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &temp)
{
    this->Multiply(temp);
    return *this;
}

Matrix &Matrix::operator=(const Matrix &temp)
{
    m_array = temp.GetNumbers();
    m_height = temp.GetHeight();
    m_width = temp.GetWidth();
    return *this;
}



