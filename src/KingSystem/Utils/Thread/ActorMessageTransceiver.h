#pragma once

#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"
#include "KingSystem/Utils/Thread/MessageTransceiverRxOnly.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"

namespace ksys {

namespace act {
class Actor;
}

class ActorMessageTransceiver final : public MessageTransceiverBase {
public:
    class IHandler : public MessageTransceiverRxOnly::IHandler,
                     public MessageTransceiverTxOnly::IHandler {};
    KSYS_CHECK_SIZE_NX150(IHandler, 0x10);

    explicit ActorMessageTransceiver(IHandler& handler);
    explicit ActorMessageTransceiver(IHandler& handler, act::Actor* actor);
    ~ActorMessageTransceiver() override;
    bool sendMessage(const MesTransceiverId& dest, const MessageType& type, void* user_data,
                     bool ack) override;
    bool sendMessageOnProcessingThread(const MesTransceiverId& dest, const MessageType& type,
                                       void* user_data, bool ack) override;
    bool sendMessage(IMessageBroker& broker, const MessageType& type, void* user_data,
                     bool ack) override;
    bool sendMessageOnProcessingThread(IMessageBroker& broker, const MessageType& type,
                                       void* user_data, bool ack) override;
    MessageReceiverEx* getReceiver() override;

private:
    class Receiver : public MessageReceiverEx {
        SEAD_RTTI_OVERRIDE(Receiver, MessageReceiverEx)
    public:
        explicit Receiver(IHandler& handler);
        ~Receiver() override;
        int handleMessage(const Message& message) override;
        void handleAck(const MessageAck& ack) override;

    private:
        IHandler& mHandler;
    };

    // TODO: rename if we figure out what this is used for
    bool getDebugArg(bool ack) const;

    Receiver mReceiver;
    act::Actor* mActor{};
};

}  // namespace ksys
