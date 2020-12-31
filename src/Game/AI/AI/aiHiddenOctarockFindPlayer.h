#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HiddenOctarockFindPlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HiddenOctarockFindPlayer, ksys::act::ai::Ai)
public:
    explicit HiddenOctarockFindPlayer(const InitArg& arg);
    ~HiddenOctarockFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mLostTimer_s{};
    // static_param at offset 0x48
    const float* mFarDist_s{};
    // static_param at offset 0x50
    const float* mActorRadius_s{};
    // static_param at offset 0x58
    const float* mLostDistOffset_s{};
    // static_param at offset 0x60
    const float* mNoticeDelayTime_s{};
};

}  // namespace uking::ai
