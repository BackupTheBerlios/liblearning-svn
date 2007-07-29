#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>

void
rect(int n, double x, double y, double w, double h, const char* fname)
{
  std::ofstream os(fname);
  assert(os.is_open() && os.good());
  for (; n; --n)
  {
    double _x = (double) rand() / (double) RAND_MAX * w + x;
    double _y = (double) rand() / (double) RAND_MAX * h + y;
    os << _x << " " << _y << "\n";
  }
}

int
main(int argc, char** argv)
{
  srand(0);
  rect(100, 0.2, 0.1, 0.6, 0.2, "../synthetic/2/rect/rect01.dat");
  rect(100, 0.2, 0.4, 0.6, 0.2, "../synthetic/2/rect/rect02.dat");
}

