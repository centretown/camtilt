#ifndef ARDUINO
#pragma once

#include "base.h"

class MicroTerm
{
private:
public:
    MicroTerm(/* args */) {}
    ~MicroTerm() {}
    size_t println(const char *p)
    {
        printf("%s\n", p);
        return 0;
    }
};

#endif