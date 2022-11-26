#include "KingSystem/Cooking/cookManager.h"
#include <codec/seadHashCRC32.h>
#include <typeindex>
#include "KingSystem/Resource/resLoadRequest.h"

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

static const CookingEffect sCookingEffects[13]{
    {"None", -1u},     {"LifeRecover", 1},    {"LifeMaxUp", 2},    {"ResistHot", 4},
    {"ResistCold", 5}, {"ResistElectric", 6}, {"AttackUp", 10},    {"DefenseUp", 11},
    {"Quietness", 12}, {"MovingSpeed", 13},   {"GutsRecover", 14}, {"ExGutsMaxUp", 15},
    {"Fireproof", 16},
};

static const u32 sCrc32_LifeRecover = sead::HashCRC32::calcStringHash("LifeRecover");
static const u32 sCrc32_GutsPerformance = sead::HashCRC32::calcStringHash("GutsPerformance");
static const u32 sCrc32_StaminaRecover = sead::HashCRC32::calcStringHash("StaminaRecover");
static const u32 sCrc32_LifeMaxUp = sead::HashCRC32::calcStringHash("LifeMaxUp");
static const u32 sCrc32_ResistHot = sead::HashCRC32::calcStringHash("ResistHot");
static const u32 sCrc32_ResistCold = sead::HashCRC32::calcStringHash("ResistCold");
static const u32 sCrc32_ResistElectric = sead::HashCRC32::calcStringHash("ResistElectric");
static const u32 sCrc32_AllSpeed = sead::HashCRC32::calcStringHash("AllSpeed");
static const u32 sCrc32_AttackUp = sead::HashCRC32::calcStringHash("AttackUp");
static const u32 sCrc32_DefenseUp = sead::HashCRC32::calcStringHash("DefenseUp");
static const u32 sCrc32_Quietness = sead::HashCRC32::calcStringHash("Quietness");
static const u32 sCrc32_Fireproof = sead::HashCRC32::calcStringHash("Fireproof");

void CookingMgr::init(sead::Heap* heap) {
    res::LoadRequest req;

    req.mRequester = "CookingMgr";
    req._22 = false;

    sead::FixedSafeString<0x80> path;
    path.format("Cooking/CookData.byml");

    auto* res = sead::DynamicCast<sead::DirectResource>(mRes2.load(path, &req));
    if (!res)
        return;

    mConfig = mConfig ? new (mConfig) al::ByamlIter(res->getRawData()) :
                        new (heap) al::ByamlIter(res->getRawData());

    mCookingEffectNameIdMap.clear();

    for (int effect_idx = 0; effect_idx < 13; effect_idx++) {
        auto& effect = sCookingEffects[effect_idx];
        u32 name_hash = sead::HashCRC32::calcStringHash(effect.name);
        mCookingEffectNameIdMap.insert(name_hash, effect.effect_id);
    }

    for (int i = 0; i < 17; i++) {
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
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    if (cei_iter.tryGetIterByIndex(&entry_iter, i) &&
                        entry_iter.tryGetUIntByKey(&uint_val, "T")) {
                        const u32 entry_hash = uint_val;

                        int entry_idx;

                        if (sCrc32_LifeRecover == entry_hash)
                            entry_idx = 1;
                        else if (sCrc32_GutsPerformance == entry_hash)
                            entry_idx = 15;
                        else if (sCrc32_StaminaRecover == entry_hash)
                            entry_idx = 14;
                        else if (sCrc32_LifeMaxUp == entry_hash)
                            entry_idx = 2;
                        else if (sCrc32_ResistHot == entry_hash)
                            entry_idx = 4;
                        else if (sCrc32_ResistCold == entry_hash)
                            entry_idx = 5;
                        else if (sCrc32_ResistElectric == entry_hash)
                            entry_idx = 6;
                        else if (sCrc32_AllSpeed == entry_hash)
                            entry_idx = 13;
                        else if (sCrc32_AttackUp == entry_hash)
                            entry_idx = 10;
                        else if (sCrc32_DefenseUp == entry_hash)
                            entry_idx = 11;
                        else if (sCrc32_Quietness == entry_hash)
                            entry_idx = 12;
                        else if (sCrc32_Fireproof == entry_hash)
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
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMMR")) {
            int size = cei_iter.getSize();
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    bool success = cei_iter.tryGetFloatByIndex(&float_val, i);
                    if (i < 5 && success) {
                        int idx = (u64)i < 5ULL ? i : 0;
                        mNMMR[idx] = sead::Mathf::clamp(float_val, 0.0f, 5.0f);
                    }
                }
            }
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMSSR")) {
            int size = cei_iter.getSize();
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    bool success = cei_iter.tryGetIntByIndex(&int_val, i);
                    if (i < 5 && success) {
                        int idx = (u64)i < 5ULL ? i : 0;
                        mNMSSR[idx] = sead::Mathi::clamp(int_val, -100, 100);
                    }
                }
            }
        }
    }
}

void CookingMgr::getCookItem(CookItem& to) {
    return to.copy(mCookItem);
}

}  // namespace ksys
