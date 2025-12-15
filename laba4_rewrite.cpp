#include <iostream>

bool is_correct(int32_t&);
bool is_natural(const int32_t&);
int32_t** Make(const int32_t&,const int32_t&);
bool Fill_mas(int32_t**,const int32_t&,const int32_t&);
void Free_mas(int32_t**,const int32_t&);
int32_t Sum_elem(int32_t**,const int32_t&,const int32_t&);
int32_t Max_Elem(int32_t**,const int32_t&,const int32_t&);
int32_t Min_Elem(int32_t**,const int32_t&,const int32_t&);
bool prov_row(int32_t&);
bool prov_col(int32_t&);
void transposed_Arr(const int32_t&, const int32_t&, int32_t**, int32_t**);
void print_transposed_Arr(const int32_t&,const int32_t&, int32_t**);
void print_Arr(const int32_t&, const int32_t&, int32_t**);
int32_t sum_main_diagonal(int32_t**, const int32_t&, const int32_t&);
void copy(int32_t**, int32_t**,const int32_t&,const int32_t&);
void sort(int32_t**,const int32_t&,const int32_t&);
void swap_row_or_col(int32_t**,const int32_t&,const int32_t&,const int32_t&,const int32_t&);
bool numb_max_row(int32_t**,const int32_t&,const int32_t&,const int32_t&,const int32_t&);
bool numb_min_row(int32_t**, const int32_t&, const int32_t&, int32_t, const int32_t&);

int main()
{
    try
    {
        int row{ 0 };
        int col{ 0 };
        if (!prov_row(row))
        {
            throw false;
        }
        if (!prov_col(col))
        {
            throw false;
        }
        int** mas = Make(row, col);
        if (!Fill_mas(mas, row, col))
        {
            throw false;
        }
        int max = Max_Elem(mas, row, col);
        int min = Min_Elem(mas, row, col);
        std::cout << "sum E elements around the perimeter " << Sum_elem(mas, row, col) << '\n';
        std::cout << "min element is " << min << '\n';
        std::cout << "max element is " << max << '\n';
        int32_t** arr = Make(col, row);
        transposed_Arr(row, col, mas, arr);
        std::cout << "this is transposed array : " << '\n';
        print_transposed_Arr(row, col, arr);
        Free_mas(arr, col);
        int32_t** arr1 = Make(row, col);
        copy(mas, arr1, row, col);
        sort(arr1, row, col);
        std::cout << "this is sort array : " << '\n';
        print_Arr(row, col, arr1);
        Free_mas(arr1, row);
        std::cout << "sum main diagonal : " << sum_main_diagonal(mas, row, col) << '\n';
        int32_t row_1 = 0;
        int32_t row_2 = 0;
        if (numb_max_row(mas, row, col, max, row_1) != 0 && numb_min_row(mas, row, col, min, row_2) != 0)
        {
            swap_row_or_col(mas, row_1, row_2, row, col);
            std::cout << "this is swap array : " << '\n';
            print_Arr(row, col, mas);
        }
        else
        {
            std::cout << "max or min numbers more then 1, Unable to sort array";
        }
        Free_mas(mas, row);

    }
    catch (bool)
    {
        std::cout << "mistake";
    }
    return 0;
}

bool Fill_mas(int32_t** mas, const int32_t& row,const int32_t& col)
{
    std::cout << "Input elements of the array:\n";
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            if (!is_correct(mas[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}
void Free_mas(int32_t** mas,const int32_t& row)
{
    for (size_t i = 0; i < row; ++i)
    {
        delete[] mas[i];
    }
    delete[] mas;
}
bool is_correct(int32_t& number)
{
    return(std::cin >> number) ? true : false;
}
bool is_natural(const int32_t& number)
{
    return(number > 0) ? true : false;
}
int32_t** Make(const int32_t& row,const int32_t& col)
{

    int32_t** mas = new int32_t* [row];

    for (size_t i = 0; i < row; ++i)
    {
        mas[i] = new int32_t[col];
    }
    return mas;
}
int32_t Sum_elem(int32_t** mas,const int32_t& row,const int32_t& col)
{
    int32_t sum = 0;
    for (size_t j = 0; j < col; ++j)
    {
        sum += mas[0][j];
        if (row > 1)
        {
            sum += mas[row - 1][j];
        }
    }
    for (size_t i = 1; i < row - 1; ++i)
    {
        sum += mas[i][0];
        if (col > 1)
        {
            sum += mas[i][col - 1];
        }
    }
    return sum;
}
int32_t Min_Elem(int32_t** mas,const int32_t& row,const int32_t& col)
{
    int32_t min{ 0 };
    min = mas[0][0];
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            if (min > mas[i][j])
            {
                min = mas[i][j];
            }
        }
    }
    return min;
}
int32_t Max_Elem(int32_t** mas,const int32_t& row,const int32_t& col)
{
    int32_t max{ 0 };
    max = mas[0][0];
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            if (max < mas[i][j])
            {
                max = mas[i][j];
            }
        }
    }
    return max;
}
bool prov_row(int32_t& row)
{
    std::cout << "Input the size of a two-dimensional array\n";
    std::cout << "Number of rows: ";
    if (is_correct(row) && is_natural(row))
    {
        return true;
    }
    return false;
}
bool prov_col(int32_t& col)
{
    std::cout << "Number of columns: ";
    if (is_correct(col) && is_natural(col))
    {
        return true;
    }
    return false;
}
void transposed_Arr(const int32_t& row,const int32_t& col, int32_t** mas, int32_t** arr)
{
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            arr[j][i] = mas[i][j];
        }
    }
}
void print_transposed_Arr(const int32_t& row,const int32_t& col, int32_t** arr)
{
    for (size_t i = 0; i < col; ++i) {
        for (size_t j = 0; j < row; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void print_Arr(const int32_t& row,const int32_t& col, int32_t** arr)
{
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int32_t sum_main_diagonal(int32_t** mas,const int32_t& row,const int32_t& col)
{
    int32_t length = (row < col) ? row : col;
    int32_t s = 0;

    for (int32_t i = 0; i < length; ++i)
    {
        s += mas[i][i];
    }

    return s;
}
void copy(int32_t** mas, int32_t** arr,const int32_t& row,const int32_t& col)
{
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            arr[i][j] = mas[i][j];
        }
    }
}
void sort(int32_t** arr1,const int32_t& row,const int32_t& col)
{
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 1; j < col; ++j)
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
void swap_row_or_col(int32_t** arr,const int32_t& max,const int32_t& min,const int32_t& row,const int32_t& col)
{
    if (max == min)
    {
        for (size_t i = 0; i < row; ++i)
        {
            int32_t temp = arr[i][max];
            arr[i][max] = arr[i][min];
            arr[i][min] = temp;
        }
    }
    else
    {
        for (size_t j = 0; j < col; ++j)
        {
            int32_t temp = arr[max][j];
            arr[max][j] = arr[min][j];
            arr[min][j] = temp;
        }
    }
}
bool numb_max_row(int32_t** arr,const int32_t& row,const int32_t& col,const int32_t& max,const int32_t& row_1)
{
    int32_t temp{ 0 };
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            if (max == arr[i][j])
            {
                temp++;
            }
        }
    }
    return temp == 1 ? true : false;
}
bool numb_min_row(int32_t** arr,const int32_t& row,const int32_t& col, int32_t min,const int32_t& row_2)
{
    int32_t temp{ 0 };
    min = arr[0][0];
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            if (min == arr[i][j])
            {
                temp++;
            }
        }
    }
    return temp == 1 ? true : false;
}