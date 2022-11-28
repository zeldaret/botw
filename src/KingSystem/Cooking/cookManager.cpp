#include "KingSystem/Cooking/cookManager.h"
#include <codec/seadHashCRC32.h>
#include <typeindex>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys {

CookingMgr::CookingMgr() = default;

SEAD_SINGLETON_DISPOSER_IMPL(CookingMgr)

CookingMgr::~CookingMgr() {
    if (mConfig) {
        delete mConfig;
        mConfig = nullptr;
    }
}

struct CookingEffect {
    sead::SafeString name;
    u32 effect_id;
};

static const CookingEffect sCookingEffects[CookingMgr::NumEffects]{
    {"None", -1u},     {"LifeRecover", 1},    {"LifeMaxUp", 2},    {"ResistHot", 4},
    {"ResistCold", 5}, {"ResistElectric", 6}, {"AttackUp", 10},    {"DefenseUp", 11},
    {"Quietness", 12}, {"MovingSpeed", 13},   {"GutsRecover", 14}, {"ExGutsMaxUp", 15},
    {"Fireproof", 16},
};

struct Crc32Constants {
    util::InitConstants init_constants;
    const u32 crc32_life_recover = sead::HashCRC32::calcStringHash("LifeRecover");
    const u32 crc32_guts_performance = sead::HashCRC32::calcStringHash("GutsPerformance");
    const u32 crc32_stamina_recover = sead::HashCRC32::calcStringHash("StaminaRecover");
    const u32 crc32_life_max_up = sead::HashCRC32::calcStringHash("LifeMaxUp");
    const u32 crc32_resist_hot = sead::HashCRC32::calcStringHash("ResistHot");
    const u32 crc32_resist_cold = sead::HashCRC32::calcStringHash("ResistCold");
    const u32 crc32_resist_electric = sead::HashCRC32::calcStringHash("ResistElectric");
    const u32 crc32_all_speed = sead::HashCRC32::calcStringHash("AllSpeed");
    const u32 crc32_attack_up = sead::HashCRC32::calcStringHash("AttackUp");
    const u32 crc32_defense_up = sead::HashCRC32::calcStringHash("DefenseUp");
    const u32 crc32_quietness = sead::HashCRC32::calcStringHash("Quietness");
    const u32 crc32_fireproof = sead::HashCRC32::calcStringHash("Fireproof");
};

static Crc32Constants sCrc32Constants;

// NON_MATCHING
void CookingMgr::cookFail(CookItem& item) {
    auto& fail_actor_name = mFailActorName;

    if (item.name.isEmpty())
        item.name = fail_actor_name;

    f32 stamina_recover_x;
    if (item.name == fail_actor_name) {
        // Dubious food
        item.stamina_recover_y = 0;
        f32 min_recovery = (f32)(s32)mFALR;
        stamina_recover_x =
            min_recovery > item.stamina_recover_x ? min_recovery : item.stamina_recover_x;
    } else {
        // Rock-hard food
        item.stamina_recover_y = 0;
        stamina_recover_x = (f32)(s32)mSFALR;
    }

    item.stamina_recover_x = stamina_recover_x;
    item.cook_effect_0_y = 0.0f;
    item.cook_effect_0_x = -1;
    item.cook_effect_1 = 2;
}

// NON_MATCHING
void CookingMgr::cookFailForMissingConfig(CookItem& item, const sead::FixedSafeString<64>& name) {
    const auto& fail_actor_name = mFailActorName;

    f32 stamina_recover_x;
    if (name.isEmpty() || name == fail_actor_name) {
        item.name = fail_actor_name;
        item.stamina_recover_y = 0;
        stamina_recover_x = (f32)(s32)mFALR;
    } else {
        item.name = name;
        item.stamina_recover_y = 0;
        stamina_recover_x = (f32)(s32)mSFALR;
    }

    item.stamina_recover_x = stamina_recover_x;
    item.cook_effect_0_y = 0.0f;
    item.cook_effect_0_x = -1;
    item.cook_effect_1 = 1;
}

