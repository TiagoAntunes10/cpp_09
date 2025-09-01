/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:19:50 by tialbert          #+#    #+#             */
/*   Updated: 2025/08/30 09:20:03 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/includes.hpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Error: Wrong number of arguments" << std::endl;
    return (1);
  }

  try {
    std::cout << RPN::calculate(argv[1]) << std::endl;
  } catch (...) {
    return (1);
  }
}
