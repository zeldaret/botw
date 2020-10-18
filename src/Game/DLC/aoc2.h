#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
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
    SEAD_ENUM(Flags1, F0, F1, F2, F3, F4, EnableLifeRegen, F7, ApplyDamageMultiplier);
    SEAD_ENUM(Flags2, EnableHardMode);

    void init(sead::Heap* heap);

    static bool
    shouldApplyMasterModeDamageMultiplier(const ksys::act::ActorConstDataAccess& accessor);
    static void buffDamage(s32& damage);

    bool isTestOfStrengthShrine() const;

    bool rankUpEnemy(const sead::SafeString& actor_name, const ksys::map::Object& obj,
                     const char** new_name);

    bool checkFlag1(Flags1 flag) const { return mFlags1.isOnBit(flag); }
    bool checkFlag2(Flags2 flag) const { return mFlags2.isOnBit(flag); }

    u8 TEMP[0x28];  // Temp to get flag offsets correct
    sead::BitFlag32 mFlags1;
    sead::BitFlag32 mFlags2;
};

}  // namespace uking
