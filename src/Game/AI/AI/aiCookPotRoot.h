#pragma once

#include "Game/Cooking/cookManager.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class CookPotRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CookPotRoot, ksys::act::ai::Ai)
public:
    explicit CookPotRoot(const InitArg& arg);
    ~CookPotRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // map_unit_param at offset 0x38
    const bool* mInitBurnState_m{};
    // aitree_variable at offset 0x40
    void* mCurrentCookResultHolder_a{};
    bool _48;
    bool mHasFinishedCookItem;
    u8 _4A[6];
    CookArg mCookArg;
    sead::Buffer<sead::FixedSafeString<64>> mCookIngredients;
    u8 _240;
    u8 _241;
    u8 _242[6];
    // vtable
    void* _248;
    s64 _250;
    s32 _258;
    u8 _25C[4];
    u8 _260[8];
    u32 _268;
    ksys::act::BaseProcLink mProcLink;
    s32 _280;
    // vtable
    void* _288;
    CookItem mCookItem;
};
KSYS_CHECK_SIZE_NX150(CookPotRoot, 0x4B8);

}  // namespace uking::ai
