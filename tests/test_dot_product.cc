#include <iostream>
#include <cassert>
#include <bits/dot_product.hpp>

int main(int argc, char** argv)
{
  int a[] = {1, 2, 3};
  int b[] = {4, 5, 6};

  assert(dot_product<3>::compute(a, b) == 4 + 10 + 18);
  assert(dot_product<1>::compute(a, b) == 4);
  assert(dot_product<0>::compute(a, b) == 0);
}

