// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Actor.h"
#include "NullActor.h"

class Director
{
public:
    Actor **list = NULL;
    size_t size = 0;
    size_t length = 0;

private:
    Director() {}

public:
    ~Director();
    size_t allocate(size_t size);
    size_t add(Actor **actor, size_t nitems);
    size_t sort();
    Actor *find(const char *id);
    static Director *getDirector();
    static Director director;

private:
    int partition(int low, int high);
    void swap(size_t i, size_t j);
    bool less(size_t i, size_t j);
    void quickSort(int low, int high);
};
