#include "../Include/includes.hpp"

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

static int binary_insert(std::list<int> *list_arr, std::list<int> &value,
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

static inline int decision_tree(std::list<int> *main, std::list<int> &inter,
                                int main_size, int last_valid_elem,
                                int last_op) {
  if (main_size < last_valid_elem && !last_op)
    last_op = binary_insert(main, inter, main_size + 1, main_size - 1);
  else if (main_size < last_valid_elem && last_op)
    last_op = binary_insert(main, inter, main_size + 1, main_size - 2);
  else if (!last_op)
    last_op = binary_insert(main, inter, main_size + 1, last_valid_elem - 1);
  else if (last_op)
    last_op = binary_insert(main, inter, main_size + 1, last_valid_elem - 2);

  return (last_op);
}

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

      if (pend_size < j)
        last_op = decision_tree(main, inter[pend_size - 1], main_size,
                                last_valid_elem, last_op);
      else
        last_op = decision_tree(main, inter[j - 1], main_size, last_valid_elem,
                                last_op);

      main_size++;
      pend_size--;
    }
    pend_array_shift(inter, init_pend_size);
    jacobs_it++;
  }

  agg_lists(container, main, num_elem, level);
}

std::list<int> merge_insert_list(std::list<int> &container, int level) {
  int num_elem = container.size() / (1 << level);

  if ((container.size() / (1 << level)) == 1)
    return (container);

  std::list<int> inter[container.size() / (1 << level)];

  split_container(container, inter, level);
  order_elements(inter, num_elem);
  agg_lists(container, inter, num_elem, level);
  merge_insert_list(container, level + 1);

  split_container(container, inter, level);
  merge_sort_elements(container, inter, num_elem, level);

  return (container);
}
