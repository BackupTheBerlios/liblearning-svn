#include <iostream>
#include <boost/multi_array.hpp>
#include <markov_chain.hpp>

void ex1() 
{
  typedef markov_chain<2, int> mc_t;
  typedef mc_t::iterator iterator;

  int I[] = {0,1,2,0,1,2,0,1,2,2,1};
  mc_t mc(&I[0], &I[11], 3);
  mc_t::iterator i = mc.begin(&I[0]);

  std::cout << I[0] << I[1] << std::endl;
  for (int n = 0; i != mc.end() && n < 100; ++i, ++n)
  {
    std::cout << *i << std::flush;
  }
  std::cout << std::endl << "current state: <";
  iterator::const_symbol_iterator si = i.begin();
  for (; si != i.end(); ++si)
  {
    std::cout << *si;
  }
  std::cout << ">" << std::endl;
}

void ex2()
{
  typedef markov_chain<2, char> mc_t;
  typedef mc_t::iterator iterator;

  char* c = "HELLO, THIS IS A TESTSTRING";
  mc_t mc(&c[0], &c[strlen(c)], 256);
  iterator i = mc.begin(&c[0]);

  std::cout << c[0] << c[1] << std::endl;
  for (int n = 0; i != mc.end() && n < 100; ++i, ++n)
  {
    std::cout << *i << std::flush;
  }
  std::cout << std::endl << "current state: <";
  iterator::const_symbol_iterator si = i.begin();
  for (; si != i.end(); ++si)
  {
    std::cout << *si;
  }
  std::cout << ">" << std::endl;
}

int main(int argc, char** argv)
{
  srand(102);
  ex1();
  ex2();

  int x[] = {0, 1, 0, 1, 0, 1, 0, 2};
  markov_chain<1, int> mc(&x[0], &x[8], 3);
  assert(mc.size() == 3);

  boost::multi_array<double, 2> a(boost::extents[mc.size()][mc.size()]);
  mc.fill_matrix(a);

  assert(a[0][2] == 0.25);
  assert(a[0][1] == 0.75);
  assert(a[1][0] == 1);
  assert(a[0][0] == 0);
}


