#include <iostream>
#include <future>
#include <vector>
 int square(int x) {
	return x * x;
}
 int main() {
	std::vector<int> data{1, 2, 3, 4, 5};
	std::vector<std::future<int>> futures;
 	for (int x : data) {
        futures.push_back(std::async(std::launch::async, square, x));
	}
 
	int sum = 0;
	for (auto& f : futures) {
    	sum += f.get();
	}
 
	std::cout << sum << std::endl;
	return 0;
}