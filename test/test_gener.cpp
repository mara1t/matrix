#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>

static void make_tests(const int n)
{
    for (int i = 1; i < n; i++) {
        int m = 3;
        std::stringstream sstr;
        std::string tmp_name_str = std::to_string(i);
        std::string tmp_name_str_with_zeroes = std::string((m - std::min(m, static_cast<int>(tmp_name_str.size()))), '0').append(tmp_name_str);
        sstr << "test_arr/" << tmp_name_str_with_zeroes << ".dat";
       
        std::string str = sstr.str();
        
        std::ofstream file;
        file.open(str.c_str());
        
        file << i << " ";
        for (int j = 0; j < i*i; j++)
            file << rand() % 100 - 50 << " ";

        file.close();
    }
}

int main()
{
    make_tests(100);
    return 0;
} 