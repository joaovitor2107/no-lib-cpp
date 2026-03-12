#pragma once
#include <cassert>

template<typename F, typename S>
class my_pair {
    public:
        F first;
        S second;

        // default constructor — initializes members with their default values
        my_pair() : first(), second() {}

        my_pair(const F& f, const S& s): first(f), second(s) {}

};
