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
 *  \author Karel Vorechovsky
 *  \date   2020 8 1
 *  \brief
 */

#ifndef GETOPTL_INTERFACE_SIMULATOR_CODAL_PARAMETERS_H_
#define GETOPTL_INTERFACE_SIMULATOR_CODAL_PARAMETERS_H_

#include "common/codasip_integer.h"
#include "getoptl/interface/optionssim.h"
#include "utility/contains.h"

namespace codasip {
namespace getopt {

/// Map of runtime parameters
class CodalParameters
{
public:
    //  maximum allowed parameter bit width is 2048
    typedef codasip::Integer<2048, true> ParameterType;
    //  internal map storage for parameters
    typedef std::map<std::string, ParameterType> CodalParameterMap;

    /**
     *  \brief  Constructor
     *  \param  parametersString string containing the unparsed argument of --codal-parameters
     *          simulator option
     */
    CodalParameters(const char* parametersString);

    /**
     *  \brief  GetParameter used in generated simulator code, either get the default value
     *          or if user supplied such parameter from command line, return that instead
     *  \param  parameterName codal name used in model declaration for parameter
     *  \param  defaultValue value used in codal model as default for the parameter
     */
    template<typename CodalParameterType>
    CodalParameterType
    GetParameter(const std::string& parameterName, const CodalParameterType& defaultValue)
    {
        m_UsedParameters.insert(parameterName);
        const auto it = m_Parameters.find(parameterName);
        if (it == m_Parameters.cend())
        {
            return defaultValue;
        }
        else
        {
            return static_cast<CodalParameterType>(it->second);
        }
    }
    /**
     *  \brief  CheckUnusedParameters called in simulator code, walks the parameter map
     *          and reports unused parameter, this helps identify typos in commandline
     *  \param  output stream to use for report
     */
    template<typename Output>
    void CheckUnusedParameters(Output& output)
    {
        bool anyLeft = false;
        for (const auto& it : m_Parameters)
        {
            if (!Contains(m_UsedParameters,
                    [&it](const std::string& used)
                    {
                        return used == it.first;
                    }))
            {
                output << "WARNING: Parameter '" << it.second
                       << "' was not consumed by the simulator" << std::endl;
                anyLeft = true;
            }
        }
        if (anyLeft)
        {
            output << "Simulator only accepts following runtime parameters: " << std::endl;
            for (const auto& it : m_UsedParameters)
            {
                output << "'" << it << "'" << std::endl;
            }
        }
    }

    /**
     *  \brief  Parses the \p inputString into a key-value map of parameters
     *  \throws std::runtime_error on invalid input
     */
    static CodalParameterMap ParseCodalParameters(const std::string& inputString);

private:
    // map storage for parameters
    CodalParameterMap m_Parameters;
    // keeps track of used parameters
    std::set<std::string> m_UsedParameters;
};

}   // namespace getopt
}   // namespace codasip

#endif
