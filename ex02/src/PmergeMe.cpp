/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:35:09 by tialbert          #+#    #+#             */
/*   Updated: 2025/09/01 14:35:24 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/includes.hpp"
// TODO: Remove this library
#include <algorithm>
#include <ctime>

static bool invalid_int(char const *str) {
  for (; *str != 0; str++) {
    if (*str != '-' && *str != '+' && !std::isdigit(*str))
      return true;
  }

  return false;
}

static void start_containers(char **arr, std::list<int> &list,
                             std::vector<int> &vector, size_t &size) {
  int num;

  size = 0;

  for (; *arr != NULL; arr++) {
    if (invalid_int(*arr))
      throw std::exception();
    num = std::atoi(*arr);
    if (num < 0)
      throw std::exception();

    list.push_back(num);
    vector.push_back(num);
    size++;
  }
}

PmergeMe::PmergeMe(void) { return; }

PmergeMe::PmergeMe(char **str_arr) {
  try {
    start_containers(str_arr, _list_cont, _vector_cont, _size);
  } catch (std::exception &e) {
    std::cout << "Error" << std::endl;
    throw e;
  }
}

// TODO: Ensure this does a deep copy
PmergeMe::PmergeMe(PmergeMe const &pmerge) {
  this->_list_cont = pmerge._list_cont;
  this->_vector_cont = pmerge._vector_cont;
}

// TODO: Ensure this does a deep copy
PmergeMe &PmergeMe::operator=(PmergeMe const &pmerge) {
  this->_list_cont = pmerge._list_cont;
  this->_vector_cont = pmerge._vector_cont;

  return (*this);
}

PmergeMe::~PmergeMe(void) { return; }

void PmergeMe::fillContainers(char **str_arr) {
  if (_list_cont.empty() && _vector_cont.empty())
    throw std::exception();

  try {
    start_containers(str_arr, _list_cont, _vector_cont, _size);
  } catch (std::exception &e) {
    std::cout << "Error" << std::endl;
    throw e;
  }
}

// NOTE: Delete later or make it "silent"/comment
template <class T>
int check_sorting(T begin, T end, T cpy_begin, T cpy_end, size_t size1,
                  size_t size2) {
  T step = begin;
  T it;

  step++;

  if (size1 != size2)
    return (3);

  for (; cpy_begin != cpy_end; cpy_begin++) {
    it = std::find(begin, end, *cpy_begin);
    if (it == end)
      return (1);
  }

  while (step != end) {
    if (*step < *begin) {
      std::cout << BLUE << *step << " < " << *begin << " - " << END;
      return (2);
    }

    begin++;
    step++;
  }

  return (0);
}

static inline float running_time(clock_t start) {
  float duration;
  clock_t end = clock();

  duration = float(end - start) / CLOCKS_PER_SEC * 1000;

  return (duration);
}

static inline void write_run_information(std::string type, size_t size,
                                         float duration) {
  std::cout << "Time to process a range of " << size
            << " elements with std::" << type << ": " << duration << " ms"
            << std::endl;
}

void PmergeMe::sortList(void) {
  clock_t start;
  float duration;

  std::cout << "before: ";
  write_container(_list_cont.begin(), _list_cont.end());

  std::list<int> cpy = _list_cont;

  start = clock();
  _list_cont = merge_insert_list(_list_cont, 0);

  duration = running_time(start);

  int error = check_sorting(_list_cont.begin(), _list_cont.end(), cpy.begin(),
                            cpy.end(), _list_cont.size(), cpy.size());
  if (error == 1)
    std::cout << RED << "One element is missing" << END << std::endl;
  else if (error == 2)
    std::cout << RED << "Sorting is wrong" << END << std::endl;
  else if (error == 3)
    std::cout << RED << "Size was changed" << END << std::endl;
  std::cout << "after: ";
  write_container(_list_cont.begin(), _list_cont.end());

  write_run_information("list", _size, duration);
}

void PmergeMe::sortVector(void) {
  clock_t start;
  float duration;

  std::vector<int> cpy = _vector_cont;

  start = clock();
  _vector_cont = merge_insert_vector(_vector_cont, 0);

  duration = running_time(start);

  int error =
      check_sorting(_vector_cont.begin(), _vector_cont.end(), cpy.begin(),
                    cpy.end(), _vector_cont.size(), cpy.size());
  if (error == 1)
    std::cout << RED << "One element is missing" << END << std::endl;
  else if (error == 2)
    std::cout << RED << "Sorting is wrong" << END << std::endl;
  else if (error == 3)
    std::cout << RED << "Size was changed" << END << std::endl;

  write_run_information("vector", _size, duration);
}
