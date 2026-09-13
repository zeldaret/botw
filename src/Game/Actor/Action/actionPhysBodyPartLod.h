#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PhysBodyPartLod : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PhysBodyPartLod, ksys::act::ai::Action)
public:
    explicit PhysBodyPartLod(const InitArg& arg);
    ~PhysBodyPartLod() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mLodType_s{};
    // static_param at offset 0x28
    const float* mRemoveDistance_s{};
    // static_param at offset 0x30
    const float* mRemoveDistanceOffset_s{};
};

}  // namespace uking::action
