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

static void start_containers(char **arr, std::list<int> &list,
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
  int num_elem = container.size() / (1 << level);

  for (int i = 0; i < num_elem; i++) {
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

static void order_elements(std::list<int> *inter, int num_elem) {
  for (int i = 1; i < num_elem; i += 2) {
    if (inter[i].back() < inter[i - 1].back())
      inter[i].swap(inter[i - 1]);
  }
}

static int jacobs_gen(int order) {
  int jacobs;

  if (order == 0)
    return (0);
  if (order == 1)
    return (1);
  jacobs = jacobs_gen(order - 1) + 2 * jacobs_gen(order - 2);

  return (jacobs);
}

static int binary_insert(std::list<int> *list_arr, std::list<int> value,
                         int main_size, int last_valid_elem) {
  int begin = 0;
  int end = last_valid_elem;
  int middle = (end + begin) / 2;

  while (begin < end && list_arr[middle].back() != value.back()) {
    if (list_arr[middle].back() > value.back())
      end = middle - 1;
    else if (list_arr[middle].back() < value.back())
      begin = middle + 1;
    middle = (end + begin) / 2;
    if (begin > end)
      middle = begin;
  }

  while (main_size > middle) {
    if (!list_arr[main_size - 1].empty())
      list_arr[main_size].swap(list_arr[main_size - 1]);
    main_size--;
  }

  list_arr[middle].swap(value);

  if (begin > end)
    return (1);
  else
    return (0);
}

static void pend_array_shift(std::list<int> *pend_arr, int total_size) {
  int trailer = 0;

  for (int i = 0; i < total_size; i++) {
    if (!pend_arr[i].empty())
      pend_arr[i].swap(pend_arr[trailer++]);
  }
}

static void merge_sort_elements(std::list<int> &container,
                                std::list<int> *inter, int num_elem,
                                int level) {
  std::list<int> main[num_elem];
  int pend_size = num_elem / 2;
  int main_size = num_elem / 2 + num_elem % 2;
  int last_op = 0;
  int main_index = 0;

  for (int i = 0; i < num_elem; i++) {
    if (i == 0 || i % 2 != 0)
      main[main_index++].swap(inter[i]);
    else
      inter[i].swap(inter[main_index - 2]);
  }

  int jacobs_it = 0;
  int init_main_size = main_size;

  while (pend_size) {
    int jacobs_num = jacobs_gen(jacobs_it + 3);
    int last_valid_elem = jacobs_num + (init_main_size - main_size);

    for (int j = jacobs_gen(jacobs_it + 3) - jacobs_gen(jacobs_it + 2);
         j > 0 && pend_size > 0; j--) {

      if (pend_size < j) {
        if (main_size < last_valid_elem && !last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size,
                                  main_size - 1);
        else if (main_size < last_valid_elem && last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size,
                                  main_size - 2);
        else if (!last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size,
                                  jacobs_num - 1);
        else if (last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size,
                                  jacobs_num - 2);
      }

      if (main_size < jacobs_num && !last_op)
        last_op = binary_insert(main, inter[j - 1], main_size, main_size - 1);
      else if (main_size < jacobs_num && last_op)
        last_op = binary_insert(main, inter[j - 1], main_size, main_size - 2);
      if (!last_op)
        last_op = binary_insert(main, inter[j - 1], main_size, jacobs_num - 1);
      else
        last_op = binary_insert(main, inter[j - 1], main_size, jacobs_num - 2);

      main_size++;
      pend_size--;
    }
    pend_array_shift(inter, num_elem / 2);
    jacobs_it++;
  }

  agg_lists(container, main, num_elem, level);
}

// TODO: Remember there are ints that are not used in the comparisons
static std::list<int> merge_insert(std::list<int> &container, int level) {
  int num_elem = container.size() / (1 << level);

  if (container.size() / (1 << level) == 1)
    return (container);

  std::list<int> inter[container.size() / (1 << level)];

  split_container(container, inter, level);
  order_elements(inter, num_elem);
  agg_lists(container, inter, num_elem, level);
  merge_insert(container, level + 1);

  split_container(container, inter, level);
  merge_sort_elements(container, inter, num_elem, level);

  return (container);
}

PmergeMe::PmergeMe(void) { return; }

PmergeMe::PmergeMe(char **str_arr) {
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

void PmergeMe::fillContainers(char **str_arr) {
  if (_list_cont.empty() && _vector_cont.empty())
    throw std::exception();

  start_containers(str_arr, _list_cont, _vector_cont);
}

void PmergeMe::sortList(void) {
  std::cout << "before: ";
  write_container(_list_cont.begin(), _list_cont.end());

  _list_cont = merge_insert(_list_cont, 0);

  std::cout << "after: ";
  write_container(_list_cont.begin(), _list_cont.end());
}

// void PmergeMe::sortVector(void) {}
