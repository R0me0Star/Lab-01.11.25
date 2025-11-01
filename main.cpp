#include <iostream>

int make(int rows, int cols)
{
    int** mtx = new int*[rows];
    for (size_t j = 0; j < rows; ++j) {
        try {
            mtx[j] = new int;
        }
        catch (const std::bad_alloc&) {
            rm(mtx, j);
            throw;
        }
    }
    return mtx;
}

void output(const int *const*mtx)
{

}

void rm(int **mtx,  int rows)
{
    for (size_t j = 0; j < rows; ++j) {
        delete[] mtx[j];
    }
    delete[] mtx;
}

void input(int** mtx, int rows, int cols)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            std::cin >> mtx[i][j];
        }
    }
}

int main() {
    int rows = 0;
    int cols = 0;
    std::cin >> rows >> cols;

    if (std::cin.fail()) {
        return 1;
    }
    int** mtx = nullptr;
    try {
        mtx = make(rows, cols);
    }
    catch (const std::bad_alloc &) {
        rm(mtx, rows);
        return 2;
    }
    output(mtx);
    rm(mtx);
}
