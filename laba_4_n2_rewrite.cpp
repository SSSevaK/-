#include <iostream>
#include <random>
#include <ctime>
#include <cstdint>

bool is_correct(int32_t&);
bool is_natural(const int32_t&);
void prov_type(int32_t&);
void prov_row(int32_t&);
void prov_col(int32_t&);
int32_t** Make(const int32_t&, const int32_t&);
void Fill_mas(int32_t**, const int32_t&, const int32_t&);
void Fill_mas_rand(int32_t**, const int32_t&, const int32_t&);
void Free_mas(int32_t**, const int32_t&);
void print_Arr(const int32_t&, const int32_t&, int32_t**);
void sort(int32_t**, const int32_t&, const int32_t&);
void anothersort(int32_t**, const int32_t&, const int32_t&);
int32_t sum_elem_with_zero(int32_t**, const int32_t&, const int32_t&);

int main()
{
    try
    {
        int32_t row{ 0 };
        int32_t col{ 0 };
        prov_row(row);
        prov_col(col);
        int32_t** mas = Make(row, col);
        int32_t type{ 0 };
        prov_type(type);
        if (type == 1) // random
        {
            Fill_mas_rand(mas, row, col);
        }
        else if (type == 2)
        {
            Fill_mas(mas, row, col);
        }
        else
        {
            throw "incorrect numb";
        }

        std::cout << "sum of elements in columns with at least one zero = " << sum_elem_with_zero(mas, row, col) << std::endl;

        anothersort(mas, row, col);
        sort(mas, row, col);

        std::cout << "sort array " << '\n';
        print_Arr(row, col, mas);

        Free_mas(mas, row);
    }
    catch (const char* msq)
    {
        std::cout << msq;
    }
    return 0;
}

void Fill_mas(int32_t** mas, const int32_t& row, const int32_t& col)
{
    std::cout << "Input elements of the array:\n";
    for (int32_t i = 0; i < row; ++i)
    {
        for (int32_t j = 0; j < col; ++j)
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            if (!is_correct(mas[i][j]))
            {
                throw "you input incorrect number";
            }
        }
    }
}

void Fill_mas_rand(int32_t** mas, const int32_t& row, const int32_t& col)
{
    std::cout << "input min and max numbers" << '\n';
    int32_t min{ 0 };
    int32_t max{ 0 };
    is_correct(min);
    is_correct(max);
    srand(time(NULL));
    for (int32_t i = 0; i < row; ++i)
    {
        for (int32_t j = 0; j < col; ++j)
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            mas[i][j] = rand() % (max - min + 1) + min;
            std::cout << mas[i][j] << std::endl;
        }
    }
}

void Free_mas(int32_t** mas, const int32_t& row)
{
    for (int32_t i = 0; i < row; ++i)
    {
        delete[] mas[i];
    }
    delete[] mas;
}

bool is_correct(int32_t& number)
{
    return (std::cin >> number) ? true : false;
}

bool is_natural(const int32_t& number)
{
    return (number > 0) ? true : false;
}

int32_t** Make(const int32_t& row, const int32_t& col)
{
    int32_t** mas = new int32_t * [row];
    for (int32_t i = 0; i < row; ++i)
    {
        mas[i] = new int32_t[col];
    }
    return mas;
}

void prov_row(int32_t& row)
{
    std::cout << "Input the size of a two-dimensional array\n";
    std::cout << "Number of rows: ";
    if (!is_correct(row) || !is_natural(row))
    {
        throw "number not correct or not natural";
    }

}

void prov_col(int32_t& col)
{
    std::cout << "Number of columns: ";
    if (!is_correct(col) || !is_natural(col))
    {
        throw "number not correct or not natural";
    }
}

void prov_type(int32_t& type)
{
    std::cout << "input 1 if you want random numbers, input 2 if you want to input numbers in array" << '\n';
    if ((!is_correct(type) || !is_natural(type) || (type != 1 && type != 2)))
    {
        throw "you input incorrect number";
    }
}

void print_Arr(const int32_t& row, const int32_t& col, int32_t** arr)
{
    for (int32_t i = 0; i < row; ++i) {
        for (int32_t j = 0; j < col; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void sort(int32_t** arr1, const int32_t& row, const int32_t& col)
{
    for (int32_t i = 0; i < row; i += 2)
    {
        for (int32_t j = 1; j < col; ++j)
        {
            int32_t key = arr1[i][j];
            int32_t k = j - 1;
            while (k >= 0 && arr1[i][k] > key)
            {
                arr1[i][k + 1] = arr1[i][k];
                --k;
            }
            arr1[i][k + 1] = key;
        }
    }
}

int32_t sum_elem_with_zero(int32_t** arr, const int32_t& row, const int32_t& col)
{
    int32_t sum = 0;
    for (int32_t i = 0; i < row; ++i)
    {
        bool hasZero = false;
        for (int32_t j = 0; j < col; ++j)
        {
            if (arr[i][j] == 0)
            {
                hasZero = true;
                break;
            }
        }
        if (hasZero)
        {
            for (int32_t j = 0; j < col; ++j)
            {
                sum += arr[i][j];
            }
        }
    }
    return sum;
}

void anothersort(int32_t** arr1, const int32_t& row, const int32_t& col)
{
    for (int32_t i = 1; i < row; i += 2)
    {
        for (int32_t j = 1; j < col; ++j)
        {
            int32_t key = arr1[i][j];
            int32_t k = j - 1;
            while (k >= 0 && arr1[i][k] < key)
            {
                arr1[i][k + 1] = arr1[i][k];
                --k;
            }
            arr1[i][k + 1] = key;
        }
    }
}
