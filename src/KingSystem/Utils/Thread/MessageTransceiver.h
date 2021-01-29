#pragma once

#include <basis/seadTypes.h>

#include "KingSystem/Utils/Types.h"

namespace ksys {

struct MesTransceiverId {
    MesTransceiverId() { reset(); }
    ~MesTransceiverId() { reset(); }

    void reset() {
        _0 = -1;
        _4 = -1;
        _8 = nullptr;
        _10 = nullptr;
    }

    MesTransceiverId& operator=(const MesTransceiverId& other) {
        _0 = other._0;
        _4 = other._4;
        _8 = other._8;
        _10 = other._10;
        return *this;
    }

    s32 _0{};
    s32 _4{};
    void* _8{};
    void* _10{};
};
KSYS_CHECK_SIZE_NX150(MesTransceiverId, 0x18);

}  // namespace ksys
