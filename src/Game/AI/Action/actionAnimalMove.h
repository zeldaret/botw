#pragma once

#include "Game/AI/Action/actionAnimalMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalMove : public AnimalMoveBase {
    SEAD_RTTI_OVERRIDE(AnimalMove, AnimalMoveBase)
public:
    explicit AnimalMove(const InitArg& arg);
    ~AnimalMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const int* mWeaponIdx_s{};
    // static_param at offset 0x78
    const float* mFinRadius_s{};
};

}  // namespace uking::action
