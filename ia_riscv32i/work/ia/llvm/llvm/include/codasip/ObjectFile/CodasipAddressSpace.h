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
 *  \date   18. 3. 2019
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_OBJECTFILE_CODASIPADDRESSSPACE_H_
#define INCLUDE_CODASIP_OBJECTFILE_CODASIPADDRESSSPACE_H_

#include <string>

#include "llvm/BinaryFormat/ELF.h"

namespace llvm {

/**
 *  \brief  Represents one address space entry in Codasip ELF.
 */
class CodasipAddressSpace {
public:
  /// Type values, TODO share it with tools enum somehow?
  enum Type { ALL, PROGRAM, DATA };

  CodasipAddressSpace(const std::string &id, const uint16_t type,
                      const uint16_t wbw, const uint16_t bbw,
                      const uint16_t isLittleEndian, const bool isDefault);

  /**
   *  \{
   *  \brief  Getter.
   */
  const std::string &getId() const;
  uint16_t getType() const;
  uint16_t getWordBitWidth() const;
  uint16_t getByteBitWidth() const;
  uint16_t getBytesPerWord() const;
  uint16_t isLittleEndian() const;
  bool isDefault() const;
  /// \}

private:
  /// Address space identifier
  std::string Id;
  /// Type of address space
  uint16_t AsType;
  /// Word bit-width
  uint16_t WordBitWidth;
  /// Byte bit-width
  uint16_t ByteBitWidth;
  /// Is little endian
  uint16_t LittleEndian;
  /// Is default
  bool Default;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline CodasipAddressSpace::CodasipAddressSpace(
    const std::string &id, const uint16_t type, const uint16_t wbw,
    const uint16_t bbw, const uint16_t isLittleEndian, const bool isDefault)
    : Id(id), AsType(type), WordBitWidth(wbw), ByteBitWidth(bbw),
      LittleEndian(isLittleEndian), Default(isDefault) {}

inline const std::string &CodasipAddressSpace::getId() const { return Id; }

inline uint16_t CodasipAddressSpace::getType() const { return AsType; }

inline uint16_t CodasipAddressSpace::getWordBitWidth() const {
  return WordBitWidth;
}

inline uint16_t CodasipAddressSpace::getByteBitWidth() const {
  return ByteBitWidth;
}

inline uint16_t CodasipAddressSpace::getBytesPerWord() const {
  return WordBitWidth / ByteBitWidth;
}

inline uint16_t CodasipAddressSpace::isLittleEndian() const {
  return LittleEndian;
}

inline bool CodasipAddressSpace::isDefault() const { return Default; }

} // namespace llvm

#endif // INCLUDE_CODASIP_OBJECTFILE_CODASIPADDRESSSPACE_H_
