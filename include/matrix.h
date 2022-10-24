#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <cstring>

namespace matrixes {

const double eps = 1e-5;

template<typename T>
class matrix
{
private:
    int n_ = 0;
    T *arr_ = nullptr;
    double *double_arr_ = nullptr;
    bool changed_determ_sign = false;
    bool diagonalized_ = 0;
    bool changed_ = true;
    double det_ = NAN;
public:
    matrix(const int n) : arr_{new T[n*n]}, double_arr_{new double[n*n]}, n_{n} {}
    matrix(const int, std::vector<T>);
    ~matrix() {delete[] arr_; delete[] double_arr_;};

    std::vector<T> get_data() const;
    void init_fields(std::vector<T>);
    int get_size() const { return n_; } 
    bool is_diagonalized() const { return diagonalized_; }
    double get_det();
    bool is_roughly_zero(const double&) const;
    void swap_rows(int, int);
    void swap_columns(const int, const int);
    double simple_determ() const;
    void get_matrix() const;

    matrix operator = (const matrix&);
    matrix operator = (const matrix &&);
    //T operator [] (const int n, const int m);
};

template<typename T>
matrix<T>::matrix(const int n, std::vector<T> vec)
{
    if (n <= 0) 
        return;
    n_ = n;
    arr_ = new T[n * n];
    double_arr_ = new double[n * n];
    init_fields(vec);
}

template<typename T>
std::vector<T> matrix<T>::get_data() const
{
    std::vector<T> tmp_vec(n_ * n_);
    for (auto &vec_elem : tmp_vec)
        std::cin >> vec_elem; 
    
    return tmp_vec;
}

template<typename T>
void matrix<T>::init_fields(std::vector<T> buf)
{
    for (int rows = 0; rows < n_; rows++)
        for (int columns = 0; columns < n_; columns++) {
            arr_[columns + n_ * rows] = buf[columns + n_ * rows];
            double_arr_[columns + n_ * rows] = static_cast<double>(buf[columns + n_ * rows]);
        }
}

template<typename T>
double matrix<T>::get_det()
{
    if (!changed_) 
        return det_;

    if (diagonalized_)
        return simple_determ();
    
    int main_row;
    double tmp_elem;

    for (int columns = 0; columns < n_ - 1; columns++) {
        main_row = columns;
        tmp_elem = double_arr_[columns + n_ * main_row];

        while (main_row < n_) {
            tmp_elem = double_arr_[columns + n_ * main_row];
            if (!is_roughly_zero(tmp_elem))
                break;
            main_row++;
        }    
        if (main_row == n_)
            return 0;

        swap_rows(main_row, columns);

        for (int rows = columns + 1; rows < n_; rows++) {
            double div_koef = double_arr_[columns + n_ * rows] / double_arr_[columns + n_ * columns];

            if (!is_roughly_zero(*(arr_ + columns + rows * n_))) {
                for (int tmp_columns = columns; tmp_columns < n_; tmp_columns++) {
                    double_arr_[tmp_columns + n_ * rows] -= double_arr_[tmp_columns + n_ * columns] * div_koef;
                }
            }
        }
    }

    diagonalized_ = 1;

    return simple_determ();
}

template<typename T>
bool matrix<T>::is_roughly_zero(const double &elem) const
{   
    return fabs(elem) < eps;
}

template<typename T>
void matrix<T>::swap_rows(int n1, int n2)
{   
    if (n1 != n2)
        changed_determ_sign = !changed_determ_sign;

    for (int columns = 0; columns < n_; columns++) {
        double swap_elem = double_arr_[columns + n_ * n1];
        double_arr_[columns + n_ * n1] = double_arr_[columns + n_ * n2];
        double_arr_[columns + n_ * n2] = swap_elem;
    }
    
}

template<typename T>
void matrix<T>::swap_columns(const int m1, const int m2)
{   
    if (m1 != m2)
        changed_determ_sign = !changed_determ_sign;

    for (int rows = 0; rows < n_; rows++) {
        double swap_elem = double_arr_[m1 + n_ * rows];
        double_arr_[m1 + n_ * rows] = double_arr_[m2 + n_ * rows];
        double_arr_[m2 + n_ * rows] = swap_elem;
    }
}

template<typename T>
double matrix<T>::simple_determ() const
{   
    double det = 1;
    for (int columns = 0; columns < n_; columns++) {
        if (is_roughly_zero(double_arr_[columns + n_ * columns]))
            return 0;

        det *= double_arr_[columns + n_ * columns];
    }

    if (changed_determ_sign) 
        return -1 * det;
    
    return det;
}

template<typename T>
void matrix<T>::get_matrix() const
{   
    std::cout << std::endl;
    for (int rows = 0; rows < n_; rows++) { 
        std::cout << "| ";
        for (int columns = 0; columns < n_; columns++)
            std::cout << *(arr_ + columns + n_ * rows) << " ";
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
        delete [] another_matrix.arr_;
        delete [] another_matrix.double_arr_;
        another_matrix.arr_ = new T[n_];
        another_matrix.double_arr_ = new double[n_];

        another_matrix.n_ = n_;
        std::memcpy(another_matrix.arr_, arr_, sizeof(T) * n_);
        std::memcpy(another_matrix.double_arr_, double_arr_, sizeof(double) * n_);
        another_matrix.det_ = det_;
        another_matrix.changed_ = changed_;
        another_matrix.changed_determ_sign = changed_determ_sign;
        another_matrix.diagonalized_ = diagonalized_;

        return *this;
    }
}



}  //  namespace matrixes

