
#include "DString.hpp"
#include <cstring>
#include <sstream>

void	DString::setData(uint8_t *buffer, int size, const charspec *charset) {
  this->charset = charset;
  this->size = size;
  data = new uint8_t[size + 1];
  memcpy(data, buffer, size);
  data[size] = '\0';
}

std::string DString::getRawString() const {
  if (!size)
	return "";
  if (charset->type == 0 &&
	  strcmp((char*) charset->data, "OSTA Compressed Unicode") == 0) {
	if (data[0] != 16)
	  return (char*) data + 1;
	else {
	  char *str = new char[size / 2 + 1];
	  for (int i = 1; i < size; i += 2) {
		str[i / 2] = data[i + 1];
	  }
	  str[size / 2] = '\0';
	  return str;
	}
  }
  return (char*) data;
}

std::string	DString::toString() const {
  std::ostringstream oss;
	
  oss << "`" << getRawString() << "`";

  return oss.str();
}

const charspec	*DString::getCharset() const
{
  return charset;
}

int	       DString::getSize() const
{
  return size;
}
