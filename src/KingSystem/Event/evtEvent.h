#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>

namespace ksys::evt {

class OrderParam;
// TODO
class Event {
public:
    Event();
    virtual ~Event();

    enum class Flag : u64 {
        _80000000000 = 0x80000000000,
    };

    bool hasFlag(Flag flag) const { return mFlags.isOn(flag); }

private:
    u8 TEMP_0[0x338];
    sead::TypedBitFlag<Flag> mFlags;
};
// sizeof() = 0x620

}  // namespace ksys::evt
