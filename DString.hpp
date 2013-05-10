
#pragma once

#include "Tag.hpp"

class DString {
  const charspec *charset;
  uint8_t *data;
  int size;

public:
  void	setData(uint8_t *buffer, int size, const charspec *charset);
  std::string	toString() const;
  std::string	getRawString() const;
};

