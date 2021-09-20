// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "Sort.h"

void Sort(Sortable *arr)
{
    quickSort(arr, 0, arr->len() - 1);
}

void quickSort(Sortable *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(Sortable *arr, int low, int high)
{
    int pivot = high;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr->less(j, pivot))
        {
            i++;
            arr->swap(i, j);
        }
    }

    i++;
    arr->swap(i, high);
    return i;
}
