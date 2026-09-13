#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainElectricCannonRootBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonRootBase, ksys::act::ai::Ai)
public:
    explicit RemainElectricCannonRootBase(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSearchMaxDist_s{};
    // static_param at offset 0x40
    const float* mSearchMinDist_s{};
    // static_param at offset 0x48
    const float* mSearchDistMargin_s{};
};

}  // namespace uking::ai
