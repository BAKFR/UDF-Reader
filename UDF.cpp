
#include "UDF.hpp"
#include "AVDP.hpp"
#include "VStructDesc.hpp"
#include "Tag.hpp"
#include "PrimaryVDesc.hpp"
#include "PartitionDescriptor.hpp"
#include "LogicalVolumeDescriptor.hpp"
#include <unistd.h>

UDF::UDF(int fd) : fd(fd), avdp(NULL), pvd(NULL), pd(NULL),
				   lvd(NULL)
{
#ifdef NDEBUG
  debug = false;
#else
  debug = true;
#endif
}

bool UDF::loadPartitionDescriptor() {
  if (pd != NULL)
	return true;

  Tag tag = getTagSector(Tag::PartitionDesc);
  if (debug)
	std::cout << "== Load PD ==" << std::endl;

  if (tag.real_location == 0) {
	std::cerr << "Error: partition Descriptor not found" << std::endl;
	return false;
  }

  if ((pd = PartitionDescriptor::loadFromFd(tag, fd)) == NULL) {
	std::cerr << "Error: Unable to load Partition Descriptor" << std::endl;
	return false;
  }

  if (debug)
	std::cout << pd->toString() << std::endl;
  return true;
}

bool UDF::loadLVD() {
  if (lvd != NULL)
	return true;

  Tag tag = getTagSector(Tag::LogicVDesc);
  if (debug)
	std::cout << "== Load LVD ==" << std::endl;

  if (tag.real_location == 0) {
	std::cerr << "Error: Logical Volume Descriptor not found" << std::endl;
	return false;
  }

  if ((lvd = LogicalVolumeDescriptor::loadFromFd(tag, fd)) == NULL) {
	std::cerr << "Error: Unable to load Logical Volume Descriptor" << std::endl;
	return false;
  }

  if (debug)
	std::cout << lvd->toString() << std::endl;
  return true;
}

bool UDF::isValid() {
  bool ret = VStructDesc::checkIsUDF(fd);
  if (debug) {
	std::cout.flags(std::ios_base::boolalpha);
	std::cout << "is it a valid UDF disk ?\t"
			  << ret << std::endl;
  }
  return ret;
}

bool UDF::loadAVDP() {
  if (avdp == NULL) {
	if (debug)
	  std::cout << "Loading AVDP ... " << std::endl;

	avdp = AVDP::getAVDPFromFd(fd);

	if (avdp == NULL) {
	  std::cerr << "Error: Unable to load AVDP sector\n" << std::endl;
	  return false;
	} else if (debug) {
	  std::cout << avdp->toString() << std::endl;
	}
	if (!avdp->isValid()) {
	  std::cerr << "Error: AVDP sector is not valid\n" << std::endl;
	  return false;
	}
  }
  return true;
}

Tag  UDF::getTagSector(int type) {
  if (!loadAVDP())
	return Tag(0);

  extend_ad ext = avdp->getMainVDS();
  unsigned char buffer[16];

  for (uint32_t i = ext.location; i < ext.location + (ext.length / 2048); i++) {
	Tag tag(i);

	if (lseek(fd, i * 2048, SEEK_SET) != i * 2048) {
	  std::cerr << "Error: Unable to seek to sector " << i << std::endl;
	  return Tag(0);
	}

	if (read(fd, buffer, 16) != 16) {
	  std::cerr << "Error: Unable to read sector " << i << std::endl;
	  return Tag(0);
	}

	tag.setData(buffer);

	if (tag.type == type) {
	  if (!tag.isValid()) {
		std::cerr << "Error: Tag Type " << type << " is not valid." << std::endl;
		return Tag(0);
	  }
	  return tag;
	}

	if (tag.type == Tag::TermDesc) {
	  if (debug) {
		std::cout << "Terminating Tag -- Tag " << type << " not found" << std::endl;
	  }
	  return Tag(0);
	}
  }
  if (debug) {
	std::cout << "Terminating Tag -- Tag " << type << " not found" << std::endl;
  }
  return Tag(0);
}

bool UDF::loadInfo() {
  if (pvd != NULL)
	return true;

  Tag tag = getTagSector(Tag::PrimaryVDesc);
  if (debug)
	std::cout << "== Load Info ==" << std::endl;

  if (tag.real_location == 0) {
	std::cerr << "Error: Primary Volume Descriptor not found" << std::endl;
	return false;
  }

  if ((pvd = PrimaryVDesc::loadPVDFromFd(tag, fd)) == NULL) {
	std::cerr << "Error: Unable to load Primary Volume Descriptor" << std::endl;
	return false;
  }

  if (debug)
	std::cout << pvd->toString() << std::endl;
  return true;
}

void UDF::listVDS() {
  if (!loadAVDP())
	return;

  extend_ad ext = avdp->getMainVDS();
  unsigned char buffer[16];

  for (uint32_t i = ext.location; i < ext.location + (ext.length / 2048); i++) {
	Tag tag(i);

	if (lseek(fd, i * 2048, SEEK_SET) != i * 2048) {
	  std::cerr << "Error: Unable to seek to sector " << i << std::endl;
	  return;
	}

	if (read(fd, buffer, 16) != 16) {
	  std::cerr << "Error: Unable to read sector " << i << std::endl;
	  return;
	}

	tag.setData(buffer);
	std::cout << tag.toString()
			  << "valid ? " << tag.isValid() << "\n" << std::endl;

	if (tag.type == Tag::TermDesc) {
	  std::cout << "Terminating Tag" << std::endl;
	  return;
	}
  }

}

UDF::~UDF() {
  close(fd);
}

