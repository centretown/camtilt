// Copyright (c) 2021 Dave Marsh. See LICENSE.
#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#endif

class Sortable
{
public:
    virtual size_t len() = 0;
    virtual void swap(size_t i, size_t j) = 0;
    virtual bool less(size_t i, size_t j) = 0;
};

void Sort(Sortable *arr);
void quickSort(Sortable *arr, int low, int high);
int partition(Sortable *arr, int low, int high);
