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
    int effect_id;
};

static CookingEffect sCookingEffects[13]{
    CookingEffect{"None", -1},         CookingEffect{"LifeRecover", 1},
    CookingEffect{"LifeMaxUp", 2},     CookingEffect{"ResistHot", 4},
    CookingEffect{"ResistCold", 5},    CookingEffect{"ResistElectric", 6},
    CookingEffect{"AttackUp", 0xA},    CookingEffect{"DefenseUp", 0xB},
    CookingEffect{"Quietness", 0xC},   CookingEffect{"MovingSpeed", 0xD},
    CookingEffect{"GutsRecover", 0xE}, CookingEffect{"ExGutsMaxUp", 0xF},
    CookingEffect{"Fireproof", 0x10},
};

static u32 crc32_None = sead::HashCRC32::calcStringHash("None");
static u32 crc32_LifeRecover = sead::HashCRC32::calcStringHash("LifeRecover");
static u32 crc32_LifeMaxUp = sead::HashCRC32::calcStringHash("LifeMaxUp");
static u32 crc32_ResistHot = sead::HashCRC32::calcStringHash("ResistHot");
static u32 crc32_ResistCold = sead::HashCRC32::calcStringHash("ResistCold");
static u32 crc32_ResistElectric = sead::HashCRC32::calcStringHash("ResistElectric");
static u32 crc32_AttackUp = sead::HashCRC32::calcStringHash("AttackUp");
static u32 crc32_DefenseUp = sead::HashCRC32::calcStringHash("DefenseUp");
static u32 crc32_Quietness = sead::HashCRC32::calcStringHash("Quietness");
static u32 crc32_MovingSpeed = sead::HashCRC32::calcStringHash("MovingSpeed");
static u32 crc32_GutsRecover = sead::HashCRC32::calcStringHash("GutsRecover");
static u32 crc32_ExGutsMaxUp = sead::HashCRC32::calcStringHash("ExGutsMaxUp");
static u32 crc32_Fireproof = sead::HashCRC32::calcStringHash("Fireproof");

void CookingMgr::init(sead::Heap* heap) {
    res::LoadRequest req;
    char buffer[0x80];
    sead::BufferedSafeString path(buffer, sizeof(buffer));

    req.mRequester = "CookingMgr";

    mRes2.load("Cooking/CookData.byml", &req);
    auto* res = sead::DynamicCast<sead::DirectResource>(mRes2.getResource());
    if (!res)
        return;

    mConfig = mConfig ? new (mConfig) al::ByamlIter(res->getRawData()) :
                        new (heap) al::ByamlIter(res->getRawData());

    _548.clear();

    for (int effect_idx = 0; effect_idx < 13; effect_idx++) {
        auto& effect = sCookingEffects[effect_idx];
        _548.insert(effect_idx, effect.effect_id);
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

    mNMSSR[0] = 5;
    mNMSSR[1] = 0;
    mNMSSR[2] = 15;
    mNMSSR[3] = 10;
    mNMSSR[4] = 20;

    mFairyTonicName = "Item_Cook_C_16";
    mFairyTonicNameHash = sead::HashCRC32::calcStringHash(mFairyTonicName);

    mFailActorName = "Item_Cook_O_01";
    mFailActorNameHash = sead::HashCRC32::calcStringHash(mFailActorName);

    mMonsterExtractName = "Item_Material_08";
    mMonsterExtractNameHash = sead::HashCRC32::calcStringHash(mMonsterExtractName);

    mLRMR = 1.0;
    mSSAET = 300;
    mSFALR = 1;
    mFALRMR = 1.0;
    mFALR = 4;

    al::ByamlIter iter;
    al::ByamlIter cei_iter;
    al::ByamlIter entry_iter;

    int int_val;
    float float_val;
    const char* string_val = nullptr;

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
                    u32 entry_hash;
                    if (cei_iter.tryGetIterByIndex(&entry_iter, i) &&
                        entry_iter.tryGetUIntByKey(&entry_hash, "T")) {
                        int entry_idx;

                        if (entry_hash == crc32_None)
                            entry_idx = 0;
                        else if (entry_hash == crc32_LifeRecover)
                            entry_idx = 1;
                        else if (entry_hash == crc32_LifeMaxUp)
                            entry_idx = 2;
                        else if (entry_hash == crc32_ResistHot)
                            entry_idx = 3;
                        else if (entry_hash == crc32_ResistCold)
                            entry_idx = 4;
                        else if (entry_hash == crc32_ResistElectric)
                            entry_idx = 5;
                        else if (entry_hash == crc32_AttackUp)
                            entry_idx = 6;
                        else if (entry_hash == crc32_DefenseUp)
                            entry_idx = 7;
                        else if (entry_hash == crc32_Quietness)
                            entry_idx = 8;
                        else if (entry_hash == crc32_MovingSpeed)
                            entry_idx = 9;
                        else if (entry_hash == crc32_GutsRecover)
                            entry_idx = 10;
                        else if (entry_hash == crc32_ExGutsMaxUp)
                            entry_idx = 11;
                        else if (entry_hash == crc32_Fireproof)
                            entry_idx = 12;
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
                        int idx = i >= 5ULL ? 0 : i;
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
                        int idx = i >= 5ULL ? 0 : i;
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
