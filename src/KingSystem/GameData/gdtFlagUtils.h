#pragma once

#include "KingSystem/GameData/gdtManager.h"

namespace ksys::gdt {

inline bool getBool(FlagHandle handle, bool debug = false) {
    bool value{};

    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getBool(handle, &value, debug);

    return value;
}

}  // namespace ksys::gdt
