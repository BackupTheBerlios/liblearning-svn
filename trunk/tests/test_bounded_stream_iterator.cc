#include <iostream>
#include <sstream>
#include <bounded_stream_iterator.hpp>

int main(int argc, char** argv)
{
  std::stringstream ss("Hello <b>World</b>, <b>nice</b> day!");
  bounded_stream_iterator<> iend;
  bounded_stream_iterator<> i("<b>", "</b>", &ss);
  for (; i != iend; ++i)
  {
    std::cout << *i << std::endl;
  }
}
