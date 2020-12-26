#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundOcclusionTagRemainsWater : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SoundOcclusionTagRemainsWater, ksys::act::ai::Action)
public:
    explicit SoundOcclusionTagRemainsWater(const InitArg& arg);
    ~SoundOcclusionTagRemainsWater() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
