#pragma once

#include "KingSystem/Utils/Thread/MessageReceiverEx.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace ksys {

class Message;

class MessageTransceiverTxOnly final : public MessageTransceiverBase {
public:
    class IHandler {
    public:
        virtual ~IHandler() = default;
        virtual void handleAck(const MessageAck& ack) = 0;
    };

    explicit MessageTransceiverTxOnly(IHandler& handler);
    ~MessageTransceiverTxOnly() override;
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
        explicit Receiver(IHandler& handler) : mHandler(handler) {}
        ~Receiver() override;
        void handleAck(const MessageAck& ack) override;

    private:
        IHandler& mHandler;
    };

    Receiver mReceiver;
};

}  // namespace ksys
