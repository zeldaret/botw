#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNeckRotateDynPosBasic : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkNeckRotateDynPosBasic, ksys::act::ai::Action)
public:
    explicit ForkNeckRotateDynPosBasic(const InitArg& arg);
    ~ForkNeckRotateDynPosBasic() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mUseSimpleOffset_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
