#include "UDF.hpp"
#include <iostream>
#include "CommandFDISK.hpp"

bool CommandFDISK::execute(FileSystemTree &tree, UDF& udf) {
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

  std::cout<<"\n\nfdisk:\n";
  std::cout<<i->volume_id<<"\n"
	   <<"Record Time: "<<i->record_time.toString()<<"\n"
	   <<"UDF version: "<<i->version<<"\n";
  std::cout.precision(3);
  std::cout<<"Disk Size:\t"<<size<<unit<<"\n"
	   <<"Disk Free size:\t"<<free_size<<free_unit<<"\n\n\n";

  std::cout<<"Command FDISK executed."<<std::endl;
  return true;
}
