/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:34:38 by tialbert          #+#    #+#             */
/*   Updated: 2025/08/28 22:05:15 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIT_HPP
#define BIT_HPP

#include <iostream>
#include <map>

class BitcoinExchange {
public:
  typedef std::map<std::string, float>::iterator iterator;
  typedef std::map<std::string, float>::size_type size_type;

  BitcoinExchange(void);
  BitcoinExchange(std::string file);
  BitcoinExchange(BitcoinExchange const &bit);
  BitcoinExchange &operator=(BitcoinExchange const &bit);
  ~BitcoinExchange(void);
  void getInfo(std::string file);
  void convert(std::string file);

private:
  std::map<std::string, float> _info;
};

#endif
