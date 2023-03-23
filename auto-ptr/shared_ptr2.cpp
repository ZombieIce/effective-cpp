#include <iostream>
#include <memory>
#include "cat.hpp"
using namespace std;

void set_by_value(std::shared_ptr<Cat> cat) {
  cout << cat->get_name() << endl;
  cat->set_cat_name("ee");
  cout << "func use count: " << cat.use_count() << endl;
}

void set_by_ref(std::shared_ptr<Cat> &cat) {
  cout << cat->get_name() << endl;
  cat.reset(new Cat());
  cout << "func ref use count: " << cat.use_count() << endl;
}

auto get_shared_ptr() {
  std::shared_ptr<Cat> cat_p = std::make_shared<Cat>("local cat");
  return cat_p;
}


int main (int argc, char *argv[])
{
  std::shared_ptr<Cat> c1 = make_shared<Cat>("dd");
  
  set_by_value(c1);
  c1->cat_info();

  cout << "c1 use count: " << c1.use_count() << endl;

  set_by_ref(c1);
  c1->cat_info();

  auto c_p = get_shared_ptr();
  c_p->cat_info();

  get_shared_ptr()->cat_info();


  return 0;
}
