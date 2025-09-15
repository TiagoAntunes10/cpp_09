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
    if (!inter[i].empty())
      inter[i].clear();
    for (int j = 0; j < (1 << level); j++) {
      inter[i].push_back(*begin++);
    }
  }
}

static void agg_lists(std::list<int> &container, std::list<int> *inter,
                      int num_elem, int level) {
  std::list<int> agg;
  std::list<int>::const_iterator it_begin = container.begin();
  std::list<int>::const_iterator it_end = container.end();

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

// TODO: Clean commented lines
static int binary_insert(std::list<int> *list_arr, std::list<int> &value,
                         int main_size, int last_valid_elem) {
  int begin = 0;
  int end = last_valid_elem;
  int middle = (end + begin) / 2;

  // std::cout << BLUE << "Value: " << END << value.back() << "; ";
  // std::cout << BLUE << "Last valid: " << END << last_valid_elem << std::endl;
  //
  while (begin < end && list_arr[middle].back() != value.back()) {
    if (list_arr[middle].back() > value.back())
      end = middle - 1;
    else if (list_arr[middle].back() < value.back())
      begin = middle + 1;
    middle = (end + begin) / 2;
    // std::cout << GREEN << "Begin: " << END << begin << "; ";
    // std::cout << GREEN << "Middle: " << END << middle << "; ";
    // std::cout << GREEN << "End: " << END << end << std::endl;
  }

  if (list_arr[middle].back() < value.back())
    middle++;

  while (main_size > middle) {
    if (!list_arr[main_size - 1].empty())
      list_arr[main_size].swap(list_arr[main_size - 1]);
    main_size--;
  }

  list_arr[middle].swap(value);

  if (begin > last_valid_elem)
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

// FIX: With >= 7 elements some numbers go missing and other numbers repeat
// (copies have a problem)
static void merge_sort_elements(std::list<int> &container,
                                std::list<int> *inter, int num_elem,
                                int level) {
  std::list<int> main[num_elem];

  int pend_size;
  int main_size = num_elem / 2 + 1;
  int main_index = 0;

  if (!(num_elem % 2))
    pend_size = num_elem / 2 - 1;
  else
    pend_size = num_elem / 2;

  for (int i = 0; i < num_elem; i++) {
    if (i == 0 || i % 2 != 0)
      main[main_index++].swap(inter[i]);
    else
      inter[i].swap(inter[main_index - 2]);
  }

  int jacobs_it = 0;
  int init_main_size = main_size;
  int init_pend_size = pend_size;

  while (pend_size) {
    int jacobs_num = jacobs_gen(jacobs_it + 3);
    int last_valid_elem = jacobs_num + (main_size - init_main_size);
    int last_op = 0;

    for (int j = jacobs_num - jacobs_gen(jacobs_it + 2); j > 0 && pend_size > 0;
         j--) {

      if (pend_size < j) {
        if (main_size < last_valid_elem && !last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size + 1,
                                  main_size - 1);
        else if (main_size < last_valid_elem && last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size + 1,
                                  main_size - 2);
        else if (!last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size + 1,
                                  last_valid_elem - 1);
        else if (last_op)
          last_op = binary_insert(main, inter[pend_size - 1], main_size + 1,
                                  last_valid_elem - 2);
      } else {
        if (main_size < jacobs_num && !last_op)
          last_op =
              binary_insert(main, inter[j - 1], main_size + 1, main_size - 1);
        else if (main_size < jacobs_num && last_op)
          last_op =
              binary_insert(main, inter[j - 1], main_size + 1, main_size - 2);
        else if (!last_op)
          last_op = binary_insert(main, inter[j - 1], main_size + 1,
                                  last_valid_elem - 1);
        else if (last_op)
          last_op = binary_insert(main, inter[j - 1], main_size + 1,
                                  last_valid_elem - 2);
      }

      main_size++;
      pend_size--;
    }
    pend_array_shift(inter, init_pend_size);
    jacobs_it++;
  }

  agg_lists(container, main, num_elem, level);
}

// TODO: Remember there are ints that are not used in the comparisons
static std::list<int> merge_insert(std::list<int> &container, int level) {
  int num_elem = container.size() / (1 << level);

  if ((container.size() / (1 << level)) == 1)
    return (container);

  std::list<int> inter[container.size() / (1 << level)];

  split_container(container, inter, level);
  order_elements(inter, num_elem);
  agg_lists(container, inter, num_elem, level);
  merge_insert(container, level + 1);

  // std::cout << RED << level << " - " << container.size() / (1 << level) <<
  // END
  //           << std::endl;

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

// NOTE: Delete later or make it "silent"/comment
static int check_sorting(std::list<int> &cont, std::list<int> &cpy) {
  std::list<int>::iterator begin = cont.begin();
  std::list<int>::iterator step = cont.begin();
  std::list<int>::iterator end = cont.end();
  std::list<int>::iterator cpy_begin = cpy.begin();
  std::list<int>::iterator cpy_end = cpy.end();
  std::list<int>::iterator it;

  step++;

  if (cont.size() != cpy.size())
    return (3);

  for (; cpy_begin != cpy_end; cpy_begin++) {
    it = std::find(cont.begin(), end, *cpy_begin);
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

void PmergeMe::sortList(void) {
  std::cout << "before: ";
  write_container(_list_cont.begin(), _list_cont.end());

  std::list<int> cpy = _list_cont;

  _list_cont = merge_insert(_list_cont, 0);

  int error = check_sorting(_list_cont, cpy);
  if (error == 1)
    std::cout << RED << "One element is missing" << END << std::endl;
  else if (error == 2)
    std::cout << RED << "Sorting is wrong" << END << std::endl;
  else if (error == 3)
    std::cout << RED << "Size was changed" << END << std::endl;
  std::cout << "after: ";
  write_container(_list_cont.begin(), _list_cont.end());
}

// void PmergeMe::sortVector(void) {}
