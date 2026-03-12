#pragma once
#include <cassert>

template<typename M>
struct MyAllocator {
    // tell the container the type of the data
    using value_type = M;

    // allocate the memory for n objects of type M
    M *allocate(size_t n) {
        return static_cast<M*>(::operator new(n * sizeof(M)));
    }

    // deallocate the memory that was allocated
    void deallocate(M *ptr, size_t n) {
        ::operator delete(ptr);
    }
};

template<typename T, typename Allocator = MyAllocator<T>>
class my_vector {
    private:
        T* _data;
        size_t _size;
        size_t _capacity;
        Allocator _alloc;

    public:
        my_vector() : _size(0), _capacity(0), _data(nullptr) {}
        my_vector(size_t n) : _size(n), _capacity(n) {
            _data = _alloc.allocate(n);
        }

        // creating a vector with a size n and filled with element val
        my_vector(size_t n, const T &val) : _size(n), _capacity(n) {
            _data = _alloc.allocate(n);
            for (size_t i = 0; i < n; i++) {
                _data[i] = val;
            }
        }

        // destructor - called when the object is destroyed
        ~my_vector() {
            _alloc.deallocate(_data, _size);
        }


        T &operator[](size_t index) {
            return _data[index];
        }

        void resize() {
            size_t new_capacity = _capacity * 2;

            T *new_data = _alloc.allocate(new_capacity);
            for (size_t i = 0; i < _capacity; i++) {
                new_data[i] = _data[i];
            }

            _alloc.deallocate(_data, _capacity);

            _capacity = new_capacity;
            _data = new_data;
        }

        // method to look for element in location n
        T &at(size_t index) {
            assert(index < _size && "index out of bounds");
            return _data[index];
        }

        // method to return size of the vector
        size_t size() {return _size;
        }


        void push_back(const T &val) {
            if (_size == _capacity) {
                resize();
            }
            _data[_size] = val;
            _size++;
        }


        T pop_back() {
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
