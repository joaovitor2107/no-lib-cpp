#pragma once
#include <functional>
#include "my_vector.hpp"

template<typename T>
class my_set {
    // Unordered set implementation using hash sets
    private:
        static constexpr size_t NUM_BUCKETS = 16;
        my_vector<my_vector<T>> _buckets;

        size_t hash(const T &key) {
            return std::hash<T>{} (key) % NUM_BUCKETS;
        }

    public:
        my_set() : _buckets(NUM_BUCKETS) { }


        T* find(const T& key) {
            size_t index = hash(key);

            for (int i = 0; i < _buckets[index].size(); i++) {
                if (_buckets[index][i] == key)
                    return &_buckets[index][i];
            }

            return nullptr;
        }


        void insert(const T& key) {
            if (find(key)) return;
            _buckets[hash(key)].push_back(key);
        }


        bool contains(const T& key) {
            return find(key) != nullptr;
        }


        void erase(const T &key) {
            size_t index = hash(key);
            for (size_t i = 0; i < _buckets[index].size(); i++) {
                if (_buckets[index][i] == key) {
                    _buckets[index].erase(i);
                    return;
              }
            }
        }
};
