#pragma once

#include "my_vector.hpp"
class my_string {
    my_vector<char> _data;

    public:
        my_string() : _data(0) { }

        my_string(const char* str) {
            while (*str != '\0') {
                _data.push_back(*str);
                str++;
            }
        }

        char &operator[](size_t index) {
            return _data[index];
        }

        const char &operator[](size_t index) const {
            return _data[index];
        }

        my_string &operator+=(const my_string& other) {
            size_t len = other._data.size();
            for (size_t i = 0; i < len; i++) {
                _data.push_back(other[i]);
            }

            return *this;
        }

        bool operator==(const my_string &other) {
            if(_data.size() != other.size()) return false;
            size_t i = 0;
            while (i < other.size() && i < _data.size()) {
                if(other[i] != _data[i]) return false;
            }
            return true;
        }

        bool operator!=(const my_string &other) {
            return !(*this == other);
        }

        size_t size() {
            return _data.size();
        }

        size_t size() const {
            return _data.size();
        }


};
