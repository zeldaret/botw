#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Thread/MessageReceiver.h"

namespace ksys {

class MessageReceiverEx : public MessageReceiver {
public:
    MessageReceiverEx();
    ~MessageReceiverEx() override;
    bool m1(void*) override;
    void m2(void* x) override;

    bool checkFlag() const;
    bool checkCounter() const;
    void setFlag(bool update_counter);

    void setFlagPointer(u8* ptr);
    void clearFlagPointer();

    SEAD_RTTI_BASE(MessageReceiverEx)

protected:
    virtual bool m6(void* x);
    virtual void m7(void* x);

private:
    u8* mFlag{};
    sead::Atomic<s32> mCounter;
};

}  // namespace ksys
