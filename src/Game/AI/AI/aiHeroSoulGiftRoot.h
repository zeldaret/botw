#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HeroSoulGiftRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HeroSoulGiftRoot, ksys::act::ai::Ai)
public:
    explicit HeroSoulGiftRoot(const InitArg& arg);
    ~HeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mUseInitMtxForBasePos_s{};
    // static_param at offset 0x40
    const bool* mUseInitMtxForBaseRot_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mPosOffset_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mRotOffset_s{};
};

}  // namespace uking::ai
