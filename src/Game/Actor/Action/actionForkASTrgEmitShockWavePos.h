#pragma once

#include "Game/Actor/Action/actionForkEmitShockWave.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgEmitShockWavePos : public ForkEmitShockWave {
    SEAD_RTTI_OVERRIDE(ForkASTrgEmitShockWavePos, ForkEmitShockWave)
public:
    explicit ForkASTrgEmitShockWavePos(const InitArg& arg);
    ~ForkASTrgEmitShockWavePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb8
    const sead::Vector3f* mOffsetPos_s{};
};

}  // namespace uking::action
