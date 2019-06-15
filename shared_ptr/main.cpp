#include "shared_ptr.hpp"
#include <iostream>


int main(void)
  {
    SharedPtr_c<float> point0(new float(5));
    SharedPtr_c<float> point1(new float(6));
    std::cout << "point0 " << *point0 << std::endl;
    std::cout << "point1 " << *point1 << std::endl;
    point1 = point0;
  }
