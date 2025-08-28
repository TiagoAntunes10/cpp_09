/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:35:23 by tialbert          #+#    #+#             */
/*   Updated: 2025/08/28 22:16:47 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/includes.hpp"

static bool invalid_date(std::string date, std::map<std::string, float> info) {
  BitcoinExchange::iterator begin = info.begin();
  BitcoinExchange::iterator end = info.end();

  end--;
  if (date.compare(begin->first) < 0 || date.compare(end->first) > 0)
    return true;

  for (unsigned int i = 0; i < date.size(); i++) {
    if (i != 4 && i != 7) {
      if (!std::isdigit(date[i]))
        return true;
    } else {
      if (date[i] != '-')
        return true;
    }
  }

  return false;
}

static bool invalid_num(float num) {
  if (num < 0) {
    std::cout << "Error: not a positive number" << std::endl;
    return true;
  } else if (num > 1000) {
    std::cout << "Error: too large a number" << std::endl;
    return true;
  }

  return false;
}

static BitcoinExchange::iterator find_middle(BitcoinExchange::iterator it,
                                             BitcoinExchange::size_type size) {
  for (BitcoinExchange::size_type i = 0; i < size; i++)
    it++;

  return (it);
}

static BitcoinExchange::iterator
map_bi_search(std::map<std::string, float> info, std::string date) {
  BitcoinExchange::iterator begin = info.begin();
  BitcoinExchange::iterator end = info.end()--;
  BitcoinExchange::size_type size = info.size();
  BitcoinExchange::iterator middle = find_middle(info.begin(), size / 2);
  int i = 2;

  while (middle != begin && middle != end) {
    if (date.compare(middle->first) > 0) {
      middle++;
      begin = middle;
      middle = find_middle(middle, size / i);
      i = i << 1;
    } else if (date.compare(middle->first) < 0) {
      middle--;
      end = middle;
      middle = find_middle(begin, size / i);
      i = i << 1;
    } else
      return (middle);
  }

  return (begin);
}

static void read_data(std::map<std::string, float> info, std::string line) {
  std::string key;
  float value;
  std::string::size_type begin;
  std::string::size_type end;
  BitcoinExchange::iterator it;
  std::string num;
  float result;

  if (line.find(" | ") == std::string::npos) {
    std::cout << "Error: bad input => " << line << std::endl;
    return;
  }

  try {
    key = line.substr(0, line.find(' '));
  } catch (...) {
    std::cout << "Error: bad input => " << line << std::endl;
    return;
  }

  if (invalid_date(key, info)) {
    std::cout << "Error: invalid date => " << line << std::endl;
    return;
  }

  begin = line.rfind(' ') + 1;
  end = line.find_last_of("0123456789");
  num = line.substr(begin, end - begin + 1);

  try {
    value = std::strtof(num.c_str(), 0);
  } catch (...) {
    std::cout << "Error: bad input => " << line << std::endl;
    return;
  }

  if (invalid_num(value)) {
    return;
  }

  it = map_bi_search(info, key);
  result = it->second * value;
  std::cout << key << " => " << value << " = " << result << std::endl;
}

BitcoinExchange::BitcoinExchange(void) { return; }

BitcoinExchange::BitcoinExchange(std::string file) {
  std::ifstream open_file;
  std::string line;
  std::string key;
  float value;
  std::string num;
  std::string::size_type pos;

  try {
    open_file.open(file.c_str());
  } catch (std::exception &e) {
    std::cout << "Error: could not open file" << std::endl;
    throw std::exception();
  }

  std::getline(open_file, line);
  while (std::getline(open_file, line)) {
    key = line.substr(0, line.find(','));
    pos = line.find_last_of("0123456789") - line.find(',') + 1;

    num = line.substr(line.find(',') + 1, pos);
    value = std::strtof(num.c_str(), 0);

    _info.insert(std::pair<std::string, float>(key, value));
  }

  open_file.close();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &bit) {
  std::map<std::string, float>::const_iterator begin = bit._info.begin();
  std::map<std::string, float>::const_iterator end = bit._info.end();

  while (begin != end) {
    this->_info.insert(
        std::pair<std::string, float>(begin->first, begin->second));
    begin++;
  }
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &bit) {
  std::map<std::string, float>::const_iterator begin = bit._info.begin();
  std::map<std::string, float>::const_iterator end = bit._info.end();

  while (begin != end) {
    this->_info.insert(
        std::pair<std::string, int>(begin->first, begin->second));
    begin++;
  }

  return (*this);
}

BitcoinExchange::~BitcoinExchange(void) { return; }

void BitcoinExchange::getInfo(std::string file) {
  if (_info.empty()) {
    std::cout << "BitcoinExchange class is already full" << std::endl;
    throw std::exception();
  }

  std::ifstream open_file;
  std::string line;
  std::string key;
  float value;
  std::string num;
  std::string::size_type pos;

  try {
    open_file.open(file.c_str());
  } catch (std::exception &e) {
    std::cout << "Error: could not open file" << std::endl;
    throw std::exception();
  }

  std::getline(open_file, line);
  while (std::getline(open_file, line)) {
    key = line.substr(0, line.find(','));
    pos = line.find_last_of("0123456789") - line.find(',') + 1;

    num = line.substr(line.find(',') + 1, pos);
    value = std::strtof(num.c_str(), 0);

    _info.insert(std::pair<std::string, float>(key, value));
  }

  open_file.close();
}

void BitcoinExchange::convert(std::string file) {
  std::ifstream open_file;
  std::string line;

  open_file.open(file.c_str());
  if (!open_file.is_open()) {
    std::cout << "Error: could not open file" << std::endl;
    return;
  }

  std::getline(open_file, line);
  while (std::getline(open_file, line))
    read_data(_info, line);

  open_file.close();
}
