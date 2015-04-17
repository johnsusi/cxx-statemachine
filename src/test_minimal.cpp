#include "statemachine.h"

struct s1 {};
struct s2 { int x = 0; };
struct e1 {};

struct test : state_machine<test, s1, s2> {

  void state(s2& s) { ++s.x; }
  void state(...) {}


  void transition(s1, s2) { }
  void transition(s2, s1) { }
  void transition(...) {}


  void event(s1, e1) { set_state<s2>(); }
  void event(s2, e1) { set_state<s1>(); }
  void event(...) {}
  
  operator int() const { return get<s2>().x; }
};

int main() {

  test x;
  for (std::size_t i = 0;i < 100000000;++i) x.process_event<e1>();
  return x == 50000000 ? 0 : -1;
}
