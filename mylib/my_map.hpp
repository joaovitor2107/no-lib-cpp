#pragma once
#include <cassert>
#include <functional>
#include "my_vector.hpp"
#include "my_pair.hpp"

template<typename k, typename v>
class my_map {
    private:
        // arbitrary number
        static constexpr size_t num_buckets = 16;
        my_vector<my_vector<my_pair<k, v>>> _buckets;

        size_t get_hash(const k &key) {
            return std::hash<k>{} (key) % num_buckets;
        }


    public:
        my_map() : _buckets(num_buckets) { }


        v& operator[](const k& key) {
            v* found = find(key);

            if (found) {
                return *found;
            }
            insert(key, v {});
            return *find(key);
        }


        v* find(const k &key) {
            size_t index = get_hash(key);

            for (size_t i = 0; i < _buckets[index].size(); i++) {
                if (key == _buckets[index][i].first) {
                    // key found
                    return & _buckets[index][i].second;
                }
            }

            return nullptr;
        }


        void insert(const k& key, const v& val) {
            v* found = find(key);

            if (found) {
                    // key already there, so we just update the value
                    *found = val;
                    return;
            }
            // new key
            _buckets[get_hash(key)].push_back({key, val});
        }


        void erase(const k& key) {
            size_t index = get_hash(key);
            for (size_t i = 0; i < _buckets[index].size(); i++) {
                if (_buckets[index][i].first == key) {
                    _buckets[index].erase(i);
                    return;
              }
            }
        }
};
