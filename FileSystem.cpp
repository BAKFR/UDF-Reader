
#include "FileSystem.hpp"
#include "FileSetDesc.hpp"

FileSystem::FileSystem(const extend_ad &from, int block_size, int fd)
  : location(from), block_size(block_size), fd(fd), root(NULL)
{
}

bool	FileSystem::loadRoot() {
  if (root)
	return true;

  root = loadDescriptor<FileSetDesc>(Tag::FileSetDesc);

  if (!root)
	return false;
  std::cout << root->toString() << std::endl;
  return true;
}


template <typename T>
T *FileSystem::loadDescriptor(Tag::Type type) {

  T *descriptor = new T();

  Tag tag = getTagSector(type);

  if (tag.type == 0) {
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

Tag  FileSystem::getTagSector(int type) {

  extend_ad ext = location;
  unsigned char buffer[16];

  for (uint32_t i = ext.location; i < ext.location + ext.length; i++) {
	Tag tag(i - ext.location);

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
	  if (true) {
		std::cout << "Terminating Tag -- Tag " << type << " not found" << std::endl;
	  }
	  return Tag(0);
	}
  }
  if (true) {
	std::cout << "Terminating Tag -- Tag " << type << " not found" << std::endl;
  }
  return Tag(0);
}
