#include <iostream>
#include <memory>
#include "cat.hpp"

using namespace std;

int main (int argc, char *argv[])
{
  std::shared_ptr<Cat> s_p_c1 = std::make_shared<Cat>("C1");
  std::weak_ptr<Cat> w_p_c1(s_p_c1);

  cout << "w_p_c1: " << w_p_c1.use_count() << endl;
  cout << "s_p_c1: " << s_p_c1.use_count() << endl;

  std::shared_ptr<Cat> s_p_c2 = w_p_c1.lock();
  cout << "w_p_c1: " << w_p_c1.use_count() << endl;
  cout << "s_p_c1: " << s_p_c1.use_count() << endl;
  cout << "s_p_c2: " << s_p_c2.use_count() << endl;

  std::shared_ptr<Cat> c3 = std::make_shared<Cat>("c3");
  std::shared_ptr<Cat> c4 = std::make_shared<Cat>("c4");
  c3->set_friend(c4);
  c4->set_friend(c3);

  return 0;
}
