/**
 * @file client.h
 * @brief Client implementations for NEX.
 */
#pragma once

#include <nn/nex/system.h>

namespace nn {
namespace nex {
class Credentials;
class EndPoint;
class Message;
class ProtocolCallContext;
class ProtocolRequestBrokerInterface;

class Protocol : public nn::nex::SystemComponent {
public:
    enum _Command { Response, Request };

    enum _Type {
        Client,  // implemented in nn::nex::ClientProtocol
        Server   // implemented in nn::nex::ServerProtocol
    };

    Protocol(u32);

    virtual ~Protocol();

    virtual char* GetType() const;
    virtual bool IsAKindOf(char const*) const;
    virtual void EnforceDeclareSysComponentMacro();

    virtual bool BeginInitialization();
    virtual bool BeginTermination();

    virtual nn::nex::Protocol::_Type GetProtocolType() const = 0;
    virtual void EndPointDisconnected(nn::nex::EndPoint*);
    virtual void FaultDetected(nn::nex::EndPoint*, u32);
    virtual nn::nex::Protocol* Clone() const;
    virtual bool Reload();

    nn::nex::EndPoint* GetOutgoingConnection() const;
    void SetIncomingConnection(nn::nex::EndPoint*);
    void SetProtocolID(u16);
    void AddMethodID(nn::nex::Message*, u32);
    void CopyMembers(nn::nex::Protocol const*);
    void AssociateProtocolRequestBroker(nn::nex::ProtocolRequestBrokerInterface*);
    void ClearFlag(u32 newFlag);

    static void ExtractProtocolKey(nn::nex::Message*, nn::nex::Protocol::_Command&, u16&);
    static bool IsOldRVDDLVersion(nn::nex::EndPoint*);

    u16 mProtocolID;  // _48
    u16 _4A;
    u32 _4C;
    nn::nex::EndPoint* mOutgoingConnection;                     // _50
    nn::nex::ProtocolRequestBrokerInterface* mBrokerInterface;  // _58
    u32 mFlags;                                                 // _60
    u32 _64;
    nn::nex::EndPoint* mIncomingConnection;  // _68
    u32 mUseLoopback;                        // _70 (boolean)
    u32 _74;
    u64 _78;
    u32 _80;
    u32 _84;
};

class ClientProtocol : public nn::nex::Protocol {
public:
    ClientProtocol(u32);

    virtual ~ClientProtocol();

    virtual char* GetType() const;
    virtual bool IsAKindOf(char const*) const;
    virtual void EnforceDeclareSysComponentMacro();

    virtual nn::nex::Protocol::_Type GetProtocolType() const = 0;

    virtual void ExtractCallSpecificResults(nn::nex::Message*, nn::nex::ProtocolCallContext*) = 0;
    virtual nn::nex::ClientProtocol* CreateResponder() const = 0;
    virtual void SetDefaultCredentials(nn::nex::Credentials*);

    bool SendOverLocalLoopback(nn::nex::ProtocolCallContext*, nn::nex::Message*);
    bool SendRMCMessage(nn::nex::ProtocolCallContext*, nn::nex::Message*);
    void ProcessResponse(nn::nex::Message*, nn::nex::EndPoint*);

    nn::nex::Credentials* mCredentials;  // _88
};

class ServerProtocol : public nn::nex::Protocol {
public:
    ServerProtocol(u32);

    virtual ~ServerProtocol();

    virtual char* GetType() const;
    virtual bool IsAKindOf(char const*) const;
    virtual void EnforceDeclareSysComponentMacro();

    virtual nn::nex::Protocol::_Type GetProtocolType() const = 0;

    virtual void DispatchProtocolMessage(nn::nex::Message*, nn::nex::Message*, bool*,
                                         nn::nex::EndPoint*) = 0;
    virtual void DispatchProtocolMessageWithAttemptCount(u64, nn::nex::Message*, nn::nex::Message*,
                                                         bool*, int*, nn::nex::EndPoint*);
    virtual bool UseAttemptCountMethod();
};
};  // namespace nex
};  // namespace nn