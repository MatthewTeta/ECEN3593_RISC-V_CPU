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
 *  \brief  Declaration and definition of common interface used to register VPI
 *          task with array readers and loaders for foreign libraries.
 */

#ifndef FLIMEMORY_VPI_LIB_INTERFACE_H_
#define FLIMEMORY_VPI_LIB_INTERFACE_H_

#include "simulator/flimemory/foreign_common.h"
#include "simulator/flimemory/vpi_common.h"

#include <string>

namespace codasip {
namespace foreign {

/**
 *  \brief  Store given reader into global container.
 *  \param  reader source object to store.
 */
void StoreReader(vpi::ArrayReaderBase& reader);

/**
 *  \brief  Reads value of single array element on given address. The value is
 *          stored inside task's output parameter.
 */
template<class AR>
PLI_INT32 ArrayRead(PLI_BYTE8*)
{
    try
    {
        vpiHandle systf = vpi_handle(vpiSysTfCall, NULL);
        AR& reader = *static_cast<AR*>(vpi_get_userdata(systf));
        reader.Read();
    }
    catch (std::exception& e)
    {
        vpi::HandleException(e.what());
    }
    return 0;
}

/**
 *  \brief  Parse, check and store parameters of the array_read system task.
 *          All handles will be stored as instance specific user data to
 *          increase performance of task calls.
 */
template<class AR>
PLI_INT32 ArrayReadCompile(PLI_BYTE8*)
{
    AR* reader = new AR;
    try
    {
        reader->Compile(vpi_handle(vpiSysTfCall, NULL));
        reader->StoreUserData();
        StoreReader(*reader);
    }
    catch (std::exception& e)
    {
        delete reader;
        vpi::HandleException(e.what());
    }
    return 0;
}

/**
 *  \copydoc ForeignLoader::LoadMemory()
 */
void LoadMemory(ForeignStorage& storage,
    const std::string& executable,
    const std::string& addressSpace,
    const codasip_address_t storageBase,
    const codasip_address_t adsLow,
    const codasip_address_t adsHigh,
    const bool forceHeapAndStack);

/**
 *  \brief  Generic VPI task to initialize array content from executable file.
 *          First all arguments are checked and then the whole array is
 *          initialized. Arguments are:
 *  \li \em hdl full hierarchical path to the memory storage, single dot is
 *          expected to be the path delimiter
 *  \li \em executable path to binary (executable) file, source data for the
 *          initialization
 *  \li \em addressSpace name of the address space
 *  \li \em storageBaseAddr base address for the whole parent memory object
 *          where data will be loaded.
 *  \li \em adsLow lowest aligned absolute address in the address space.
 *          Data will be loaded from this address.
 *  \li \em adsHigh highest aligned absolute address in the address space.
 *          This is the last address to load.
 *  \li \em sbcIndex sub-block index of given storage in a parent memory
 *  \li \em sbcMax number of sub-blocks in a parent memory, minimum is one
 */
template<class Loader>
PLI_INT32 ArrayInit(PLI_BYTE8*)
{   // parsing arguments
    std::string executable;
    std::string hdl;
    try
    {
        vpiHandle systf = vpi_handle(vpiSysTfCall, NULL);
        const std::string errorPrefix = vpi::GetErrorPrefix(systf);
        const std::string taskName = vpi::GetTaskName(systf);
        CHECK_CONDITION(vpi::GetParameterCount(systf) == 6)
            << errorPrefix << "Expecting exactly eight parameters for '" << taskName << "'.";
        vpiHandle argIterator = vpi_iterate(vpiArgument, systf);
        hdl = vpi::CheckAndReadStringParam(vpi_scan(argIterator), errorPrefix, taskName, 1);
        executable = vpi::CheckAndReadStringParam(vpi_scan(argIterator), errorPrefix, taskName, 2);
        const std::string addressSpace =
            vpi::CheckAndReadStringParam(vpi_scan(argIterator), errorPrefix, taskName, 3);
        const codasip_address_t baseAddress =
            vpi::CheckAndReadAddressParam(vpi_scan(argIterator), errorPrefix, taskName, 4);
        const codasip_address_t lowAddress =
            vpi::CheckAndReadAddressParam(vpi_scan(argIterator), errorPrefix, taskName, 5);
        const codasip_address_t highAddress =
            vpi::CheckAndReadAddressParam(vpi_scan(argIterator), errorPrefix, taskName, 6);
        // release the iterator
        vpi_free_object(argIterator);
        CHECK_CONDITION(!executable.empty())
            << errorPrefix << " : " << taskName << ": Empty executable path (1. parameter).";
        CHECK_CONDITION(!addressSpace.empty())
            << errorPrefix << " : " << taskName << ": Empty address space (2. parameter).";
        Loader::Init(vpi::CheckFullHierPath(hdl), executable, addressSpace, baseAddress, lowAddress, highAddress);
    }
    catch (std::exception& e)
    {
        vpi::HandleLoadException(e.what(), executable, hdl);
        return 1;
    }
    return 0;
}

/**
 *  \brief  Register new system function which should be used to deallocate all
 *          dynamically allocated global variables.
 */
void CleanRegister();

/**
 *  \brief  Register new system task which should be used to initialize content
 *          of array storage from executable file.
 */
template<class Loader>
inline void ArrayInitRegister()
{
    s_vpi_systf_data tf_data;

    tf_data.type = vpiSysTask;
    tf_data.sysfunctype = vpiSysTask;
    tf_data.tfname = const_cast<PLI_BYTE8*>(vpi::MEMORY_INIT);
    tf_data.calltf = ArrayInit<Loader>;
    tf_data.compiletf = NULL;
    tf_data.sizetf = NULL;
    tf_data.user_data = NULL;
    vpi_register_systf(&tf_data);
}

/**
 *  \brief  Register new system task which should be used to read value from of
 *          one array element.
 */
template<class Reader>
inline void ArrayReadRegister()
{
    s_vpi_systf_data tf_data;

    tf_data.type = vpiSysTask;
    tf_data.sysfunctype = vpiSysTask;
    tf_data.tfname = const_cast<PLI_BYTE8*>(vpi::MEMORY_READ);
    tf_data.calltf = ArrayRead<Reader>;
    tf_data.compiletf = ArrayReadCompile<Reader>;
    tf_data.sizetf = NULL;
    tf_data.user_data = NULL;
    vpi_register_systf(&tf_data);
}

}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_VPI_LIB_INTERFACE_H_
