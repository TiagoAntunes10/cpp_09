/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:33:48 by tialbert          #+#    #+#             */
/*   Updated: 2025/08/28 17:04:13 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/includes.hpp"

int main(int argc, char **argv) {
  try {
    BitcoinExchange btc("data.csv");

    if (argc > 2) {
      std::cout << "Error: Incorrect number of inputs" << std::endl;
      return (1);
    } else if (argc < 2) {
      std::cout << "Error: could not open file" << std::endl;
      return (1);
    }

    btc.convert(argv[1]);
  } catch (...) {
    return (1);
  }
}
