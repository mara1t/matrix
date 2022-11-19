#include "matrix.h"

int main()
{
    int n;
    if (!(std::cin >> n) || !(std::cin.good())) {
        std::cout << "rank should be >= 1\n";
        return -1;
    }   
    std::vector<double> vec(static_cast<size_t>(n * n));
    
    for (unsigned int i = 0; i < n * n; i++)
        if (!(std::cin >> vec[i]) || !(std::cin.good())) {
            std::cout << "error in elem input\n";
            return -1;
        }  

    matrixes::matrix<double> matrix{static_cast<unsigned int>(n), vec};

    double det = matrix.get_det();

    std::cout << det << std::endl;

    return 0;
}