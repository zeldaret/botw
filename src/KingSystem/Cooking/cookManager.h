#pragma once

#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"
#include "cookItem.h"

namespace al {

class ByamlIter;

}

namespace ksys {

struct CookArg;
struct CookIngredient;

// TODO: Find actual type
struct UnkItem;

// TODO
class CookingMgr {
    SEAD_SINGLETON_DISPOSER(CookingMgr)
public:
    CookingMgr();
    ~CookingMgr();

    struct BoostArg;
    struct Ingredient;

    void cookFail(CookItem& item);
    void cookFailForMissingConfig(CookItem& item, const sead::FixedSafeString<64>& name);
    void cookCalcBoost(const Ingredient ingredients[], CookItem& item, const BoostArg& boost_arg);
    void cookHandleBoostSuccessInner(const Ingredient ingredients[], CookItem& item);
    void cookCalc3(const Ingredient ingredients[], CookItem& item);
    void cookCalcItemPrice(const Ingredient ingredients[], CookItem& item);
    void cookCalc1(const Ingredient ingredients[], CookItem& item);

    void init(sead::Heap* heap);

    bool cook(const CookArg& arg, const CookItem& cookItem, const BoostArg& boostArg);

    bool resetArgCookData(const CookArg& arg, const CookItem& item);

    bool cookWithItems(const CookArg& arg, const UnkItem& item1, const UnkItem& item2,
                       const UnkItem& item3, const UnkItem& item4, const UnkItem& item5,
                       const CookItem& cook_item, const BoostArg& boost_arg);

    void getCookItem(CookItem& to);

    void x(CookItem& to);

private:
    al::ByamlIter* mConfig = nullptr;

    ksys::res::Handle mRes2;

    sead::FixedSafeString<64> mFailActor;
    sead::FixedSafeString<64> mFairyTonicName;
    sead::FixedSafeString<64> mMonsterExtractName;

    int _180 = 0;

    int mFairyTonicNameHash = 0;
    u32 mMonsterExtractNameHash = 0;

    float _18C = 1.0f;
    float _190 = 1.0f;
    u32 _194 = 4;
    u32 _198 = 1;
    u32 _19C = 300;
    u64 _1A0 = 0;
    u32 _1A8 = 0;
    float _1AC = 1.0f;
    u64 _1B0 = 1;
    float _1B8 = 0.0f;
    int _1BC = 0;
    float _1C0 = 1.0f;

    u32 _1C4 = 1;
    u64 _1C8 = 0;
    u32 _1D0 = 0;
    float _1D4 = 1.0f;
    u64 _1D8 = 1;
    u64 _1E0 = 0;
    float _1E8 = 1.0f;

    u32 _1EC = 1;
    u64 _1F0 = 0;
    u32 _1F8 = 0;
    float _1FC = 1.0f;
    u64 _200 = 1;
    u64 _208 = 0;
    float _210 = 1.0f;

    u32 _214 = 1;
    u64 _218 = 0;
    u32 _220 = 0;
    float _224 = 1.0f;
    u64 _228 = 1;
    u64 _230 = 0;
    float _238 = 1.0f;

    u32 _23C = 1;
    u64 _240 = 0;
    u32 _248 = 0;
    float _24C = 1.0f;
    u64 _250 = 1;
    u64 _258 = 0;
    float _260 = 1.0f;

    u32 _264 = 1;
    u64 _268 = 0;
    u32 _270 = 0;
    float _274 = 1.0f;
    u64 _278 = 1;
    u64 _280 = 0;
    float _288 = 1.0f;

    u32 _28C = 1;
    u64 _290 = 0;
    u32 _298 = 0;
    float _29C = 1.0f;
    u64 _2A0 = 1;
    u64 _2A8 = 0;
    float _2B0 = 1.0f;

    u32 _2B4 = 1;
    u64 _2B8 = 0;
    u32 _2C0 = 0;
    float _2C4 = 1.0f;
    u64 _2C8 = 1;
    u64 _2D0 = 0;
    float _2D8 = 1.0f;

    __attribute__((packed)) __attribute__((aligned(1))) u64 _2DC = 1;
    __attribute__((packed)) __attribute__((aligned(1))) u64 _2E4 = 0;

    int _2EC = 1;

    float _2F0 = 1.0f;

    float _2F4[5];

    int _308[1];

    int _30C;
    int _310;
    int _314;
    int _318;
    int _31C;

    CookItem mCookItem;

    sead::FixedObjArray<s64[5], 13> _548{};
};
KSYS_CHECK_SIZE_NX150(CookingMgr, 0x7D8);

}  // namespace ksys
