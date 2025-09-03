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

static bool invalid_int(char const *str) {
  for (; *str != 0; str++) {
    if (*str != '-' && *str != '+' && !std::isdigit(*str))
      return true;
  }

  return false;
}

static void start_containers(char const **arr, std::list<int> &list,
                             std::vector<int> &vector) {
  int num;

  for (; *arr != NULL; arr++) {
    if (invalid_int(*arr))
      throw std::exception();
    num = std::atoi(*arr);
    if (num < 0)
      throw std::exception();

    list.push_back(num);
    vector.push_back(num);
  }
}

static void split_container(std::list<int> const &container,
                            std::list<int> *inter, int level) {
  std::list<int>::const_iterator begin = container.begin();

  for (int i = 0; i < container.size() / (1 << level); i++) {
    for (int j = 0; j < (1 << level); j++) {
      inter[i].push_back(*begin++);
    }
  }
}

static void agg_lists(std::list<int> &container, std::list<int> *inter,
                      int num_elem, int level) {
  std::list<int> agg;
  std::list<int>::const_iterator it_begin = container.begin();
  std::list<int>::const_iterator it_end = container.begin();

  agg.swap(inter[0]);
  for (int i = 1; i < num_elem; i++) {
    std::list<int>::const_iterator begin = inter[i].begin();
    std::list<int>::const_iterator end = inter[i].end();
    std::list<int>::iterator agg_end = agg.end()--;

    agg.insert(agg_end, begin, end);
  }

  for (int i = 0; i < num_elem * (1 << level); i++)
    it_begin++;

  while (it_begin != it_end) {
    agg.push_back(*it_begin);
    it_begin++;
  }

  container.swap(agg);
}

static void order_elements(std::list<int> *inter, int num_elem, int level) {
  for (int i = 1; i < num_elem; i += 2) {
    if (inter[i].back() < inter[i - 1].back())
      inter[i].swap(inter[i - 1]);
  }
}

static void merge_sort_elements(std::list<int> &container,
                                std::list<int> *inter, int num_elem,
                                int level) {
  std::list<int> tmp[num_elem];

  for (int i = 0; i < num_elem; i++) {
    if (i == 0 || i % 2 != 0)
      tmp[i].swap(inter[i]);
  }

  for (int i = 0; i < num_elem; i++) {
  }
}

// TODO: Remember there are ints that are not used in the comparisons
static std::list<int> merge_insert(std::list<int> &container, int level) {
  int num_elem = container.size() / (1 << level);

  if (container.size() / (1 << level) == 1)
    return (container);

  std::list<int> inter[container.size() / (1 << level)];

  split_container(container, inter, level);
  order_elements(inter, num_elem, level);
  agg_lists(container, inter, num_elem, level);
  merge_insert(container, level + 1);

  split_container(container, inter, level);
  merge_sort_elements(container, inter, num_elem, level);

  return (container);
}

PmergeMe::PmergeMe(void) { return; }

PmergeMe::PmergeMe(char const **str_arr) {
  start_containers(str_arr, _list_cont, _vector_cont);
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

void PmergeMe::fillContainers(char const **str_arr) {
  if (_list_cont.empty() && _vector_cont.empty())
    throw std::exception();

  start_containers(str_arr, _list_cont, _vector_cont);
}

void PmergeMe::sortList(void) {}

void PmergeMe::sortVector(void) {}
