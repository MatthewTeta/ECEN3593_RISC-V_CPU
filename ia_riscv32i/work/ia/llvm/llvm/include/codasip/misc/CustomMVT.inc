/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2018 Codasip Ltd
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the property of Codasip Ltd
 * and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and proprietary to
 * Codasip Ltd and are protected by trade secret and copyright law.  In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author jan
 *  \date   19 Feb 2018
 *  \brief  Declaration/Implementation of the class.
 */

// note: this needs to included by preprocessor, placing this in a codasip lib wouldn't work

namespace llvm {

static inline unsigned getCustomSizeInBits(MVT VT)
{
  switch (VT.SimpleTy)
  {
    case MVT::i256:
    case MVT::v2i128: case MVT::v256i1:
      return 256;
    case MVT::i512:
    case MVT::v4i128:
      return 512;
    case MVT::i1024:
    case MVT::v8i128:
      return 1024;
    case MVT::i2048:
    case MVT::v16i128: case MVT::v2048i1:
      return 2048;
    default: ;
  }
  // same as in caller
  llvm_unreachable("getSizeInBits called on extended MVT.");
}

static MVT getCustomVectorVT(MVT VT, unsigned NumElements)
{
  switch (VT.SimpleTy)
  {
    case MVT::i1:
      switch (NumElements)
      {
        case 256: return MVT::v256i1;
        case 2048: return MVT::v2048i1;
        default: break;
      }
      break;
    case MVT::i128:
      switch (NumElements)
      {
        case 2:  return MVT::v2i128;
        case 4:  return MVT::v4i128;
        case 8:  return MVT::v8i128;
        case 16: return MVT::v16i128;
        default: break;
      }
      break;
    default: ;
  }
  // same as in getVectorVT
  return MVT::INVALID_SIMPLE_VALUE_TYPE;
}

static inline MVT getCustomVectorElementType(MVT VT)
{
  switch (VT.SimpleTy)
  {
    case MVT::v256i1:
    case MVT::v2048i1: return MVT::i1;
    case MVT::v2i128:
    case MVT::v4i128:
    case MVT::v8i128:
    case MVT::v16i128: return MVT::i128;
    default:
      llvm_unreachable("getVectorElementType: Not a vector MVT!");
  }
}

static inline unsigned getCustomVectorNumElements(MVT VT)
{
  switch (VT.SimpleTy)
  {
    case MVT::v2i128: return 2;
    case MVT::v4i128: return 4;
    case MVT::v8i128: return 8;
    case MVT::v16i128: return 16;
    case MVT::v256i1: return 256;
    case MVT::v2048i1: return 2048;
    default:
      llvm_unreachable("getVectorNumElements: Not a vector MVT!");
  }
}

}//namespace llvm
