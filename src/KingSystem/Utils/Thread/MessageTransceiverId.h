#pragma once

#include <basis/seadTypes.h>
#include <tuple>

#include "KingSystem/Utils/Types.h"

namespace ksys {

class MessageReceiver;

struct MesTransceiverId {
    MesTransceiverId() : receiver(), self_ref() { reset(); }
    MesTransceiverId(const MesTransceiverId& other) { *this = other; }
    MesTransceiverId(u32& id, MessageReceiver* receiver)
        : id(++id), receiver(receiver), self_ref() {}
    ~MesTransceiverId() { reset(); }

    void reset() {
        queue_id = 0xffffffff;
        id = 0xffffffff;
        receiver = nullptr;
        self_ref = nullptr;
    }

    MesTransceiverId& operator=(const MesTransceiverId& other) {
        queue_id = other.queue_id;
        id = other.id;
        receiver = other.receiver;
        self_ref = other.self_ref;
        return *this;
    }

    bool isRegistered() const {
        if (!self_ref || !*self_ref)
            return false;

        const auto fields = [](const MesTransceiverId& i) { return std::tie(i.queue_id, i.id); };
        return fields(*this) == fields(**self_ref);
    }

    u32 queue_id = 0xffffffff;
    u32 id = 0xffffffff;
    MessageReceiver* receiver;
    /// If registered, this points to a pointer that points to this object.
    /// Otherwise, this value is nullptr.
    MesTransceiverId** self_ref;
};
KSYS_CHECK_SIZE_NX150(MesTransceiverId, 0x18);

}  // namespace ksys
