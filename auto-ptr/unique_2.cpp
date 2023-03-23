#include <iostream>
#include <memory>
#include "cat.hpp"

void do_with_cat_pass_value(std::unique_ptr<Cat> c) {
  c->cat_info();
}

void do_with_cat_pass_ref(std::unique_ptr<Cat> &c) {
  c->set_cat_name("oo");
  c->cat_info();
  c.reset();
}

void do_with_cat_pass_ref1(const std::unique_ptr<Cat> &c) {
  c->set_cat_name("oo");
  c->cat_info();
  // c.reset();
}

std::unique_ptr<Cat> get_unique_ptr() {
  std::unique_ptr<Cat> p_dog = std::make_unique<Cat>("local cat");
  // 指针指向地址
  std::cout << "unique address: " << p_dog.get() << std::endl;
  // 指针地址
  std::cout << "unique address: " << &p_dog << std::endl;
  return p_dog;
}


int main (int argc, char *argv[])
{
  // 1. pass by value
  std::unique_ptr<Cat> c1 = std::make_unique<Cat>("ff");

  do_with_cat_pass_value(std::move(c1));
  
  do_with_cat_pass_value(std::make_unique<Cat>()); // 自动转换为move


  // 2. pass by reference
  // no const
  std::unique_ptr<Cat> c2 = std::make_unique<Cat>("f2");
  do_with_cat_pass_ref(c2);
  // c2->cat_info();
  std::cout << c2.get() << std::endl;

  std::unique_ptr<Cat> c3 = std::make_unique<Cat>("f3");
  do_with_cat_pass_ref1(c3);
  c3->cat_info();
  std::cout << c3.get() << std::endl;

  // 链式
  get_unique_ptr()->cat_info();


  return 0;
}
