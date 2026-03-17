#include <iostream>
#include <utility>
using namespace std;

int* min(int arr[], int n)
{
    int min = *arr;
    for (int i = 0; i < n; i++)
    {
        if (*(arr + i) < min)
        {
            min = *(arr + i);
        }
    }
    int *p_min = new int(min);

    return p_min;
}

void sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int min_i = i;

        for (int j = i + 1; j < n; ++j)
        {
            if (*(arr + j) < *(arr + min_i))
            {
                min_i = j;
            }
        }
        std::swap(*(arr + i), *(arr + min_i));
    }


    cout << "Отсортированный массив:" << " ";
    for (int i = 0; i < n; ++i)
    {
        
        cout << arr[i] << " ";
    }
}


int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    
    cout << "Указатель минимального элемента: " << min(arr, n) << endl;
    
    sort(arr, n);
    delete[] arr; 

}