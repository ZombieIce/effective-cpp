#include <iostream>
#include <memory>
#include "cat.hpp"

using namespace std;

std::unique_ptr<Cat> get_unique_ptr() {
  std::unique_ptr<Cat> c_p = std::make_unique<Cat>("unique cat");
  return c_p;
}


int main (int argc, char *argv[])
{
  std::unique_ptr<Cat> c_p_1 = std::make_unique<Cat>("dd");
  std::shared_ptr<Cat> c_p_2 = std::move(c_p_1);

  cout << "c_p_2 use count: " << c_p_2.use_count() << endl;

  std::shared_ptr<Cat> c_p_3 = get_unique_ptr();
  if (c_p_3) {
    c_p_3->cat_info();
    cout << "c_p_3 use count: " << c_p_3.use_count() << endl;
  }

  return 0;
}
