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
 *  \date   Feb 1, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SOURCE_CODASIP_ARCHDEFINITION_H_
#define SOURCE_CODASIP_ARCHDEFINITION_H_

// C Includes
// C++ Includes
#include <string>
#include <set>
#include <vector>
// C++ Includes
// Other libraries and framework includes
#include "lldb/Utility/JSON.h"
#include "lldb/Utility/Status.h"
#include "lldb/lldb-private.h"
#include "lldb/Codasip/Register.h"
#include "lldb/Codasip/AddressSpace.h"
#include "lldb/Codasip/Cache.h"
#include "lldb/Codasip/Codal.h"
#include "lldb/Codasip/Interface.h"
#include "lldb/Codasip/Memory.h"
#include "lldb/Codasip/Port.h"
#include "lldb/Codasip/Signal.h"

namespace lldb_private {
namespace platform_codasip_simulator {
class PlatformCodasipSimulator;
}
}

namespace codasip {

class SymbolFileCodal;

/// Container for registers
typedef std::vector<Register> Registers;
/// Container for address spaces
typedef std::vector<AddressSpace> AddressSpaces;
/// Container for caches
typedef std::vector<Cache> Caches;
/// Container for interfaces
typedef std::vector<Interface> Interfaces;
/// Container for memories
typedef std::vector<Memory> Memories;
/// Container for ports
typedef std::vector<Port> Ports;
typedef std::vector<ResourceSet> PortsSet;
/// Container for signals
typedef std::vector<Signal> Signals;
typedef std::vector<ResourceSet> SignalsSet;
/// Container for codal variables
typedef std::vector<CodalVariable> CodalVariables;
typedef std::vector<ResourceSet> CodalVariablesSet;

/**
 * \class ArchDefinition
 * \brief Singleton for architecture definition
 */
class ArchDefinition
{
public:
    /// Container with a callee saved DWARF register index
    typedef std::set<unsigned> CalleeSavedRegisters;
    /// Container with all supported instruction sizes
    typedef std::set<unsigned> IntructionSizes;
    /**
     * \brief Return singleton
     */
    static ArchDefinition& GetInstance();
    /**
     * \brief Return data layout for Clang target
     */
    std::string GetDatalayout() const;
    /**
     * \brief Return callee save registers
     */
    CalleeSavedRegisters GetCalleeSavedRegisters() const;
    /**
     * \brief Return constainer with all supported instruction sizes
     */
    IntructionSizes GetInstructionSizes() const;
    /**
     * \brief Return pointer size
     */
    unsigned GetPointerSize() const;
    /**
     * \brief Return stack alignment
     */
    unsigned GetStackAlignment() const;
    /**
     * \brief Return minimum instruction length in bytes
     */
    uint32_t GetMinimumOpcodeByteSize() const;
    /**
     * \brief Return maximum instruction length in bytes
     */
    uint32_t GetMaximumOpcodeByteSize() const;
    /**
     * \{
     * \brief Find an item in a JSON objects and cast it to a proper type
     * \param jsonObject JSON object with data
     * \param key Key to JSON object
     * \param optional Turns off warning message if item with 'key' not present
     * \return Error is printed when the key is not found and the default value is returned,
     *         otherwise a proper value is returned
     */
    static unsigned int GetAsUnsigned(
        const lldb_private::JSONObject::SP& jsonObject,
        const std::string& key,
        const bool optional = false);
    static std::string GetAsString(
        const lldb_private::JSONObject::SP& jsonObject,
        const std::string& key,
        const bool optional = false);
    static lldb::Encoding GetEncoding(const lldb_private::JSONObject::SP& jsonObject);
    static lldb::Format GetFormat(const lldb_private::JSONObject::SP& jsonObject);
    /**
     * \brief Return size in bytes
     */
    static uint32_t GetSizeInBytes(const uint32_t bits);
    /** \} */
    static bool IsCodalAddress(const AddressBase& addr);
    /**
     * \brief Return path to the disassemler library
     */
    std::string GetDisassemblerLibraryPath() const;
    /**
     * \brief Print warning if codal debugger is requested but not present.
     * \param stream Output stream where the warning is printed.
     * \param codalDbgRequested true if codal debugger operation is requested.
     */
    static void WarnIfNoCodalDbg(lldb::StreamSP stream, const bool codalDbgRequest);
    /**
     * \{
     * \brief Don't Implement
     */
    ArchDefinition(ArchDefinition const&) = delete;
    void operator=(ArchDefinition const&) = delete;
    /** \} */
    /**
     *  \{
     *  \brief  Search for a resource of given name or dwarf.
     *  \return If there is no such a resource, a non-valid resource is returned.
     */
    Addressable GetAddressable(const uint32_t dwarf) const;
    Addressable GetAddressable(const std::string& name) const;

    AddressSpace GetAddressSpace(const uint32_t dwarf) const;
    AddressSpace GetAddressSpace(const std::string& name) const;

    Cache GetCache(const uint32_t dwarf) const;
    Cache GetCache(const std::string& name) const;

    Interface GetInterface(const uint32_t dwarf) const;
    Interface GetInterface(const std::string& name) const;

    Memory GetMemory(const uint32_t dwarf) const;
    Memory GetMemory(const std::string& name) const;

    const Port* GetPort(const uint32_t dwarf) const;
    const Port* GetPort(const std::string& name) const;

    const Signal* GetSignal(const uint32_t dwarf) const;
    const Signal* GetSignal(const std::string& name) const;

