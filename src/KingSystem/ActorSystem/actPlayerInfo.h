#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {

class PlayerBase;

// TODO
class PlayerInfo {
    SEAD_SINGLETON_DISPOSER(PlayerInfo)
    PlayerInfo();
    virtual ~PlayerInfo();

public:
    PlayerBase* getPlayer() const;
    s32 getLife() const;
    u32 getMaxHearts() const;
    f32 getMaxStamina() const;
};

}  // namespace ksys::act
