// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "Director.h"

Director Director::director;

Director *Director::getDirector()
{
    return &director;
}

size_t Director::allocate(size_t count)
{
    list = (Actor **)malloc(count * sizeof(Actor *));
    if (list == NULL)
    {
        return 0;
    }
    memset(list, 0, count * sizeof(Actor *));
    size = count;
    return size;
}

Director::~Director()
{
    free(list);
}

size_t Director::add(Actor **actor, size_t nitems)
{
    for (size_t i = 0; i < nitems; i++)
    {
        if (length >= size)
        {
            return i;
        }
        list[length] = actor[i];
        length++;
    }
    return nitems;
}

Actor *Director::find(const char *code)
{
    size_t left = 0;
    size_t right = length;

    while (left <= right)
    {
        // mid = left + (right - left) / 2;
        size_t mid = left + ((right - left) >> 1);
        int cmp = strcmp(code, list[mid]->id);
        if (cmp == 0)
        {
            return list[mid];
        }
        if (cmp > 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return &nullActor;
}

int Director::partition(int low, int high)
{
    int pivot = high;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (less(j, pivot))
        {
            i++;
            swap(i, j);
        }
    }

    i++;
    swap(i, high);
    return i;
}

void Director::swap(size_t i, size_t j)
{
    Actor *t = list[i];
    list[i] = list[j];
    list[j] = t;
}

bool Director::less(size_t i, size_t j)
{
    int cmp = strcmp(list[i]->id, list[j]->id);
    return cmp < 0;
}

size_t Director::sort()
{
    quickSort(0, length - 1);
    return length;
}

void Director::quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}