    const CodalVariable* GetCodalVariable(const uint32_t dwarf) const;
    /// \param address Address where \a name is in scope.
    const CodalVariable* GetCodalVariable(const std::string& name, const lldb::addr_t address) const;
    /** \} */
    /**
     * \brief Get address space for type
     * \param dataType Data type (e.g. v4i32)
     */
    AddressSpace GetTypeAddressSpace(const std::string& dataType) const;
    /**
     * \brief Return default program address space
     */
    AddressSpace GetProgramAddressSpace() const;
    /**
     * \brief Return default data address space
     */
    AddressSpace GetDataAddressSpace() const;
    /**
     * \brief Return codal address space (artificial AS for codal debug)
     */
    AddressSpace GetCodalAddressSpace() const;
    /**
     * \brief Return index of the return register at a certain index. If there is no register
     *        at the index, then LLDB_INVALID_REGNUM is returned
     * \param index Index of the return register
     * \param as Address space for which we're looking for return registers
     */
    uint32_t GetFunctionResultDwarf(const unsigned index, const AddressSpace& as) const;
    size_t GetPortsSetCount() const;
    codasip::ResourceSet* GetPortsSet(unsigned idx);
    size_t GetSignalsSetCount() const;
    codasip::ResourceSet* GetSignalsSet(unsigned idx);
    size_t GetCodalVariablesSetCount() const;
    codasip::ResourceSet* GetCodalVariablesSet(unsigned idx);
    /**
     * \brief Return number of supported watchpoints. 0 means that the watchpoints are not
     *        supported
     */
    uint32_t GetWatchpoints() const;
    /**
     * \brief Return true, if the target supports Codal debugging
     */
    bool HasCodal() const;
    /**
     * \{
     * \brief Get a list of resources
     */
    const AddressSpaces& GetAddressSpaces() const;
    const Caches& GetCaches() const;
    const Interfaces& GetInterfaces() const;
    const Memories& GetMemories() const;
    const Ports& GetPorts() const;
    const Registers& GetRegisters() const;
    const Signals& GetSignals() const;
    /** \} */

    // TODO: get codal debug info in a format usable by lldb
    //       or install codal debug info into the lldb debuginfo tables

    // NOTE: not sure if this will stay public or be further processed and passed out in a more refined form
    lldb_private::JSONObject::SP GetCodalDebugInfo() const;

    std::string GetCodalDebugInfoFilePath() const;
    /**
     * \brief Get register index to given DWARF.
     * \param[in] dwarf DWARF index
     */
    size_t GetRegisterIndex(const uint32_t dwarf) const;
    /**
     * \brief Return software breakpoint op code if exists
     */
    void GetSoftwareBreakpointTrapOpcode(const uint8_t*& bp, size_t& size);

private:
    typedef void (ArchDefinition::*ParseItemFunction)(lldb_private::JSONObject::SP);
    typedef std::pair<unsigned, uint8_t*> SoftwareBreakpoint;

    ArchDefinition();
    ~ArchDefinition();
    void LoadDefinition();
    static std::string GetExecutablePath();
    static std::string GetExecutableDirectory();
    static std::string GetExecutablePrefix();
    lldb_private::JSONObject::SP GetJsonHostInfo() const;
    lldb_private::JSONObject::SP GetJsonDefinition() const;
    lldb_private::JSONArray::SP GetJsonArray(const std::string &id, const bool optional = false) const;
    void ParseArray(const std::string &id, ParseItemFunction function, const bool optional = false);
    void ParseSoftwareBreakpoint();
    void ParseAddressSpace(lldb_private::JSONObject::SP);
    void ParseCache(lldb_private::JSONObject::SP);
    void ParseInterface(lldb_private::JSONObject::SP);
    void ParseMemory(lldb_private::JSONObject::SP);
    void ParsePort(lldb_private::JSONObject::SP);
    void ParseRegister(lldb_private::JSONObject::SP);
    void ParseSignal(lldb_private::JSONObject::SP);
    static AddressSpace::DataTypes GetDataTypes(const lldb_private::JSONObject::SP);
    static AddressSpace::FunctionResult GetFunctionResult(const lldb_private::JSONObject::SP);

    ResourceSet& GetPortSet(const std::string&);
    ResourceSet& GetSignalSet(const std::string&);
    ResourceSet& GetCodalVariablesSet(const std::string&);
    static uint32_t GetOpcodeByteSize(const uint32_t, const uint32_t);

    void AddCodalVariable(const CodalVariable&);

    friend lldb_private::platform_codasip_simulator::PlatformCodasipSimulator;
    // SymbolFileCodal is parsing the codal variables and codal types
    friend codasip::SymbolFileCodal;

    /// Loaded definition file
    lldb_private::JSONObject::SP m_Definition;
    /// Container with registers
    Registers m_Registers;
    /// Container with address spaces
    AddressSpaces m_AddressSpaces;
    /// Container with caches
    Caches m_Caches;
    /// Container with interfaces
    Interfaces m_Interfaces;
    /// Container with Memories
    Memories m_Memories;
    /// Container with ports
    Ports m_Ports;
    /// Container with port sets
    PortsSet m_PortsSet;
    /// Container with signals
    Signals m_Signals;
    /// Container with signal sets
    SignalsSet m_SignalsSet;
    /// Software breakpoint
    SoftwareBreakpoint m_SoftwareBreakpoint;
    /// Container with codal variables
    CodalVariables m_CodalVariables;
    /// Container with codal variable sets
    CodalVariablesSet m_CodalVariablesSet;
    /// Codal address space, is contained within m_AddressSpaces
    mutable const AddressSpace* m_CodalAddressSpace;
};

}   // namespace codasip

#endif  // SOURCE_CODASIP_ARCHDEFINITION_H_

