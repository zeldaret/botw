#pragma once

#include "Game/AI/Action/actionFixedMagneStick.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FixedMagneSliderBlock : public FixedMagneStick {
    SEAD_RTTI_OVERRIDE(FixedMagneSliderBlock, FixedMagneStick)
public:
    explicit FixedMagneSliderBlock(const InitArg& arg);
    ~FixedMagneSliderBlock() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
