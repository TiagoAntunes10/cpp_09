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

static bool invalid_day(int day, int month, int year) {
  if (day <= 0 || day > 31)
    return true;

  if (month <= 7) {
    if (month == 2) {
      if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        if (day > 29)
          return (true);
      } else {
        if (day > 28)
          return (true);
      }
    } else if (month % 2 == 0) {
      if (day > 30)
        return (true);
    }
  }

  if (month > 7) {
    if (month % 2 != 0) {
      if (day > 30)
        return (true);
    }
  }

  return (false);
}

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

  size_t first_hifen;
  size_t last_hifen;

  first_hifen = date.find_first_of("-");
  last_hifen = date.find_last_of("-");

  int year = atoi(date.substr(0, 4).c_str());
  int month = atoi(date.substr(first_hifen + 1, 2).c_str());
  int day = atoi(date.substr(last_hifen + 1, 2).c_str());

  if (month > 12 || month <= 0)
    return (true);

  if (invalid_day(day, month, year))
    return (true);

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
                                             BitcoinExchange::size_type size,
                                             int direction) {
  if (direction > 0) {
    for (BitcoinExchange::size_type i = 0; i < size; i++)
      it++;
    if (size == 0)
      it++;
  } else {
    for (BitcoinExchange::size_type i = 0; i < size; i++)
      it--;
    if (size == 0)
      it--;
  }

  return (it);
}

static float map_bi_search(std::map<std::string, float> info,
                           std::string date) {
  BitcoinExchange::iterator begin = info.begin();
  BitcoinExchange::iterator end = --info.end();
  BitcoinExchange::size_type size = info.size();
  BitcoinExchange::iterator middle = find_middle(begin, size / 2, 1);

  int i = 2;

  while (middle != begin && middle != end && begin != end) {
    if (date.compare(middle->first) > 0) {
      begin = middle;
      if (i < 2048)
        i = i << 1;
      middle = find_middle(middle, size / i, 1);
    } else if (date.compare(middle->first) < 0) {
      end = middle;
      if (i < 2048)
        i = i << 1;
      middle = find_middle(middle, size / i, -1);
    } else
      return (middle->second);
  }

  return (begin->second);
}

static void read_data(std::map<std::string, float> info, std::string line) {
  std::string key;
  float value = 0;
  std::string::size_type begin;
  std::string::size_type end;
  std::string num;
  float result;
  float price;

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

  price = map_bi_search(info, key);
  result = price * value;
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

  open_file.open(file.c_str());
  if (!open_file.is_open()) {
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
