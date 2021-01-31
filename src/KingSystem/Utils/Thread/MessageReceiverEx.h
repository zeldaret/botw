#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Thread/MessageReceiver.h"

namespace ksys {

class MessageReceiverEx : public MessageReceiver {
public:
    MessageReceiverEx();
    ~MessageReceiverEx() override;
    int receive(const Message& message) override;
    void receive(const MessageAck& ack) override;

    bool checkFlag() const;
    bool checkCounter() const;
    void setFlag(bool update_counter);

    void setFlagPointer(u8* ptr);
    void clearFlagPointer();

    SEAD_RTTI_BASE(MessageReceiverEx)

protected:
    virtual int handleMessage(const Message& message);
    virtual void handleAck(const MessageAck& ack);

private:
    u8* mFlag{};
    sead::Atomic<s32> mCounter;
};

}  // namespace ksys
