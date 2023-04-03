#ifndef MATRIX_H
#define MATRIX_H


class Matrix
{
private:
    int m_height;
    int m_width;
    int** m_array;

public:
    Matrix();//Default constructor, height:0 width:0
    Matrix(const Matrix&);//copy constructor

    Matrix(int height, int width, int* numbers);//constructor with height and width of matrix and massive of numbers
                                                //if height*width < numbers then unnesessary numbers just ignors
                                                //if height*width > numbers then missing numbers is just 0
    //Getters
    int GetHeight() const;
    int GetWidth() const;
    int** GetNumbers() const;

    //Setters
    void setSize(int m, int n);
    void setData(int m, int n, int* numbers);
    void setNumbers(int* numbers);


    //maint functions of class
    void Add(const Matrix&);//add matrices
    void Substr();//substruct matrices
    void Multiply();//multiply matrices
    Matrix& operator+=(const Matrix& temp);//overloading operators
    Matrix& operator-=(const Matrix& temp);
    Matrix& operator*=(const Matrix& temp);

};

#endif // MATRIX_H
