
#include "UDF.hpp"
#include "AVDP.hpp"
#include "VStructDesc.hpp"
#include "Tag.hpp"
#include "PrimaryVDesc.hpp"
#include "PartitionDescriptor.hpp"
#include "LogicalVolumeDescriptor.hpp"
#include "UnallocSpaceDesc.hpp"
#include <unistd.h>

UDF::UDF(int fd) : fd(fd), avdp(NULL), pvd(NULL), pd(NULL),
				   lvd(NULL), usd(NULL)
{
#ifdef NDEBUG
  debug = false;
#else
  debug = true;
#endif
}

bool UDF::loadPD() {
  if (this->pd != NULL)
	return true;

  PartitionDescriptor *pd;

  pd = loadDescriptor<PartitionDescriptor>(Tag::PartitionDesc);
  this->pd = pd;

  if (debug)
	std::cout << pd->toString() << std::endl;

  return pd != NULL;
}

bool UDF::loadLVD() {
  if (this->lvd != NULL)
	return true;

  LogicalVolumeDescriptor *lvd;

  lvd = loadDescriptor<LogicalVolumeDescriptor>(Tag::LogicVDesc);
  if (lvd) {
	int length_pm = lvd->getLengthPM();

	uint8_t *buffer = new uint8_t[length_pm];
	if (read(fd, buffer, length_pm) != length_pm) {
	  std::cerr << "Error: Unable to read partition maps from LVD" << std::endl;
	  delete lvd;
	  delete[] buffer;
	  return NULL;
	}
	lvd->loadPartitionMaps(buffer);
	delete[] buffer;
  }
  this->lvd = lvd;

  if (debug)
	std::cout << lvd->toString() << std::endl;

  return lvd != NULL;
}

bool UDF::loadUSD() {
  if (this->usd != NULL)
	return true;

  UnallocSpaceDesc *usd;

  usd = loadDescriptor<UnallocSpaceDesc>(Tag::UnallocSpDesc);
  if (usd) {
	int length = usd->getNbAllocDescs() * 8;
  
	uint8_t *buffer = new uint8_t[length];
	if (read(fd, buffer, length) != length) {
	  std::cerr << "Error: Unable to read Allocation Descriptors"
				<< " from USD" << std::endl;
	  delete usd;
	  delete[] buffer;
	  return NULL;
	}
	usd->loadAllocationDescs(buffer);
	delete[] buffer;
  }
  this->usd = usd;

  if (debug)
	std::cout << usd->toString() << std::endl;

  return usd != NULL;
}

bool UDF::loadPVD() {
  if (this->pvd != NULL)
	return true;

  PrimaryVDesc *pvd;

  pvd = loadDescriptor<PrimaryVDesc>(Tag::PrimaryVDesc);
  this->pvd = pvd;

  if (debug)
	std::cout << pvd->toString() << std::endl;
  return pvd != NULL;
}

template <typename T>
T *UDF::loadDescriptor(Tag::Type type) {

  T *descriptor = new T();

  Tag tag = getTagSector(type);
  if (debug)
	std::cout << "== Load Descriptor ==" << std::endl;

  if (tag.real_location == 0) {
	std::cerr << "Error: " << descriptor->getName()
			  << " not found" << std::endl;
	delete descriptor;
	return NULL;
  }

  if (!descriptor->loadFromFd(tag, fd)) {
	std::cerr << "Error: Unable to load "
			  << descriptor->getName() << std::endl;
	delete descriptor;
	return NULL;
  }

  return descriptor;
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

UDF::Info *UDF::loadInfo() {
  if (!loadPVD()
	  || !loadPD()
	  || !loadLVD()
	  || !loadUSD())
	return NULL;

  Info *info = new Info();

  info->volume_id = lvd->getVolumeID();
  info->record_time = pvd->getTimestamp();
  //
  info->block_size = lvd->getBlockSize();
  info->nb_block = pd->getPartition().length;
  info->free_size = usd->getFreeSpace();
  //

  return info;
}

void	UDF::listMVDS() {
  if (!loadAVDP())
	return;

  listVDS(avdp->getMainVDS());
}

void	UDF::listPartition() {
  if (!loadPVD()
	  || !loadPD()
	  || !loadLVD())
	return;

  std::cout << "\n\n\n";
  listVDS(pd->getPartition());
}

void UDF::listVDS(const extend_ad &ext) {
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

