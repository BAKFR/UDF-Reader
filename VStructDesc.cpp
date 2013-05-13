
#include <iostream>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include "VStructDesc.hpp"


VStructDesc *VStructDesc::readFromFd(int fd) {
  int ret;
  char buffer[2048];
  VStructDesc *desc;

  ret = read(fd, &buffer, 2048);
  if (ret != 2048)
	return NULL;

  desc = new VStructDesc();
  desc->type = buffer[0];
  memcpy(desc->id, &buffer[1], 5);
  desc->id[5] = '\0';
  desc->version = buffer[6];
  memcpy(desc->data, &buffer[7], 2041);
  return desc;
}

std::string VStructDesc::toString() const {
  std::ostringstream oss;

  oss << "Type: " << (int)this->type << "\n";
  oss << "Id: " << this->id << "\n";
  oss << "version: " << (int)this->version << "\n";
  oss << "Data: " << this->type << "\n";
  
  return oss.str();
}

bool	VStructDesc::isBEA() const {
  return !memcmp(this->id, "BEA01", 5);
}

bool	VStructDesc::isTEA() const {
  return !memcmp(this->id, "TEA01", 5);
}

bool	VStructDesc::checkIsUDF(int fd) {
  if (lseek(fd, 32768, SEEK_SET) != 32768)
	return false;

  int nb_remaining_read = MAX_DESCRIPTOR_READ;
  bool has_BEA = false;

  while (nb_remaining_read --> 0) {
	VStructDesc *desc = VStructDesc::readFromFd(fd);
	
	if (desc == NULL)
	  return false;

	//std::cout << desc->toString() << std::endl;

	if (!has_BEA)
	  has_BEA = desc->isBEA();
	else if (desc->isTEA()) {
	  delete desc;
	  return true;
	}
	delete desc;
  }
  return false;
}

std::string	VStructDesc::getVersion(int fd) {
  if (lseek(fd, 32768, SEEK_SET) != 32768)
	return "";

  int nb_remaining_read = MAX_DESCRIPTOR_READ;

  while (nb_remaining_read --> 0) {
	VStructDesc *desc = VStructDesc::readFromFd(fd);
	
	if (desc == NULL)
	  return "";

	if (!strcmp(desc->id, "NSR02"))
	  return "1.02";
	else if (!strcmp(desc->id, "NSR02"))
	  return "1.03";

	if (desc->isTEA()) {
	  delete desc;
	  return "";
	}
	delete desc;
  }
  return "";  
}
