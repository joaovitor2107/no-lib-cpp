CXXFLAGS := -std=c++17 -Iinclude/containers -Iinclude/hash

main: src/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: main
	./main
