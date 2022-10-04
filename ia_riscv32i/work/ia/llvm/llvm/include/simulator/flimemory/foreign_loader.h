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
 *  \author Potesil Josef
 *  \date   9. 6. 2016
 *  \brief  Declaration of the class codasip::foreign::ForeignLoader.
 */

#ifndef FLIMEMORY_FOREIGN_LOADER_H_
#define FLIMEMORY_FOREIGN_LOADER_H_

#include "common/codasip_integer.h"
#include "simulator/flimemory/foreign_common.h"

#include <memory>

namespace llvm {

// Forward declaration
class CodasipObjectFile;

namespace object {

// Forward declaration
class SectionRef;

}   // namespace object
}   // namespace llvm

namespace codasip {
namespace foreign {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  ForeignLoader
 *  \brief  Loader that calls \ref ForeignStorage::Write to write data stored in executable.
 *          Object of this class also stores all loaded executables so they won't be loaded
 *          multiple times
 *  \}
 */
class ForeignLoader
{
public:
    /**
     *  \brief  Constructor
     */
    ForeignLoader();
    /**
     *  \brief  Destructor. Automatically frees all loaded applications.
     */
    ~ForeignLoader();
    /**
     *  \brief  Initialize memory storage content from executable file.
     *  \param  storage memory storage to be initialized. It may be part (sub-block)
     *          of a "parent" memory.
     *  \param  executable path of executable
     *  \param  addressSpace name of the address space
     *  \param  storageBaseAddr base address for the whole parent memory object
     *          where data will be loaded.
     *  \param  adsLow lowest aligned absolute address in the address space.
     *          Data will be loaded from this address.
     *  \param  adsHigh highest absolute address in the address space.
     *          This is the last address to load.
     *  \param  forceHeapAndStack indicates whether default heap and stack section
     *          is forced to be loaded or not.
     * \{
     */
    void LoadMemory(ForeignStorage& storage,
        const std::string& executable,
        const std::string& addressSpace,
        const codasip_address_t storageBaseAddr,
        const codasip_address_t adsLow,
        const codasip_address_t adsHigh,
        const bool forceHeapAndStack);

    void LoadMemory(ForeignStorage& storage,
        const llvm::CodasipObjectFile& executable,
        const std::string& addressSpace,
        const codasip_address_t storageBaseAddr,
        const codasip_address_t adsLow,
        const codasip_address_t adsHigh,
        const bool forceHeapAndStack);
    /**
     *  \} \{
     *  \brief  Loads executable. If given executable was already loaded, it won't get loaded again.
     *  \param  file Path to executable to load
     */
    const llvm::CodasipObjectFile& LoadAndGetExecutable(const std::string& file);
    void LoadExecutable(const std::string& file);
    /**
     *  \}
     *  \brief  Indicates whether given section should be loaded or not. Currently
     *          debug and info section should not be loaded.
     *  \param  section section to check
     *  \param  forceHeapAndStack indicates whether default heap and stack section
     *          is forced to be loaded or not.
     */
    static bool IsLoadable(const llvm::object::SectionRef& section,
        const llvm::CodasipObjectFile& executable,
        const bool forceHeapAndStack);
    /**
     *  \brief  Indicates whether given section matches the address space
     *          properties with the ones stored in the binary.
     *  \param  section section to check
     *  \param  executable object file
     *  \param  addressSpace name of the address space
     */
    static bool IsAddressSpaceMatch(const llvm::object::SectionRef& section,
        const llvm::CodasipObjectFile& executable,
        const std::string& addressSpace);
    /**
     *  \brief  Free all opened executables.
     */
    void ClearExecutables();
    /**
     *  \brief  Return number of sections in previously accessed executable. If
     *          there is no executable opened, zero is returned.
     */
    uint64_t GetSectionCount() const;
    /**
     *  \brief  Indicates whether given section should be loaded or not. Currently
     *          debug and info section should not be loaded. Also address space
     *          must fit.
     *  \param  sectionIndex section index inside executable
     *  \param  addressSpace name of the address space
     *  \param  forceHeapAndStack indicates whether default heap and stack section
     *          is forced to be loaded or not.
     */
    bool IsSectionLoadable(const uint64_t sectionIndex,
        const char* addressSpace,
        const bool forceHeapAndStack) const;
    /**
     *  \brief  Return address where section should be loaded.
     *  \param  sectionIndex section index inside executable
     */
    codasip_address_t GetSectionStartAddress(const uint64_t sectionIndex) const;
    /**
     *  \brief  Return size of a section in bytes.
     *  \param  sectionIndex section index inside executable
     */
    uint64_t GetSectionSize(const uint64_t sectionIndex) const;
    /**
     *  \brief  Return size of a byte (in bits) used by given section.
     *  \param  sectionIndex section index inside executable
     */
    uint64_t GetSectionByteSize(const uint64_t sectionIndex) const;
    /**
     *  \brief  Return number of bytes per word used by given section.
     *  \param  sectionIndex section index inside executable
     */
    uint64_t GetSectionBytesPerWord(const uint64_t sectionIndex) const;
    /**
     *  \brief  Return default byte order of given section.
     *  \param  sectionIndex section index inside executable
     *  \retval true little endian
     *  \retval false big endian
     */
    bool IsSectionLittle(const uint64_t sectionIndex) const;
    /**
     *  \{
     *  \brief  Read byte from previously open executable, from given section
     *          and address.
     *  \param  sectionIndex section index inside executable
     *  \param  sectionAddr address inside the section
     */
    uint32_t GetByte32(const uint64_t sectionIndex, const codasip_address_t sectionAddr) const;
    uint64_t GetByte64(const uint64_t sectionIndex, const codasip_address_t sectionAddr) const;
    MaxUint GetByteMax(const uint64_t sectionIndex, const codasip_address_t sectionAddr) const;
    /**
     *  \} \{
     *  \brief  Read word from previously open executable, from given section
     *          and address.
     *  \param  sectionIndex section index inside executable
     *  \param  sectionAddr address inside the section
     */
    uint32_t GetWord32(const uint64_t sectionIndex, const codasip_address_t sectionAddr) const;
    uint64_t GetWord64(const uint64_t sectionIndex, const codasip_address_t sectionAddr) const;
    MaxUint GetWordMax(const uint64_t sectionIndex, const codasip_address_t sectionAddr) const;
    /** \} */
private:
    // disable copies, just to be sure
    ForeignLoader(const ForeignLoader&);
    ForeignLoader& operator=(const ForeignLoader&);

    const llvm::CodasipObjectFile& GetLastExecutable() const;

    /// Container with parsed executables, key => file path, value => pointer to object file
    typedef std::map<std::string, std::unique_ptr<llvm::CodasipObjectFile>> LoadedExecutables;
    /// Loaded executables
    LoadedExecutables m_Executables;
    /// currently accessed executable file
    const llvm::CodasipObjectFile* m_LastExecutable;
};

}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_FOREIGN_LOADER_H_
