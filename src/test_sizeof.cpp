#include <iostream>

#include "statemachine.h"

struct s1 {};
struct s2 { int x = 0; };
struct s3 { std::string x = {}; };

struct a : state_machine<a, s1> {

};



struct b : state_machine<b, s1, s2> {
  void state(...) {}
  void transition(...) {}
  void event(...) {}

};

struct c : state_machine<b, s1, s2, s3> {

};



int main() {

  std::cout << sizeof(a) << std::endl;
  std::cout << sizeof(b) << std::endl;
  return 0;
}
