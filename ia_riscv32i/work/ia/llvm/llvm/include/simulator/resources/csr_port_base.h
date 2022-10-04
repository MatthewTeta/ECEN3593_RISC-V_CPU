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
 *  \date   Feb 23, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_PORT_BASE_H_
#define SIMULATOR_RESOURCES_CSR_PORT_BASE_H_

#include "simulator/resources/csr_helpers.h"

#include <algorithm>
#include <vector>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  Port
 *  \brief  Class representing one port
 *  \}
 */
template<class T>
class PortBase
{
public:
    typedef T data_type;
    typedef typename detail::CallTraits<data_type>::param_type param_type;

    /**
     * \brief Destructor
     */
    virtual ~PortBase() {}
    /**
     * \brief Bind this port with rhs port, the direction is taken into account a->b, not b->a
     * \param rhs Connected port
     */
    void bind(PortBase& rhs);
    /**
     * \{
     * \brief Par of port interface
     */
    virtual T read() const = 0;
    virtual T dread() const = 0;
    virtual void write(param_type) = 0;
    virtual void dwrite(param_type) = 0;
    /** \} */

protected:
    /// Container for binded targets
    typedef std::vector<PortBase<T>*> Binds;

    /**
     * \{
     * \brief Par of port interface
     */
    virtual void write_cb(param_type) = 0;
    virtual void dwrite_cb(param_type) = 0;
    /**
     * \}
     * \{
     * \brief Getter
     */
    Binds& get_fw_binds();
    const Binds& get_fw_binds() const;
    /**
     * \}
     * \{
     * \brief Propagate value to all forward connections
     */
    void handle_write_cb(param_type);
    void handle_dwrite_cb(param_type);
    /** \} */

private:
    void fw_bind(PortBase& rhs);
    void bw_bind(PortBase& lhs);

    void add_bind(Binds&, PortBase&);
    void add_binds(Binds&, Binds&);

    /// forwards binds
    Binds m_FwBinds;
    /// backwards binds
    Binds m_BwBinds;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PortBase<T>::bind(PortBase& rhs)
{
    // forward bind
    fw_bind(rhs);
    // backward bind
    bw_bind(rhs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline typename PortBase<T>::Binds& PortBase<T>::get_fw_binds()
{
    return m_FwBinds;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline const typename PortBase<T>::Binds& PortBase<T>::get_fw_binds() const
{
    return m_FwBinds;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void PortBase<T>::handle_write_cb(param_type data)
{
    // write only to this port
    this->write_cb(data);
    // update the rest
    for (auto it = this->get_fw_binds().begin(); it != this->get_fw_binds().end(); ++it)
    {
        (*it)->write_cb(data);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void PortBase<T>::handle_dwrite_cb(param_type data)
{
    // write only to this port
    this->dwrite_cb(data);
    // update the rest
    for (auto it = this->get_fw_binds().begin(); it != this->get_fw_binds().end(); ++it)
    {
        (*it)->dwrite_cb(data);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PortBase<T>::fw_bind(PortBase& rhs)
{
    // chain: a -> b -> c -> d
    // a.bind(b) means:
    // add b's fw binds (c, d)
    add_binds(m_FwBinds, rhs.get_fw_binds());
    // add b itself
    add_bind(m_FwBinds, rhs);
    // update all bw binds with the new fw binds of this
    for (auto it = m_BwBinds.begin(); it != m_BwBinds.end(); ++it)
    {
        (*it)->fw_bind(*this);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PortBase<T>::bw_bind(PortBase& rhs)
{
    // chain: a -> b -> c -> d
    // a.bind(b) means:
    // add a to b's bw binds
    rhs.add_bind(rhs.m_BwBinds, *this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PortBase<T>::add_bind(Binds& binds, PortBase& rhs)
{
    // ignore ourselves
    if (&rhs == this)
    {
        return;
    }
    // check that there is no such port already inserted
    if (std::find(binds.begin(), binds.end(), &rhs) != binds.end())
    {
        return;
    }
    // create a connection
    binds.push_back(&rhs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PortBase<T>::add_binds(Binds& binds, Binds& newBinds)
{
    // add everything we have
    for (auto it = newBinds.begin(); it != newBinds.end(); ++it)
    {
        add_bind(binds, **it);
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_PORT_BASE_H_
