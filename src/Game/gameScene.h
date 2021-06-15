#pragma once

#include <prim/seadSafeString.h>

namespace uking {

// TODO
class GameScene {
public:
    static bool isOpenWorldDemo() { return sIsOpenWorldDemo; }

    /// Get the current map type (e.g. MainFieldDungeon)
    static const sead::SafeString& getCurrentMapType();

    /// Get the current map name (e.g. RemainsWind, FinalTrial, ...)
    static const sead::SafeString& getCurrentMapName();

private:
    static bool sIsOpenWorldDemo;
};

}  // namespace uking
