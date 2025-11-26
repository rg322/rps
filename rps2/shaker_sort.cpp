#include "shaker_sort.h"
#include <algorithm> // для std::swap

//реализация шейкерной сортировки (вариант пузырьковой с проходом в обе стороны)
void shakerSort(std::vector<int>& arr)
{
    bool swapped = true;
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (swapped)
    {
        swapped = false;

        //проход слева направо
        for (int i = left; i < right; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        right--;

        //если обменов не было — массив отсортирован
        if (!swapped) break;

        swapped = false;

        //проход справа налево
        for (int i = right; i > left; --i)
        {
            if (arr[i] < arr[i - 1])
            {
                std::swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        left++;
    }
}
