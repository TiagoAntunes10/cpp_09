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

RPN::RPN(void) { return; }

RPN::RPN(RPN const &rpn) { (*this) = rpn; }

RPN &RPN::operator=(RPN const &rpn) {
  (void)rpn;
  return (*this);
}

RPN::~RPN(void) { return; }

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

int RPN::calculate(std::string input) {
  int a = 0;
  int b = 0;
  int res = 0;
  std::string tmp;
  std::stack<int> cache;

  if (cache.size() > 1) {
    std::cout << "Error" << std::endl;
    throw std::exception();
  }

  for (unsigned int i = 0; i < input.size(); i++) {
    if (i % 2 == 0) {
      tmp = input.substr(i, 1);

      if (isdigit(tmp[0]))
        cache.push(std::atoi(tmp.c_str()));
      else {
        if (cache.empty() || cache.size() < 2) {
          std::cout << "Error" << std::endl;
          throw std::exception();
        }

        if (!cache.empty()) {
          b = cache.top();
          cache.pop();
        }
        if (!cache.empty()) {
          a = cache.top();
          cache.pop();
        }

        try {
          res = find_op(a, b, tmp);
        } catch (...) {
          std::cout << "Error" << std::endl;
          throw std::exception();
        }

        cache.push(res);
      }
    } else {
      if (input.substr(i, 1) != " ") {
        std::cout << "Error" << std::endl;
        throw std::exception();
      }
    }
  }

  if (cache.size() > 1) {
    std::cout << "Error" << std::endl;
    throw std::exception();
  }

  if (cache.size() == 1 && input.size() == 1)
    return (cache.top());

  return (res);
}
