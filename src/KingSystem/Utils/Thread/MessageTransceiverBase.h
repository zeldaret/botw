#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Thread/MessageDispatcherBase.h"
#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

class IMessageBroker;
class IMessageBrokerRegister;
struct MesTransceiverId;
struct MessageType;

class MessageTransceiverBase {
public:
    MessageTransceiverBase();
    virtual ~MessageTransceiverBase();
    bool checkReceiverFlag();
    bool isWaitingForAck();
    virtual bool sendMessage(const MesTransceiverId& dest, const MessageType& type, void* user_data,
                             bool ack);
    virtual bool sendMessageOnProcessingThread(const MesTransceiverId& dest,
                                               const MessageType& type, void* user_data, bool ack);
    virtual bool sendMessage(IMessageBroker& broker, const MessageType& type, void* user_data,
                             bool ack);
    virtual bool sendMessageOnProcessingThread(IMessageBroker& broker, const MessageType& type,
                                               void* user_data, bool ack);
    virtual MessageReceiverEx* getReceiver() = 0;
    MessageDispatcherBase* getDispatcher();
    MesTransceiverId* getId() const { return mId; }
    IMessageBrokerRegister* getRegister(IMessageBroker& broker) const;

    static void setGlobalDispatcher(MessageDispatcherBase* dispatcher);

protected:
    void registerReceiver(MessageReceiverEx& receiver) {
        getDispatcher()->registerTransceiver(receiver);
        mId = receiver.MessageReceiver::getId();
    }

    void deregisterReceiver(MessageReceiverEx& receiver) {
        getDispatcher()->deregisterTransceiver(receiver);
    }

private:
    static MessageDispatcherBase* sDispatcher;

    MessageDispatcherBase* mDispatcher = sDispatcher;
    MesTransceiverId* mId{};
};

}  // namespace ksys