void CookingMgr::init(sead::Heap* heap) {
    res::LoadRequest req;

    req.mRequester = "CookingMgr";
    req._22 = false;

    sead::FixedSafeString<0x80> path;
    path.format("Cooking/CookData.byml");

    auto* res = sead::DynamicCast<sead::DirectResource>(mResHandle.load(path, &req));
    if (!res)
        return;

    mConfig = mConfig ? new (mConfig) al::ByamlIter(res->getRawData()) :
                        new (heap) al::ByamlIter(res->getRawData());

    mCookingEffectNameIdMap.clear();

    for (int effect_idx = 0; effect_idx < NumEffects; effect_idx++) {
        auto& effect = sCookingEffects[effect_idx];
        u32 name_hash = sead::HashCRC32::calcStringHash(effect.name);
        mCookingEffectNameIdMap.insert(name_hash, effect.effect_id);
    }

    for (int i = 0; i < NumEffectSlots; i++) {
        mCookingEffectEntries[i] = CookingEffectEntry{};
        mCookingEffectEntries[i].ssa = 0;
    }

    mNMMR[0] = 1.0f;
    mNMMR[1] = 1.0f;
    mNMMR[2] = 1.0f;
    mNMMR[3] = 1.0f;
    mNMMR[4] = 1.0f;

    mNMSSR[0] = 0;
    mNMSSR[1] = 5;
    mNMSSR[2] = 10;
    mNMSSR[3] = 15;
    mNMSSR[4] = 20;

    mFairyTonicName = "Item_Cook_C_16";
    mFairyTonicNameHash = sead::HashCRC32::calcStringHash(mFairyTonicName);

    mFailActorName = "Item_Cook_O_01";
    mFailActorNameHash = sead::HashCRC32::calcStringHash(mFailActorName);

    mMonsterExtractName = "Item_Material_08";
    mMonsterExtractNameHash = sead::HashCRC32::calcStringHash(mMonsterExtractName);

    mLRMR = 1.0;
    mSFALR = 1;
    mSSAET = 300;
    mFALRMR = 1.0;
    mFALR = 4;

    al::ByamlIter iter;
    al::ByamlIter cei_iter;
    al::ByamlIter entry_iter;

    const char* string_val = nullptr;
    int int_val;
    u32 uint_val;
    float float_val;

    if (mConfig->tryGetIterByKey(&iter, "System")) {
        if (iter.tryGetStringByKey(&string_val, "FA")) {
            mFailActorName = string_val;
            mFailActorNameHash = sead::HashCRC32::calcStringHash(mFailActorName);
        }
        if (iter.tryGetStringByKey(&string_val, "FCA")) {
            mFairyTonicName = string_val;
            mFairyTonicNameHash = sead::HashCRC32::calcStringHash(mFairyTonicName);
        }
        if (iter.tryGetStringByKey(&string_val, "MEA")) {
            mMonsterExtractName = string_val;
            mMonsterExtractNameHash = sead::HashCRC32::calcStringHash(mMonsterExtractName);
        }

        if (iter.tryGetFloatByKey(&float_val, "LRMR") && float_val >= 0)
            mLRMR = float_val;
        if (iter.tryGetFloatByKey(&float_val, "FALRMR") && float_val >= 0)
            mFALRMR = float_val;
        if (iter.tryGetIntByKey(&int_val, "FALR") && int_val >= 0)
            mFALR = int_val;
        if (iter.tryGetIntByKey(&int_val, "SFALR") && int_val >= 0)
            mSFALR = int_val;
        if (iter.tryGetIntByKey(&int_val, "SSAET") && int_val >= 0)
            mSSAET = int_val;

        if (iter.tryGetIterByKey(&cei_iter, "CEI")) {
            int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetIterByIndex(&entry_iter, i) &&
                    entry_iter.tryGetUIntByKey(&uint_val, "T")) {
                    const u32 entry_hash = uint_val;

                    int entry_idx;

                    if (sCrc32Constants.crc32_life_recover == entry_hash)
                        entry_idx = 1;
                    else if (sCrc32Constants.crc32_guts_performance == entry_hash)
                        entry_idx = 15;
                    else if (sCrc32Constants.crc32_stamina_recover == entry_hash)
                        entry_idx = 14;
                    else if (sCrc32Constants.crc32_life_max_up == entry_hash)
                        entry_idx = 2;
                    else if (sCrc32Constants.crc32_resist_hot == entry_hash)
                        entry_idx = 4;
                    else if (sCrc32Constants.crc32_resist_cold == entry_hash)
                        entry_idx = 5;
                    else if (sCrc32Constants.crc32_resist_electric == entry_hash)
                        entry_idx = 6;
                    else if (sCrc32Constants.crc32_all_speed == entry_hash)
                        entry_idx = 13;
                    else if (sCrc32Constants.crc32_attack_up == entry_hash)
                        entry_idx = 10;
                    else if (sCrc32Constants.crc32_defense_up == entry_hash)
                        entry_idx = 11;
                    else if (sCrc32Constants.crc32_quietness == entry_hash)
                        entry_idx = 12;
                    else if (sCrc32Constants.crc32_fireproof == entry_hash)
                        entry_idx = 16;
                    else
                        continue;

                    if (entry_iter.tryGetIntByKey(&int_val, "BT"))
                        mCookingEffectEntries[entry_idx].bt = int_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "Ma"))
                        mCookingEffectEntries[entry_idx].ma = int_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "Mi"))
                        mCookingEffectEntries[entry_idx].mi = int_val;

                    if (entry_iter.tryGetFloatByKey(&float_val, "MR"))
                        mCookingEffectEntries[entry_idx].mr = float_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "SSA"))
                        mCookingEffectEntries[entry_idx].ssa = int_val;
                }
            }
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMMR")) {
            int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetFloatByIndex(&float_val, i) && i < NumIngredientsMax) {
                    mNMMR[i] = sead::Mathf::clamp(float_val, 0.0f, 5.0f);
                }
            }
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMSSR")) {
            int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetIntByIndex(&int_val, i) && i < NumIngredientsMax) {
                    mNMSSR[i] = sead::Mathi::clamp(int_val, -100, 100);
                }
            }
        }
    }
}

void CookingMgr::setCookItem(const CookItem& from) {
    from.copy(mCookItem);
}

void CookingMgr::getCookItem(CookItem& to) const {
    mCookItem.copy(to);
}

}  // namespace ksys
