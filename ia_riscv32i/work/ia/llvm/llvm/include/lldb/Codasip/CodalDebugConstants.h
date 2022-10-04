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
 * Codasip s.r.o. and are protected by trade secret and copyright law. In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Albert Miko
 *  \date   2018-09-25
 *  \brief  Constants for reading codal debug info from json.
 */

#ifndef liblldb_codasip_codaldebug_consts_h_
#define liblldb_codasip_codaldebug_consts_h_

/// \{ \brief names of json objects in codal debug info
const std::string FILE_TABLE = "FileTab";
const std::string LINE_TABLE = "LineTab";
const std::string BLOCKS_ROOT = "Root";
const std::string BLOCKS = "Blocks";
const std::string VARIABLES = "Variables";
const std::string RANGES = "Ranges";
const std::string FUNC_INFO = "FunctionInfo";
const std::string FI_TYPE = "type";
const std::string FI_NAME = "name";
const std::string FI_INSTANCE_ID = "instanceID";
/// \}

#endif // liblldb_codasip_codaldebug_consts_h_
