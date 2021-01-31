#pragma once

#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

class MessageReceiverAdapter : public MessageReceiverEx {
    SEAD_RTTI_OVERRIDE(MessageReceiverAdapter, MessageReceiverEx)
public:
    explicit MessageReceiverAdapter(MessageReceiver* wrapped);
    ~MessageReceiverAdapter() override;

protected:
    bool m6(void* x) override;
    void m7(void* x) override;

private:
    MessageReceiver* mReceiver;
};

}  // namespace ksys
