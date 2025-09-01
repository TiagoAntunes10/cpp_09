/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:20:38 by tialbert          #+#    #+#             */
/*   Updated: 2025/08/30 12:01:45 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
public:
  // RPN(std::string input);
  // RPN(RPN const &rpn);
  // RPN &operator=(RPN const &rpn);
  // ~RPN(void);
  static int calculate(std::string input);
  // void calculate(void);

private:
  RPN(void);
  // std::queue<std::string> _cache;
};

#endif
