#include <stdio.h>
#include <iostream>

static void make_tests(const int n)
{
    for (int i = 2; i < n; i++) {
        char str[100];

        sprintf(str, "%s%.3d%s", "test_arr/", i, ".dat");
        FILE *tmp_file = fopen(str, "w");

        fprintf(tmp_file, "%d ", i);

        for (int j = 0; j < i*i; j++)
            fprintf(tmp_file, "%d ", rand() % 100 - 50);

        fclose(tmp_file);
    }
}

int main()
{
    make_tests(100);
    return 0;
} 