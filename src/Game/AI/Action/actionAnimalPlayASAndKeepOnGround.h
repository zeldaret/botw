#pragma once

#include "Game/AI/Action/actionPlayASForAnimalUnit.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalPlayASAndKeepOnGround : public PlayASForAnimalUnit {
    SEAD_RTTI_OVERRIDE(AnimalPlayASAndKeepOnGround, PlayASForAnimalUnit)
public:
    explicit AnimalPlayASAndKeepOnGround(const InitArg& arg);
    ~AnimalPlayASAndKeepOnGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mDownImpulseScale_s{};
    // static_param at offset 0x68
    const bool* mIsUseDownImpulse_s{};
    // aitree_variable at offset 0x70
    bool* mIsChangeableStateFreeFall_a{};
};

}  // namespace uking::action
