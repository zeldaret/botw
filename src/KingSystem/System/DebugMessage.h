#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

struct DebugMessage {
    DebugMessage() = default;
    explicit DebugMessage(const sead::SafeString& msg) : message(msg) {}

    virtual ~DebugMessage() { ; }

    void log(const char* format, ...);

    u64 _8 = 0;
    sead::FixedSafeString<64> message;
    sead::Color4f color = sead::Color4f::cWhite;
    f32 _78 = 0.3;
    f32 _7c = 0.3;
    f32 _80 = 0.3;
    f32 _84 = 0.8;
    bool _88 = true;
    bool _89 = true;
};
KSYS_CHECK_SIZE_NX150(DebugMessage, 0x90);

}  // namespace ksys
