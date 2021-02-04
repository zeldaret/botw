#pragma once

#include "KingSystem/Utils/Thread/MessageReceiverEx.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace ksys {

class Message;

class MessageTransceiverRxOnly : public MessageTransceiverBase {
public:
    class IHandler {
    public:
        virtual ~IHandler() = default;
        virtual int handleMessage(const Message& message) = 0;
    };

    explicit MessageTransceiverRxOnly(IHandler& handler);
    ~MessageTransceiverRxOnly() override;
    MessageReceiverEx* getReceiver() override;

private:
    class Receiver : public MessageReceiverEx {
        SEAD_RTTI_OVERRIDE(Receiver, MessageReceiverEx)
    public:
        explicit Receiver(IHandler& handler) : mHandler(handler) {}
        ~Receiver() override;
        int handleMessage(const Message& message) override;

    private:
        IHandler& mHandler;
    };

    Receiver mReceiver;
};

}  // namespace ksys
