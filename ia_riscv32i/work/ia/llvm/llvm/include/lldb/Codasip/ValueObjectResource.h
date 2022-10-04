//===-- ValueObjectResource.h -----------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_ValueObjectResource_h_
#define liblldb_ValueObjectResource_h_

#include "lldb/Codasip/Resource.h"    // for ResourceValue
#include "lldb/Core/ValueObject.h"
#include "lldb/Symbol/CompilerType.h" // for CompilerType
#include "lldb/Utility/ConstString.h" // for ConstString
#include "lldb/lldb-defines.h"        // for DISALLOW_COPY_AND_ASSIGN
#include "lldb/lldb-enumerations.h"   // for ValueType, ValueType::eValueTy...
#include "lldb/lldb-forward.h"        // for RegisterContextSP, ValueObjectSP
#include "lldb/lldb-private-types.h"  // for RegisterInfo, RegisterSet (ptr...

#include <stddef.h> // for size_t
#include <stdint.h> // for uint32_t, uint64_t, int32_t

namespace lldb_private {
class DataExtractor;
}
namespace lldb_private {
class Status;
}
namespace lldb_private {
class ExecutionContextScope;
}
namespace lldb_private {
class Scalar;
}
namespace lldb_private {
class Stream;
}

namespace lldb_private {

class ValueObjectResourceSet : public ValueObject {
public:
  ~ValueObjectResourceSet() override;

  static lldb::ValueObjectSP Create(ExecutionContextScope *exe_scope,
                                    codasip::ResourceContextSP &resource_ctx_sp,
                                    uint32_t set_idx);

  uint64_t GetByteSize() override;

  lldb::ValueType GetValueType() const override {
    return lldb::eValueTypeRegisterSet; // TODO new enum type?
  }

  ConstString GetTypeName() override;

  ConstString GetQualifiedTypeName() override;

  size_t CalculateNumChildren(uint32_t max) override;

  ValueObject *CreateChildAtIndex(size_t idx, bool synthetic_array_member,
                                  int32_t synthetic_index) override;

  lldb::ValueObjectSP GetChildMemberWithName(ConstString name,
                                             bool can_create) override;

  size_t GetIndexOfChildWithName(ConstString name) override;

protected:
  bool UpdateValue() override;

  CompilerType GetCompilerTypeImpl() override;

  codasip::ResourceContextSP m_resource_ctx_sp;
  const codasip::ResourceSet *m_resource_set;
  uint32_t m_resource_set_idx;

private:
  friend class ValueObjectResourceContext;

  ValueObjectResourceSet(ExecutionContextScope *exe_scope,
                         codasip::ResourceContextSP &resource_ctx_sp, uint32_t set_idx);

  //------------------------------------------------------------------
  // For ValueObject only
  //------------------------------------------------------------------
  DISALLOW_COPY_AND_ASSIGN(ValueObjectResourceSet);
};

class ValueObjectResource : public ValueObject {
public:
  ~ValueObjectResource() override;

  static lldb::ValueObjectSP Create(ExecutionContextScope *exe_scope,
                                    codasip::ResourceContextSP &resource_ctx_sp,
                                    uint32_t resource_num);

  uint64_t GetByteSize() override;
  lldb::ValueType GetValueType() const override;

  ConstString GetTypeName() override;

  size_t CalculateNumChildren(uint32_t max) override;

  bool SetValueFromCString(const char *value_str, Status &error) override;

  bool SetData(DataExtractor &data, Status &error) override;

  bool ResolveValue(Scalar &scalar) override;

  void
  GetExpressionPath(Stream &s, bool qualify_cxx_base_classes,
                    GetExpressionPathFormat epformat =
                        eGetExpressionPathFormatDereferencePointers) override;

protected:
  bool UpdateValue() override;

  CompilerType GetCompilerTypeImpl() override;

  codasip::ResourceContextSP m_resource_ctx_sp;
  codasip::Resource m_resource;
  codasip::ResourceValue m_resource_value;
  ConstString m_type_name;
  CompilerType m_compiler_type;

private:
  void ConstructObject(uint32_t resource_num);

  friend class ValueObjectResourceSet;

  ValueObjectResource(ValueObject &parent, codasip::ResourceContextSP &resource_ctx_sp,
                      uint32_t resource_num);
  ValueObjectResource(ExecutionContextScope *exe_scope,
                      codasip::ResourceContextSP &resource_ctx_sp, uint32_t resource_num);

  //------------------------------------------------------------------
  // For ValueObject only
  //------------------------------------------------------------------
  DISALLOW_COPY_AND_ASSIGN(ValueObjectResource);
};

} // namespace lldb_private

#endif // liblldb_ValueObjectResource_h_
