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
 *  \date   Dec 18, 2017
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RSPL_RSP_SERVER_H_
#define SIMULATOR_RSPL_RSP_SERVER_H_

#include "simulator/rspl/rsp_interface.h"
#include "simulator/simbase/codasip_interface.h"

#include <thread>

namespace codasip {
class Socket;
class ServerSocket;
}   // namespace codasip

namespace codasip {
namespace debugger {

// forward
class RspInterpreter;
class RspTarget;
class RspPacket;

/**
 * \class RspServer
 * \brief Top level RSP server that runs in the simulator
 */
class RspServer
{
public:
    /**
     * \brief Constructor
     * \param port Port that is used for a communication
     */
    RspServer();
    /**
     * \brief Destructor
     */
    virtual ~RspServer();
    /**
     * \copydoc RspServerInterface::Register
     */
    void Register(RspTarget& target);
    /**
     * \brief Start waiting on the connection
     * \param port TCP port
     * \param spawn If true, a new thread is created and RSP runs there
     */
    void Start(const int serverPort, const int lldbPort = 0, const bool spawn = true);
    /**
     * \brief Stop the server
     */
    void Stop();
    /**
     * \brief Return info whether the server has started or not
     */
    bool IsRunning() const;

private:
    // interpreter requires access to server
    friend class RspInterpreter;
    friend class RspTarget;

    void Listen(const int);
    void Run();
    void Accept();
    void SendAck(const bool);
    bool ReceiveAck();

    bool ReadPacket(RspPacket&);
    bool WritePacket(const RspPacket&);
    int ReadData(std::string&);
    int WriteData(const std::string&);

    void Deatach();
    void SetAckMode(const bool);

    RspTarget& GetTarget();

    /// server side socket
    ServerSocket* m_ServerSocket;
    /// client socket
    Socket* m_ClientSocket;
    /// RSP Target
    RspTarget* m_Target;
    /// Command interpreter
    RspInterpreter& m_Interpreter;
    /// Execution thread
    std::thread m_Thread;
    /// Info whether the server is running
    bool m_Running;
    /// Info whether the server is running
    bool m_AckMode;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool RspServer::IsRunning() const
{
    return m_Running;
}

}   // namespace debugger
}   // namespace codasip

#endif   // SIMULATOR_RSPL_RSP_SERVER_H_
