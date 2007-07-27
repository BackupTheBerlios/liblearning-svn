#include <search.hpp>
#include <iostream>

int main(int argc, char** argv) {
	int n[] = { 1, 2, 4, 7, 9 };

	linear_lower_bound l;
	std::cout << *l(&n[0], &n[5], 7) << std::endl;

	binary_lower_bound b;
	std::cout << *l(&n[0], &n[5], 7) << std::endl;
}
