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
 * \brief	Header file of cross-platform thread
 * \author	Hons Petr
 * \date	9.7.2014
 */

#ifndef THREADSL_THREAD_H_
#define THREADSL_THREAD_H_

namespace codasip {
/**
 * \addtogroup OS
 * \{
 * \defgroup Threadsl     Thread and synchronization library
 * \{
 * Uniform access to operation system specific threads
 * and synchronization primitives (mutex, semaphore).
 */

/// Namespace for creating and managing threads.
namespace threads {

/// Namespace for accessing and managing current thread.
namespace this_thread {
/**
 * \brief Suspend current thread for given time in milliseconds.
 * \param millisec Number of milliseconds current thread should be suspended for.
 */
void Sleep(unsigned int millisec);

}   // namespace this_thread
}   // namespace threads
}   // namespace codasip

#endif /* THREADSL_THREAD_H_ */
