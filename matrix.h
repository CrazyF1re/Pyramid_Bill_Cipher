#ifndef MATRIX_H
#define MATRIX_H

#include <QApplication>
#include <iostream>
class Matrix
{
private:
    int m_height;
    int m_width;
    float** m_array;

public:
    Matrix();//Default constructor, height:0 width:0
    Matrix(const Matrix&);//copy constructor

    Matrix(int height, int width, float numbers[]);//constructor with height and width of matrix and massive of numbers
                                                //if height*width < numbers then unnesessary numbers just ignors
    //Getters
    int GetHeight() const;
    int GetWidth() const;
    float** GetNumbers() const;


    void print()
    {
        for(int i=0;i<m_height;i++)
        {
            for(int j=0;j<m_width;j++)
            {
                std::cout<<m_array[i][j]<<' ';
            }
            std::cout<<'\n';
        }
    }

    //main functions of class
    bool Add(const Matrix&);//add matrices
    bool Substr(const Matrix&);//substruct matrices
    bool Multiply(const Matrix&);//multiply matrices
    Matrix& operator+=(const Matrix& temp);//overloading operators
    Matrix& operator-=(const Matrix& temp);
    Matrix& operator*=(const Matrix& temp);
    Matrix& operator=(const Matrix& temp);

};

#endif // MATRIX_H
