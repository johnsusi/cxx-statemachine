#ifndef __SE_SUSI_STATEMACHINE_H
#define __SE_SUSI_STATEMACHINE_H

#include <tuple>

template <std::size_t I, std::size_t N, typename... Types>
struct tuple_apply_helper {
  // It is undefined behaviour to call apply with N > sizeof...(Types)
  template <typename F>
  static inline void apply(std::tuple<Types...>& tuple, const std::size_t i, F callback) {
    return (i == (N - I)) ? callback(std::get<N-I>(tuple)) :
        tuple_apply_helper<I-1, N, Types...>::apply(tuple, i, callback);
  }
};

template <std::size_t N, typename... Types>
struct tuple_apply_helper<0, N, Types...> {
  template <typename F>
  static inline void apply(std::tuple<Types...>&, const std::size_t, F) {}
};

template <std::size_t N, typename... Types, typename Fn>
void apply(std::tuple<Types...>& tuple, std::size_t i, Fn callback) {
  tuple_apply_helper<N, N, Types...>::apply(tuple, i, callback);
}

template <std::size_t I, std::size_t N, typename... Types> struct tuple_index_helper;

template <std::size_t I, std::size_t N, typename T, typename... Types>
struct tuple_index_helper<I, N, T, T, Types...> : std::integral_constant<std::size_t, (N-I)> {};

template <std::size_t I, std::size_t N, typename T, typename U, typename... Types>
struct tuple_index_helper<I, N, T, U, Types...> : tuple_index_helper<I-1, N, T, Types...> {};

template <std::size_t N, typename T>
struct tuple_index_helper<0, N, T> : std::integral_constant<std::size_t, N> {};


template <typename T, typename... Types>
std::size_t index(const T&, const std::tuple<Types...>&) {
  constexpr const std::size_t N = sizeof...(Types);
  return tuple_index_helper<N, N, T, Types...>::value;
}

template <typename T, typename... Types>
std::size_t index(const std::tuple<Types...>&) {
  constexpr const std::size_t N = sizeof...(Types);
  return tuple_index_helper<N, N, T, Types...>::value;
}

template <typename CRTP, typename... States>
struct state_machine {

private:

  static constexpr const std::size_t N = sizeof...(States);

  struct index_t {
    std::size_t index = 0;
    operator std::size_t&() { return index; }
  };

  std::tuple<States..., index_t> states;

  std::size_t& current_state() { return std::get<N>(states); }
  CRTP* crtp() { return static_cast<CRTP*>(this); }

  template <typename T> void set_state(T& new_state)
  {
    apply([_this = crtp(), &new_state](auto state) { _this->transition(state, new_state); });
    current_state() = index(new_state, states);
    crtp()->state(new_state);
  }

  template <typename Fn>
  void apply(Fn callback) {
    return ::apply<N>(states, current_state(), callback);
  }

protected:

  template <typename T> void set_state() { set_state( std::get<T>(states) ); }

public:

  template <typename T> void process_event(T event = {})
  {
    apply( [_this = crtp(), &event](auto state) { _this->event(state, event); });
  }

  template <typename St> const St& get() const { return std::get<St>(states); }
  template <std::size_t I> auto    get() const { return std::get<I>(states); }

};

#endif
