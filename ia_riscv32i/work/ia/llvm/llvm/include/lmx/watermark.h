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
 *  \date   Mar 13, 2017
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef CODALL_WATERMARK_H_
#define CODALL_WATERMARK_H_

#include <string>
#include <map>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream>

namespace codasip {
namespace lmx {

/**
 * \class ModelWatermark
 * \brief Simple class holding a watermark.
 *        It has to have an implementation in the header (because of a license checking)!
 */
class Watermark
{
public:
    /// Items being hanged by watermark
    typedef enum
    {
        PIPELINE_STAGE = 0,
        ADDRESS_SPACE,
        INTERFACE,
        PORT,
        REGISTER,
        REGISTER_FILE,
        EVENT,
        EMULATION,
        PEEPHOLE,
        ELEMENT,
        ITEMS_COUNT
    } WatermarkItem;

    /// weights for checking may be passed from a license
    typedef std::map<WatermarkItem, unsigned> Tolerance;

	/**
	 * \brief Constructor
	 */
	Watermark();
	/**
	 * \brief Constructor
	 */
	explicit Watermark(const std::string& signature);
    /**
     * \brief Return signature of this configuration
     */
    std::string GetSignature() const;
    /**
     * \brief Reset configuration
     */
    void Reset();
    /**
     * \brief Check whether the signature is valu
     * \param lhs Reference configuration
     * \param weights Weights for a checking
     */
    bool Check(const Watermark& lhs, const Tolerance& tolerance = Tolerance()) const;
    /**
     * \brief Increment number of an item
     */
    void Inc(const WatermarkItem);
    /**
     * \brief Parse and create a tolerance
     * \param rhs Encoded tolerance in string
     */
    static Tolerance GetTolerance(const std::string& rhs);
    /**
     * \brief Return string representation of Watermark item
     */
    static std::string WatermarkItemToString(const WatermarkItem);
    /**
     * \brief Return Watermark Item from string
     */
    static WatermarkItem WatermarkItemFromString(const std::string& str);
private:

    /// ranges for checking
    static const int STRICT_MATCH_BEGIN = PIPELINE_STAGE;
    static const int STRICT_MATCH_END = INTERFACE;
    static const int WEAK_MATCH_BEGIN = PORT;
    static const int WEAK_MATCH_END = PEEPHOLE;
    static const int RELAXED_MATCH_BEGIN = ELEMENT;
    static const int RELAXED_MATCH_END = ELEMENT;

    void Parse(const std::string&);
    static bool Equal(const unsigned, const unsigned, const unsigned);
    template <class T>
    static void SplitNames(T&, const std::string&, const char);
    static void Exit(const std::string&);

    static const int WEAK_TOLERANCE = 10;
    static const int RELAXED_TOLERANCE = 30;

