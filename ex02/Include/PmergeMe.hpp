/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:34:06 by tialbert          #+#    #+#             */
/*   Updated: 2025/09/01 14:34:50 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_HPP
#define MERGE_HPP

#include <iostream>
#include <list>
#include <vector>

class PmergeMe {
public:
  PmergeMe(void);
  PmergeMe(char **str_arr);
  PmergeMe(PmergeMe const &pmerge);
  PmergeMe &operator=(PmergeMe const &pmerge);
  ~PmergeMe(void);
  void fillContainers(char **str_arr);
  void sortList(void);
  template <class T> void write_container(T begin, T end) {
    while (begin != end) {
      std::cout << *begin << " ";
      begin++;
    };
    std::cout << std::endl;
  }
  // void sortVector(void);

private:
  std::list<int> _list_cont;
  std::vector<int> _vector_cont;
  size_t _size;
};

#endif
