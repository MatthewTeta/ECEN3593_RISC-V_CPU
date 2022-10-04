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
 *  \date   Mar 4, 2016
 *  \brief  Main include header to import all resource template definitions.
 */

#ifndef SIMULATOR_RESOURCES_CSR_INCLUDE_H_
#define SIMULATOR_RESOURCES_CSR_INCLUDE_H_

#include "simulator/resources/csr_access_checker.h"
#include "simulator/resources/csr_address_checker.h"
#include "simulator/resources/csr_ahb_arbiter.h"
#include "simulator/resources/csr_ahb_bus.h"
#include "simulator/resources/csr_ahb_initiator_interface.h"
#include "simulator/resources/csr_ahb_pac.h"
#include "simulator/resources/csr_ahb_profiler.h"
#include "simulator/resources/csr_ahb_target_interface.h"
#include "simulator/resources/csr_axi_arbiter.h"
#include "simulator/resources/csr_axi_bus.h"
#include "simulator/resources/csr_axi_initiator_interface.h"
#include "simulator/resources/csr_axi_lite_bus.h"
#include "simulator/resources/csr_axi_lite_initiator_interface.h"
#include "simulator/resources/csr_axi_lite_pac.h"
#include "simulator/resources/csr_axi_lite_target_interface.h"
#include "simulator/resources/csr_axi_pac.h"
#include "simulator/resources/csr_axi_request.h"
#include "simulator/resources/csr_axi_target_interface.h"
#include "simulator/resources/csr_cache.h"
#include "simulator/resources/csr_cache_block.h"
#include "simulator/resources/csr_cache_block_data_interface.h"
#include "simulator/resources/csr_cache_block_instruction_interface.h"
#include "simulator/resources/csr_cache_block_interface_base.h"
#include "simulator/resources/csr_cache_block_interface_buffer.h"
#include "simulator/resources/csr_cache_interface.h"
#include "simulator/resources/csr_cache_master_interface.h"
#include "simulator/resources/csr_cache_registers.h"
#include "simulator/resources/csr_cache_registers_interface.h"
#include "simulator/resources/csr_cache_registers_storage.h"
#include "simulator/resources/csr_cache_registers_target_interface.h"
#include "simulator/resources/csr_cache_request.h"
#include "simulator/resources/csr_cache_rpl.h"
#include "simulator/resources/csr_cache_storage.h"
#include "simulator/resources/csr_cpb_bus.h"
#include "simulator/resources/csr_cpb_initiator_interface.h"
#include "simulator/resources/csr_cpb_pac.h"
#include "simulator/resources/csr_cpb_target_interface.h"
#include "simulator/resources/csr_dff_storage.h"
#include "simulator/resources/csr_dumper.h"
#include "simulator/resources/csr_endianness.h"
#include "simulator/resources/csr_foreign.h"
#include "simulator/resources/csr_fve_interface.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_interface.h"
#include "simulator/resources/csr_interface_base.h"
#include "simulator/resources/csr_memory.h"
#include "simulator/resources/csr_memory_storage.h"
#include "simulator/resources/csr_pac_base.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_payload_sentinel.h"
#include "simulator/resources/csr_port.h"
#include "simulator/resources/csr_port_base.h"
#include "simulator/resources/csr_register.h"
#include "simulator/resources/csr_register_file.h"
#include "simulator/resources/csr_rw_profiler.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/resources/csr_signal.h"
#include "simulator/resources/csr_storage_sentinel.h"
#include "simulator/resources/csr_tcm.h"
#include "simulator/resources/csr_unaligned_cpb.h"
#include "simulator/resources/csr_variable.h"
#include "simulator/resources/csr_variable_storage.h"
#include "simulator/resources/csr_watchpoint.h"

// defined in csr_sentinel, but can be used in every header
#undef RES_LOG

#endif   // SIMULATOR_RESOURCES_CSR_INCLUDE_H_
