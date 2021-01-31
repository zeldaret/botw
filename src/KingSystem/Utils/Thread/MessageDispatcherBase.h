#pragma once

#include <prim/seadRuntimeTypeInfo.h>

namespace ksys {

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
                             const MessageType& type, void* user_data, bool ack) = 0;
    virtual bool sendMessageOnProcessingThread(const MesTransceiverId& src,
                                               const MesTransceiverId& dest,
                                               const MessageType& type, void* user_data,
                                               bool ack) = 0;
    // TODO
    virtual void m_8() = 0;
    virtual void m_9() = 0;
    virtual void update() = 0;

protected:
    void setAsGlobalInstance();
};

}  // namespace ksys
