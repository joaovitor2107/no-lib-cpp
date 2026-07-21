#pragma once
#include <cassert>
#include <functional>
#include "my_vector.hpp"
#include "my_pair.hpp"

template<typename k, typename v>
class my_map {
    private:
        // arbitrary number to start
        size_t _num_buckets = 16;
        size_t _count = 0;  // number of elements

        my_vector<my_vector<my_pair<k, v>>> _buckets;

        size_t get_hash(const k &key) {
            return std::hash<k>{} (key) % _num_buckets;
        }

        void rehash() {
            size_t new_num_buckets = _num_buckets * 2;
            my_vector<my_vector<my_pair<k, v>>> new_buckets(new_num_buckets);

            _num_buckets = new_num_buckets;
            for (size_t i = 0; i < _buckets.size(); i++) {
                for (size_t j = 0; j < _buckets[i].size(); j++) {
                    auto& entry =  _buckets[i][j];
                    size_t new_index = get_hash(entry.first);
                    new_buckets[new_index].push_back(entry);
                }
            }

        }

    public:
        my_map() : _buckets(_num_buckets) { }


        // alterar para ser atomico
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
            if (_count + 1 > _num_buckets) {
                rehash();
            }

            _buckets[get_hash(key)].push_back({key, val});
            _count++;
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
