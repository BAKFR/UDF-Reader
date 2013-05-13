
#include <fcntl.h>
#include "UDF.hpp"
#include "FileSystem.hpp"

int main(int argc, char **argv) {

  if (argc < 2)
	return 1;

  int fd = open(argv[1], O_RDONLY);

  UDF udf(fd);

  if (!udf.isValid())
	return 1;

  UDF::Info *i = udf.loadInfo();
  long double size = (uint64_t)i->block_size * i->nb_block;
  long double free_size = (uint64_t)i->free_size * i->nb_block;
  size /= 1024;
  free_size /= 1024;
  const char *unit = "KB";
  const char *free_unit = "KB";

  if (size > 2000) {
	size /= 1024;
	unit = "MB";
  }
  if (size > 2000) {
	size /= 1024;
	unit = "GB";
  }

  if (free_size > 2000) {
	free_size /= 1024;
	free_unit = "MB";
  }
  if (free_size > 2000) {
	free_size /= 1024;
	free_unit = "GB";
  }

  std::cout << "\n\nfdisk:\n";
  std::cout << i->volume_id << "\n"
			<< "Record Time: " << i->record_time.toString() << "\n"
			<< "UDF Version: " << i->version << "\n";
  std::cout.precision(3);
  std::cout << "Disk Size:\t" << size << unit << "\n"
			<< "Disk Free Size:\t" << free_size << free_unit << "\n"
			<< "\n\n";

  udf.listPartition();

  FileSystem fs(udf.getPartition(), udf.getSizeBlock(), fd);

  fs.loadRoot();
  //udf.listMVDS();
}
