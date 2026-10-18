#pragma once

#include <prim/seadSafeString.h>

namespace uking {

// TODO
class GameScene {
public:
    static bool isOpenWorldDemo() { return sIsOpenWorldDemo; }

private:
    static bool sIsOpenWorldDemo;
};

}  // namespace uking
