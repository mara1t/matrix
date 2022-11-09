#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>

namespace matrixes {

const double eps = 1e-5;

template<typename T>
class matrix
{
private:
    int n_ = 0;
    T *arr_ = nullptr;
    bool changed_determ_sign_ = false;
    bool changed_ = true;
    double det_ = NAN;
public:
    matrix(const unsigned int n) : arr_{new T[n*n]}, n_{n} {}
    matrix(const unsigned int, const std::vector<T> &);
    matrix(const matrix&);
    matrix(const matrix&&);
    ~matrix() { delete[] arr_; };

    void init_fields(const std::vector<T> &);
    int get_size() const { return n_; } 
    double get_det();
    bool is_roughly_zero(const double&) const;
    void swap_rows(const int, const int, double []);
    void swap_columns(const int, const int, double []);
    double simple_determ() const;
    void get_matrix() const;

    matrix operator = (const matrix&);
    matrix operator = (const matrix&&);
    //T operator [] (const int n, const int m);
};

template<typename T>
matrix<T>::matrix(const unsigned int n, const std::vector<T> &vec)
{
    n_ = n;
    arr_ = new T[n * n];
    init_fields(vec);
}

template<typename T>
matrix<T>::matrix(const matrix& another_matrix)
{
    if (&another_matrix == this) 
        return;
    
    n_ = another_matrix.n_;
    arr_ = new T[n_ * n_];
    std::copy(another_matrix.arr_, another_matrix.arr_ + n_ * n_, arr_);
}

template<typename T>
matrix<T>::matrix(const matrix&& another_matrix)
{
    if (&another_matrix == this) 
        return;
    
    n_ = another_matrix.n_;
    arr_ = another_matrix.arr_;
    another_matrix = nullptr;
}

template<typename T>
void matrix<T>::init_fields(const std::vector<T> &buf)
{
    for (int rows = 0; rows < n_; rows++)
        for (int columns = 0; columns < n_; columns++)
            arr_[columns + n_ * rows] = buf[columns + n_ * rows];
}


// measuring determinant without any changing in matrix
template<typename T>
double matrix<T>::get_det()
{
    if (!changed_) 
        return det_;
    
    int main_row;
    double tmp_elem;

    double *double_arr = new double[n_ * n_];
     
    for (int rows = 0; rows < n_; rows++)
        for (int columns = 0; columns < n_; columns++)
            double_arr[columns + n_ * rows] = static_cast<double>(arr_[columns + n_ * rows]);

    for (int columns = 0; columns < n_ - 1; columns++) {
        main_row = columns;
        tmp_elem = double_arr[columns + n_ * main_row];

        while (main_row < n_) {
            tmp_elem = double_arr[columns + n_ * main_row];
            if (!is_roughly_zero(tmp_elem))
                break;
            main_row++;
        }    
        if (main_row == n_)
            return 0;

        swap_rows(main_row, columns, double_arr);

        for (int rows = columns + 1; rows < n_; rows++) {
            double div_koef = double_arr[columns + n_ * rows] / double_arr[columns + n_ * columns];

            if (!is_roughly_zero(double_arr[columns + rows * n_])) {
                for (int tmp_columns = columns; tmp_columns < n_; tmp_columns++) {
                    double_arr[tmp_columns + n_ * rows] -= double_arr[tmp_columns + n_ * columns] * div_koef;
                }
            }
        }
    }

    double det = 1;
    for (int columns = 0; columns < n_; columns++) {
        if (is_roughly_zero(double_arr[columns + n_ * columns]))
            return 0;

        det *= double_arr[columns + n_ * columns];
    }

    if (changed_determ_sign_) 
        return -1 * det;

    delete [] double_arr;

    return det;
}

template<typename T>
bool matrix<T>::is_roughly_zero(const double &elem) const
{   
    return std::fabs(elem) < eps;
}

template<typename T>
void matrix<T>::swap_rows(const int n1, const int n2, double double_arr[])
{   
    if (n1 != n2)
        changed_determ_sign_ = !changed_determ_sign_;

    for (int columns = 0; columns < n_; columns++)
        std::swap(double_arr[columns + n_ * n1], double_arr[columns + n_ * n2]);
}

template<typename T>
void matrix<T>::swap_columns(const int m1, const int m2, double double_arr[])
{   
    if (m1 != m2)
        changed_determ_sign_ = !changed_determ_sign_;

    for (int rows = 0; rows < n_; rows++)
        std::swap(double_arr[m1 + n_ * rows], double_arr[m2 + n_ * rows]);
}

template<typename T>
void matrix<T>::get_matrix() const
{   
    std::cout << std::endl;
    for (int rows = 0; rows < n_; rows++) { 
        std::cout << "| ";
        for (int columns = 0; columns < n_; columns++)
            std::cout << arr_[columns + n_ * rows] << " ";
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

template<typename T>
matrix<T> matrix<T>::operator = (const matrix& another_matrix)
{
    if (&another_matrix == this)
        return *this;

    if (another_matrix.n_ != n_) {
        delete [] arr_;
        arr_ = new T[n_];
        n_ = another_matrix.n_;
    }
    std::copy(another_matrix.arr_, another_matrix.arr_ + n_ * n_, arr_);
    det_ = another_matrix.det_;
    changed_ = another_matrix.changed_;
    changed_determ_sign_ = another_matrix.changed_determ_sign_;

    return *this;   
}

template<typename T>
matrix<T> matrix<T>::operator = (const matrix&& another_matrix)
{
    if (&another_matrix == this)
        return *this;

    n_ = another_matrix.n_;
    arr_ = another_matrix.arr_;
    another_matrix.arr_ = nullptr;
    det_ = another_matrix.det_;
    changed_ = another_matrix.changed_;
    changed_determ_sign_ = another_matrix.changed_determ_sign_;

    return *this;   
}

}  //  namespace matrixes

