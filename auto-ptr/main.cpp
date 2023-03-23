#include <iostream>
#include <memory>
#include "cat.hpp"

int main (int argc, char *argv[])
{
  using namespace std;
  //Cat c1("OK");
  //c1.cat_info();
  //{
  //  Cat c1("OK1");
  //  c1.cat_info();
  //}

  // heap
  // raw pointer
  // Cat *c_p1 = new Cat("yy");
  // int *i_p1 = new int(100);
  //c_p1->cat_info();
  //{
  //  int *i_p1 = new int(200);
  //  Cat *c_p1 = new Cat("yy1");
  //  c_p1->cat_info();
  //  delete c_p1;
  //  delete i_p1;
  //}
  //delete c_p1;
  //cout << *i_p1 << endl;
  //delete c_p1;

  // Cat *c_p2 = new Cat("c2");
  // std::unique_ptr<Cat> u_c_p2{c_p2};

  // 建议销毁
  // c_p2->cat_info();
  // u_c_p2->cat_info();
  // c_p2->set_cat_name("OK2");
  // u_c_p2->cat_info();
  // delete c_p2;
  // c_p2 = nullptr;
  // u_c_p2->cat_info();

  std::unique_ptr<Cat> u_c_p3 {new Cat("dd")};
  u_c_p3->cat_info();
  u_c_p3->set_cat_name("oo");
  u_c_p3->cat_info();

  // 推荐方式 std::make_unique
  std::unique_ptr<Cat> u_c_p4 = make_unique<Cat>();
  u_c_p4->cat_info();
  u_c_p4->set_cat_name("oo4");
  u_c_p4->cat_info();

  // get 常量类型
  std::unique_ptr<int> u_i_p3 {new int(100)};
  cout << *u_i_p3 << endl;
  cout << "int address: " << u_i_p3.get() << endl;
  cout << "int address: " << u_c_p3.get() << endl;

  std::unique_ptr<int> u_i_p4 = make_unique<int>(200);
  cout << *u_i_p4 << endl;
  cout << "int address: " << u_i_p4.get() << endl;
  cout << "int address: " << u_c_p4.get() << endl;


  return 0;
}
