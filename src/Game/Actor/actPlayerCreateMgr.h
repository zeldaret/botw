#pragma once

#include <container/seadSafeArray.h>
#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <prim/seadStringBuilder.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/StringBoard.h"
#include "KingSystem/Utils/TrackerStub.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class InstParamPack;
class Actor;
}  // namespace ksys::act

namespace uking::ui {
enum class PouchItemType;
enum class EquipmentSlot;
}  // namespace uking::ui

namespace uking::act {
struct WeaponModifierInfo;

enum class CreateEquipmentSlot : u8 {
    WeaponSword = 0,
    WeaponShield = 1,
    WeaponBow = 2,
    ArmorHead = 3,
    ArmorUpper = 4,
    ArmorLower = 5,
    Length = 6,
};

inline bool isArmorCreateEquipmentSlot(s32 slot) {
    return slot == (s32)CreateEquipmentSlot::ArmorHead ||
           slot == (s32)CreateEquipmentSlot::ArmorUpper ||
           slot == (s32)CreateEquipmentSlot::ArmorLower;
}

// Used in both CreatePlayerEquipActorMgr and CreatePlayerTrashActorMgr,
// but stubbed out other than constructor and init
class PlayerCreateDebugStub {
public:
    void init();

private:
    s32 _0 = 3;
    sead::SafeString mDebugStatus;
    f32 _18 = 1;
    u32 _1c = 0;
    sead::Color4f mColor20 = sead::Color4f::cBlack;
    sead::Color4f mColor30 = sead::Color4f::cBlack;
    sead::Vector2f _40{0, 0};
    sead::Vector2f _48{1, 1};
    sead::Color4f mColor50 = sead::Color4f::cBlue;
    u64 _60 = 0;
    u64 _68 = 0;
    u64 _70 = 0;
    sead::Vector3f _78{0, 0, 0};
    sead::Color4f mColor84 = sead::Color4f::cBlack;
};
KSYS_CHECK_SIZE_NX150(PlayerCreateDebugStub, 0x98);

class CreatePlayerEquipActorMgr {
    SEAD_SINGLETON_DISPOSER(CreatePlayerEquipActorMgr)
    CreatePlayerEquipActorMgr();
    virtual ~CreatePlayerEquipActorMgr();

public:
    void init();
    void postCalc();
    void resetAll();
    void reset(s32 slot_idx);
    bool areAllWeaponActorsReady() const;
    bool isEquipmentProcReady(s32 slot_idx) const;
    ksys::act::Actor* tryGetEquipmentActor(s32 slot_idx);

    void doRequestCreateWeapon(s32 slot_idx, const sead::SafeString& name, int value,
                               const WeaponModifierInfo* modifier, const sead::SafeString& caller);

    void requestCreateWeapon(const sead::SafeString& name, int value,
                             const WeaponModifierInfo* modifier, const sead::SafeString& caller);

    void doRequestCreateArmor(s32 slot_idx, const sead::SafeString& name, int dye_color,
                              const sead::SafeString& caller);
    void requestCreateArmor(const sead::SafeString& name, int dye_color,
                            const sead::SafeString& caller);

    void requestCreateDefaultArmor(s32 slot_idx, const sead::SafeString& caller);
    void requestCreateArmorHeadB(const sead::SafeString& name, int dye_color,
                                 const sead::SafeString& caller);

private:
    enum class EntryStatus : s32 { Idle = 0, Loading = 1, Ready = 2 };

    template <typename T>
    class Slots {
    private:
        sead::SafeArray<T, (s32)CreateEquipmentSlot::Length> mArray;

    public:
        T& operator[](s32 idx) { return mArray[idx]; }
        const T& operator[](s32 idx) const { return mArray[idx]; }
        s32 size() const { return mArray.size(); }
    };

    class Entry {
        friend class CreatePlayerEquipActorMgr;
        sead::FixedStringBuilder<64> mActorName;
        EntryStatus mStatus = EntryStatus::Idle;
        ksys::act::BaseProcLink mProcLink;

        void reset() {
            mActorName.clear();
            mStatus = EntryStatus::Idle;
            mProcLink.reset();
        }
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x68);

    bool isSlotLoading(s32 slot_idx) const {
        return mIsLoading.isOnBit(slot_idx) && mEntries[slot_idx].mStatus == EntryStatus::Loading;
    }

    void deleteLoadingProc(s32 slot_idx) {
        if (mIsLoading.isOnBit(slot_idx)) {
            mProcHandles[slot_idx].deleteProc();
        }
    }

    void onSlotLoadingRequested(s32 slot_idx, const sead::SafeString& name) {
        if (mProcHandles[slot_idx].isAllocatedOrFailed()) {
            auto& entry = mEntries[slot_idx];
            entry.mActorName.copy(name.cstr());
            mIsLoading.setBit(slot_idx);
            entry.mStatus = EntryStatus::Loading;
        }
    }

    Slots<ksys::act::BaseProcHandle> mProcHandles{};
    sead::BitFlag8 mIsLoading;
    ksys::util::TrackerStub mTrackerStub;
    Slots<Entry> mEntries{};

    ksys::StringBoard mStringBoard;
    u64 _310 = 0;

    PlayerCreateDebugStub mDebugStub;
};
KSYS_CHECK_SIZE_NX150(CreatePlayerEquipActorMgr, 0x3B0);

// TODO
class CreatePlayerTrachActorMgr {};

bool needsArmorHeadB(const sead::SafeString& armor_head_name,
                     const sead::SafeString& armor_upper_name);
bool isArmorHeadMantleType2(const sead::SafeString& armor_head_name);
bool isArmorUpperNotUseMantleType0(const sead::SafeString& armor_upper_name);

}  // namespace uking::act
