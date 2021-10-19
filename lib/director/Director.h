// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#endif

#include "Sort.h"
#include "Actor.h"
#include "NullActor.h"

class Director : public Sortable
{
private:
    Director() {}

public:
    Actor **list = NULL;
    static Director *getDirector();
    static Director director;

    size_t size = 0;
    size_t length = 0;

public:
    ~Director();
    size_t allocate(size_t size);
    size_t add(Actor **actor, size_t nitems);
    Actor *find(const char *id);

    void sort();
    void swap(size_t i, size_t j);
    bool less(size_t i, size_t j);
    size_t len() { return length; }
};
