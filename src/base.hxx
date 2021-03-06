#pragma once

#include <algorithm>
#include <string>
#include <sstream>

namespace bistro
{
template <typename value_t, typename char_t>
Base<value_t, char_t>::Base()
{
}

template <typename value_t, typename char_t>
Base<value_t, char_t>::Base(std::initializer_list<char_t> list)
{
  for (auto repr : list)
    add_digit(repr);
}

template <typename value_t, typename char_t>
size_t Base<value_t, char_t>::get_base_num() const
{
  return digits_repr_.size();
}

template <typename value_t, typename char_t>
void Base<value_t, char_t>::add_digit(char_t repr)
{
  if (is_digit(repr))
    throw std::invalid_argument("Digit is already present in the base");
  if (is_operator(repr))
    throw std::invalid_argument(
      "Digit has the same representation as an operator");
  digits_repr_.push_back(repr);
}

template <typename value_t, typename char_t>
bool Base<value_t, char_t>::is_digit(char_t c) const
{
  return std::find(digits_repr_.begin(), digits_repr_.end(), c) !=
         digits_repr_.end();
}

template <typename value_t, typename char_t>
bool Base<value_t, char_t>::is_operator(char_t c)
{
  const std::vector<char> operators{'+', '-', '*', '/', '%', '(', ')'};
  return std::find(operators.begin(), operators.end(), c) != operators.end();
}

template <typename value_t, typename char_t>
char_t Base<value_t, char_t>::get_digit_representation(value_t i) const
{
  if (i >= digits_repr_.size())
  {
    std::stringstream ss;
    ss << "The value " << i << " has no represention in this base of length "
       << get_base_num();
    throw std::out_of_range(ss.str());
  }
  return digits_repr_[i];
}

template <typename value_t, typename char_t>
value_t Base<value_t, char_t>::get_char_value(char_t r) const
{
  auto it = find(digits_repr_.begin(), digits_repr_.end(), r);
  if (it == digits_repr_.end())
  {
    std::stringstream ss;
    ss << "Symbol " << r
       << " is not the representation of any symbol of the base";
    throw std::out_of_range(ss.str());
  }
  return it - digits_repr_.begin();
}
}
