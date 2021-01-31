#pragma once

#include <basis/seadTypes.h>

#include "KingSystem/Utils/Types.h"

namespace ksys {

class MessageReceiver;

struct MesTransceiverId {
    MesTransceiverId() { reset(); }
    MesTransceiverId(u32& id, MessageReceiver* receiver) : id(++id), receiver(receiver) {}
    ~MesTransceiverId() { reset(); }

    void reset() {
        queue_id = 0xffffffff;
        id = 0xffffffff;
        receiver = nullptr;
        next = nullptr;
    }

    MesTransceiverId& operator=(const MesTransceiverId& other) {
        queue_id = other.queue_id;
        id = other.id;
        receiver = other.receiver;
        next = other.next;
        return *this;
    }

    u32 queue_id = 0xffffffff;
    u32 id = 0xffffffff;
    MessageReceiver* receiver{};
    MesTransceiverId** next{};
};
KSYS_CHECK_SIZE_NX150(MesTransceiverId, 0x18);

}  // namespace ksys
