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
 *  \date   Jan 15, 2013
 *  \brief
 */

#ifndef _LOADER_H_
#define _LOADER_H_

#include "common/toolstypes.h"
#include "os/filesysteml/filesystem.h"
#include "simulator/simbase/codasip_interface.h"   // UID

#include <set>

namespace llvm {

// Forward declaration
class CodasipObjectFile;

namespace object {

// Forward declaration
class SectionRef;

}   // namespace object
}   // namespace llvm

namespace codasip {
namespace simulator {

// Forward declaration
class SimulatorPrivateInterface;
class AddressSpaceInfo;

/**
 * \brief Class which loads executable into the simulator's memory. It also stores loaded
 *        executable that can be used later
 */
class Loader
{
public:
    /// Ignored sections
    typedef std::set<std::string> IgnoredSections;
    /**
     * \brief Constructor, it only initialize internal structures. It does
     *        not load executable.
     * \param simulator Pointer to the simulator, it must not be NULL.
     * \param asip UID of the asip instance where the executable will be loaded into.
     */
    Loader(SimulatorPrivateInterface& simulator);
    /// Desctructor, it does not deallocate simulator or debugger.
    ~Loader();
    /**
     * \brief Loads executable from the file. The debuginfos are NOT handled. This loaded object
     *        file can be retrieved using \ref GetExecutable and is owned by this object (destroyed
     *        in destructor)
     * \param path Path to the executable.
     */
    void LoadExecutable(const filesystem::Path& path);
    /**
     * \brief Return loaded executable object or NULL if no executable was loaded
     */
    const llvm::CodasipObjectFile* GetExecutable() const;
    /**
     * \brief Loads executable data into the simulator from already loaded executable.
     *        Also, if parameters for executable are present, the loader loads them
     *        to the specified part of memory according to the pre-defined sections
     *        in the executable.
     * \param arguments Arguments that will be send into simulator
     * \param ignoreArguments  FVE ignores arguments, so we need to pass this info
     * \param ignored Sections that should not be loaded into simulator
     */
    void LoadIntoSimulator(const std::string& arguments,
        const bool ignoreArguments = false,
        const IgnoredSections* ignored = NULL);
    /**
     *  \brief  Return starting address against program counter.
     */
    Address GetEntryPoint() const;

    /**
     * Reads executable data from simulator and compares it with original executable file
     * @param ignored Sections that should not be checked
     */
    void VerifyExecutable(const IgnoredSections* ignored = NULL);

private:
    typedef enum
    {
        /// Perform program loading
        LOAD_PROGRAM = 0,
        /// Perform program verification
        VERIFY_PROGRAM = 1
    } Mode;

    void LoadExecutable(const llvm::CodasipObjectFile&, const IgnoredSections*);
    void LoadArguments(const llvm::CodasipObjectFile&, const std::string&);
    void LoadSymbols(const llvm::CodasipObjectFile&);
    void EnableStackOverflowCheck(const llvm::CodasipObjectFile&);

    bool GetSymbolAddressAndSection(codasip_address_t&,
        llvm::object::SectionRef&,
        const llvm::CodasipObjectFile&,
        const char*);
    bool GetArgumentSymbolAddressesAndSection(codasip_address_t&,
        codasip_address_t&,
        codasip_address_t&,
        llvm::object::SectionRef&,
        const llvm::CodasipObjectFile&,
        const bool);

    void LoadOrVerifyExecutable(const llvm::CodasipObjectFile&, const IgnoredSections*, const Mode);

    /// Simulator object
    SimulatorPrivateInterface& m_Simulator;
    /// Structure holding object file
    std::unique_ptr<llvm::CodasipObjectFile> m_Executable;
};

}   // namespace simulator
}   // namespace codasip

#endif   // _LOADER_H_
