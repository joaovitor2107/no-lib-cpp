#include <iostream>
#include "my_vector.hpp"
#include "my_set.hpp"
#include "my_pair.hpp"
#include "my_map.hpp"


int main(int argc, char *argv[]) {

    //my_vector<int> vec(10, 1);
    my_vector<my_pair<int, char>> vec(3, {1, 'a'});
    //vec.at(9) = 20;
    //vec.erase(9);

    my_map<char, int> map;
    std::cout << "map: ";
    map.insert('a', 1);
    std::cout << map['a'] << " ";
    map.insert('b', 2);
    std::cout << map['b'] << " ";
    map.insert('a', 2);
    std::cout << map['a'] << " ";
    std::cout << "\n";

    my_set<int> set;
    std::cout << "set: ";
    set.insert(1);
    std::cout << set.contains(1) << " ";
    std::cout << set.contains(2) << " ";
    set.insert(2);
    std::cout << set.contains(2) << " ";
    std::cout << "\n";

    std::cout << "vector: ";
    for (int i = 0; i < vec.size(); i++) {
        //std::cout << vec.at(i) << " ";
        std::cout << vec.at(i).first << "-" << vec.at(i).second;
    }

    return 0;
}
