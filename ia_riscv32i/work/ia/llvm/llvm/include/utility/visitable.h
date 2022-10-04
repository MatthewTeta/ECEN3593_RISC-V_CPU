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
 *  \author Zdenek Prikryl
 *  \date   Jan 20, 2015
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef CODASIP_VISITABLE_H_
#define CODASIP_VISITABLE_H_

// Universal macros for const and non-const visitables.
// Used in brand-new classed (e.g. in nested classes)
#define CODASIP_ENABLE_VISIT(visitor_class_name)     \
    void Accept(visitor_class_name<false>& visitor); \
    void Accept(visitor_class_name<true>& visitor);  \
    void Accept(visitor_class_name<true>& visitor) const;

// Used in class with inheritance
#define CODASIP_ENABLE_VISIT_OVERRIDE(visitor_class_name)     \
    void Accept(visitor_class_name<false>& visitor) override; \
    void Accept(visitor_class_name<true>& visitor) override;  \
    void Accept(visitor_class_name<true>& visitor) const override;

#define CODASIP_DEFINE_VISIT(class_name, visitor_class_name)         \
    void class_name::Accept(visitor_class_name<false>& visitor)      \
    {                                                                \
        visitor.Visit(*this);                                        \
    }                                                                \
    void class_name::Accept(visitor_class_name<true>& visitor)       \
    {                                                                \
        visitor.Visit(*this);                                        \
    }                                                                \
    void class_name::Accept(visitor_class_name<true>& visitor) const \
    {                                                                \
        visitor.Visit(*this);                                        \
    }

// Macros for const visitables.
#define CODASIP_ENABLE_CONST_VISIT(visitor_class_name) \
    void Accept(visitor_class_name& visitor);          \
    void Accept(visitor_class_name& visitor) const;

#define CODASIP_DEFINE_CONST_VISIT(class_name, visitor_class_name) \
    void class_name::Accept(visitor_class_name& visitor)           \
    {                                                              \
        visitor.Visit(*this);                                      \
    }                                                              \
    void class_name::Accept(visitor_class_name& visitor) const     \
    {                                                              \
        visitor.Visit(*this);                                      \
    }

namespace codasip {

/**
 *  \brief  Universal visitable base class.
 */
template<template<bool> class T>
class Visitable
{
public:
    /**
     *  \{
     *  \brief  Accepts base visitor.
     *  \param  visitor Visitor.
     */
    virtual void Accept(T<false>& visitor) = 0;
    virtual void Accept(T<true>& visitor) = 0;
    virtual void Accept(T<true>& visitor) const = 0;
    /** \} */

    /**
     *  \brief  Do nothing.
     */
    virtual ~Visitable() = 0;
};

/**
 *  \brief  Constant visitable base class.
 */
template<class T>
class ConstVisitable
{
public:
    /**
     *  \{
     *  \brief  Accepts base visitor.
     *  \param  visitor Visitor.
     */
    virtual void Accept(T& visitor) = 0;
    virtual void Accept(T& visitor) const = 0;
    /** \} */

    /**
     *  \brief  Do nothing.
     */
    virtual ~ConstVisitable() = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Public interface                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<template<bool> class T>
inline Visitable<T>::~Visitable()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline ConstVisitable<T>::~ConstVisitable()
{}

}   // namespace codasip

#endif   // CODASIP_VISITABLE_H_
