#include <iostream>
#include <cassert>
#include <bits/length.hpp>

int main(int argc, char** argv)
{
  int a[] = {1, 2, 3};
  int b[] = {4, 3, 6};

  assert(length<1>::compute(b) == 4);
  assert(length<2>::compute(b) == 5);
}

