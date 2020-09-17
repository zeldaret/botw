#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"

namespace uking {

// FIXME: incomplete
class aoc2 {
    SEAD_SINGLETON_DISPOSER(aoc2)

    aoc2();
    virtual ~aoc2();

public:
    void init(sead::Heap* heap);

    static bool
    shouldApplyMasterModeDamageMultiplier(const ksys::act::ActorConstDataAccess& accessor);

    bool isTestOfStrengthShrine() const;

    bool rankUpEnemy(const sead::SafeString& actor_name, const ksys::map::Object& obj,
                     const char** new_name);
};

}  // namespace uking
