#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WeaponDrawn : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(WeaponDrawn, OnetimeStopASPlay)
public:
    explicit WeaponDrawn(const InitArg& arg);
    ~WeaponDrawn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action
