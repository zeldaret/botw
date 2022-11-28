#pragma once

#include <container/seadTreeMap.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Types.h"
#include "cookItem.h"

namespace ksys {

struct CookArg;
struct CookIngredient;

// TODO: Find actual type
struct UnkItem;

// TODO
class CookingMgr {
    SEAD_SINGLETON_DISPOSER(CookingMgr)
public:
    static constexpr s32 NumIngredientsMax = 5;
    static constexpr s32 NumEffects = 13;
    static constexpr s32 NumEffectSlots = 17;

    struct Ingredient {
        u32 name_hash;
        int _4;
        const CookIngredient* arg;
        bool _10;
        al::ByamlIter actor_data;
    };

    struct BoostArg {
        bool always_boost;
        bool enable_random_boost;
    };

    CookingMgr();
    ~CookingMgr();

    void cookFail(CookItem& item);
    void cookFailForMissingConfig(CookItem& item, const sead::FixedSafeString<64>& name);
    void cookCalcBoost(const Ingredient ingredients[], CookItem& item, const BoostArg& boost_arg);
    void cookHandleBoostSuccessInner(const Ingredient ingredients[], CookItem& item);
    void cookCalc3(const Ingredient ingredients[], CookItem& item);
    void cookCalcItemPrice(const Ingredient ingredients[], CookItem& item);
    void cookCalc1(const Ingredient ingredients[], CookItem& item);

    void init(sead::Heap* heap);

    bool cook(const CookArg& arg, const CookItem& cook_item, const BoostArg& boost_arg);

    bool resetArgCookData(const CookArg& arg, const CookItem& item);

    bool cookWithItems(const CookArg& arg, const UnkItem& item1, const UnkItem& item2,
                       const UnkItem& item3, const UnkItem& item4, const UnkItem& item5,
                       const CookItem& cook_item, const BoostArg& boost_arg);

    void setCookItem(const CookItem& from);

    void getCookItem(CookItem& to) const;

private:
    struct CookingEffectEntry {
        int bt = 0;
        int ma = 0;
        int mi = 0;
        float mr = 1.0f;
        int ssa = 1;
    };

    al::ByamlIter* mConfig = nullptr;

    ksys::res::Handle mResHandle;

    sead::FixedSafeString<64> mFailActorName;
    sead::FixedSafeString<64> mFairyTonicName;
    sead::FixedSafeString<64> mMonsterExtractName;

    u32 mFailActorNameHash = 0;
    u32 mFairyTonicNameHash = 0;
    u32 mMonsterExtractNameHash = 0;

    float mLRMR = 1.0f;
    float mFALRMR = 1.0f;
    u32 mFALR = 4;
    u32 mSFALR = 1;
    u32 mSSAET = 300;

    CookingEffectEntry mCookingEffectEntries[NumEffectSlots];

    sead::SafeArray<float, NumIngredientsMax> mNMMR;

    sead::SafeArray<int, NumIngredientsMax> mNMSSR;

    CookItem mCookItem;

    sead::FixedTreeMap<u32, u32, NumEffects> mCookingEffectNameIdMap{};
};
KSYS_CHECK_SIZE_NX150(CookingMgr, 0x7D8);

struct CookIngredient {
    sead::FixedSafeString<64> name;
    int _58;
};
KSYS_CHECK_SIZE_NX150(CookIngredient, 0x60);

struct CookArg {
    CookIngredient ingredients[CookingMgr::NumIngredientsMax];
};
KSYS_CHECK_SIZE_NX150(CookArg, 0x1E0);

}  // namespace ksys
