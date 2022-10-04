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
 *  \author Martin Ministr
 *  \date   4. 4. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INSTRSET_ASSEMBLER_ASMBASE_AST_NODE_H_
#define INSTRSET_ASSEMBLER_ASMBASE_AST_NODE_H_

#include "utility/location.h"
#include "utility/visitable.h"

#include <set>
#include <vector>

namespace codasip {
namespace ast {
namespace assembler {

// Forward declaration.
template<bool isConst>
class BaseVisitor;

////////////////////////////////////////////////////////////////////////////////////////////////////
class Node : public Visitable<BaseVisitor>
{
public:
    typedef std::vector<Node*> Children;
    typedef std::set<Node*> Nodes;

    Node(const Location& location);
    Node(const Node&);

    virtual ~Node();

    /**
     *  \{
     *  \brief  Getter.
     */
    unsigned int GetStartOffset() const;
    unsigned int GetEndOffset() const;
    /**
     *  \}
     *  \brief  Delete all nodes accessible from this node.
     */
    void Delete();
    /**
     *  \brief  Gather all the nodes accessible from this node.
     *  \param[in, out] nodes
     */
    void GetNodes(Nodes& nodes);

    /**
     *  \brief Returns child on given index. Fails if index is out of range.
     *  \param[in] index
     */
    Node& GetChild(const size_t index) const;
    /**
     *  \brief  Get child on given index. Has to be of specified type.
     *  \param[in]  index
     *  \tparam     T expected child type
     */
    template<class T>
    typename std::enable_if<!std::is_same<typename std::decay<T>::type, Node>::value, T&>::type
    GetChild(const size_t index) const
    {
        Node& child = Node::GetChild(index);
        this->ThrowTypeException(child.Is<T>());
        return child.To<T>();
    }
    Children& GetChildren();
    const Children& GetChildren() const;

    /**
     *  \brief  Add child into the node. Will be added to the back.
     *  \param[in]  child
     */
    virtual void AddChild(Node& child);
    /**
     *  \brief  Add child into the node. Will be added to the front.
     *  \param[in]  child
     */
    void AddChildToFront(Node& child);

    /**
     *  \brief  Check that the node is a particular type.
     */
    template<class T>
    bool Is() const;
    /**
     *  \brief  Convert node to a particular type.
     */
    template<class T>
    const T& To() const;
    /**
     *  \brief  Convert node to a particular type.
     */
    template<class T>
    T& To();

    /**
     * \brief Converts node and his children to string representation.
     * \param[in] indent
     */
    const std::string ToString(const int indent = 0) const;

    /// \brief  Create deep clone of the node.
    virtual Node& Clone() const = 0;
    /**
     *  \brief  Get match info of the given node and his children.
     *          Vector of false (opcode) and true (attribute).
     */
    virtual const std::string GetMatchInfo() const = 0;
    /**
     *  \brief  Add additional match info to the node.
     *  \param[in]  info
     */
    virtual void AddMatchInfo(const std::string& info);
    /// \brief  Get opcode string. It is used for conditional section architectures.
    virtual const std::string GetOpcode() const = 0;
    /// \brief Print one node.
    virtual const std::string PrintNode() const = 0;
    /// \brief Compares that two AST are describing the same instruction.
    virtual bool operator==(const Node& other) const = 0;
    bool operator!=(const Node& other) const;

protected:
    /// Children of the node
    Children m_Children;

private:
    void ThrowTypeException(const bool) const;

    /// Codasip location should not be used as line and column, it is used as LLVM buffer offsets
    Location m_Location;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int Node::GetStartOffset() const
{
    return m_Location.GetLine();
}

inline unsigned int Node::GetEndOffset() const
{
    return m_Location.GetColumn();
}

inline Node::Children& Node::GetChildren()
{
    return m_Children;
}

inline const Node::Children& Node::GetChildren() const
{
    return m_Children;
}

inline void Node::AddChild(Node& child)
{
    m_Children.push_back(&child);
}

inline void Node::AddChildToFront(Node& child)
{
    m_Children.insert(m_Children.begin(), &child);
}

template<class T>
inline bool Node::Is() const
{
    return dynamic_cast<const T* const>(this) != nullptr;
}

template<class T>
inline const T& Node::To() const
{
    return dynamic_cast<const T&>(*this);
}

template<class T>
inline T& Node::To()
{
    return dynamic_cast<T&>(*this);
}

inline bool Node::operator!=(const Node& other) const
{
    return !(*this == other);
}

}   // namespace assembler
}   // namespace ast
}   // namespace codasip

#endif   // INSTRSET_ASSEMBLER_ASMBASE_AST_NODE_H_
