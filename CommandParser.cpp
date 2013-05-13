#include <iostream>
#include "UDF.hpp"
#include "CommandParser.hpp"
#include "ParseLinkFDISK.hpp"
#include "ParseLinkEXIT.hpp"
#include "ParseLinkDIR.hpp"
#include "ParseLinkCD.hpp"
#include "ParseLinkCP.hpp"

CommandParser::CommandParser() {
  chainOfResponsibility = new ParseLinkFDISK;
  chainOfResponsibility->next = new ParseLinkCP;
  chainOfResponsibility->next->next = new ParseLinkEXIT;
  chainOfResponsibility->next->next->next = new ParseLinkDIR;
  chainOfResponsibility->next->next->next->next = new ParseLinkCD;
}

Command *CommandParser::parse(std::string commandString) {
  ParseLink *pl;

  pl = chainOfResponsibility;
  while (pl != NULL) {
    if (pl->test(commandString)) {
      return pl->parse(commandString);
    }
    pl = pl->next;
  }
  std::cout<<"Unrecognized command."<<std::endl;
  return NULL;
}

bool CommandParser::execute(FileSystemTree &tree, Command *command, UDF *udf) {
  return command->execute(tree, *udf);
}
