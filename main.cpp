
#include <fcntl.h>
#include "Prompt.hpp"

int main(int argc, char **argv) {
  Prompt prompt(argc, argv);
  prompt.run();
  return 0;
}
