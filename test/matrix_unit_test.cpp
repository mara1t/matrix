#include "matrix.h"
#include <gtest/gtest.h>

TEST(matrixTest, test1) {
    int n = 2;
    std::vector<int> vec{1, 2, 5, 7};
    matrixes::matrix<int> matrix{n, vec};

    EXPECT_EQ(1, fabs(matrix.get_det() + 3) < matrixes::eps);
}

TEST(matrixTest, test2) {
    int n = 3;
    std::vector<int> vec{5, 6, 7 ,8 ,9 , 10, 11, 12, 50};
    matrixes::matrix<int> matrix{n, vec};
    
    EXPECT_EQ(1, fabs(matrix.get_det() + 111) < matrixes::eps);
}

TEST(matrixTest, test3) {
    int n = 4;
    std::vector<int> vec{5, 6, 7, 1, 8, 9, 10, 2, 11, 12, 50, 3, 7, 8, 40, 51};
    matrixes::matrix<int> matrix{n, vec};

    EXPECT_EQ(1, fabs(matrix.get_det() + 5476) < matrixes::eps);
}

TEST(matrixTest, test4) {
    int n = 5;
    std::vector<int> vec{5, 6, 7, -5, 8, 8, 9, 10, 7, -21, 11, 12, 50, 49, 24, 5, 90, 85, 12, 40, 3, 2, 1, 67, 100};
    matrixes::matrix<int> matrix{n, vec};

    EXPECT_EQ(1, fabs(matrix.get_det() + 60103724) < matrixes::eps);
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}