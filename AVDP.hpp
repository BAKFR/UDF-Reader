
#pragma once

#include <cstdint>
#include <iostream>
#include "Tag.hpp"

class AVDP {
  Tag tag;
  extend_ad main_VDecSeq;
  extend_ad reserve_VDecSeq;
public:

  AVDP();
  std::string toString() const;
  bool		  isValid() const;
  const extend_ad &getMainVDS() const;

  static AVDP *getAVDPFromFd(int fd);
};
