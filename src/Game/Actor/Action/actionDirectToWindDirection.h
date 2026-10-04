#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DirectToWindDirection : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DirectToWindDirection, ksys::act::ai::Action)
public:
    explicit DirectToWindDirection(const InitArg& arg);
    ~DirectToWindDirection() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mRotMax_s{};
    // static_param at offset 0x30
    const sead::Vector3f* mFrontDir_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mUpDir_s{};
};

}  // namespace uking::action
