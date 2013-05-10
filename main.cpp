
#include <fcntl.h>
#include "UDF.hpp"

int main(int argc, char **argv) {

  if (argc < 2)
	return 1;

  int fd = open(argv[1], O_RDONLY);

  UDF udf(fd);

  if (!udf.isValid())
	return 1;

  UDF::Info *i = udf.loadInfo();
  long double size = (uint64_t)i->block_size * i->nb_block;
  size /= 1024;
  const char *unit = "KB";

  if (size > 2000) {
	size /= 1024;
	unit = "MB";
  }
  if (size > 2000) {
	size /= 1024;
	unit = "GB";
  }

  std::cout << "\n\nfdisk:\n";
  std::cout << i->volume_id << "\n"
			<< "Record Time: " << i->record_time.toString() << "\n"
			<< "???\n";
  std::cout.precision(3);
  std::cout << "Disk Size:\t" << size << unit << "\n"
			<< "????\n"
			<< "\n";
}
