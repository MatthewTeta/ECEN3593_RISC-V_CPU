/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip s.r.o.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the property of
 * Codasip s.r.o. and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and proprietary to
 * Codasip s.r.o. and are protected by trade secret and copyright law.  In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author zdeny
 *  \date   May 21, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_LLDB_CODASIP_ADDRESSBASE_H_
#define INCLUDE_LLDB_CODASIP_ADDRESSBASE_H_

#include "lldb/lldb-types.h"            // for addr_t
#include "lldb/Codasip/AddressSpace.h"
#include "lldb/Codasip/Defines.h"
#include "lldb/Codasip/Interface.h"

/**
 * \brief Unary operators post and pre ++ and --
 */

#define CODASIP_ADDRESS_BASE_UNARY_OP_INCDEC(op) \
    AddressBase operator op(const int) { \
        AddressBase nrv(*this); \
        op(m_offset); \
        return nrv; \
    } \
    AddressBase& operator op() { \
        op(m_offset); \
        return *this; \
    }

/**
 * \brief Unary operators generator
 */
#define CODASIP_ADDRESS_BASE_UNARY_OP(op) \
AddressBase operator op () const\
{\
    return AddressBase(op m_offset, m_dwarf);\
}

/**
 * \brief Assign operator generator, it uses AddressBase and lldb::addr_t as the base types
 */
#define CODASIP_ADDRESS_BASE_ASSIGN_OP(op)\
AddressBase& operator op (const lldb::addr_t rhs)\
{\
    m_offset op rhs;\
    return *this;\
}\
AddressBase& operator op (const AddressBase& rhs)\
{\
    assert(GetDwarf() == rhs.GetDwarf());\
    m_offset op rhs.GetOffset();\
    return *this;\
}

/**
 * \brief Logical operator generator, it uses AddressBase and lldb::addr_t as the base types
 */
#define CODASIP_ADDRESS_BASE_LOGICAL_OP(op) \
inline bool operator op (const AddressBase &lhs, const AddressBase &rhs)\
{\
    assert(lhs.GetDwarf() == rhs.GetDwarf());\
    return lhs.GetOffset() op rhs.GetOffset();\
}\
inline bool operator op (const lldb::addr_t lhs, const AddressBase &rhs)\
{\
    return lhs op rhs.GetOffset();\
}\
inline bool operator op (const AddressBase &lhs, const lldb::addr_t rhs)\
{\
    return lhs.GetOffset() op rhs;\
}

/**
 * \brief Binary operator generator, it uses AddressBase and lldb::addr_t as the base types
 */
#define CODASIP_ADDRESS_BASE_BINARY_OP(op) \
inline AddressBase operator op (const AddressBase &lhs, const AddressBase &rhs)\
{\
    assert(lhs.GetDwarf() == rhs.GetDwarf());\
    return AddressBase(lhs.GetOffset() op rhs.GetOffset(), lhs.GetDwarf());\
}\
inline AddressBase operator op (const lldb::addr_t lhs, const AddressBase &rhs)\
{\
    return AddressBase(lhs op rhs.GetOffset(), rhs.GetDwarf());\
}\
inline AddressBase operator op (const AddressBase &lhs, const lldb::addr_t rhs)\
{\
    return AddressBase(lhs.GetOffset() op rhs, lhs.GetDwarf());\
}

namespace codasip {

/**
 * \class AddressBase
 * \brief Holds an address and an address space identifier
 */
class AddressBase
{
public:
    /**
     * \brief Default constructor, an address as well as an address space is set to non-valid
     */
    AddressBase();
    /**
     * \brief Default constructor, the address space is assigned to the non-valid
     */
    AddressBase(const lldb::addr_t addr);
    /**
     * \brief Full constructor, initialize address
     */
    explicit AddressBase(const lldb::addr_t addr, uint32_t dwarf);
    /**
     * \brief Copy constructor. Create a duplicate.
     */
    AddressBase(const AddressBase& rhs);
    /**
     * \brief Destructor
     */
    virtual ~AddressBase();
    /**
     * \brief The assignment operator. Create a duplicate.
     */
    AddressBase& operator=(const AddressBase& rhs);
    /**
     * {
     * \brief Getter
     */
    // taken from Address()
    lldb::addr_t GetOffset() const;
    virtual uint32_t GetDwarf() const;
    virtual bool IsValidDwarf() const;
    /** \} */
    /**
     * \{
     * \brief Setter
     */
    // taken from Address()
    bool SetOffset(lldb::addr_t offset);
    virtual void SetDwarf(uint32_t dwarf);
    virtual void SetDwarf(const codasip::AddressSpace& as);
    virtual void SetDwarf(const codasip::Interface& ifc);
    /** \} */
    /**
     * \brief Casting to the normal type without an address space information
     */
    operator lldb::addr_t() const;
    /**
     * \brief Unary operator !
     */
    bool operator ! () const;

    // post/pre increment
    CODASIP_ADDRESS_BASE_UNARY_OP_INCDEC(++)
    CODASIP_ADDRESS_BASE_UNARY_OP_INCDEC(--)
    // unary operators
    CODASIP_ADDRESS_BASE_UNARY_OP(~)
    CODASIP_ADDRESS_BASE_UNARY_OP(-)
    CODASIP_ADDRESS_BASE_UNARY_OP(+)
    // assign operators
    CODASIP_ADDRESS_BASE_ASSIGN_OP(+=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(-=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(*=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(/=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(%=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(<<=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(>>=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(|=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(&=)
    CODASIP_ADDRESS_BASE_ASSIGN_OP(^=)

protected:
    /// Absolute address or an offset in the section.
    /// The name must follow class Address()'s attribute.
    lldb::addr_t m_offset;
    /// Dwarf number
    uint32_t m_dwarf;
};

// off-class binary operators
CODASIP_ADDRESS_BASE_BINARY_OP(+)
CODASIP_ADDRESS_BASE_BINARY_OP(-)
CODASIP_ADDRESS_BASE_BINARY_OP(*)
CODASIP_ADDRESS_BASE_BINARY_OP(/)
CODASIP_ADDRESS_BASE_BINARY_OP(%)
CODASIP_ADDRESS_BASE_BINARY_OP(<<)
CODASIP_ADDRESS_BASE_BINARY_OP(>>)
CODASIP_ADDRESS_BASE_BINARY_OP(|)
CODASIP_ADDRESS_BASE_BINARY_OP(&)
CODASIP_ADDRESS_BASE_BINARY_OP(^)
// off-class logical operators
CODASIP_ADDRESS_BASE_LOGICAL_OP(&&)
CODASIP_ADDRESS_BASE_LOGICAL_OP(||)
CODASIP_ADDRESS_BASE_LOGICAL_OP(<)
CODASIP_ADDRESS_BASE_LOGICAL_OP(>)
CODASIP_ADDRESS_BASE_LOGICAL_OP(==)
CODASIP_ADDRESS_BASE_LOGICAL_OP(!=)
CODASIP_ADDRESS_BASE_LOGICAL_OP(<=)
CODASIP_ADDRESS_BASE_LOGICAL_OP(>=)

#undef CODASIP_ADDRESS_BASE_BINARY_OP
#undef CODASIP_ADDRESS_BASE_LOGICAL_OP
#undef CODASIP_ADDRESS_BASE_ASSIGN_OP
#undef CODASIP_ADDRESS_BASE_UNARY_OP
#undef CODASIP_ADDRESS_BASE_UNARY_OP_INCDEC

}   // namespace codasip

#endif  // INCLUDE_LLDB_CODASIP_ADDRESSBASE_H_
