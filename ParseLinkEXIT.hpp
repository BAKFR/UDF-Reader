#pragma

#include "ParseLink.hpp"
#include "Command.hpp"
#include <string>

class ParseLinkEXIT : public ParseLink {
public:
  virtual bool test(std::string stringCommand);
  virtual Command* parse(std::string stringCommand);
};
