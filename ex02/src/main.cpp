/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:31:48 by tialbert          #+#    #+#             */
/*   Updated: 2025/09/01 14:33:57 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/includes.hpp"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Error" << std::endl;
    return (1);
  }

  try {
    PmergeMe merge(++argv);

    merge.sortList();
    merge.sortVector();
  } catch (...) {
    return (1);
  }
}
