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
 *  \author Nemcek
 *  \date   12. 10. 2017
 *  \brief  Declaration of the codasip::simulator::Path class
 *          Declaration of the codasip::simulator::PathIterator class.
 */

#ifndef SIMULATOR_SIMBASE_SIMULATOR_PATH_H_
#define SIMULATOR_SIMBASE_SIMULATOR_PATH_H_

#include <sstream>
#include <string>

namespace codasip {
namespace simulator {

class Path;

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  PathIterator
 *  \brief  Bidirectional const iterator over simulator Path
 */
class PathIterator : public std::iterator<std::bidirectional_iterator_tag,
                         const std::string,   // Iterator type
                         unsigned>            // Reference type
{
public:
    /// \brief  Constructor
    PathIterator(const Path& ppath);
    /// \brief  Constructor of end() iterator
    PathIterator();
    /// \brief  Access to stored element
    reference operator*() const;
    /// \brief  Access to stored element
    pointer operator->() const;
    /**
     *  \brief  Iterator operators
     *  \{
     */
    bool operator==(const PathIterator& rhs) const;
    bool operator!=(const PathIterator& rhs) const;
    PathIterator& operator--();
    PathIterator& operator++();
    PathIterator operator--(int);
    PathIterator operator++(int);
    /**
     *  \}
     */
private:
    /// \brief  Move the iterator
    void Move(const bool forward);

    /// Associated path object
    const Path* m_Path;
    /// Current element
    std::string m_Current;
    /// Position of current element
    size_t m_Pos;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  Path
 *  \brief  Stores string that contains path to the resource (e.g. "level1.asip.resource_test")
 */
class Path
{
public:
    typedef PathIterator const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef std::string value_type;
    typedef value_type::difference_type difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    /**
     *  \brief  Constructor
     *  \{
     */
    Path();
    Path(const std::string&);
    Path(const char*);

    template<class Iterator>
    Path(Iterator it, Iterator last);
    /**
     *  \}
     *  \brief  Automatic conversion
     */
    operator std::string() const
    {
        return m_Path;
    }
    /**
     *  \{
     *  \brief  Return stored path string
     */
    const std::string& GetPath() const;
    const char* c_str() const;
    /**
     *  \}
     *  \brief  Set stored path string
     */
    void SetPath(const std::string& path);
    /**
     *  \brief  Return const begin iterator
     */
    const_iterator begin() const;
    /**
     *  \brief  Return const end iterator
     */
    const_iterator end() const;
    /**
     *  \brief  Return if given path is empty
     */
    bool Empty() const;
    /**
     *  \brief  Clears stored path
     */
    void Clear();

private:
    std::string m_Path;
};

/**
 * \brief Enables using Path in C++ streams, returns its name
 */
inline std::ostream& operator<<(std::ostream& os, const Path& s)
{
    os << s.GetPath();
    return os;
}
/**
 * \brief Compares the contents of a Path with another Path using the stored name
 */
inline bool operator==(const Path& l, const Path& r)
{
    return l.GetPath() == r.GetPath();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Iterator>
Path::Path(Iterator it, Iterator last)
{
    for (; it != last; ++it)
    {
        if (!m_Path.empty())
        {
            m_Path.append(1, '.');
        }
        m_Path += *it;
    }
}

}   // namespace simulator
}   // namespace codasip

#endif   // SIMULATOR_SIMBASE_SIMULATOR_PATH_H_
