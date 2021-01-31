#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys {

class MessageReceiver {
public:
    MessageReceiver();
    virtual ~MessageReceiver();
    virtual MesTransceiverId* getId();
    virtual bool m1(void*);
    virtual void m2(void* x);
    virtual void setField0(const u32& value) { mTransceiverId.queue_id = value; }

protected:
    MesTransceiverId mTransceiverId;

private:
    static u32 sId;
};

}  // namespace ksys
