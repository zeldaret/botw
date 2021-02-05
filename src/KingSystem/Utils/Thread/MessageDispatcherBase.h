#pragma once

#include <prim/seadRuntimeTypeInfo.h>

namespace ksys {

class IMessageBrokerRegister;
class MessageReceiverEx;
struct MesTransceiverId;
struct MessageType;

class MessageDispatcherBase {
    SEAD_RTTI_BASE(MessageDispatcherBase)
public:
    MessageDispatcherBase();
    virtual ~MessageDispatcherBase();

    virtual void registerTransceiver(MessageReceiverEx& receiver) = 0;
    virtual void deregisterTransceiver(MessageReceiverEx& receiver) = 0;
    virtual bool sendMessage(const MesTransceiverId& src, const MesTransceiverId& dest,
                             const MessageType& type, void* user_data, bool ack, bool) = 0;
    virtual bool sendMessageOnProcessingThread(const MesTransceiverId& src,
                                               const MesTransceiverId& dest,
                                               const MessageType& type, void* user_data, bool ack,
                                               bool) = 0;
    virtual bool sendMessage(const MesTransceiverId& src, IMessageBrokerRegister& reg,
                             const MessageType& type, void* user_data, bool ack, bool) = 0;
    virtual bool sendMessageOnProcessingThread(const MesTransceiverId& src,
                                               IMessageBrokerRegister& reg, const MessageType& type,
                                               void* user_data, bool ack, bool) = 0;
    virtual void update() = 0;

protected:
    void setAsGlobalInstance();
};

}  // namespace ksys
