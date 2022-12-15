#include "shared_ptr.hpp"
#include <iostream>

int main()
{
  shared_ptr<int> a (42);
  std::cout << a.use_count() << std::endl;
  std::cout << a.use_count() << std::endl;
  shared_ptr<int> c (a);
  std::cout << c.use_count() << std::endl;
  std::cout << 12 << std::endl;
  std::cout << c.use_count() << std::endl;
  shared_ptr<int> b (12);
  std::cout << b.use_count() << std::endl;
  b = c;
  std::cout << "счетчики" << std::endl;
  std::cout << a.use_count() << std::endl;
  std::cout << c.use_count() << std::endl;
  std::cout << b.use_count() << std::endl;

  std::cout << 42 << std::endl;

  return 0;
}
