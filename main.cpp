#include <iostream>
#include <new>
#include <cstddef>

void rm(int** mtx, int rows)
{
  if (mtx == nullptr) return; // memory check if mtx is not zero
  for (size_t i = 0; i < rows; i++)  
    delete[] mtx[i];
  delete[] mtx;
}

int** make(size_t rows, const size_t* lns)
{
  int** mtx = new int*[rows];
  for (size_t i = 0; i < rows; i++)
    mtx[i] = nullptr; // another check to not delete by mistake

  for (size_t i = 0; i < rows; i++) 
  {
    try
    {
      mtx[i] = new int[lns[i]];
    }
    catch (const std::bad_alloc &) 
    {
      rm(mtx, i);
      throw;
    }
  }
  return mtx;
}

void output(const int* const* mtx, size_t rows, const size_t* lns)
{
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < lns[i]; j++)
      std::cout << mtx[i][j] << ' ';
    std::cout << '\n';
  }
}

int** convert(const int* t, size_t n, const size_t* lns, size_t rows)
{
  int** result = make(rows, lns);
  size_t start = 0, pos = 0;

  while (start < n)
  {
    for (size_t i = 0; i < lns[pos]; i++)
    {
      result[pos][i] = t[start + i];
    }
    start += lns[pos++];
  }
  return result;
}

void input(int** mtx, int rows, int cols)
{
  for (size_t i = 0; i < rows; ++i) 
  {
    for (size_t j = 0; j < rows; ++j) 
    {
      std::cin >> mtx[i][j];
    }
  }
}

int main() 
{
  size_t n = 0, rows = 0;
  std::cin >> n >> rows;
  int* t = nullptr;

  try
  {
    t = new int[n];
  }

  catch (const std::bad_alloc&)
  {
    return 2;
  }

  for (size_t i = 0; i < n; i++)
  {
    std::cin >> t[i];
  }

  if (std::cin.fail())
  {
    delete[] t;
    return 1;
  }
  size_t* lns = nullptr;

  try
  {
    lns = new size_t[rows];
  }

  catch (const std::bad_alloc&)
  {
    delete[] t;
    return 2;
  }

  for (size_t i = 0; i < rows; i++)
  {
    std::cin >> lns[i];
  }

  if (std::cin.fail())
  {
    delete[] t;
    delete[] lns;
    return 1;
  }
  int** result = nullptr;

  try
  {
    result = convert(t, n, lns, rows);
  }

  catch (std::bad_alloc&)
  {
    return 2;
  }
  output(result, rows, lns);
  rm(result, rows);
  delete[] t;
  delete[] lns;
}