/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2018 Codasip Ltd
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the
 * property of Codasip Ltd and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and
 * proprietary to Codasip Ltd and are protected by trade secret and copyright
 * law.  In addition, elements of the technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this file, may be use, copied, modified, or distributed
 * except in accordance with the terms contained in Codasip license agreement
 * under which you obtained this file.
 *
 *  \file
 *  \author Martin Ministr
 *  \date   8. 10. 2018
 *  \brief  Declaration/Implementation of the class.
 *  \warning  This header is meant to be included only into *.cpp files.
 */

#ifndef INCLUDE_CODASIP_JUMPTHREADING_JTDEBUG_H_
#define INCLUDE_CODASIP_JUMPTHREADING_JTDEBUG_H_

#include <string>

#include "Ir/JTFwd.h"

#define DEBUG_TYPE "codasip-jump-threading"

namespace llvm {
namespace jumpthreading {

// Forward declaration.
class JTGraph;
class JTThreadableNode;

/**
 *  \brief  Provides debugging facility for the JT passes.
 */
class JTDebug {
public:
  /**
   *  \brief  Prints dot representation of JT graph.
   *  \param[in]  G JT graph
   *  \param[in]  FileName Output file
   */
  static void printDot(JTGraph &G, const std::string &FileName);
  /**
   *  \brief  Prints dot representation of threadable node tree.
   *  \param[in]  Tree threadable node tree
   *  \param[in]  FileName Output file
   */
  static void printDot(JTThreadableNode &Tree, const std::string &FileName);

  /// \brief  Get pass count.
  static size_t getPassCount();
  /// \brief  Increment pass count.
  static void incrementPassCount();

private:
  /// Pass count, TODO support multithreading once?
  static size_t PassCount;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline size_t JTDebug::getPassCount() { return PassCount; }

inline void JTDebug::incrementPassCount() { PassCount++; }

} // namespace jumpthreading
} // namespace llvm

#endif // INCLUDE_CODASIP_JUMPTHREADING_JTDEBUG_H_