    /// number of pipelineStages
    std::map<WatermarkItem, unsigned> m_WatermarkItems;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Watermark::Watermark()
{
    Reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Watermark::Watermark(const std::string& signature)
{
    Reset();
    Parse(signature);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline std::string Watermark::GetSignature() const
{
    std::string signature;
    for (size_t ii = 0; ii < ITEMS_COUNT; ++ii)
    {
        signature += (signature.empty() ? "" : ",") +
            const_cast<Watermark*>(this)->WatermarkItemToString(WatermarkItem(ii)) + ":" +
            std::to_string(m_WatermarkItems.find(WatermarkItem(ii))->second);
    }
    return signature;
}

/**
 * \brief Parse input string and fill a configuration
 * \param lhs String used for parsings
 */
inline void Watermark::Parse(const std::string& signature)
{
    std::vector<std::string> parts;
    SplitNames(parts, signature, ',');

    // load all parts
    for (auto& part : parts)
    {
        std::vector<std::string> pair;
        SplitNames(pair, part, ':');

        if (pair.size() != 2)
        {
            Exit("Wrong tolerance, corrupted a:b format");
        }

        m_WatermarkItems[WatermarkItemFromString(pair.at(0))] = std::stoi(pair.at(1));
    }
}

/**
 * \brief Return ture, if the items are equal with respect to the tolerance
 * \param lhs Left hand side
 * \param rhs Right hand side
 * \param tolerance Number giving a tolerance
 * \return True, if weakly lsh == rhs
 */
inline bool Watermark::Equal(const unsigned lhs, const unsigned rhs, const unsigned tolerance)
{
    int sub = static_cast<int>(lhs) - static_cast<int>(rhs);
    unsigned abs = std::abs(sub);

    // use  fixed number
    return abs <= tolerance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Watermark::Reset()
{
    m_WatermarkItems.clear();
    for (size_t ii = 0; ii < ITEMS_COUNT; ++ii)
    {
        m_WatermarkItems[WatermarkItem(ii)] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Watermark::Check(const Watermark& lhs, const Tolerance& tolerance) const
{
    for (size_t ii = 0; ii < ITEMS_COUNT; ++ii)
    {
        WatermarkItem wi = WatermarkItem(ii);
        (m_WatermarkItems.count(wi));
        if (lhs.m_WatermarkItems.count(wi) == 0)
        {
            Exit("Watermark item was not found.");
        }

        // default checking
        unsigned int t = (wi >= STRICT_MATCH_BEGIN && wi <= STRICT_MATCH_END)
            ? 0
            : (wi >= WEAK_MATCH_BEGIN && wi <= WEAK_MATCH_END)
                ? WEAK_TOLERANCE
                : RELAXED_TOLERANCE;

        // explicit, overwrite the default
        if (tolerance.count(wi))
        {
            t = tolerance.find(wi)->second;
        }

        bool equal = Equal(m_WatermarkItems.find(wi)->second,
            lhs.m_WatermarkItems.find(wi)->second,
            t);

        if (!equal)
        {
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Watermark::Inc(const WatermarkItem item)
{
    ++m_WatermarkItems[item];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Watermark::Tolerance Watermark::GetTolerance(const std::string& rhs)
{
    Tolerance tolerance;

    std::vector<std::string> parts;
    SplitNames(parts, rhs, ',');

    // load all parts
    for (auto& part : parts)
    {
        std::vector<std::string> pair;
        SplitNames(pair, part, ':');

        if (pair.size() != 2)
        {
            Exit("Wrong tolerance, corrupted a:b format");
        }
        tolerance[Watermark().WatermarkItemFromString(pair.at(0))] = std::stoi(pair.at(1));
    }

    return tolerance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline std::string Watermark::WatermarkItemToString(const WatermarkItem watermarkItem)
{
    switch (watermarkItem)
    {
        case PIPELINE_STAGE:
            return "ps";
        case ADDRESS_SPACE:
            return "as";
        case INTERFACE:
            return "if";
        case PORT:
            return "p";
        case REGISTER:
            return "r";
        case REGISTER_FILE:
            return "rf";
        case EVENT:
            return "ev";
        case EMULATION:
            return "em";
        case PEEPHOLE:
            return "ph";
        case ELEMENT:
            return "el";
        case ITEMS_COUNT:
            break;
    }
    return "";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Watermark::WatermarkItem Watermark::WatermarkItemFromString(const std::string& str)
{
    for (int ii = 0; ii < ITEMS_COUNT; ++ii)
    {
        if (str == WatermarkItemToString(WatermarkItem(ii)))
        {
            return WatermarkItem(ii);
        }
    }
    return ITEMS_COUNT;
}

/**
 * \brief Split string
 */
template <class T>
inline void Watermark::SplitNames(T& tokens, const std::string& s, const char delim)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        tokens.push_back(item);
    }
}

/**
 * \brief When error detected, just exit
 * \param msg Message to print
 */
inline void Watermark::Exit(const std::string& msg)
{
    std::cerr << "error: " << msg;
    exit(1);
}

} /* namespace lmx */
} /* namespace codasip */


#endif /* CODALL_WATERMARK_H_ */
