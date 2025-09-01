/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:41:11 by tialbert          #+#    #+#             */
/*   Updated: 2025/08/30 12:18:30 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/includes.hpp"

static int find_op(int a, int b, std::string op) {
  int res;

  switch (op[0]) {
  case ('+'):
    res = a + b;
    break;
  case ('-'):
    res = a - b;
    break;
  case ('*'):
    res = a * b;
    break;
  case ('/'):
    res = a / b;
    break;
  default:
    throw std::exception();
  }

  return (res);
}

// static unsigned int split_input(std::string input,
//                                 std::queue<std::string> &cache) {
//   unsigned int a;
//   unsigned int b;
//   unsigned int res;
//   std::string tmp;
//
//   for (unsigned int i = 0; i < input.size(); i++) {
//     if (i % 2 == 0) {
//       tmp = input.substr(i, 1);
//       if (isdigit(tmp[0]))
//         cache.push(tmp);
//       else {
//         b = std::atoi(cache.front().c_str());
//         cache.pop();
//         a = std::atoi(cache.front().c_str());
//         cache.pop();
//         try {
//           res = find_op(a, b, tmp);
//         } catch (...) {
//           throw std::exception();
//         }
//         cache.push(ft_itoa(res, 10));
//       }
//     }
//   }
//
//   return (res);
// }

// TODO: Complete function
// Maybe add another argument with the result
// static unsigned int rpn(std::queue<std::string> &cache, unsigned int carry) {
//   unsigned int a;
//   unsigned int b;
//   unsigned int res;
//   std::string op;
//
//   if (cache.size() == 1)
//     return (std::atoi(cache.front().c_str()));
//
//   a = std::atoi(cache.front().c_str());
//   cache.pop();
//   b = std::atoi(cache.front().c_str());
//   cache.pop();
//   op = cache.front();
//   cache.pop();
//
//   if (op.size() != 1)
//     throw std::exception();
//
//   try {
//     res = find_op(a, b, op);
//   } catch (...) {
//     throw std::exception();
//   }
//
//   if (cache.size() > 0 &&
// }

// RPN::RPN(void) { return; }

// RPN::RPN(std::string input) { split_input(input, _cache); }
//
// // TODO: Confirm if its a deep copy
// RPN::RPN(RPN const &rpn) { this->_cache = rpn._cache; }
//
// RPN &RPN::operator=(RPN const &rpn) {
//   this->_cache = rpn._cache;
//
//   return (*this);
// }

// RPN::~RPN(void) { return; }

int RPN::calculate(std::string input) {
  int a;
  int b;
  int res;
  std::string tmp;
  std::stack<int> cache;

  for (unsigned int i = 0; i < input.size(); i++) {
    if (i % 2 == 0) {
      tmp = input.substr(i, 1);
      if (isdigit(tmp[0]))
        cache.push(std::atoi(tmp.c_str()));
      else {
        if (cache.empty()) {
          std::cout << "Error" << std::endl;
          throw std::exception();
        }
        b = cache.top();
        cache.pop();
        a = cache.top();
        cache.pop();
        std::cout << a << " " << tmp << " " << b << " = ";
        try {
          res = find_op(a, b, tmp);
        } catch (...) {
          std::cout << "Error" << std::endl;
          throw std::exception();
        }
        std::cout << res << std::endl;
        cache.push(res);
      }
    }
  }

  return (res);
}

// void RPN::calculate(void) {
//   unsigned int result;
//
//   result = rpn(_cache);
//   std::cout << result << std::endl;
// }
