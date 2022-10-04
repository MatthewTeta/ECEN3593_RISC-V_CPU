/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip s.r.o.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the
 * property of Codasip s.r.o. and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and
 * proprietary to Codasip s.r.o. and are protected by trade secret and copyright
 * law.  In addition, elements of the technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this file, may be use, copied, modified, or distributed
 * except in accordance with the terms contained in Codasip license agreement
 * under which you obtained this file.
 *
 *  \file
 *  \author Martin Ministr
 *  \date   21. 3. 2019
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_OBJECTFILE_CODASIPSECTIONINFO_H_
#define INCLUDE_CODASIP_OBJECTFILE_CODASIPSECTIONINFO_H_

namespace llvm {

/**
 *  \brief  Represents extra Codasip section information.
 */
class CodasipSectionInfo {
public:
  CodasipSectionInfo();

  /**
   *  \{
   *  \brief  Getter.
   */
  unsigned int getVirtualAsIndex() const;
  unsigned int getLoadAsIndex() const;
  unsigned int getOctetsPerByteShift() const;
  /**
   *  \}
   *  \{
   *  \brief  Setter.
   */
  void setVirtualAsIndex(const unsigned int);
  void setLoadAsIndex(const unsigned int);
  /// \}
  /**
   *  \brief  Function to pre-compute octets per byte shift.
   *  \param[in]  bytebitWidth Section byte bit-width
   */
  void determineOctetsPerByteShift(const uint16_t bytebitWidth);
  /**
   *  \brief  Convert between sizes in octets to sizes in bytes.
   *  \param[in]  size
   */
  uint32_t toSize(const uint32_t size) const;

private:
  /// 0 ~ not set, otherwise use 'index - 1' to access address space
  unsigned int VirtualAsIndex;
  /// 0 ~ not set, otherwise use 'index - 1' to access address space
  unsigned int LoadAsIndex;
  /// Octets per byte shift
  unsigned int OctetsPerByteShift;
};

inline CodasipSectionInfo::CodasipSectionInfo()
    : VirtualAsIndex(0), LoadAsIndex(0), OctetsPerByteShift(0) {}

inline unsigned int CodasipSectionInfo::getVirtualAsIndex() const {
  return VirtualAsIndex;
}

inline unsigned int CodasipSectionInfo::getLoadAsIndex() const {
  return LoadAsIndex;
}

inline unsigned int CodasipSectionInfo::getOctetsPerByteShift() const {
  return OctetsPerByteShift;
}

inline void CodasipSectionInfo::setVirtualAsIndex(const unsigned int index) {
  VirtualAsIndex = index;
}

inline void CodasipSectionInfo::setLoadAsIndex(const unsigned int index) {
  LoadAsIndex = index;
}

inline void
CodasipSectionInfo::determineOctetsPerByteShift(const uint16_t bytebitWidth) {
  // determine shift from byte bit-width
  unsigned int cmp = 8;
  unsigned int octets = 0;
  while (bytebitWidth > cmp) {
    cmp *= 2;
    octets += 1;
  }

  OctetsPerByteShift = octets;
}

inline uint32_t CodasipSectionInfo::toSize(const uint32_t size) const {
  return size << getOctetsPerByteShift();
}

} // namespace llvm

#endif // INCLUDE_CODASIP_OBJECTFILE_CODASIPSECTIONINFO_H_
