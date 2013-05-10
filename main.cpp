
#include <fcntl.h>
#include "UDF.hpp"

int main(int argc, char **argv) {

  if (argc < 2)
	return 1;

  int fd = open(argv[1], O_RDONLY);

  UDF udf(fd);

  udf.isValid();
  //udf.listVDS();
  udf.loadInfo();
  udf.loadPartitionDescriptor();
  udf.loadLVD();
}
