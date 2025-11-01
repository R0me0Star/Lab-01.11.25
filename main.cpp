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
  size_t start = 0;

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < lns[i]; j++)
    {
      if (start + j >= n) // I use runtime_error to throw logic errors
      {
        rm(result, rows); // check on borders of array
        throw std::runtime_error("Beyond the borders of array");
      }
      result[i][j] = t[start + j];
    }
    start += lns[i];
  }

  if (start != n)
  {
    rm(result, rows); // check on lns
    throw std::runtime_error("Sum of lns < n");
  }
  return result;
}

int main() 
{
  size_t n = 0, rows = 0; // n is number of elements in t
  std::cin >> n >> rows; // first input (n and rows)

  int* t = nullptr; // t is original array
  size_t* lns = nullptr;
  int** result = nullptr;

  try
  {
    t = new int[n]; // creating elements of array
    for (size_t i = 0; i < n; i++)
      std::cin >> t[i]; // second input (elements)

    if (std::cin.fail())
    {
      std::cerr << "Input error with t\n";
      delete[] t;
      delete[] lns;
      return 1;
    }

    lns = new size_t[rows];
    for (size_t i = 0; i < rows; i++)
      std::cin >> lns[i]; // third input (rows size of matrix)

    if (std::cin.fail())
    {
      std::cerr << "Input error with lns\n";
      delete[] t;
      delete[] lns;
      return 1;
    }

    result = convert(t, n, lns, rows);
    output(result, rows, lns);
  }

  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory allocation fail\n";
    return 2; // memory error
  }

  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << '\n'; // catching logic errors
    return 3;
  }

  rm(result, rows);
  delete[] t;
  delete[] lns;
}