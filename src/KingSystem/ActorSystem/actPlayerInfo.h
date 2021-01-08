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
};

}  // namespace ksys::act
