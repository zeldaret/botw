#pragma once

#include <arpa/inet.h>  //FIXME requires proper musl-setup
#include <sys/socket.h>
#include "RootObject.h"

namespace nn {
namespace nex {
class TransportProtocol {
public:
    enum Type {
        Sock_Default = 0,
        Sock_Stream = SOCK_STREAM,
        Sock_DGram = SOCK_DGRAM,
        Sock_Raw = SOCK_RAW,
        Sock_SeqPacket = SOCK_SEQPACKET,
        Sock_NonBlock = SOCK_NONBLOCK
    };
};

class SocketDriver : nn::nex::RootObject {
public:
    typedef in_addr_t InetAddress;

    enum _SocketFlag : int32_t {
        Msg_None = 0,
        Msg_Oob = MSG_OOB,
        Msg_Peek = MSG_PEEK,
        Msg_DontRoute = MSG_DONTROUTE,
        Msg_Eor = MSG_EOR,
        Msg_Trunc = MSG_TRUNC,
        Msg_CTrunc = MSG_CTRUNC,
        Msg_WaitAll = MSG_WAITALL,
        Msg_DontWait = MSG_DONTWAIT,
        Msg_Eof = MSG_EOF,
        Msg_Notification = MSG_NOTIFICATION,
        Msg_Nbio = MSG_NBIO,
        Msg_Compat = MSG_COMPAT,
        //    Msg_SoCallbck = MSG_SOCALLBCK,
        //    Msg_NoSignal = MSG_NOSIGNAL,
        Msg_CMsg_CloExec = MSG_CMSG_CLOEXEC
    };

    class Socket {
        virtual void Open(nn::nex::TransportProtocol::Type);
        virtual void Close();
        virtual void Bind(ushort&);
        virtual void RecvFrom(uchar*, ulong, InetAddress*, ulong*,
                              nn::nex::SocketDriver::_SocketFlag);
        virtual void SendTo(uchar const*, ulong, nn::nex::SocketDriver::InetAddress const&, ulong*);
    };

    class PollInfo {};

    virtual Socket* Create();
    virtual void Delete(Socket*);
    virtual int Poll(PollInfo*, uint, uint);
    virtual bool CanUseGetAllReceivableSockets();
    virtual void GetAllReceivableSockets(Socket**, ulong, uint);
};

class BerkelySocket : public SocketDriver::Socket {};

class BerkeleySocketDriver
    : SocketDriver {  // inherits SocketDriver and RootObject but not documented
    virtual ~BerkeleySocketDriver();
};

class ClientWebSocketDriver : SocketDriver {
    class ClientWebSocket : Socket {};
};
};  // namespace nex
};  // namespace nn