#pragma once

#include <basis/seadTypes.h>

#include "KingSystem/Utils/Types.h"

namespace ksys {

class MesTransceiverIdGen;

struct MesTransceiverId {
    MesTransceiverId() { reset(); }
    MesTransceiverId(u32& id, MesTransceiverIdGen* generator)
        : _0(0xffffffff), id(++id), generator(generator) {}

    ~MesTransceiverId() { reset(); }

    void reset() {
        _0 = 0xffffffff;
        id = 0xffffffff;
        generator = nullptr;
        next = nullptr;
    }

    MesTransceiverId& operator=(const MesTransceiverId& other) {
        _0 = other._0;
        id = other.id;
        generator = other.generator;
        next = other.next;
        return *this;
    }

    u32 _0{};
    u32 id{};
    MesTransceiverIdGen* generator{};
    MesTransceiverId** next{};
};
KSYS_CHECK_SIZE_NX150(MesTransceiverId, 0x18);

}  // namespace ksys
