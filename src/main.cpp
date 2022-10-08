#include "..//include//matrix.h"

int main()
{
    int n;
    std::cin >> n;
    std::vector<double> vec(n * n);
    
    for (int i = 0; i < n * n; i++) {
        std::cin >> vec[i];
    }
    matrixes::matrix<double> matrix{n, vec};
    //matrix.get_matrix();

    double det = matrix.get_det();
    //matrix.get_matrix();
    std::cout << det << std::endl;


    return 0;
}