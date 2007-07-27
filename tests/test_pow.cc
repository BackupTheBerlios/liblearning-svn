#include <iostream>
#include <bits/pow.hpp>

int main(int argc, char** argv)
{
	int y = rand();
	int r = y;
	__asm ("xxx:\n\t");
	for (int i = 2; i <= 8; ++i, r *= y);
	std::cout << r << std::endl;

	// just three multiplications in asm
	int x;
	__asm ( "bla:\n\t" );
	x = dz::pow<8>::compute(rand());
	std::cout << x << std::endl;
}


