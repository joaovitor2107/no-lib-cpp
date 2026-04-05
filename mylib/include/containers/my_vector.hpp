#pragma once
#include <cassert>

template<typename m>
struct myallocator {
    // tell the container the type of the data
    using value_type = m;

    // allocate the memory for n objects of type m
    m *allocate(size_t n) {
        return static_cast<m*>(::operator new(n * sizeof(m)));
    }

    // deallocate the memory that was allocated
    void deallocate(m *ptr, size_t n) {
        ::operator delete(ptr);
    }
};

template<typename t, typename allocator = myallocator<t>>
class my_vector {
    private:
        t* _data;
        size_t _size;
        size_t _capacity;
        allocator _alloc;

    public:
        my_vector() : _size(0), _capacity(0), _data(nullptr) {}
        my_vector(size_t n) : _size(n), _capacity(n) {
            _data = _alloc.allocate(n);
        }

        // creating a vector with a size n and filled with element val
        my_vector(size_t n, const t &val) : _size(n), _capacity(n) {
            _data = _alloc.allocate(n);
            for (size_t i = 0; i < n; i++) {
                _data[i] = val;
            }
        }

        // destructor - called when the object is destroyed
        ~my_vector() {
            _alloc.deallocate(_data, _size);
        }


        t &operator[](size_t index) {
            return _data[index];
        }

        void resize() {
            size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;

            t *new_data = _alloc.allocate(new_capacity);
            for (size_t i = 0; i < _capacity; i++) {
                new_data[i] = _data[i];
            }

            _alloc.deallocate(_data, _capacity);

            _capacity = new_capacity;
            _data = new_data;
        }

        t &at(size_t index) {
            assert(index < _size && "index out of bounds");
            return _data[index];
        }

        // method to look for element in location n
        t &at(size_t index) const {
            assert(index < _size && "index out of bounds");
            return _data[index];
        }

        // method to return size of the vector
        size_t size() const { return _size;
        }


        void push_back(const t &val) {
            if (_size == _capacity) {
                resize();
            }
            _data[_size] = val;
            _size++;
        }


        t pop_back() {
           assert(_size > 0 && "vector is empty");
           return _data[--_size];
        }


        void erase(size_t index) {
            assert(index < _size && "index out of bounds");

            if (index == _size - 1) {
                pop_back();
                return;
            }

            for (size_t i = index; i < _size; i++) {
                _data[i] = _data[i+1];
            }

            _size--;
        }
};
