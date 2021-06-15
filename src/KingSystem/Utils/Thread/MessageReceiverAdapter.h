#pragma once

#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

class MessageReceiverAdapter : public MessageReceiverEx {
    SEAD_RTTI_OVERRIDE(MessageReceiverAdapter, MessageReceiverEx)
public:
    explicit MessageReceiverAdapter(MessageReceiver* wrapped);
    ~MessageReceiverAdapter() override;

protected:
    int handleMessage(const Message& message) override;
    void handleAck(const MessageAck& ack) override;

private:
    MessageReceiver* mReceiver;
};

}  // namespace ksys
